
/*
最初から２線通信を想定したUART系のクラス
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 通信を二線通信のみにした。
 H28 05 23 ver1.0.0 C_UART_baseの派生クラスにした。それにともなって色々変えた。
 H28 05 24 ver1.1.0 Set_base_addrを多用するのはやめた。マクロ追加した。
*/

#pragma once

//public member

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
	
	_mem_uart_r2_flag_state = EU_NONE;
	
	_mem_uart_r2_flag_priority0 = TRUE;
	_mem_uart_r2_flag_priority1 = TRUE;
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
Check_in ()
//受信しなかった方を受信禁止にしたらうまくいった。
{
	__UCSRB_0__ |= (1 << RXEN);
	__UCSRB_1__ |= (1 << RXEN);
	
	_mem_timer.Start();
	
	while (1)
	{
		if (F_Check_bit_bool(__UCSRA_0__, RXC) & _mem_uart_r2_flag_priority0 & _mem_timer.Ret_state())	//UART0受信完了
		{
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 0;
			
			_mem_uart_r2_flag_priority1 = FALSE;
			
			break;
		}
		
		if (F_Check_bit_bool(__UCSRA_1__, RXC) & _mem_uart_r2_flag_priority1 & _mem_timer.Ret_state())	//UART1受信完了
		{
			__UCSRB_0__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 1;
			
			_mem_uart_r2_flag_priority0 = FALSE;
			
			break;;
		}
		
		if (_mem_timer.Check())	//カウント完了(タイムアウト)
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
In (BOOL _arg_nf_auto_cut = TRUE)
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
	
	_mem_uart_base_addr = _mem_arr_uart_r2_addr[_mem_uart_r2_num_seccess];	//受信成功したポートにする
	
	if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_data_in |= (1 << 8);	//9bit通信時
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
	if (_arg_uart_r2._mem_uart_r2_flag_state == _arg_uart_flag_comp)	return true;
	
	return false;
}

bool 
operator != 
(
	C_UART_R2 &_arg_uart_r2,
	E_UART_FLAG _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}