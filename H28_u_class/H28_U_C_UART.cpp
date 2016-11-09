
/*
受信、送信両方を行えるUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART.h"

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

C_UART ::
C_UART
(
	E_UART_ADDR _arg_uart_addr, 
	E_UART_MODE _arg_uart_mode, 
	BOOL _arg_uart_nf_isr = FALSE
)
: C_UART_R(_arg_uart_addr)
{
	_mem_uart_mode = _arg_uart_mode;
	
	Reset_isr(_arg_uart_nf_isr);
}

#elif defined(_AVR_IOM88_H_)

C_UART ::
C_UART
(
	E_UART_MODE _arg_uart_mode,
	BOOL _arg_uart_nf_isr = FALSE
)
: C_UART_R()
{
	_mem_uart_mode = _arg_uart_mode;
	
	Reset_isr(_arg_uart_nf_isr);
}

#endif

inline void 
C_UART ::
Reset_mode (E_UART_MODE _arg_uart_mode)
{
	_mem_uart_mode = _arg_uart_mode;
}

inline void 
C_UART ::
Reset_isr (BOOL _arg_uart_nf_isr)
{
	switch(_mem_uart_mode)
	{
		case EU_REC:	C_UART_R :: Reset_isr(_arg_uart_nf_isr);	break;
		case EU_TRA:	C_UART_T :: Reset_isr(_arg_uart_nf_isr);	break;
	}
}
