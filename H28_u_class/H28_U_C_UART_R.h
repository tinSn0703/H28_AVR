
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/


#pragma once

#include "H28_U_C_UART_base.h"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/*************************************************************************

UARTを受信モードで操作するためのクラス

*************************************************************************/


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
	void Reset_isr(BOOL _arg_uart_nf_isr);
	
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
	 * \param _arg_nf_auto_cut : 自動で通信を終了する機能の使用について
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

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

inline
C_UART_R ::
C_UART_R ()
: _mem_timer(80)
{
	_mem_uart_r_flag_state = EU_NONE;
}

inline
C_UART_R ::
C_UART_R
(
	const E_UART_ADDR	_arg_uart_addr,
	const BOOL			_arg_uart_nf_isr = FALSE
)
: C_UART_base(_arg_uart_addr)
, _mem_timer(80) //8ms
{
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#elif defined(_AVR_IOM88_H_)

inline
C_UART_R ::
C_UART_R (const BOOL _arg_uart_nf_isr = FALSE)
: C_UART_base()
, _mem_timer(80) //8ms
{
	Reset_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag_state = EU_NONE;
}

#endif

inline void
C_UART_R ::
Reset_isr (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB__ |=  (1 << RXCIE);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << RXCIE);	break; //Off
	}
}

void
C_UART_R ::
Check_in ()
{
	__UCSRB__ |= (1 << RXEN); //受信許可
	
	_mem_uart_r_flag_state = EU_NONE;
	
	_mem_timer.Start();
	
	while (1)
	{
		if ((_mem_timer.Ret_state() & F_Check_bit_bool(__UCSRA__, RXC)) == TRUE)	//受信完了
		{
			_mem_timer.Stop();
			
			_mem_uart_r_flag_state = EU_SUCCE;
			
			break;
		}
		
		if (_mem_timer.Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag_state = EU_ERROR;
			
			break;
		}
	}
}

T_DATA
C_UART_R ::
In (const BOOL _arg_nf_auto_cut = TRUE)
{
	if (_arg_nf_auto_cut)
	{
		Check_in(); //受信チェック
		
		if (_mem_uart_r_flag_state == EU_ERROR)	return IN_ERROR;	//受信失敗
	}
	else
	{
		_mem_uart_r_flag_state = EU_NONE;
		
		__UCSRB__ |= (1 << RXEN); //受信許可
		
		while ( ! (__UCSRA__ & (1 << RXC)));
	}
	
	T_DATA _ret_in_data = 0;
	
	if (__UCSRA__ & ((1 << FE) | (1 << DOR) | (1 << UPE)))
	{
		_mem_uart_r_flag_state = EU_ERROR;
		
		_ret_in_data = __UDR__;
		
		return __UCSRA__;
	}
	else
	{
		T_DATA _ret_in_data_9 = 0;
		
		if (__UCSRB__ & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data_9 = (1 << 8);	//9bit通信時
		
		_ret_in_data = __UDR__;
		
		_ret_in_data |= _ret_in_data_9;
	}
	
	return _ret_in_data;
}

inline E_UART_FLAG
C_UART_R ::
Ret_state()
{
	return _mem_uart_r_flag_state;
}

void
operator >>
(
	C_UART_R	&_arg_uart_r,
	T_DATA		&_arg_uart_data_in
)
{
	_arg_uart_data_in = _arg_uart_r.In();
}

void
operator >>
(
	C_UART_R &_arg_uart_r,
	T_DATA_8 &_arg_uart_data_in
)
{
	_arg_uart_r.Set_bit9(FALSE);
	_arg_uart_data_in = (T_DATA_8 )_arg_uart_r.In();
}

bool
operator ==
(
	C_UART_R			&_arg_uart_r,
	const E_UART_FLAG	 _arg_uart_r_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag_state == _arg_uart_r_flag_comp)	return true;
	
	return false;
}

bool
operator !=
(
	C_UART_R			&_arg_uart_r,
	const E_UART_FLAG	 _arg_uart_flag_comp
)
{
	if (_arg_uart_r._mem_uart_r_flag_state != _arg_uart_flag_comp)	return true;
	
	return false;
}