﻿
/*
UART系の基底となるクラス。こいつは宣言しないでね
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 コンストラクタ消しといた。
*/

#pragma once

#include "H28_U_C_UART_base.h"

//protected member

inline void 
C_UART_base::
Set (E_UART_ADDR _arg_uart_addr)
/*
UARTの初期設定
250[kbps]
倍速
奇数パリティ

	_arg_uart_base_addr : 使うUARTのレジスタ
*/
{
	_mem_uart_base_addr = _arg_uart_addr;
	
	UBRRH = 0x00;
	UBRRL = 0x04;
	//F_CPU=10MHz 250kbps
	
	UCSRA = (1<<U2X);
	//Double teransmission spead
	
	UCSRB &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	UCSRC = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//Odd parity mode_i
}

//public member

inline void 
C_UART_base::
Set_bit9 (BOOL _arg_uart_nf_bit9)
/*
9bit通信のONOFF
8bitと9bitどうしではうまく通信できないので注意

	_arg_uart_base_nf_bit9 : ON/OFF
	TRUE  -> ON
	FALES -> OFF
*/
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	UCSRB |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB &= ~(1 << UCSZ2);	break; //Off
	}
}

inline BOOL 
C_UART_base :: 
Ret_bit9 ()
{
	return CHECK_BIT_TF(UCSRB,UCSZ2);
}
