
/*
UART系の基底となるクラス。こいつは宣言しないでね
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 コンストラクタ消しといた。
*/

#pragma once

/*************************************************************************

UART系の基底となるクラス

*************************************************************************/

class C_UART_base
{
protected:

#if defined(_AVR_IOM640_H_)

	E_UART_ADDR _mem_uart_base_addr :9;	//レジスタ用のアドレス

#elif defined(_AVR_IOM164_H_)

	E_UART_ADDR _mem_uart_base_addr :8;

#endif

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)
#	define __UCSRA__ _SFR_MEM8(_mem_uart_base_addr + 0)
#	define __UCSRB__ _SFR_MEM8(_mem_uart_base_addr + 1)
#	define __UCSRC__ _SFR_MEM8(_mem_uart_base_addr + 2)
#	define __UBRRL__ _SFR_MEM8(_mem_uart_base_addr + 4)
#	define __UBRRH__ _SFR_MEM8(_mem_uart_base_addr + 5)
#	define __UDR__	 _SFR_MEM8(_mem_uart_base_addr + 6)
#elif defined(_AVR_IOM88_H_)
#	define __UCSRA__ _SFR_MEM8(0xc0)
#	define __UCSRB__ _SFR_MEM8(0xc1)
#	define __UCSRC__ _SFR_MEM8(0xc2)
#	define __UBRRL__ _SFR_MEM8(0xc4)
#	define __UBRRH__ _SFR_MEM8(0xc5)
#	define __UDR__	 _SFR_MEM8(0xc6)
#endif

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

	/**
	 * \brief コンストラクタの中身。
	 * 
	 * \param _arg_uart_addr : コンストラクタ参照
	 */
	void Set (E_UART_ADDR _arg_uart_addr);

public:
	
	C_UART_base ()	{}
	
	/**
	 * \brief 
	 * コンストラクタ。UARTの初期設定を行う
	 *		250[kbps]
	 *		倍速許可
	 *		奇数パリティ
	 * 
	 * \param _arg_uart_addr : 使うUART
	 */
	C_UART_base (E_UART_ADDR _arg_uart_addr);
	
#elif defined(_AVR_IOM88_H_)
	
public:
	
	/**
	 * \brief 
	 * コンストラクタ。UARTの初期設定を行う
	 *		250[kbps]
	 *		倍速許可
	 *		奇数パリティ
	 */
	C_UART_base ();
	
#endif

	/**
	 * \brief 
	 * 9bit通信の設定
	 * 8bitと9bitどうしではうまく通信できないので注意
	 *
	 * \param _arg_uart_nf_bit9 : ON/OFF
	 */
	void Set_bit9 (BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 
	 * 9bit通信をONにする
	 * 8bitと9bitどうしではうまく通信できないので注意
	 */
	void Set_bit9_on ();
	
	/**
	 * \brief 
	 * 9bit通信をOFFにする
	 * 8bitと9bitどうしではうまく通信できないので注意
	 */
	void Set_bit9_off ();
	
	/**
	 * \brief 9bit通信が設定されているかの確認。
	 * 
	 * \return BOOL 
	 *		TRUE  -> 設定されている
	 *		FALES -> 設定されていない
	 */
	BOOL Ret_nf_bit9 ();
};

/************************************************************************/
//protected

#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

inline void
C_UART_base ::
Set (const E_UART_ADDR _arg_uart_addr)
{
	_mem_uart_base_addr = _arg_uart_addr;
	
	__UBRRH__ = 0x00;
	__UBRRL__ = 0x04;
	//F_CPU = 10[MHz] 250[kbps]
	
	__UCSRA__ = (1<<U2X);
	//倍速許可
	
	__UCSRB__ &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	__UCSRC__ = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//奇数パリティ
}

/************************************************************************/
//public

inline C_UART_base ::
C_UART_base (const E_UART_ADDR _arg_uart_addr)
{
	Set(_arg_uart_addr);
};
#elif defined(_AVR_IOM88_H_)
//public member

inline C_UART_base ::
C_UART_base ()
{
	__UBRRH__ = 0x00;
	__UBRRL__ = 0x04;
	//F_CPU=10MHz 250kbps
	
	__UCSRA__ = (1<<U2X);
	//Double teransmission spead
	
	__UCSRB__ &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	__UCSRC__ = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//Odd parity mode_i
};
#endif

inline void
C_UART_base ::
Set_bit9 (const BOOL _arg_uart_nf_bit9)
{
	switch (_arg_uart_nf_bit9)
	{
		case TRUE:	__UCSRB__ |=  (1 << UCSZ2);	break; //On
		case FALSE:	__UCSRB__ &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void
C_UART_base ::
Set_bit9_on ()
{
	__UCSRB__ |=  (1 << UCSZ2);
}

inline void
C_UART_base ::
Set_bit9_off ()
{
	__UCSRB__ &= ~(1 << UCSZ2);
}

inline BOOL
C_UART_base ::
Ret_nf_bit9 ()
{
	return F_Check_bit_bool(__UCSRB__, UCSZ2);
}