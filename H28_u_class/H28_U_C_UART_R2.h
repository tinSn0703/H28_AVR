
/*
�ŏ�����Q���ʐM��z�肵��UART�n�̃N���X
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 �ʐM�����ʐM�݂̂ɂ����B
 H28 05 23 ver1.0.0 C_UART_base�̔h���N���X�ɂ����B����ɂƂ��Ȃ��ĐF�X�ς����B
 H28 05 24 ver1.1.0 Set_base_addr�𑽗p����̂͂�߂��B�}�N���ǉ������B
*/

#pragma once

#include "H28_U_C_UART_base.h"

#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/*************************************************************************

UART��2��������M���[�h�ő��삷�邽�߂̃N���X

*************************************************************************/

class C_UART_R2 : protected C_UART_base
{
	
private:
	
	C_TIMER_inside _mem_timer;
	
	E_UART_FLAG _mem_uart_r2_flag_state :2;
	T_NUM		_mem_uart_r2_num_seccess :1;
	
	BOOL _mem_uart_r2_flag_priority0 :1;
	BOOL _mem_uart_r2_flag_priority1 :1;
	
	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//���W�X�^�̃A�h���X
	
#	define __UCSRA_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 0)
#	define __UCSRB_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 1)
#	define __UCSRC_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 2)
#	define __UBRRL_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 4)
#	define __UBRRH_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 5)
#	define __UDR_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 6)
	
#	define __UCSRA_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 0)
#	define __UCSRB_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 1)
#	define __UCSRC_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 2)
#	define __UBRRL_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 4)
#	define __UBRRH_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 5)
#	define __UDR_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 6)
	
public:
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����^�C�}�̐ݒ�݂̂��s��
	 */
	C_UART_R2 ();
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_addr : �g��UART
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R2 (E_UART_ADDR _arg_uart_addr_0, E_UART_ADDR _arg_uart_addr_1, BOOL _arg_uart_nf_isr_0, BOOL _arg_uart_nf_isr_1);
	
	/**
	 * \brief 0�Ԃ̎�M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr_0 (BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 1�Ԃ̎�M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr_1 (BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 0�Ԃ�9nit�ʐM��ONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFF�̐ݒ�
	 */
	void Set_bit9_0 (BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 1�Ԃ�9nit�ʐM��ONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFF�̐ݒ�
	 */
	void Set_bit9_1 (BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 
	 * ��M���ł��邩���m�F����B���ʂ�_mem_uart_r2_flag�Ɋi�[�����̂Ŏg���Ƃ��ɂ�������ǂ�łق����B
	 * In()�͎����I�ɁA��ɐ��������ق��ōs���܂��B
	 * �m�F���͂��̊֐��Œ�~���܂��B
	 * �m�F�ɂ͍Œ���8ms��������܂�
	 */
	void Check_in ();
	
	/**
	 * \brief 
	 * ��M����
	 * Check_in()�Ő��������ق���p���� 
	 * 
	 * \param _arg_nf_auto_cut : �����ŒʐM�̊m�F���I�����邩�ǂ���
	 *
	 * \return T_DATA : ��M�����f�[�^
	 */
	T_DATA In (BOOL _arg_nf_auto_cut);
	
	/**
	 * \brief ���O�̎�M��Ԃ�return����B
	 */
	E_UART_FLAG Ret_flag ();
	
	/**
	 * \brief C_UART_R2::In()�̉��Z�q�o�[�W�����B
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R2::In()�̉��Z�q�o�[�W�����B
	 * 8bit�ʐM�̂Ƃ��p
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R2::Check_in()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ƃ�true
	 */
	friend bool operator == (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R2::Check_in()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ȃ��Ƃ�true
	 */
	friend bool operator != (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
};

/************************************************************************/

inline
C_UART_R2 ::
C_UART_R2 ()
: _mem_timer(200)
{
	_mem_uart_r2_flag_state = EU_NONE;
	
	_mem_uart_r2_flag_priority0 = TRUE;
	_mem_uart_r2_flag_priority1 = TRUE;
}


inline
C_UART_R2::
C_UART_R2
(
	const E_UART_ADDR	_arg_uart_addr_0,
	const E_UART_ADDR	_arg_uart_addr_1,
	const BOOL			_arg_uart_nf_isr_0 = FALSE,
	const BOOL			_arg_uart_nf_isr_1 = FALSE
)
: _mem_timer(80)
{
	_mem_arr_uart_r2_addr[0] = _arg_uart_addr_0;
	_mem_arr_uart_r2_addr[1] = _arg_uart_addr_1;
	
	C_UART_base::Set(_arg_uart_addr_0);
	C_UART_base::Set(_arg_uart_addr_1);
	
	Set_isr_0(_arg_uart_nf_isr_0);
	Set_isr_1(_arg_uart_nf_isr_1);
	
	_mem_uart_r2_flag_state = EU_NONE;
	
	_mem_uart_r2_flag_priority0 = TRUE;
	_mem_uart_r2_flag_priority1 = TRUE;
}

inline void
C_UART_R2::
Set_isr_0 (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB_0__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB_0__ &= ~(1 << RXCIE);	break; //Off
	}
}

inline void
C_UART_R2::
Set_isr_1 (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB_1__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB_1__ &= ~(1 << RXCIE);	break; //Off
	}
}

inline void
C_UART_R2::
Set_bit9_0 (const BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_0__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_0__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void
C_UART_R2::
Set_bit9_1 (const BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_1__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_1__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void
C_UART_R2::
Check_in ()
//��M���Ȃ�����������M�֎~�ɂ����炤�܂��������B
{
	__UCSRB_0__ |= (1 << RXEN);
	__UCSRB_1__ |= (1 << RXEN);
	
	_mem_timer.Start();
	
	while (1)
	{
		if (F_Check_bit_bool(__UCSRA_0__, RXC) & _mem_uart_r2_flag_priority0 & _mem_timer.Ret_state())	//UART0��M����
		{
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 0;
			
			_mem_uart_r2_flag_priority1 = FALSE;
			
			break;
		}
		
		if (F_Check_bit_bool(__UCSRA_1__, RXC) & _mem_uart_r2_flag_priority1 & _mem_timer.Ret_state())	//UART1��M����
		{
			__UCSRB_0__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 1;
			
			_mem_uart_r2_flag_priority0 = FALSE;
			
			break;;
		}
		
		if (_mem_timer.Check())	//�J�E���g����(�^�C���A�E�g)
		{
			__UCSRB_0__ &= ~(1 << RXEN);
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_flag_state = EU_ERROR;
			
			_mem_uart_r2_flag_priority0 = TRUE;
			_mem_uart_r2_flag_priority1 = TRUE;
			
			return (void)0;
		}
	}
	
	_mem_timer.Stop();
	
	_mem_uart_r2_flag_state = EU_SUCCE;
}

T_DATA
C_UART_R2::
In (const BOOL _arg_nf_auto_cut = TRUE)
{
	if (_arg_nf_auto_cut)
	{
		Check_in();
		
		if (_mem_uart_r2_flag_state == EU_ERROR)	return IN_ERROR;
	}
	else
	{
		__UCSRB_0__ |= (1 << RXEN);
		__UCSRB_1__ |= (1 << RXEN);
		
		while (1)
		{
			if (__UCSRA_0__ & (1 << RXC))	_mem_uart_r2_num_seccess = 0;	break;
			if (__UCSRA_1__ & (1 << RXC))	_mem_uart_r2_num_seccess = 1;	break;
		}
	}
	
	T_DATA _ret_data_in = 0;
	
	_mem_uart_base_addr = _mem_arr_uart_r2_addr[_mem_uart_r2_num_seccess];	//��M���������|�[�g�ɂ���
	
	if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_data_in |= (1 << 8);	//9bit�ʐM��
	}
	
	_ret_data_in |= __UDR__;
	
	return _ret_data_in;
}

inline E_UART_FLAG
C_UART_R2 ::
Ret_flag ()
{
	return _mem_uart_r2_flag_state;
}

void
operator >>
(
	C_UART_R2	&_arg_uart_r2,
	T_DATA		&_arg_uart_data_in
)
{
	_arg_uart_data_in = _arg_uart_r2.In();
}

void
operator >>
(
	C_UART_R2	&_arg_uart_r2,
	T_DATA_8	&_arg_uart_data_in
)
{
	_arg_uart_data_in = (T_DATA_8)_arg_uart_r2.In();
}

bool
operator ==
(
	C_UART_R2			&_arg_uart_r2,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag_state == _arg_uart_flag_comp)	return true;
	
	return false;
}

bool
operator !=
(
	C_UART_R2			&_arg_uart_r2,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}

