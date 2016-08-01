
/*
AD変換を行うクラス。ポテンジョンメータの値を読むことができる。
 H28 05 10 ver0.0.0
 H28 05 21 ver0.0.1   IOポートの設定を前の逆にした
 H28 05 21 ver0.0.2   メンバ変数の名前の変更
 H28 05 21 ver1.0.0   ADMUXのリセットがうまくいっておらず、複数個用いる場合のAD変換の値が共有されてしまうバグを解消した。
					あと割り込み処理を設定できないようにした。
 H28 05 22 ver2.0.0   メンバ変数をカプセル化した。
*/

#pragma once

#include "H28_I_C_AD.h"

//public member

C_AD::
C_AD
(
	E_AD_NUM _arg_ad_num, 
	BOOL _arg_ad_io_turn = TRUE
)
{	
	static BOOL _sta_ad_flag_first = FALES;
	
	if (_sta_ad_flag_first == FALES)
	{
		ADMUX  = (1<<REFS0);
		ADCSRA = ((1 << ADEN) | (1 << ADPS1) | (1 << ADPS0));
		ADCSRB = 0;
		DIDR0  = 0;
		
#ifdef _AVR_IOM640_H_
		DIDR2  = 0;
#endif
		
		_sta_ad_flag_first = TRUE;
	}

	_mem_ad._mux_admux = _arg_ad_num;
	
#if defined(_AVR_IOM640_H_)
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRF  &= ~(TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			PORTF |=  (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			
			DDRK  &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			PORTK |=  (_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			
			break;
		}
		case FALES:
		{
			DDRF  |=  (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			PORTF &= ~(TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			
			DDRK  |=  (_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			PORTK &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			
			break;
		}
	}

	DIDR0 |= (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
	DIDR2 |= (_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
#elif defined(_AVR_IOM164_H_)
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRA  &= ~(1 << _mem_ad._ad_num);
			PORTA |=  (1 << _mem_ad._ad_num);
			
			break;
		}
		case FALES:
		{
			DDRA  |=  (1 << _mem_ad._ad_num);
			PORTA &= ~(1 << _mem_ad._ad_num);
			
			break;
		}
	}

	DIDR0 |= (1 << _mem_ad._ad_num);
#endif
}

inline usint 
C_AD::
Do ()
{	
	ADMUX += _mem_ad._mux_admux;
#ifdef _AVR_IOM640_H_
	ADCSRB = (_mem_ad._mux_bit._mux5 << MUX5);
#endif	
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1<<ADSC));
	
	usint _ret_data_in = ADCL;
	_ret_data_in |= (ADCH << 8);
	
	ADMUX  = (1<<REFS0);
	ADCSRB = 0;
	
	return _ret_data_in;
}