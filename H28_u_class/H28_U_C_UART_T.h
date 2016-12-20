
/*
送信を行うUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_base.h"

/*************************************************************************

 UARTを送信モードで操作するためのクラス

*************************************************************************/

class C_UART_T : public virtual C_UART_base
{
	
public:
	
#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)
	
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

#elif defined(_AVR_IOM88_H_)
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 初期設定を行う。詳細はC_UART_base参照
	 * 
	 * \param _arg_uart_nf_isr : 送信データレジスタ空き割り込みのONOFF
	 */
	C_UART_T(BOOL _arg_uart_nf_isr);

#endif
	
	/**
	 * \brief	送信データレジスタ空き割り込みの設定 
	 *
	 * \param _arg_uart_nf_isr : ONOFFの設定
	 */
	void Reset_isr(BOOL _arg_uart_nf_isr);
	
//	void Out (int _arg_uart_data_out);
	
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
	 * \brief	C_UART_T::Out()の演算子ver 
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

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

C_UART_T ::
C_UART_T
(
	const E_UART_ADDR	_arg_uart_addr,
	const BOOL			_arg_uart_nf_isr = FALSE
)
: C_UART_base(_arg_uart_addr)
{
	Reset_isr(_arg_uart_nf_isr);
}

#elif defined(_AVR_IOM88_H_)

C_UART_T ::
C_UART_T (const BOOL _arg_uart_nf_isr = FALSE)
: C_UART_base()
{
	Reset_isr(_arg_uart_nf_isr);
}

#endif

inline void
C_UART_T ::
Reset_isr (const BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	__UCSRB__ |=  (1 << UDRIE);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << UDRIE);	break; //Off
	}
}

void
C_UART_T ::
Out (const T_DATA _arg_uart_data_out)
{
	__UCSRB__ |= (1 << TXEN); //送信許可する。
	
	while (!(__UCSRA__ & (1 << UDRE))); //送信が可能になるまで待機
	
	if ((C_UART_base :: Ret_nf_bit9() & F_Check_bit_bool(_arg_uart_data_out, 8)) == TRUE)
	{
		__UCSRB__ |= (1 << TXB8);	//8bit目の送信
	}

	__UDR__ = (_arg_uart_data_out & 0xff);
	
	while (!(__UCSRA__ & (1 << TXC))); //送信完了まで待機
	
	__UCSRA__ |= (1 << TXC);
}

void
C_UART_T ::
Out (const T_DATA_8 _arg_uart_data_out)
{
	__UCSRB__ |= (1 << TXEN); //送信許可する。
	
	while (!(__UCSRA__ & (1 << UDRE))); //送信が可能になるまで待機

	__UDR__ = _arg_uart_data_out;
	
	while (!(__UCSRA__ & (1 << TXC))); //送信完了まで待機
	
	__UCSRA__ |= (1 << TXC);
}

inline void
operator <<
(
	C_UART_T		&_arg_uart_t,
	const T_DATA	 _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}

inline void
operator <<
(
	C_UART_T		&_arg_uart_t,
	const T_DATA_8	 _arg_uart_data_out
)
{
	_arg_uart_t.Out(_arg_uart_data_out);
}