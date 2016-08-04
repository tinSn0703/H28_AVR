
/*
TIMER系の基底クラス
 H28 05 18 ver0.0.0
 H28 05 20 ver0.1.0 Flag_timerの中身を書き換えた
 H28 05 20 ver0.2.0 コンストラクタを付けた。割り込みを基本OFFにした
 H28 05 20 ver1.0.0 実際の動作系の関数を削って、設定用の変数と関数を追加した。
 H28 05 20 ver1.0.1 _mam_timer_base_nf_isrが不要だったので削除した。
*/

#pragma once

#include "H28_T_C_TIMER_base.h"

//protected member

#if defined(_AVR_IOM640_H_)
inline void 
C_TIMER_base ::
Set_base
(
	E_TIMER_ADDR _arg_timer_addr,
	E_TIMER_MODE _arg_timer_mode , 
	BOOL _arg_timer_nf_isr = FALSE
)
{
	_mem_timer_base_clock = EC_0;
	_mem_timer_base_counter = 0;
	
	_mem_timer_base_addr = _arg_timer_addr;
	
	switch (_arg_timer_addr)
	{
		case ET_TIMER1:	_mem_timer_base_addr_plus = 1;	break;
		case ET_TIMER3:	_mem_timer_base_addr_plus = 3;	break;
		case ET_TIMER4:	_mem_timer_base_addr_plus = 4;	break;
		case ET_TIMER5:	_mem_timer_base_addr_plus = 5;	break;
	}

	__TCCRA__ = 0x00;
	
	Set_mode(_arg_timer_mode, _arg_timer_nf_isr);
	
	__TCCRC__ = 0x00;
}
#elif defined(_AVR_IOM164_H_)
inline void
C_TIMER_base ::
Set_base
(
	E_TIMER_MODE _arg_timer_mode ,
	BOOL _arg_timer_nf_isr = FALSE
)
{
	__TCCRA__ = 0x00;
	
	Set_mode(_arg_timer_mode, _arg_timer_nf_isr);
	
	__TCCRC__ = 0x00;
}
#endif


void 
C_TIMER_base ::
Set_mode
(
	E_TIMER_MODE _arg_timer_mode, 
	BOOL _arg_timer_nf_isr = FALSE
)
{
	_mem_timer_base_mode = _arg_timer_mode;
	
	switch (_arg_timer_mode)
	{
		case ET_CAPUTER:	//比較
		{
			__TCCRB__ = ((1<<WGM3) | (1<<WGM2));
			__TIMSK__ = (_arg_timer_nf_isr << ICIE);
			break;
		}
		case ET_COMPARE:	//捕獲
		{
			__TCCRB__ = (1<<WGM2);
			__TIMSK__ = (_arg_timer_nf_isr << OCIEA);
			break;
		}
		case ET_OVERFLOW:	//溢れ
		{
			__TCCRB__ = 0x00;
			__TIMSK__ = (_arg_timer_nf_isr << TOIE);
			break;
		}
	}
}

//public member

inline void 
C_TIMER_base ::
Set_condition
(
	E_CLOCK _arg_timer_clock, 
	usint _arg_timer_counter
)
{
	_mem_timer_base_clock = _arg_timer_clock;
	_mem_timer_base_counter = _arg_timer_counter;
}