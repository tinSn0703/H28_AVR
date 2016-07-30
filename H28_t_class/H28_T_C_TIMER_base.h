
#pragma once

#include "H28_t_class.h"

/**
 * TIMER�n�N���X�̊��N���X
 */
class C_TIMER_base
{
protected:
	
	E_TIMER_MODE	_mem_timer_base_mode :4;
	usint			_mem_timer_base_counter :16;
	E_CLOCK			_mem_timer_base_clock :3;
	
#if defined(_AVR_IOM640_H_)
	E_TIMER_ADDR	_mem_timer_base_addr :9;
	T_NUM			_mem_timer_base_addr_plus :3;

#	define TCCRA	_SFR_MEM8(_mem_timer_base_addr + 0)
#	define TCCRB	_SFR_MEM8(_mem_timer_base_addr + 1)
#	define TCCRC	_SFR_MEM8(_mem_timer_base_addr + 2)
#	define TIMSK	_SFR_MEM8(_mem_timer_base_addr_plus + 0x6e)
#	define TIFR		_SFR_MEM8(_mem_timer_base_addr_plus + 0x35)
#	define COUNTERL	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 0)
#	define COUNTERH	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 1)
#elif defined(_AVR_IOM164_H_)
#	define TCCRA	TCCR1A
#	define TCCRB	TCCR1B
#	define TCCRC	TCCR1C
#	define TIMSK	TIMSK1
#	define TIFR		TIFR1
#	define COUNTERL	_SFR_MEM8(0x080 + _mem_timer_base_mode)
#	define COUNTERH	_SFR_MEM8(0x081 + _mem_timer_base_mode)
#endif
	

#if defined(_AVR_IOM640_H_)
	
	/**
	 * \brief ���W�X�^�̏����ݒ���s��
	 * 
	 * \param _arg_timer_addr : �g��TIMER
	 * \param _arg_timer_mode : TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_base (E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
#elif defined(_AVR_IOM164_H_)
	
	/**
	 * \brief ���W�X�^�̏����ݒ���s��
	 *
	 * \param _arg_timer_mode : TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_base (E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
#endif

	/**
	 * \brief TIMER�̃��[�h�A���荞�݂ɂ��Ă̐ݒ���s��
	 * 
	 * \param _arg_timer_mode : �ݒ肷��TIMER�̃��[�h
	 * \param _arg_timer_nf_isr : ���荞�ݏ�����p���邩�ǂ���
	 */
	void Set_mode(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
public:
	
	/**
	 * \brief �����l�A�J�E���g�p���W�X�^�̐ݒ�
	 * 
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 */
	void Set_condition(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
};