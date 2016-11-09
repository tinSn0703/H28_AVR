
/*
UART系の基底となるクラス。こいつは宣言しないでね
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 コンストラクタ消しといた。
*/

#pragma once

#include "H28_U_C_UART_base.h"

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)
//protected member

inline void 
C_UART_base ::
Set (E_UART_ADDR _arg_uart_addr)
{
	_mem_uart_base_addr = _arg_uart_addr;
	
	__UBRRH__ = 0x00;
	__UBRRL__ = 0x04;
	//F_CPU = 10[MHz] 250[kbps]
	
	__UCSRA__ = (1<<U2X);
	//倍速許可
	
	__UCSRB__ &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	__UCSRC__ = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//奇数パリティ
}

//public member

inline C_UART_base :: 
C_UART_base (E_UART_ADDR _arg_uart_addr)
{
	Set(_arg_uart_addr);
};
#elif defined(_AVR_IOM88_H_)
//public member

inline C_UART_base ::
C_UART_base ()
{
	__UBRRH__ = 0x00;
	__UBRRL__ = 0x04;
	//F_CPU=10MHz 250kbps
	
	__UCSRA__ = (1<<U2X);
	//Double teransmission spead
	
	__UCSRB__ &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	__UCSRC__ = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//Odd parity mode_i
};
#endif

inline void 
C_UART_base ::
Set_bit9 (BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
C_UART_base ::
Set_bit9_on ()
{
	__UCSRB__ |=  (1 << UCSZ2);
}

inline void 
C_UART_base :: 
Set_bit9_off ()
{
	__UCSRB__ &= ~(1 << UCSZ2);
}

inline BOOL 
C_UART_base :: 
Ret_nf_bit9 ()
{
	return CHECK_BIT_TF(__UCSRB__,UCSZ2);
}
