
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
	
	E_UART_FLAG _mem_uart_r_flag_state :2; //最後の受信状態の記録
	
public:
	
#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

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
	
#elif defined(_AVR_IOM88_H_)
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * あと内部タイマの設定も
	 * 
	 * \param _arg_uart_nf_isr : 受信完了割り込みのONOFF
	 */
	C_UART_R(BOOL _arg_uart_nf_isr);

#endif

	/**
	 * \brief 受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Reset_isr(BOOL );
	
	/**
	 * \brief 
	 * 受信ができるかを確認する。結果は_mem_uart_r_flagに格納されるので使うときにそっちを読んでほしい。
	 * Timerを用いて、一定時間で受信できなかった場合は、自動的に終了します
	 * 確認中はこの関数で停止します。
	 * 確認には最長で8ms程かかります
	 */
	void Check_in();
	
	/**
	 * \brief 受信
	 * 
	 * \param _arg_nf_auto_cut : 自動で通信を終了するかの使用について
	 *
	 * \return T_DATA : 受信したデータ
	 */
	T_DATA In(BOOL _arg_nf_auto_cut);

	/**
	 * \brief 受信状態をreturnする。
	 * 
	 * \return E_UART_FLAG
	 *	失敗	-> EU_ERROR
	 *	成功	-> EU_SUCCE
	 *	その他	-> EU_NONE
	 */
	E_UART_FLAG Ret_state();
	
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
	 * C_UART_R::Check_in()のあとで使って
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
	 * C_UART_R::Check_in()のあとで使って
	 * 
	 * \param _arg_uart_r : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しくないときtrue
	 */
	friend bool operator != (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R.cpp"