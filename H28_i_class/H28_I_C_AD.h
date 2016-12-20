
/*
AD�ϊ����s���N���X�B�|�e���W�������[�^�̒l��ǂނ��Ƃ��ł���B
 H28 05 10 ver0.0.0
 H28 05 21 ver0.0.1   IO�|�[�g�̐ݒ��O�̋t�ɂ���
 H28 05 21 ver0.0.2   �����o�ϐ��̖��O�̕ύX
 H28 05 21 ver1.0.0   ADMUX�̃��Z�b�g�����܂������Ă��炸�A�����p����ꍇ��AD�ϊ��̒l�����L����Ă��܂��o�O�����������B
					���Ɗ��荞�ݏ�����ݒ�ł��Ȃ��悤�ɂ����B
 H28 05 22 ver2.0.0   �����o�ϐ����J�v�Z���������B
*/

#pragma once

#include "H28_i_class.h"

/**
 * AD�ϊ��������N���X
 */
class C_AD
{
protected:
	
	union U_AD_MUX
	{
		struct S_AD_MUX
		{
			BOOL _mux0 :1;
			BOOL _mux1 :1;
			BOOL _mux2 :1;
			BOOL _mux3 :1;
			BOOL _mux4 :1;
			
#ifdef _AVR_IOM640_H_
			BOOL _mux5 :1;
#endif
			
		};
		
		S_AD_MUX _mux_bit;
		usint _ad_num :5;
		
#if defined(_AVR_IOM640_H_)
		E_AD_NUM _mux_admux :6;
#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_)
		E_AD_NUM _mux_admux :5;
#endif

	};
	
	U_AD_MUX _mem_ad;
	
public:

	C_AD()	{}
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_ad_num		: �g���ԍ�
	 * \param _arg_ad_io_turn	: IO�s���̐ݒ�B���܂������Ȃ��Ƃ��ɕς����肵��
	 *		TRUE  -> OUT
	 *		FALES -> IN
	 */
	C_AD(E_AD_NUM _arg_ad_num, BOOL _arg_ad_io_turn);

	/**
	 * \brief AD�ϊ������s����
	 * 
	 * \return usint : ���s���ʂ̃f�[�^�B10bit��0~1023�܂�
	 */
	usint Do();
};

/************************************************************************/
//public

C_AD ::
C_AD
(
	const E_AD_NUM	_arg_ad_num,
	const BOOL		_arg_ad_io_turn = TRUE
)
{
	static BOOL _sta_ad_flag_first = FALSE;
	
	if (_sta_ad_flag_first == FALSE)
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
			DDRF  &= ~(F_Turn_bool(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			PORTF |=  (F_Turn_bool(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			
			DDRK  &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			PORTK |=  (_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			
			break;
		}
		case FALSE:
		{
			DDRF  |=  (F_Turn_bool(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			PORTF &= ~(F_Turn_bool(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
			
			DDRK  |=  (_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			PORTK &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._ad_num);
			
			break;
		}
	}

	DIDR0 |= (F_Turn_bool(_mem_ad._mux_bit._mux5) << _mem_ad._ad_num);
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
		case FALSE:
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
C_AD ::
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