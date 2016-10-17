
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

typedef enum
{
	EU_NON  = 0b00,	//パリティ禁止
	EU_EVEN = 0b10,	//偶数パリティ
	EU_ODD  = 0b11	//奇数パリティ
}
E_UART_PARITY; 

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
 * UARTの初期設定を行う
 * 倍速許可
 * bpsは_arg_bpsから
 * パリティについては_arg_parityから 
 *
 * \param _arg_uart_addr : 設定するUART
 * \param _arg_bps		 : 値はデータシート参照
 * \param _arg_parity	 : 禁止、偶数パリティ、奇数パリティから
 */
void F_uart_set_detail(E_UART_ADDR _arg_uart_addr, T_DATA _arg_bps, E_UART_PARITY _arg_parity);

/**
 * \brief 9bit通信の設定を行う
 * 
 * \param _arg_uart_addr : 設定するUART
 * \param _arg_uart_nf_bit9 : ON/OFF
 */
void F_uart_bit9(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_bit9);

/**
 * \brief 9bit通信をONにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_bit9_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 9bit通信をOFFにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_bit9_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 割り込み処理の設定
 * 
 * \param _arg_uart_addr : 設定するUART
 * \param _arg_uart_mode
 *		EM_REC -> 受信完了割り込み
 *		EM_TRA -> 送信データレジスタ空き割り込み
 *
 * \param _arg_uart_nf_isr : ON/OFF
 */
void F_uart_isr(E_UART_ADDR _arg_uart_addr, E_UART_MODE _arg_uart_mode, BOOL _arg_uart_nf_isr);

/**
 * \brief 送信データレジスタ空き割り込みをONにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_t_isr_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 受信完了割り込みをONにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_r_isr_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 送信データレジスタ空き割り込みをOFFにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_t_isr_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 受信完了割り込みをOFFにする
 * 
 * \param _arg_uart_addr : 設定するUART
 */
void F_uart_r_isr_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 送信する
 * 
 * \param _arg_uart_addr : 使うUART
 * \param _arg_uart_out_data : 送信するデータ
 */
void F_uart_out(E_UART_ADDR _arg_uart_addr, T_DATA _arg_uart_out_data);

/**
 * \brief 送信する。8bit通信の時用。確認とかはしてないから気を付けてね
 *
 * \param _arg_uart_addr : 使うUART
 * \param _arg_uart_out_data : 送信するデータ
 */
void F_uart_out_8(E_UART_ADDR _arg_uart_addr, T_DATA_8 _arg_uart_out_data);

/**
 * \brief 受信する
 * 
 * \param _arg_uart_addr : 使うUART
 * 
 * \return T_DATA 受信したデータ
 */
E_UART_FLAG F_uart_in(E_UART_ADDR _arg_uart_addr, T_DATA *_arg_uart_in_data);

/**
 * \brief 受信する。8bit通信の時用
 * 
 * \param _arg_uart_addr : 使うUART
 * 
 * \return T_DATA_8 受信したデータ
 */
E_UART_FLAG F_uart_in_8(E_UART_ADDR _arg_uart_addr, T_DATA_8 *_arg_uart_in_data);

#include "H28_u_func.c"

#include "H28_U_S_UART.h"

#ifdef __cplusplus
}
#endif