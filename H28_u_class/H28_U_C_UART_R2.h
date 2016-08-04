
#pragma once

#include "H28_U_C_UART_base.h"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

class C_UART_R2 : protected C_UART_base
{
private:
	
	C_TIMER_inside _mem_timer;
	
	E_UART_FLAG _mem_uart_r2_flag :2;
	T_NUM _mem_uart_r2_num :1;
	
protected:

	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//レジスタ用のアドレス
	
#	define __UCSRA_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 0)
#	define __UCSRB_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 1)
#	define __UCSRC_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 2)
#	define __UBRRL_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 4)
#	define __UBRRH_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 5)
#	define __UDR_0__	_SFR_MEM8(_mem_arr_uart_r2_addr[0] + 6)
	
#	define __UCSRA_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 0)
#	define __UCSRB_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 1)
#	define __UCSRC_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 2)
#	define __UBRRL_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 4)
#	define __UBRRH_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 5)
#	define __UDR_1__	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 6)
	
public:
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 内部タイマの設定のみを行う
	 */
	C_UART_R2();
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * あと内部タイマの設定も
	 * 
	 * \param _arg_uart_addr : 使うUART
	 * \param _arg_uart_nf_isr : 受信完了割り込みのONOFF
	 */
	C_UART_R2(E_UART_ADDR _arg_uart_addr_0, E_UART_ADDR _arg_uart_addr_1, BOOL _arg_uart_nf_isr_0, BOOL _arg_uart_nf_isr_1);
	
	/**
	 * \brief 0番の受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr_0(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 1番の受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr_1(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 0番の9nit通信のONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFFの設定
	 */
	void Set_bit9_0(BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 0番の9nit通信のONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFFの設定
	 */
	void Set_bit9_1(BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 
	 * 受信ができるかを確認する。結果は_mem_uart_r2_flagに格納されるので使うときにそっちを読んでほしい。
	 * In()は自動的に、先に成功したほうで行われます。
	 * 確認中はこの関数で停止します。
	 * 確認には最長で8ms程かかります
	 */
	void Check();
	
	/**
	 * \brief 
	 * 受信する
	 * Check()で成功したほうを用いる 
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
	 * C_UART_R2::In()の演算子バージョン。
	 * 
	 * \param _arg_uart_r2 : みたまま
	 * \param _arg_uart_data_in : 受信データが書き込まれる場所
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R2::In()の演算子バージョン。
	 * 8bit通信のとき用
	 * 
	 * \param _arg_uart_r2 : みたまま
	 * \param _arg_uart_data_in : 受信データが書き込まれる場所
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if文などでの受信状態の比較用
	 * C_UART_R2::Check()のあとで使って
	 * 
	 * \param _arg_uart_r2 : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しいときtrue
	 */
	friend bool operator == (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if文などでの受信状態の比較用
	 * C_UART_R2::Check()のあとで使って
	 * 
	 * \param _arg_uart_r2 : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しくないときtrue
	 */
	friend bool operator != (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R2.cpp"