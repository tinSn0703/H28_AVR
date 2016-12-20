
/*
�J�E���g���x�͂ł���B�@�\�I�ɂ�StopWatch�̂悤�Ȃ���
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_base�̃R���X�g���N�^�ŃR���X�g���N�^�̐ݒ�����邱�Ƃɂ���.
 H28 05 20 ver 1.0.0 C_TOMER_base�ɐݒ�p�̊֐��ƕϐ����ڂ��A����n�̊֐��̒��g�������Ă���
*/

#pragma once

#include "H28_T_C_TIMER_base.h"

/*************************************************************************

TIMER�𑀍삷�邽�߂̃N���X

*************************************************************************/

class C_TIMER : public virtual C_TIMER_base
{	
public:

	C_TIMER()	{}
	
#if defined(_AVR_IOM640_H_) /********************************************/

	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_addr : �g��TIMER�̔ԍ�
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_addr : �g��TIMER�̔ԍ�
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
	
#elif defined(_AVR_IOM164_H_) /******************************************/

	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
	
#endif /*****************************************************************/

	/**
	 * \brief �^�C�}���E���^���J�n����
	 */
	void Start();
	
	/**
	 * \brief �����̒l��p���ă^�C�}�J�E���^���J�n����
	 * 
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 */
	void Start(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
	
	/**
	 * \brief �^�C�}�J�E���^�̊������m�F����
	 * 
	 * \param _arg_timer_continue : �������Ƀ^�C�}�J�E���^���ēx�s����
	 * 
	 * \return BOOL
	 *	TRUE  -> ����
	 *	FALES -> ����
	 */
	BOOL Flag_timer(BOOL _arg_timer_continue);
	
	/**
	 * \brief �^�C�}�J�E���^�̊������m�F����
	 * 
	 * \param _arg_timer_continue : �������Ƀ^�C�}�J�E���^���ēx�s����
	 * 
	 * \return BOOL
	 *	TRUE  -> ����
	 *	FALES -> ����
	 */
	BOOL Flag_timer_overflow(BOOL _arg_timer_continue);
	
	/**
	 * \brief �^�C�}�J�E���^�̊������m�F����
	 * 
	 * \param _arg_timer_continue : �������Ƀ^�C�}�J�E���^���ēx�s����
	 * 
	 * \return BOOL
	 *	TRUE  -> ����
	 *	FALES -> ����
	 */
	BOOL Flag_timer_compare(BOOL _arg_timer_continue);
	
	/**
	 * \brief �^�C�}�J�E���^���I������
	 */
	void Stop();
	
	/**
	 * \brief TCNT�̒l��Ԃ��B
	 * 
	 * \return usint : TCNT�̒l�B10bit
	 */
	usint Ret_time()	{	return ((__TCNTH__ << 8) | __TCNTL__);	}
	
	/**
	 * \brief �����l�̐ݒ��Ԃ�
	 * 
	 * \return E_CLOCK return
	 */
	E_CLOCK Ret_clock()	{	return _mem_timer_base_clock;	}
};

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) /********************************************/

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_ADDR	_arg_timer_addr,
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
}

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_ADDR	_arg_timer_addr,
	E_TIMER_MODE	_arg_timer_mode,
	E_CLOCK			_arg_timer_clock,
	usint			_arg_timer_counter,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base :: Set_condition(_arg_timer_clock, _arg_timer_counter);
}

#elif defined(_AVR_IOM164_H_) /******************************************/

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_mode, _arg_timer_nf_isr);
}

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_MODE	_arg_timer_mode,
	E_CLOCK			_arg_timer_clock,
	usint			_arg_timer_counter,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base :: Set_condition(_arg_timer_clock, _arg_timer_counter);
}

#endif /*****************************************************************/

inline void
C_TIMER ::
Start ()
{
	Stop();
	
	__COUNTERH__ = (_mem_timer_base_counter >> 8);
	__COUNTERL__ = _mem_timer_base_counter;
	
	__TCCRB__ |= _mem_timer_base_clock;
}

inline void
C_TIMER ::
Start
(
	E_CLOCK _arg_timer_clock,
	usint	_arg_timer_counter
)
{
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
	
	Start();
}

inline BOOL
C_TIMER ::
Flag_timer_overflow (BOOL _arg_timer_continue = TRUE)
{
	if (__TIFR__ & (1 << TOV))
	{
		__COUNTERH__ = (_mem_timer_base_counter >> 8);
		__COUNTERL__ = _mem_timer_base_counter;
		
		if (_arg_timer_continue == FALSE)
		{
			Stop();
		}
		
		__TIFR__ |= (1 << TOV);
		
		return TRUE;
	}
	
	return FALSE;
}

inline BOOL
C_TIMER ::
Flag_timer_compare (BOOL _arg_timer_continue = TRUE)
{
	if (F_Check_bit_bool(__TIFR__, OCFA))
	{
		__TIFR__ |= (1 << OCFA);
		
		if (_arg_timer_continue == FALSE)
		{
			Stop();
		}
		
		return TRUE;
	}
	
	return FALSE;
}

inline BOOL
C_TIMER ::
Flag_timer (BOOL _arg_timer_continue = TRUE)
{
	switch (_mem_timer_base_mode)
	{
		case ET_OVERFLOW:
		{
			return Flag_timer_overflow(_arg_timer_continue);
		}
		case ET_COMPARE:
		{
			return Flag_timer_compare(_arg_timer_continue);
		}
		case ET_CAPUTER:
		{
			
		}
		break;
	}
	
	return FALSE;
}

inline void
C_TIMER ::
Stop ()
{
	__TCCRB__ &= TIME_SET_BIT;
}
