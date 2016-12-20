
/*
��M�̂݉\��UART�n��̃N���X
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 �p����C_TIMER_inside���Ƃ�����,class�����̃J�E���g�������ōs���悤�ɂ����B
 H28 05 23 ver 0.2.0 C_UART_base�̉����ɍ��킹��
*/


#pragma once

#include "H28_U_C_UART_base.h"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/*************************************************************************

UART����M���[�h�ő��삷�邽�߂̃N���X

*************************************************************************/


class C_UART_R : public virtual C_UART_base
{
private:

	C_TIMER_inside _mem_timer;
	
	E_UART_FLAG _mem_uart_r_flag_state :2; //�Ō�̎�M��Ԃ̋L�^
	
public:
	
#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����^�C�}�̐ݒ�݂̂��s��
	 */
	C_UART_R();
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_addr : �g��UART
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_isr);
	
#elif defined(_AVR_IOM88_H_)
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R(BOOL _arg_uart_nf_isr);

#endif

	/**
	 * \brief ��M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Reset_isr(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 
	 * ��M���ł��邩���m�F����B���ʂ�_mem_uart_r_flag�Ɋi�[�����̂Ŏg���Ƃ��ɂ�������ǂ�łق����B
	 * Timer��p���āA��莞�ԂŎ�M�ł��Ȃ������ꍇ�́A�����I�ɏI�����܂�
	 * �m�F���͂��̊֐��Œ�~���܂��B
	 * �m�F�ɂ͍Œ���8ms��������܂�
	 */
	void Check_in();
	
	/**
	 * \brief ��M
	 * 
	 * \param _arg_nf_auto_cut : �����ŒʐM���I������@�\�̎g�p�ɂ���
	 *
	 * \return T_DATA : ��M�����f�[�^
	 */
	T_DATA In(BOOL _arg_nf_auto_cut);

	/**
	 * \brief ��M��Ԃ�return����B
	 * 
	 * \return E_UART_FLAG
	 *	���s	-> EU_ERROR
	 *	����	-> EU_SUCCE
	 *	���̑�	-> EU_NONE
	 */
	E_UART_FLAG Ret_state();
	
	/**
	 * \brief 
	 * C_UART_R::In()�̉��Z�q�o�[�W�����B
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R::In()�̉��Z�q�o�[�W�����B
	 * 8bit�ʐM�̂Ƃ��p
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R::Check_in()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ƃ�true
	 */
	friend bool operator == (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R::Check_in()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ȃ��Ƃ�true
	 */
	friend bool operator != (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
};

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

inline
C_UART_R ::
C_UART_R ()
: _mem_timer(80)
{
	_mem_uart_r_flag_state = EU_NONE;
}

inline
C_UART_R ::
C_UART_R
(
	const E_UART_ADDR	_arg_uart_addr,
	const BOOL			_arg_uart_nf_isr = FALSE
)
: C_UART_base(_arg_uart_addr)
, _mem_timer(80) //8ms
{
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#elif defined(_AVR_IOM88_H_)

inline
C_UART_R ::
C_UART_R (const BOOL _arg_uart_nf_isr = FALSE)
: C_UART_base()
, _mem_timer(80) //8ms
{
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#endif

inline void
C_UART_R ::
Reset_isr (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << RXCIE);	break; //Off
	}
}

void
C_UART_R ::
Check_in ()
{
	__UCSRB__ |= (1 << RXEN); //��M����
	
	_mem_uart_r_flag_state = EU_NONE;
	
	_mem_timer.Start();
	
	while (1)
	{
		if ((_mem_timer.Ret_state() & F_Check_bit_bool(__UCSRA__, RXC)) == TRUE)	//��M����
		{
			_mem_timer.Stop();
			
			_mem_uart_r_flag_state = EU_SUCCE;
			
			break;
		}
		
		if (_mem_timer.Check() == TRUE)	//�J�E���g����(�^�C���A�E�g)
		{
			_mem_uart_r_flag_state = EU_ERROR;
			
			break;
		}
	}
}

T_DATA
C_UART_R ::
In (const BOOL _arg_nf_auto_cut = TRUE)
{
	if (_arg_nf_auto_cut)
	{
		Check_in(); //��M�`�F�b�N
		
		if (_mem_uart_r_flag_state == EU_ERROR)	return IN_ERROR;	//��M���s
	}
	else
	{
		_mem_uart_r_flag_state = EU_NONE;
		
		__UCSRB__ |= (1 << RXEN); //��M����
		
		while ( ! (__UCSRA__ & (1 << RXC)));
	}
	
	T_DATA _ret_in_data = 0;
	
	if (__UCSRA__ & ((1 << FE) | (1 << DOR) | (1 << UPE)))
	{
		_mem_uart_r_flag_state = EU_ERROR;
		
		_ret_in_data = __UDR__;
		
		return __UCSRA__;
	}
	else
	{
		T_DATA _ret_in_data_9 = 0;
		
		if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data_9 = (1 << 8);	//9bit�ʐM��
		
		_ret_in_data = __UDR__;
		
		_ret_in_data |= _ret_in_data_9;
	}
	
	return _ret_in_data;
}

inline E_UART_FLAG
C_UART_R ::
Ret_state()
{
	return _mem_uart_r_flag_state;
}

void
operator >>
(
	C_UART_R	&_arg_uart_r,
	T_DATA		&_arg_uart_data_in
)
{
	_arg_uart_data_in = _arg_uart_r.In();
}

void
operator >>
(
	C_UART_R &_arg_uart_r,
	T_DATA_8 &_arg_uart_data_in
)
{
	_arg_uart_r.Set_bit9(FALSE);
	_arg_uart_data_in = (T_DATA_8 )_arg_uart_r.In();
}

bool
operator ==
(
	C_UART_R			&_arg_uart_r,
	const E_UART_FLAG	 _arg_uart_r_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag_state == _arg_uart_r_flag_comp)	return true;
	
	return false;
}

bool
operator !=
(
	C_UART_R			&_arg_uart_r,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}