
#pragma once

#include "H28_U_C_UART_base.h"

/**
 * UARTの送信を扱うクラス
 */
class C_UART_T : public virtual C_UART_base
{
public:

	/**
	 * \brief 
	 * 空のコンストラクタ。ほんとに何もしない
	 */
	C_UART_T() {}
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * 
	 * \param _aeg_uart_addr   : 使うUART
	 * \param _arg_uart_nf_isr : 送信データレジスタ空き割り込みのONOFF
	 */
	C_UART_T(E_UART_ADDR _aeg_uart_addr, BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 
	 *  : 送信データレジスタ空き割り込みの設定 
	 *
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 
	 * データを送信する。
	 * 連続で通信を行う場合は相手側にも処理があることを考えながらやってね
	 * 
	 * \param _arg_uart_data_out : 送信するデータ
	 */
	void Out(T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * データを送信する。
	 * 連続で通信を行う場合は相手側にも処理があることを考えながらやってね
	 * 8bit通信の時用
	 * 
	 * \param _arg_uart_data_out : 送信するデータ
	 */
	void Out(T_DATA_8 _arg_uart_data_out);
	
	/**
	 * \brief 
	 * C_UART_T::Out()の演算子ver 
	 *
	 * \param _arg_uart_t : みたまま
	 * \param _arg_uart_data_out : 送信するデータ
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * C_UART_T::Out()の演算子ver 
	 * 8bit通信の時用
	 *
	 * \param _arg_uart_t : みたまま
	 * \param _arg_uart_data_out : 送信するデータ
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA_8 _arg_uart_data_out);
};

#include "H28_U_C_UART_T.cpp"