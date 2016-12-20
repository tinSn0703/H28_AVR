
/*
最初から２線通信を想定したUART系のクラス
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 通信を二線通信のみにした。
 H28 05 23 ver1.0.0 C_UART_baseの派生クラスにした。それにともなって色々変えた。
 H28 05 24 ver1.1.0 Set_base_addrを多用するのはやめた。マクロ追加した。
*/

#pragma once

#include "H28_U_C_UART_base.h"

#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/*************************************************************************

UARTを2線同時受信モードで操作するためのクラス

*************************************************************************/

class C_UART_R2 : protected C_UART_base
{
	
private:
	
	C_TIMER_inside _mem_timer;
	
	E_UART_FLAG _mem_uart_r2_flag_state :2;
	T_NUM		_mem_uart_r2_num_seccess :1;
	
	BOOL _mem_uart_r2_flag_priority0 :1;
	BOOL _mem_uart_r2_flag_priority1 :1;
	
	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//レジスタのアドレス
	
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
	C_UART_R2 ();
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * あと内部タイマの設定も
	 * 
	 * \param _arg_uart_addr : 使うUART
	 * \param _arg_uart_nf_isr : 受信完了割り込みのONOFF
	 */
	C_UART_R2 (E_UART_ADDR _arg_uart_addr_0, E_UART_ADDR _arg_uart_addr_1, BOOL _arg_uart_nf_isr_0, BOOL _arg_uart_nf_isr_1);
	
	/**
	 * \brief 0番の受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr_0 (BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 1番の受信完了割り込みのONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Set_isr_1 (BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 0番の9nit通信のONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFFの設定
	 */
	void Set_bit9_0 (BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 1番の9nit通信のONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFFの設定
	 */
	void Set_bit9_1 (BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 
	 * 受信ができるかを確認する。結果は_mem_uart_r2_flagに格納されるので使うときにそっちを読んでほしい。
	 * In()は自動的に、先に成功したほうで行われます。
	 * 確認中はこの関数で停止します。
	 * 確認には最長で8ms程かかります
	 */
	void Check_in ();
	
	/**
	 * \brief 
	 * 受信する
	 * Check_in()で成功したほうを用いる 
	 * 
	 * \param _arg_nf_auto_cut : 自動で通信の確認を終了するかどうか
	 *
	 * \return T_DATA : 受信したデータ
	 */
	T_DATA In (BOOL _arg_nf_auto_cut);
	
	/**
	 * \brief 直前の受信状態をreturnする。
	 */
	E_UART_FLAG Ret_flag ();
	
	/**
	 * \brief C_UART_R2::In()の演算子バージョン。
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
	 * C_UART_R2::Check_in()のあとで使って
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
	 * C_UART_R2::Check_in()のあとで使って
	 * 
	 * \param _arg_uart_r2 : みたまま
	 * \param _arg_uart_flag_comp : 比較するやつ
	 * 
	 * \return bool 等しくないときtrue
	 */
	friend bool operator != (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
};

/************************************************************************/

inline
C_UART_R2 ::
C_UART_R2 ()
: _mem_timer(200)
{
	_mem_uart_r2_flag_state = EU_NONE;
	
	_mem_uart_r2_flag_priority0 = TRUE;
	_mem_uart_r2_flag_priority1 = TRUE;
}


inline
C_UART_R2::
C_UART_R2
(
	const E_UART_ADDR	_arg_uart_addr_0,
	const E_UART_ADDR	_arg_uart_addr_1,
	const BOOL			_arg_uart_nf_isr_0 = FALSE,
	const BOOL			_arg_uart_nf_isr_1 = FALSE
)
: _mem_timer(80)
{
	_mem_arr_uart_r2_addr[0] = _arg_uart_addr_0;
	_mem_arr_uart_r2_addr[1] = _arg_uart_addr_1;
	
	C_UART_base::Set(_arg_uart_addr_0);
	C_UART_base::Set(_arg_uart_addr_1);
	
	Set_isr_0(_arg_uart_nf_isr_0);
	Set_isr_1(_arg_uart_nf_isr_1);
	
	_mem_uart_r2_flag_state = EU_NONE;
	
	_mem_uart_r2_flag_priority0 = TRUE;
	_mem_uart_r2_flag_priority1 = TRUE;
}

inline void
C_UART_R2::
Set_isr_0 (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB_0__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB_0__ &= ~(1 << RXCIE);	break; //Off
	}
}

inline void
C_UART_R2::
Set_isr_1 (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB_1__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB_1__ &= ~(1 << RXCIE);	break; //Off
	}
}

inline void
C_UART_R2::
Set_bit9_0 (const BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_0__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_0__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void
C_UART_R2::
Set_bit9_1 (const BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB_1__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB_1__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void
C_UART_R2::
Check_in ()
//受信しなかった方を受信禁止にしたらうまくいった。
{
	__UCSRB_0__ |= (1 << RXEN);
	__UCSRB_1__ |= (1 << RXEN);
	
	_mem_timer.Start();
	
	while (1)
	{
		if (F_Check_bit_bool(__UCSRA_0__, RXC) & _mem_uart_r2_flag_priority0 & _mem_timer.Ret_state())	//UART0受信完了
		{
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 0;
			
			_mem_uart_r2_flag_priority1 = FALSE;
			
			break;
		}
		
		if (F_Check_bit_bool(__UCSRA_1__, RXC) & _mem_uart_r2_flag_priority1 & _mem_timer.Ret_state())	//UART1受信完了
		{
			__UCSRB_0__ &= ~(1 << RXEN);
			
			_mem_uart_r2_num_seccess = 1;
			
			_mem_uart_r2_flag_priority0 = FALSE;
			
			break;;
		}
		
		if (_mem_timer.Check())	//カウント完了(タイムアウト)
		{
			__UCSRB_0__ &= ~(1 << RXEN);
			__UCSRB_1__ &= ~(1 << RXEN);
			
			_mem_uart_r2_flag_state = EU_ERROR;
			
			_mem_uart_r2_flag_priority0 = TRUE;
			_mem_uart_r2_flag_priority1 = TRUE;
			
			return (void)0;
		}
	}
	
	_mem_timer.Stop();
	
	_mem_uart_r2_flag_state = EU_SUCCE;
}

T_DATA
C_UART_R2::
In (const BOOL _arg_nf_auto_cut = TRUE)
{
	if (_arg_nf_auto_cut)
	{
		Check_in();
		
		if (_mem_uart_r2_flag_state == EU_ERROR)	return IN_ERROR;
	}
	else
	{
		__UCSRB_0__ |= (1 << RXEN);
		__UCSRB_1__ |= (1 << RXEN);
		
		while (1)
		{
			if (__UCSRA_0__ & (1 << RXC))	_mem_uart_r2_num_seccess = 0;	break;
			if (__UCSRA_1__ & (1 << RXC))	_mem_uart_r2_num_seccess = 1;	break;
		}
	}
	
	T_DATA _ret_data_in = 0;
	
	_mem_uart_base_addr = _mem_arr_uart_r2_addr[_mem_uart_r2_num_seccess];	//受信成功したポートにする
	
	if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_data_in |= (1 << 8);	//9bit通信時
	}
	
	_ret_data_in |= __UDR__;
	
	return _ret_data_in;
}

inline E_UART_FLAG
C_UART_R2 ::
Ret_flag ()
{
	return _mem_uart_r2_flag_state;
}

void
operator >>
(
	C_UART_R2	&_arg_uart_r2,
	T_DATA		&_arg_uart_data_in
)
{
	_arg_uart_data_in = _arg_uart_r2.In();
}

void
operator >>
(
	C_UART_R2	&_arg_uart_r2,
	T_DATA_8	&_arg_uart_data_in
)
{
	_arg_uart_data_in = (T_DATA_8)_arg_uart_r2.In();
}

bool
operator ==
(
	C_UART_R2			&_arg_uart_r2,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag_state == _arg_uart_flag_comp)	return true;
	
	return false;
}

bool
operator !=
(
	C_UART_R2			&_arg_uart_r2,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r2._mem_uart_r2_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}

