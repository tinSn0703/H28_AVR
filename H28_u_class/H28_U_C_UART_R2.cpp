
/*
最初から２線通信を想定したUART系のクラス
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 通信を二線通信のみにした。
 H28 05 23 ver1.0.0 C_UART_baseの派生クラスにした。それにともなって色々変えた。
 H28 05 24 ver1.1.0 Set_base_addrを多用するのはやめた。マクロ追加した。
*/

#pragma once

#include "H28_U_C_UART_R2.h"

//public member

inline 
C_UART_R2 :: 
C_UART_R2 ()
: _mem_timer(80)
{
	_mem_uart_r2_flag = EU_NONE;
}


inline 
C_UART_R2::
C_UART_R2
(
	E_UART_ADDR _arg_uart_addr_0,
	E_UART_ADDR _arg_uart_addr_1,
	BOOL _arg_uart_nf_isr_0 = FALSE,
	BOOL _arg_uart_nf_isr_1 = FALSE
)
: _mem_timer(80)
{
	_mem_arr_uart_r2_addr[0] = _arg_uart_addr_0;
	_mem_arr_uart_r2_addr[1] = _arg_uart_addr_1;
	
	C_UART_base::Set(_arg_uart_addr_0);
	C_UART_base::Set(_arg_uart_addr_1);
	
	Set_isr_0(_arg_uart_nf_isr_0);
	Set_isr_1(_arg_uart_nf_isr_1);
	
	_mem_uart_r2_flag = EU_NONE;
}

inline void 
C_UART_R2::
Set_isr_0 (BOOL _arg_uart_nf_isr)
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
Set_bit9_0 (BOOL _arg_uart_nf_bit9)
{	
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_0__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_0__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
C_UART_R2::
Set_bit9_1 (BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_1__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_1__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
C_UART_R2::
Check ()
//受信しなかった方を受信禁止にしたらうまくいった。
{
	__UCSRB_0__ |= (1 << RXEN);
	__UCSRB_1__ |= (1 << RXEN);
	
	_mem_timer.Start();
	
	while (1)
	{
		if (CHECK_BIT_TF(__UCSRA_0__,RXC) & _mem_timer.Ret_flag())	//UART0受信完了
		{
			_mem_timer.End();
			
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 0;
		
			break;
		}
		
		if (CHECK_BIT_TF(__UCSRA_1__,RXC) & _mem_timer.Ret_flag())	//UART1受信完了
		{
			_mem_timer.End();
			
			__UCSRB_0__ &= ~(1 << RXEN);
			
			_mem_uart_r2_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 1;
			
			break;
		}
		
		if (_mem_timer.Check())	//カウント完了(タイムアウト)
		{
			_mem_uart_r2_flag = EU_ERROR;
			
			break;
		}
	}
}

T_DATA 
C_UART_R2::
In ()
{
	Check();
	
	if (_mem_uart_r2_flag == EU_ERROR)	return IN_ERROR;
	
	T_DATA _ret_in_data = 0;
	
	_mem_uart_base_addr = _mem_arr_uart_r2_addr[_mem_uart_r2_num];	//受信成功したポートにする
	
	if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_in_data |= (1 << 8);	//9bit通信時
	}
	
	_ret_in_data |= __UDR__;
	
	_mem_uart_r2_flag = EU_NONE;
	
	return _ret_in_data;
}

inline E_UART_FLAG 
C_UART_R2 :: 
Ret_flag ()
{
	return _mem_uart_r2_flag;
}

void 
operator >> 
(
	C_UART_R2 &_arg_uart_r2,
	T_DATA &_arg_uart_data_in
)
{
	_arg_uart_data_in = _arg_uart_r2.In();
}

void 
operator >> 
(
	C_UART_R2 &_arg_uart_r2,
	T_DATA_8 &_arg_uart_data_in
)
{
	_arg_uart_data_in = (T_DATA_8)_arg_uart_r2.In();
}

bool 
operator == 
(
	C_UART_R2 &_arg_uart_r2,
	E_UART_FLAG _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag == _arg_uart_flag_comp)	return true;
	
	return false;
}

bool 
operator != 
(
	C_UART_R2 &_arg_uart_r2,
	E_UART_FLAG _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag != _arg_uart_flag_comp)	return true;
	
	return false;
}