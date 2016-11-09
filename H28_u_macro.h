
/*
UART�n�̃N���X��֐����g�����߂̃}�N����typdef
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
	EU_SUCCE = 1,	//��M����
	EU_ERROR = 2,	//��M���s
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
	EU_TRA  = 0, //���M
	EU_REC  = 1, //��M
};

//bit UCSRA
#define RXC  7		//��M�����t���O
#define TXC	 6		//���M�����t���O
#define UDRE 5		//���M�f�[�^�󂫃��W�X�^�t���O
#define FE	 4		//�t���[�~���O�ُ�t���O
#define DOR  3		//�f�[�^�I�[�o�[�����t���O
#define UPE  2		//�p���e�B���t���O
#define U2X  1		//�{������
#define MPCM 0		//�����v���Z�b�T�ʐM����

//bit UCSRB
#define RXCIE 7		//��M�������荞�݋���
#define TXCIE 6		//���M�������荞�݋���
#define UDRIE 5		//���M�f�[�^���W�X�^�󂫊��荞�݋���
#define RXEN  4		//��M����
#define TXEN  3		//���M����
#define UCSZ2 2		//�f�[�^�r�b�g���I��2
#define RXB8  1		//��M�f�[�^�r�b�g8
#define TXB8  0		//���M�f�[�^�r�b�g8

//bit UCSRC
#define UMSEL1 7	//USART����I��1
#define UMSEL0 6	//USART����I��0
#define UPM1   5	//�p���e�B�I��1
#define UPM0   4	//�p���e�B�I��0
#define USBS   3	//��~�r�b�g�I��
#define UCSZ1  2	//�f�[�^�r�b�g���I��1
#define UCSZ0  1	//�f�[�^�r�b�g���I��0
#define UCPOL  0	//�N���b�N�ɐ��I��

#ifndef __NOT_USE_FUNK_UART__
#include "H28_u_func/H28_u_func.h"
#endif

#include "H28_u_class/H28_u_class.h"