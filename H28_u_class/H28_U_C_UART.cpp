
/*
受信、送信両方を行えるUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART.h"

C_UART::
C_UART
(
	E_UART_ADDR _arg_uart_addr, 
	E_UART_MODE _arg_uart_mode, 
	BOOL _arg_uart_nf_isr = FALES
)
: C_UART_R(_arg_uart_addr)
{
	_mem_uart_mode = _arg_uart_mode;
	
	Set_isr(_arg_uart_nf_isr);
}

inline void 
C_UART::
Chan_mode (E_UART_MODE _arg_uart_mode)
{
	_mem_uart_mode = _arg_uart_mode;
}

inline void 
C_UART::
Set_isr (BOOL _arg_uart_nf_isr)
{
	switch(_mem_uart_mode)
	{
		case EU_REC:	C_UART_R::Set_isr(_arg_uart_nf_isr);	break;
		case EU_TRA:	C_UART_T::Set_isr(_arg_uart_nf_isr);	break;
	}
}
