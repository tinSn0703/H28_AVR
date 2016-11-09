
#pragma once

#include "H28_u_func.h"

inline void 
F_Uart_set (E_UART_ADDR _arg_uart_addr)
{
	__UBRRH_F(_arg_uart_addr) = 0x00;
	__UBRRL_F(_arg_uart_addr) = 0x04;
	
	__UCSRA_F(_arg_uart_addr) = (1<<U2X);
	
	__UCSRB_F(_arg_uart_addr) &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	
	__UCSRC_F(_arg_uart_addr) = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
}

inline void 
F_Uart_set_detail
(
	E_UART_ADDR _arg_uart_addr, 
	T_DATA _arg_bps, 
	E_UART_PARITY _arg_parity
)
{
	__UBRRH_F(_arg_uart_addr) = ((_arg_bps >> 8) & 0xff);
	__UBRRL_F(_arg_uart_addr) = (_arg_bps & 0xff);
	
	__UCSRA_F(_arg_uart_addr) = (1<<U2X);
	
	__UCSRB_F(_arg_uart_addr) &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	
	__UCSRC_F(_arg_uart_addr) = ((_arg_parity << UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
}

inline void 
F_Uart_set_bit9
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
F_Uart_set_bit9_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |=  (1 << UCSZ2);
}

inline void
F_Uart_set_bit9_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &=  ~(1 << UCSZ2);
}

inline void 
F_Uart_set_isr
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
F_Uart_set_isr_u_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << UDRIE);
}

inline void
F_Uart_set_isr_r_on (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << RXCIE);
}

inline void
F_Uart_set_isr_u_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &= ~(1 << UDRIE);
}

inline void
F_Uart_set_isr_r_off (E_UART_ADDR _arg_uart_addr)
{
	__UCSRB_F(_arg_uart_addr) &= ~(1 << RXCIE);
}

void 
F_Uart_out
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
}

void 
F_Uart_out_8
(
	E_UART_ADDR _arg_uart_addr, 
	T_DATA_8 _arg_uart_out_data
)
{
	__UCSRB_F(_arg_uart_addr) |= (1 << TXEN); //���M������B
	
	while (!(__UCSRA_F(_arg_uart_addr) & (1 << UDRE))); //���M���\�ɂȂ�܂őҋ@

	__UDR_F(_arg_uart_addr) = _arg_uart_out_data;
}

E_UART_FLAG 
F_Uart_in 
(
	E_UART_ADDR _arg_uart_addr,
	T_DATA *_arg_uart_in_data
)
{
	while(!(__UCSRA_F(_arg_uart_addr) & (1 << RXC)));
	
	if (__UCSRA_F(_arg_uart_addr) & ((1 << FE) | (1 << DOR) | (1 << UPE)))
	{
		*_arg_uart_in_data = __UDR_F(_arg_uart_addr);
		*_arg_uart_in_data = __UCSRA_F(_arg_uart_addr);
		
		return EU_ERROR;
	}
	else
	{
		if (__UCSRB_F(_arg_uart_addr) & ((1<<UCSZ2) | (1<<RXB8)))
		{
			*_arg_uart_in_data = (1 << 8);	//9bit�ʐM��
		}
		
		*_arg_uart_in_data |= __UDR_F(_arg_uart_addr);
		
		return EU_SUCCE;
	}
	
	return EU_NONE;
}

E_UART_FLAG 
F_Uart_in_8 
(
	E_UART_ADDR _arg_uart_addr,
	T_DATA_8 *_arg_uart_in_data
)
{
	while(!(__UCSRA_F(_arg_uart_addr) & (1 << RXC)));
	
	if (__UCSRA_F(_arg_uart_addr) & ((1 << FE) | (1 << DOR) | (1 << UPE)))
	{
		*_arg_uart_in_data = __UDR_F(_arg_uart_addr);
		*_arg_uart_in_data = __UCSRA_F(_arg_uart_addr);
		
		return EU_ERROR;
	}
	else
	{		
		*_arg_uart_in_data = __UDR_F(_arg_uart_addr);
		
		return EU_SUCCE;
	}
	
	return EU_NONE;
}

