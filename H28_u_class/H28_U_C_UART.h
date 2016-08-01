
#pragma once

#include "H28_U_C_UART_R.h"
#include "H28_U_C_UART_T.h"

class C_UART : public C_UART_R , public C_UART_T
{
protected:
	
	E_UART_MODE _mem_uart_mode :1;	//ÉÇÅ[ÉhÇÃãLò^
	
public:

	C_UART() {}
	C_UART(E_UART_ADDR ,E_UART_MODE ,BOOL);
	
	void Chan_mode(E_UART_MODE );
	
	void Set_isr(BOOL );
};

#include "H28_U_C_UART.cpp"