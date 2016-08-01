
#pragma once

#include "H28_U_C_UART_base.h"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/**
 * UARTで受信を扱うクラス
 */
class C_UART_R : public virtual C_UART_base
{
private:

	C_TIMER_inside _mem_timer;

protected:
	
	E_UART_FLAG _mem_uart_r_flag :2; //最後の受信状態の記録
	
public:

	/**
	 * \brief 
	 * コンストラクタ
	 * 内部タイマの設定のみを行う
	 */
	C_UART_R();
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * あと内部タイマの設定も
	 * 
	 * \param _arg_uart_addr : 使うUART
	 * \param _arg_uart_nf_isr : 受信完了割り込みのONOFF
	 */
	C_UART_R(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr(BOOL );
	
	/**
	 * \brief 
	 * 受信ができるかを確認する。結果は_mem_uart_r_flagに格納されるので使うときにそっちを読んでほしい。
	 * 確認中はこの関数で停止します。
	 * 確認には最長で8ms程かかります
	 */
	void Check();
	
	/**
	 * \brief 受信する 
	 * 
	 * \return T_DATA : 受信したデータ
	 */
	T_DATA In();

	/**
	 * \brief 直前の受信状態をreturnする。
	 * 
	 * \return E_UART_FLAG
	 */
	E_UART_FLAG Ret_flag();
	
	/**
	 * \brief 
	 * C_UART_R::In()の演算子バージョン。
	 * 
	 * \param _arg_uart_r : みたまま
	 * \param _arg_uart_data_in : 受信データが書き込まれる場所
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R::In()の演算子バージョン。
	 * 8bit通信のとき用
	 * 
	 * \param _arg_uart_r : みたまま
	 * \param _arg_uart_data_in : 受信データが書き込まれる場所
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if文などでの受信状態の比較用
	 * C_UART_R::Check()のあとで使って
	 * 
	 * \param _arg_uart_r : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しいときtrue
	 */
	friend bool operator == (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if文などでの受信状態の比較用
	 * C_UART_R::Check()のあとで使って
	 * 
	 * \param _arg_uart_r : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しくないときtrue
	 */
	friend bool operator != (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R.cpp"