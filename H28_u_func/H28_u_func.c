
#pragma once

#include "H28_u_func.h"

inline void 
F_uart_set (E_UART_ADDR _arg_uart_addr)
{
	__UBRRH_F(_arg_uart_addr) = 0x00;
	__UBRRL_F(_arg_uart_addr) = 0x04;
	
	__UCSRA_F(_arg_uart_addr) = (1<<U2X);
	
	__UCSRB_F(_arg_uart_addr) &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	
	__UCSRC_F(_arg_uart_addr) = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
}

inline void 
F_uart_bit9
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_bit9
)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_F(_arg_uart_addr) |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_F(_arg_uart_addr) &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
F_uart_bit9_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |=  (1 << UCSZ2);
}

inline void
F_uart_bit9_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &=  ~(1 << UCSZ2);
}

inline void 
F_uart_isr
(
	E_UART_ADDR _arg_uart_addr, 
	E_UART_MODE _arg_uart_mode, 
	BOOL _arg_uart_nf_isr
)
{
	uchar _tenp_bit = 0;
	
	switch (_arg_uart_mode)
	{
		case EU_REC:	_tenp_bit = RXCIE;	break;
		case EU_TRA:	_tenp_bit = UDRIE;	break;
	}
	
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB_F(_arg_uart_addr) |=  (1 << _tenp_bit);	break; //On
		case FALSE:	__UCSRB_F(_arg_uart_addr) &= ~(1 << _tenp_bit);	break; //Off
	}
}

inline void 
F_uart_t_isr_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << UDRIE);
}

inline void
F_uart_r_isr_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << RXCIE);
}

inline void
F_uart_t_isr_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &= ~(1 << UDRIE);
}

inline void
F_uart_r_isr_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &= ~(1 << RXCIE);
}

void 
F_uart_out
(
	E_UART_ADDR _arg_uart_addr, 
	T_DATA _arg_uart_out_data
)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << TXEN); //���M������B
	
	while (!(__UCSRA_F(_arg_uart_addr) & (1 << UDRE))); //���M���\�ɂȂ�܂őҋ@
	
	if ((CHECK_BIT_TF(__UCSRB_F(_arg_uart_addr),UCSZ2) & CHECK_BIT_TF(_arg_uart_out_data,8)) == TRUE)
	{
		__UCSRB_F(_arg_uart_addr) |= (1 << TXB8);
	}

	__UDR_F(_arg_uart_addr) = (_arg_uart_out_data & 0xff);
	
	while (!(__UCSRA_F(_arg_uart_addr) & (1 << TXC))); //���M�����܂őҋ@
	
	__UCSRA_F(_arg_uart_addr) |= (1 << TXC);
}

void 
F_uart_out_8
(
	E_UART_ADDR _arg_uart_addr, 
	T_DATA_8 _arg_uart_out_data
)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << TXEN); //���M������B
	
	while (!(__UCSRA_F(_arg_uart_addr) & (1 << UDRE))); //���M���\�ɂȂ�܂őҋ@

	__UDR_F(_arg_uart_addr) = (_arg_uart_out_data & 0xff);
	
	while (!(__UCSRA_F(_arg_uart_addr) & (1 << TXC))); //���M�����܂őҋ@
	
	__UCSRA_F(_arg_uart_addr) |= (1 << TXC);
}

T_DATA 
F_uart_in (E_UART_ADDR _arg_uart_addr)
{
	T_DATA _ret_data = 0;
	
	while(!(__UCSRA_F(_arg_uart_addr) & (1 << RXC)));
	
	if (__UCSRB_F(_arg_uart_addr) & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_data = (1 << 8);	//9bit�ʐM��
	}
	
	_ret_data |= __UDR_F(_arg_uart_addr);
	
	return _ret_data;
}

T_DATA_8 
F_uart_in_8 (E_UART_ADDR _arg_uart_addr)
{
	T_DATA_8 _ret_data = 0;
	
	while(!(__UCSRA_F(_arg_uart_addr) & (1 << RXC)));
	
	_ret_data |= __UDR_F(_arg_uart_addr);
	
	return _ret_data;
}

