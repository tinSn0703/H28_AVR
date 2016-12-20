
/*
�N���X�����Ƃ��ł̓����^�C�}�p�̃C���[�W�B�p�����Ďg���Ăǂ���
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 public�����o�Ȃ�����錾���Ă��Ӗ��Ȃ���<-���͐� 
*/

#pragma once

#include "H28_t_class.h"

/*************************************************************************

�^�C�}-�p�N���X
��莞�Ԃ̌v���p�B���[�v���Ă钆�Ŏg���Ă�
C_COUNTER�̎q�ɂ���������
�����܂Ő��x�͂悭�Ȃ��̂Ńv���O��������~���Ȃ��҂����Ԓ��x�ɍl���ĂƂ���
TIMER0���g���Ă܂�
TIMER2ver�����납��

*************************************************************************/

class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count ; //�J�E���^
	usint _mem_timer_inside_limit ; //�J�E���g�̏��
	BOOL _mem_timer_inside_flag  :1;  //�J�E���g�̓���t���O
	
public:
	
	/**
	 * \brief	�R���X�g���N�^�B_mem_timer_inside_limit��0�ɂ��邾��
	 */
	C_TIMER_inside();
	
	/**
	 * \brief 
	 *	�R���X�g���N�^
	 *	TIMER�̏����ݒ���s���B 
	 *
	 * \param _arg_limit : �J�E���g����B1�J�E���g�ɂ�100us
	 */
	C_TIMER_inside(usint _arg_timer_limit);
	
	/**
	 * \brief �^�C�}�̊J�n
	 */
	void Start();
	
	/**
	 * \brief �^�C�}�̌���̊m�F 
	 * 
	 * \return BOOL 
	 *	TRUE  -> ����
	 *	FALES -> ����ȊO
	 */
	BOOL Check();
	
	/**
	 * \brief �^�C�}�̏I��
	 */
	void Stop();
	
	/**
	 * \brief �J�E���g�̓���t���O�̒l��Ԃ�
	 * 
	 * \return BOOL
	 *	TRUE  -> �J�E���g���s���Ă���
	 *	FALES -> �J�E���g���s���Ă��Ȃ�
	 */
	BOOL Ret_state();
	
	/**
	 * \brief �J�E���g�̏���l��ύX���鉉�Z�q
	 * 
	 * \param _arg_timer_limit : �V�������
	 */
	C_TIMER_inside & operator = (usint _arg_timer_limit);
	
	/**
	 * \brief 
	 * if���Ȃǂł̔�r�p�̉��Z�q
	 * C_TIMER_inside::Ret_state()�Ɣ�r����
	 * 
	 * \param _arg_timer_inside : �݂��܂�
	 * \param _arg_timer_flag_comp : ��r������
	 * 
	 * \return friend bool �������Ƃ�ture
	 */
	friend bool operator == (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̔�r�p�̉��Z�q
	 * C_TIMER_inside::Ret_state()�Ɣ�r����
	 * 
	 * \param _arg_timer_inside : �݂��܂�
	 * \param _arg_timer_flag_comp : ��r������
	 * 
	 * \return friend bool �������Ȃ��Ƃ�ture
	 */
	friend bool operator != (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
};

/************************************************************************/
//public

C_TIMER_inside ::
C_TIMER_inside ()
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;
	
	_mem_timer_inside_limit = 0;
}

C_TIMER_inside ::
C_TIMER_inside (usint _arg_timer_limit)
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;

	_mem_timer_inside_limit = _arg_timer_limit;
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag  = FALSE;
}

inline void
C_TIMER_inside ::
Start ()
{
	_mem_timer_inside_flag = TRUE;
	_mem_timer_inside_count = 0;
	
	TCNT0 = 130; //100us
	TCCR0B = (1<<CS01);
}

inline BOOL
C_TIMER_inside ::
Check ()
{
	if ((_mem_timer_inside_flag & F_Check_bit_bool(TIFR0, TOV0)) == TRUE)
	{
		TCNT0  = 130; //100us
		
		TIFR0 |= (1 << TOV0);
		
		if (_mem_timer_inside_count < _mem_timer_inside_limit)
		//�J�E���g��,1�����o��
		{
			_mem_timer_inside_count++;
		}
		else
		//�J�E���g����
		{
			Stop();
			
			return TRUE;
		}
	}
	
	return FALSE;
}

inline void
C_TIMER_inside ::
Stop ()
{
	TCCR0B = 0;
	
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag = FALSE;
}

inline BOOL
C_TIMER_inside ::
Ret_state ()
{
	return _mem_timer_inside_flag;
}

inline C_TIMER_inside &
C_TIMER_inside ::
operator = (usint _arg_timer_limit)
{
	_mem_timer_inside_limit = _arg_timer_limit;
	
	return *this;
}

inline bool
operator ==
(
	C_TIMER_inside &_arg_timer_inside,
	BOOL			_arg_timer_flag_comp
)
{
	if (_arg_timer_inside._mem_timer_inside_flag == _arg_timer_flag_comp)
	{
		return true;
	}
	
	return false;
}

inline bool
operator !=
(
	C_TIMER_inside &_arg_timer_inside,
	BOOL			_arg_timer_flag_comp
)
{
	if (_arg_timer_inside._mem_timer_inside_flag != _arg_timer_flag_comp)
	{
		return true;
	}
	
	return false;
}