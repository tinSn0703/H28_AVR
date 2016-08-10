
#pragma once

/**
 * 受信を扱うための構造体。使うときは絶対に関数を通せ
 */
typedef struct
{

#if defined(_AVR_IOM640_H_)
	E_UART_ADDR _mem_uart_addr :9;
#elif defined(_AVR_IOM164_H_)
	E_UART_ADDR _mem_uart_addr :8;
#endif

	E_UART_MODE _mem_uart_mode :1;

	E_UART_FLAG _mem_uart_flag :2;
}
S_UART;

inline void
S_UART_set 
(
	S_UART *_arg_uart,
	E_UART_ADDR _arg_uart_addr,
	E_UART_MODE _arg_uart_mode
)
{	
	_arg_uart->_mem_uart_addr = _arg_uart_addr;
	
	_arg_uart->_mem_uart_mode = _arg_uart_mode;
	
	_arg_uart->_mem_uart_flag = EU_NONE;
	
	F_uart_set(_arg_uart_addr);
}

inline void 
S_UART_R_set 
(
	S_UART *_arg_uart_r,
	E_UART_ADDR _arg_uart_addr
)
{
	_arg_uart_r->_mem_uart_addr = _arg_uart_addr;
	
	_arg_uart_r->_mem_uart_mode = EU_REC;
	
	_arg_uart_r->_mem_uart_flag = EU_NONE;
	
	F_uart_set(_arg_uart_addr);
}

inline void
S_UART_T_set
(
	S_UART *_arg_uart_t,
	E_UART_ADDR _arg_uart_addr
)
{
	_arg_uart_t->_mem_uart_addr = _arg_uart_addr;
	
	_arg_uart_t->_mem_uart_mode = EU_TRA;
	
	_arg_uart_t->_mem_uart_flag = EU_NONE;
	
	F_uart_set(_arg_uart_addr);
}

inline void 
S_UART_isr
(
	const S_UART *_arg_uart,
	BOOL _arg_uart_nf_isr
)
{
	F_uart_isr(_arg_uart->_mem_uart_addr, _arg_uart->_mem_uart_mode, _arg_uart_nf_isr);
}

inline void 
S_UART_isr_on (const S_UART *_arg_uart)
{
	F_uart_isr(_arg_uart->_mem_uart_addr, _arg_uart->_mem_uart_mode, TRUE);
}

inline void
S_UART_isr_off (const S_UART *_arg_uart)
{
	F_uart_isr(_arg_uart->_mem_uart_addr, _arg_uart->_mem_uart_mode, FALSE);
}

inline void 
S_UART_R_isr 
(
	const S_UART *_arg_uart_r,
	BOOL _arg_uart_nf_isr
)
{
	if (_arg_uart_r->_mem_uart_mode == EU_REC)
	{
		F_uart_isr(_arg_uart_r->_mem_uart_addr, EU_REC, _arg_uart_nf_isr);
	}
}

