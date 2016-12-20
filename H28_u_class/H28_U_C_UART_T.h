
/*
���M���s��UART�n�̃N���X
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_base�̉����ɍ��킹��
*/

#pragma once

#include "H28_U_C_UART_base.h"

/*************************************************************************

 UART�𑗐M���[�h�ő��삷�邽�߂̃N���X

*************************************************************************/

class C_UART_T : public virtual C_UART_base
{
	
public:
	
#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)
	
	C_UART_T() {}
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * 
	 * \param _aeg_uart_addr   : �g��UART
	 * \param _arg_uart_nf_isr : ���M�f�[�^���W�X�^�󂫊��荞�݂�ONOFF
	 */
	C_UART_T(E_UART_ADDR _aeg_uart_addr, BOOL _arg_uart_nf_isr);

#elif defined(_AVR_IOM88_H_)
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * 
	 * \param _arg_uart_nf_isr : ���M�f�[�^���W�X�^�󂫊��荞�݂�ONOFF
	 */
	C_UART_T(BOOL _arg_uart_nf_isr);

#endif
	
	/**
	 * \brief	���M�f�[�^���W�X�^�󂫊��荞�݂̐ݒ� 
	 *
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Reset_isr(BOOL _arg_uart_nf_isr);
	
//	void Out (int _arg_uart_data_out);
	
	/**
	 * \brief 
	 * �f�[�^�𑗐M����B
	 * �A���ŒʐM���s���ꍇ�͑��葤�ɂ����������邱�Ƃ��l���Ȃ������Ă�
	 * 
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	void Out(T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * �f�[�^�𑗐M����B
	 * �A���ŒʐM���s���ꍇ�͑��葤�ɂ����������邱�Ƃ��l���Ȃ������Ă�
	 * 8bit�ʐM�̎��p
	 * 
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	void Out(T_DATA_8 _arg_uart_data_out);
	
	/**
	 * \brief	C_UART_T::Out()�̉��Z�qver 
	 *
	 * \param _arg_uart_t : �݂��܂�
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * C_UART_T::Out()�̉��Z�qver 
	 * 8bit�ʐM�̎��p
	 *
	 * \param _arg_uart_t : �݂��܂�
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA_8 _arg_uart_data_out);
};

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

C_UART_T ::
C_UART_T
(
	const E_UART_ADDR	_arg_uart_addr,
	const BOOL			_arg_uart_nf_isr = FALSE
)
: C_UART_base(_arg_uart_addr)
{
	Reset_isr(_arg_uart_nf_isr);
}

#elif defined(_AVR_IOM88_H_)

C_UART_T ::
C_UART_T (const BOOL _arg_uart_nf_isr = FALSE)
: C_UART_base()
{
	Reset_isr(_arg_uart_nf_isr);
}

#endif

inline void
C_UART_T ::
Reset_isr (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB__ |=  (1 << UDRIE);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << UDRIE);	break; //Off
	}
}

void
C_UART_T ::
Out (const T_DATA _arg_uart_data_out)
{
	__UCSRB__ |= (1 << TXEN); //���M������B
	
	while (!(__UCSRA__ & (1 << UDRE))); //���M���\�ɂȂ�܂őҋ@
	
	if ((C_UART_base :: Ret_nf_bit9() & F_Check_bit_bool(_arg_uart_data_out, 8)) == TRUE)
	{
		__UCSRB__ |= (1 << TXB8);	//8bit�ڂ̑��M
	}

	__UDR__ = (_arg_uart_data_out & 0xff);
	
	while (!(__UCSRA__ & (1 << TXC))); //���M�����܂őҋ@
	
	__UCSRA__ |= (1 << TXC);
}

void
C_UART_T ::
Out (const T_DATA_8 _arg_uart_data_out)
{
	__UCSRB__ |= (1 << TXEN); //���M������B
	
	while (!(__UCSRA__ & (1 << UDRE))); //���M���\�ɂȂ�܂őҋ@

	__UDR__ = _arg_uart_data_out;
	
	while (!(__UCSRA__ & (1 << TXC))); //���M�����܂őҋ@
	
	__UCSRA__ |= (1 << TXC);
}

inline void
operator <<
(
	C_UART_T		&_arg_uart_t,
	const T_DATA	 _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}

inline void
operator <<
(
	C_UART_T		&_arg_uart_t,
	const T_DATA_8	 _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}