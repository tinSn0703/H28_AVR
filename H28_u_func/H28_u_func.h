
#pragma once

#ifdef __cplusplus
	extern "C" {
#endif

#define __UCSRA_F(_def_addr)	_SFR_MEM8(_def_addr + 0)
#define __UCSRB_F(_def_addr)	_SFR_MEM8(_def_addr + 1)
#define __UCSRC_F(_def_addr)	_SFR_MEM8(_def_addr + 2)
#define __UBRRL_F(_def_addr)	_SFR_MEM8(_def_addr + 4)
#define __UBRRH_F(_def_addr)	_SFR_MEM8(_def_addr + 5)
#define __UDR_F(_def_addr)		_SFR_MEM8(_def_addr + 6)

/**
 * \brief 
 * UARTの初期設定を行う
 * 250[kbps]
 * 倍速許可
 * 奇数パリティ
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_set(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 
 * 
 * \param _arg_uart_addr : 設定するUART
 * \param _arg_uart_nf_bit9 :
 */
void F_uart_bit9(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_bit9);

void F_uart_bit9_on(E_UART_ADDR _arg_uart_addr);

void F_uart_bit9_off(E_UART_ADDR _arg_uart_addr);

void F_uart_isr(E_UART_ADDR _arg_uart_addr, E_UART_MODE _arg_uart_mode, BOOL _arg_uart_nf_isr);

void F_uart_t_isr_on(E_UART_ADDR _arg_uart_addr);

void F_uart_r_isr_on(E_UART_ADDR _arg_uart_addr);

void F_uart_t_isr_off(E_UART_ADDR _arg_uart_addr);

void F_uart_r_isr_off(E_UART_ADDR _arg_uart_addr);

void F_uart_out(E_UART_ADDR _arg_uart_addr, T_DATA _arg_uart_out_data);

void F_uart_out_8(E_UART_ADDR _arg_uart_addr, T_DATA_8 _arg_uart_out_data);

T_DATA F_uart_in(E_UART_ADDR _arg_uart_addr);

T_DATA_8 F_uart_in_8(E_UART_ADDR _arg_uart_addr);

#include "H28_u_func.c"

#ifdef __cplusplus
}
#endif