
/*
TIMER�n�̊��N���X
 H28 05 18 ver0.0.0
 H28 05 20 ver0.1.0 Flag_timer�̒��g������������
 H28 05 20 ver0.2.0 �R���X�g���N�^��t�����B���荞�݂���{OFF�ɂ���
 H28 05 20 ver1.0.0 ���ۂ̓���n�̊֐�������āA�ݒ�p�̕ϐ��Ɗ֐���ǉ������B
 H28 05 20 ver1.0.1 _mam_timer_base_nf_isr���s�v�������̂ō폜�����B
*/


#pragma once

#include "H28_t_class.h"

/*************************************************************************

�@TIMER�n�N���X�̊��N���X�B
�@�Ȃ�ł���Ȃ��̂����邩�Ƃ����ƁA�ŏ��͂����Ɣh���悪����\�肾�����̂�
�����AC_TIMER�����ł����񂶂�ˁA�ƂȂ�������ł��B

*************************************************************************/

class C_TIMER_base
{
	
protected:
	
	E_TIMER_MODE	_mem_timer_base_mode :4;
	usint			_mem_timer_base_counter :16;
	E_CLOCK			_mem_timer_base_clock :3;
	
#if defined(_AVR_IOM640_H_) /********************************************/

	E_TIMER_ADDR	_mem_timer_base_addr :9;
	T_NUM			_mem_timer_base_addr_plus :3;
	
#	define __TCCRA__	_SFR_MEM8(_mem_timer_base_addr + 0)
#	define __TCCRB__	_SFR_MEM8(_mem_timer_base_addr + 1)
#	define __TCCRC__	_SFR_MEM8(_mem_timer_base_addr + 2)
#	define __TCNTL__	_SFR_MEM8(_mem_timer_base_addr + ET_OVERFLOW + 0)
#	define __TCNTH__	_SFR_MEM8(_mem_timer_base_addr + ET_OVERFLOW + 1)
#	define __OCRL__		_SFR_MEM8(_mem_timer_base_addr + ET_COMPARE + 0)
#	define __OCRH__		_SFR_MEM8(_mem_timer_base_addr + ET_COMPARE + 1)
#	define __ICRL__		_SFR_MEM8(_mem_timer_base_addr + ET_CAPUTER + 0)
#	define __ICRH__		_SFR_MEM8(_mem_timer_base_addr + ET_CAPUTER + 1)
#	define __COUNTERL__	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 0)
#	define __COUNTERH__	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 1)
#	define __TIMSK__	_SFR_MEM8(_mem_timer_base_addr_plus + 0x6e)
#	define __TIFR__		_SFR_MEM8(_mem_timer_base_addr_plus + 0x35)
	
#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_) /****************/
	
	
#	define __TCCRA__	TCCR1A
#	define __TCCRB__	TCCR1B
#	define __TCCRC__	TCCR1C
#	define __TIMSK__	TIMSK1
#	define __TIFR__		TIFR1
#	define __TCNTL__	TCNT1L
#	define __TCNTH__	TCNT1H
#	define __OCRL__		OCR1AL	
#	define __OCRH__		OCR1AH
#	define __ICRL__		ICR1L
#	define __ICRH__		ICR1H
#	define __COUNTERL__	_SFR_MEM8(0x080 + _mem_timer_base_mode)
#	define __COUNTERH__	_SFR_MEM8(0x081 + _mem_timer_base_mode)
	
#endif /*****************************************************************/
	
#	define TIME_SET_BIT 0x07 //((1 << CS2) | (1 << CS1) | (1 << CS0))
	
#if defined(_AVR_IOM640_H_)	/********************************************/

	/**
	 * \brief ���W�X�^�̏����ݒ���s��
	 * 
	 * \param _arg_timer_addr : �g��TIMER
	 * \param _arg_timer_mode : TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_timer (E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_) /****************/

	/**
	 * \brief ���W�X�^�̏����ݒ���s��
	 *
	 * \param _arg_timer_mode	: TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_timer (E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
#endif /*****************************************************************/

	/**
	 * \brief TIMER�̃��[�h�A���荞�݂ɂ��Ă̐ݒ���s��
	 * 
	 * \param _arg_timer_mode	: �ݒ肷��TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_mode(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
public:
	
	/**
	 * \brief �����l�A�J�E���g�p���W�X�^�̐ݒ�
	 * 
	 * \param _arg_timer_clock	 : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 */
	void Set_condition(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
};

/************************************************************************/
//protected

#if defined(_AVR_IOM640_H_) /********************************************/

inline void
C_TIMER_base ::
Set_timer
(
	E_TIMER_ADDR	_arg_timer_addr,
	E_TIMER_MODE	_arg_timer_mode ,
	BOOL			_arg_timer_nf_isr = FALSE
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

#elif defined(_AVR_IOM164_H_) /******************************************/

inline void
C_TIMER_base ::
Set_timer
(
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	__TCCRA__ = 0x00;
	
	Set_mode(_arg_timer_mode, _arg_timer_nf_isr);
	
	__TCCRC__ = 0x00;
}

#endif /*****************************************************************/

void
C_TIMER_base ::
Set_mode
(
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	_mem_timer_base_mode = _arg_timer_mode;
	
	switch (_arg_timer_mode)
	{
		case ET_CAPUTER:	//��r
		{
			__TCCRB__ = ((1<<WGM3) | (1<<WGM2));
			__TIMSK__ = (_arg_timer_nf_isr << ICIE);
			break;
		}
		case ET_COMPARE:	//�ߊl
		{
			__TCCRB__ = (1<<WGM2);
			__TIMSK__ = (_arg_timer_nf_isr << OCIEA);
			break;
		}
		case ET_OVERFLOW:	//���
		{
			__TCCRB__ = 0x00;
			__TIMSK__ = (_arg_timer_nf_isr << TOIE);
			break;
		}
	}
}

/************************************************************************/
//public

inline void
C_TIMER_base ::
Set_condition
(
	E_CLOCK _arg_timer_clock,
	usint	_arg_timer_counter
)
{
	_mem_timer_base_clock = _arg_timer_clock;
	_mem_timer_base_counter = _arg_timer_counter;
}
