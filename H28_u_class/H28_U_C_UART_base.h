
#pragma once

class C_UART_base
{
protected:

#if defined(_AVR_IOM640_H_)
	E_UART_ADDR _mem_uart_base_addr :9;	//レジスタ用のアドレス
#elif defined(_AVR_IOM164_H_)
	E_UART_ADDR _mem_uart_base_addr :8;
#endif

#	define UCSRA _SFR_MEM8(_mem_uart_base_addr + 0)
#	define UCSRB _SFR_MEM8(_mem_uart_base_addr + 1)
#	define UCSRC _SFR_MEM8(_mem_uart_base_addr + 2)
#	define UBRRL _SFR_MEM8(_mem_uart_base_addr + 4)
#	define UBRRH _SFR_MEM8(_mem_uart_base_addr + 5)
#	define UDR	 _SFR_MEM8(_mem_uart_base_addr + 6)

	void Set(E_UART_ADDR );

public:

	C_UART_base()	{}
	C_UART_base(E_UART_ADDR _arg_uart_addr);
	
	void Set_bit9(BOOL );
	BOOL Ret_bit9();
};

#include "H28_U_C_UART_base.cpp"