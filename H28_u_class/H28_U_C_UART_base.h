
#pragma once

/**
 * UART系の基底となるクラス
 */
class C_UART_base
{
protected:

#if defined(_AVR_IOM640_H_)
	E_UART_ADDR _mem_uart_base_addr :9;	//レジスタ用のアドレス
#elif defined(_AVR_IOM164_H_)
	E_UART_ADDR _mem_uart_base_addr :8;
#endif

#	define UCSRA _SFR_MEM8(_mem_uart_base_addr + 0)
#	define UCSRB _SFR_MEM8(_mem_uart_base_addr + 1)
#	define UCSRC _SFR_MEM8(_mem_uart_base_addr + 2)
#	define UBRRL _SFR_MEM8(_mem_uart_base_addr + 4)
#	define UBRRH _SFR_MEM8(_mem_uart_base_addr + 5)
#	define UDR	 _SFR_MEM8(_mem_uart_base_addr + 6)

	/**
	 * \brief コンストラクタの中身。
	 * 
	 * \param _arg_uart_addr : コンストラクタ参照
	 */
	void Set(E_UART_ADDR _arg_uart_addr);

public:

	/**
	 * \brief 空のコンストラクタ.何もしない
	 */
	C_UART_base()	{}
	
	/**
	 * \brief 
	 * コンストラクタ。UARTの初期設定を行う
	 *		250[kbps]
	 *		倍速許可
	 *		奇数パリティ
	 * 
	 * \param _arg_uart_addr : 使うUART
	 */
	C_UART_base(E_UART_ADDR _arg_uart_addr);
	
	/**
	 * \brief 
	 * 9bit通信の設定
	 * 8bitと9bitどうしではうまく通信できないので注意
	 *
	 * \param _arg_uart_nf_bit9 : ON/OFF
	 */
	void Set_bit9(BOOL _arg_uart_nf_bit9);
	
	
	/**
	 * \brief 
	 * 9bit通信が設定されているかの確認。
	 * 
	 * \return BOOL 
	 *		TRUE  -> 設定されている
	 *		FALES -> 設定されていない
	 */
	BOOL Ret_bit9();
};

#include "H28_U_C_UART_base.cpp"