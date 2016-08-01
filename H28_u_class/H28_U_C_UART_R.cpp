
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_R.h"

//public member

inline 
C_UART_R :: 
C_UART_R ()
: _mem_timer(80)
{
	_mem_uart_r_flag = EU_NONE;
}

inline 
C_UART_R::
C_UART_R
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_isr = FALES
)
 : C_UART_base(_arg_uart_addr)
 , _mem_timer(80) //8ms
{	
	Set_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag = EU_NONE;
}

inline void 
C_UART_R::
Set_isr (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB &= ~(1 << RXCIE);	break; //Off
	}
}

void 
C_UART_R::
Check ()
{
	UCSRB |= (1 << RXEN); //受信許可
	
	_mem_timer.Start();
	
	while (1)
	{
		if ((_mem_timer.Ret_flag() & CHECK_BIT_TF(UCSRA,RXC)) == TRUE)	//受信完了
		{
			_mem_timer.End();
			
			_mem_uart_r_flag = EU_SUCCE;
			
			break;
		}
		
		if (_mem_timer.Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag = EU_ERROR;
			
			break;
		}
	}
}

T_DATA 
C_UART_R::
In ()
{
	Check(); //受信チェック
	
	if (_mem_uart_r_flag == EU_ERROR)	return IN_ERROR;	//受信失敗
	
	T_DATA _ret_in_data = 0;
		
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data = (1 << 8);	//9bit通信時
	
	_ret_in_data |= UDR;
	
	_mem_uart_r_flag = EU_NONE;
	
	return _ret_in_data;
}

inline E_UART_FLAG 
C_UART_R :: 
Ret_flag()
{
	return _mem_uart_r_flag;
}

void 
operator >> 
(
	C_UART_R &_arg_uart_r,
	T_DATA &_arg_uart_data_in
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
	_arg_uart_r.Set_bit9(FALES);
	_arg_uart_data_in = (T_DATA_8 )_arg_uart_r.In();
}

bool 
operator == 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_r_flag_comp
)
{	
	if (_arg_uart_r._mem_uart_r_flag == _arg_uart_r_flag_comp)	return true;
	
	return false;
}

bool 
operator != 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag != _arg_uart_flag_comp)	return true;
	
	return false;
}