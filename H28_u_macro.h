
/*
UART系のクラスや関数を使うためのマクロやtypdef
 H28 05 18 ver0.0.0
*/

#pragma once

#ifndef _H28_AVR_H_
#	error "Include <H28_AVR.h>"
#endif

#define IN_ERROR 0xfff

enum E_UART_FLAG
{
	EU_NONE  = 0,	
	EU_SUCCE = 1,	//受信成功
	EU_ERROR = 2,	//受信失敗
};

#ifndef _AVR_IOM88_H_

enum E_UART_ADDR
{
	
#if defined(_AVR_IOM640_H_)

	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
	EU_UART2 = 0xd0,
	EU_UART3 = 0x130,

#elif defined(_AVR_IOM164_H_)

	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,

#endif
	
};

#endif

enum E_UART_MODE
{
	EU_TRA  = 0, //送信
	EU_REC  = 1, //受信
};

//bit UCSRA
#define RXC  7		//受信完了フラグ
#define TXC	 6		//送信完了フラグ
#define UDRE 5		//送信データ空きレジスタフラグ
#define FE	 4		//フレーミング異常フラグ
#define DOR  3		//データオーバーランフラグ
#define UPE  2		//パリティ誤りフラグ
#define U2X  1		//倍速許可
#define MPCM 0		//複数プロセッサ通信動作

//bit UCSRB
#define RXCIE 7		//受信完了割り込み許可
#define TXCIE 6		//送信完了割り込み許可
#define UDRIE 5		//送信データレジスタ空き割り込み許可
#define RXEN  4		//受信許可
#define TXEN  3		//送信許可
#define UCSZ2 2		//データビット長選択2
#define RXB8  1		//受信データビット8
#define TXB8  0		//送信データビット8

//bit UCSRC
#define UMSEL1 7	//USART動作選択1
#define UMSEL0 6	//USART動作選択0
#define UPM1   5	//パリティ選択1
#define UPM0   4	//パリティ選択0
#define USBS   3	//停止ビット選択
#define UCSZ1  2	//データビット長選択1
#define UCSZ0  1	//データビット長選択0
#define UCPOL  0	//クロック極性選択

#ifndef __NOT_USE_FUNK_UART__
#include "H28_u_func/H28_u_func.h"
#endif

#include "H28_u_class/H28_u_class.h"