
/*
送信を行うUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_T.h"

//public member

C_UART_T ::
C_UART_T
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_isr = FALES
)
: C_UART_base(_arg_uart_addr)
{	
	Set_isr(_arg_uart_nf_isr);
}

inline void 
C_UART_T::
Set_isr (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << UDRIE);	break; //On
		case FALES:	UCSRB &= ~(1 << UDRIE);	break; //Off
	}
}

void 
C_UART_T::
Out (T_DATA _arg_uart_data_out)
{	
	UCSRB |= (1 << TXEN); //送信許可する。
	
	while (!(UCSRA & (1 << UDRE))); //送信が可能になるまで待機
	
	if ((C_UART_base::Ret_bit9() & CHECK_BIT_TF(_arg_uart_data_out,8)) == TRUE)
	{
		UCSRB |= (1 << TXB8);
	}

	UDR = (_arg_uart_data_out & 0xff);
	
	while (!(UCSRA & (1 << TXC))); //送信完了まで待機
	
	UCSRA |= (1 << TXC);
}

void
C_UART_T::
Out (T_DATA_8 _arg_uart_data_out)
{
	UCSRB |= (1 << TXEN); //送信許可する。
	
	while (!(UCSRA & (1 << UDRE))); //送信が可能になるまで待機

	UDR = _arg_uart_data_out;
	
	while (!(UCSRA & (1 << TXC))); //送信完了まで待機
	
	UCSRA |= (1 << TXC);
}

inline void 
operator << 
(
	C_UART_T &_arg_uart_t,
	T_DATA _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}

inline void
operator <<
(
	C_UART_T &_arg_uart_t,
	T_DATA_8 _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}