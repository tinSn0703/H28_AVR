
/*
UART�n�̃N���X��֐����g�����߂̃}�N����typdef
 H28 05 18 ver0.0.0
*/

#pragma once

#ifndef _H28_AVR_H_
#	error "Include <H28_AVR.h>"
#endif

#include "H28_i_macro.h"
#include "H28_t_macro.h"

//UART
typedef unsigned char T_DATA_8;
typedef unsigned short int T_DATA;

#define IN_ERROR 0xfff 
//���̃}�N����12bit�ȏ�Ȃ��Ǝg���Ȃ�����ȋC��t�����Bby H28 May 13��Sn


enum E_UART_FLAG
//UART FLAG COMAND
{
	EU_NONE  = 0,	
	EU_SUCCE = 1,	//��M����
	EU_ERROR = 2,	//��M���s
};

#if _H28_AVR_H_ == 640
enum E_UART_ADDR
//UART NUMBER SET COMAND
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
	EU_UART2 = 0xd0,
	EU_UART3 = 0x130,
};
#elif _H28_AVR_H_ == 164
enum E_UART_ADDR
//UART NUMBER SET COMAND
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
};
#endif

enum E_UART_MODE
//UART MODE SET COMAND
{
	EU_TRA  = 0, //���M
	EU_REC  = 1, //��M
};

//bit UCSRA
#define RXC  7
#define TXC	 6
#define UDRE 5
#define FE	 4
#define DOR  3
#define UPE  2
#define U2X  1
#define MPCM 0

//bit UCSRB
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0

//bit UCSRC
#define UMSEL1 7
#define UMSEL0 6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

#include "H28_u_class/H28_u_class.h"