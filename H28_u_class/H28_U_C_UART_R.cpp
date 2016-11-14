
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/

#pragma once

//public member

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

inline
C_UART_R ::
C_UART_R ()
: _mem_timer(80)
{
	_mem_uart_r_flag_state = EU_NONE;
}

inline 
C_UART_R ::
C_UART_R
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_isr = FALSE
)
 : C_UART_base(_arg_uart_addr)
 , _mem_timer(80) //8ms
{	
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#elif defined(_AVR_IOM88_H_)

inline
C_UART_R ::
C_UART_R (BOOL _arg_uart_nf_isr = FALSE)
: C_UART_base()
, _mem_timer(80) //8ms
{
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#endif

inline void 
C_UART_R::
Reset_isr (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << RXCIE);	break; //Off
	}
}

void 
C_UART_R::
Check_in ()
{
	__UCSRB__ |= (1 << RXEN); //受信許可
	
	_mem_uart_r_flag_state = EU_NONE;
	
	_mem_timer.Start();
	
	while (1)
	{
		if ((_mem_timer.Ret_state() & F_Check_bit_bool(__UCSRA__, RXC)) == TRUE)	//受信完了
		{
			_mem_timer.Stop();
			
			_mem_uart_r_flag_state = EU_SUCCE;
			
			break;
		}
		
		if (_mem_timer.Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag_state = EU_ERROR;
			
			break;
		}
	}
}

T_DATA 
C_UART_R::
In (BOOL _arg_nf_auto_cut = TRUE)
{
	if (_arg_nf_auto_cut)
	{
		Check_in(); //受信チェック
		
		if (_mem_uart_r_flag_state == EU_ERROR)	return IN_ERROR;	//受信失敗
	}
	else
	{
		_mem_uart_r_flag_state = EU_NONE;
		
		__UCSRB__ |= (1 << RXEN); //受信許可
		
		while ( ! (__UCSRA__ & (1 << RXC)));
	}
	
	T_DATA _ret_in_data = 0;
	
	if (__UCSRA__ & ((1 << FE) | (1 << DOR) | (1 << UPE)))
	{
		_mem_uart_r_flag_state = EU_ERROR;
		
		_ret_in_data = __UDR__;
		
		return __UCSRA__;
	}
	else
	{
		T_DATA _ret_in_data_9 = 0;
		
		if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data_9 = (1 << 8);	//9bit通信時
			
		_ret_in_data = __UDR__;
		
		_ret_in_data |= _ret_in_data_9;
	}
	
	return _ret_in_data;
}

inline E_UART_FLAG 
C_UART_R :: 
Ret_state()
{
	return _mem_uart_r_flag_state;
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
	_arg_uart_r.Set_bit9(FALSE);
	_arg_uart_data_in = (T_DATA_8 )_arg_uart_r.In();
}

bool 
operator == 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_r_flag_comp
)
{	
	if (_arg_uart_r._mem_uart_r_flag_state == _arg_uart_r_flag_comp)	return true;
	
	return false;
}

bool 
operator != 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}