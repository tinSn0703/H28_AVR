
#pragma once

#ifdef __cplusplus
	extern "C" {
#endif

#define __UCSRA_F(_def_addr)	_SFR_MEM8(_def_addr + 0)
#define __UCSRB_F(_def_addr)	_SFR_MEM8(_def_addr + 1)
#define __UCSRC_F(_def_addr)	_SFR_MEM8(_def_addr + 2)
#define __UBRRL_F(_def_addr)	_SFR_MEM8(_def_addr + 4)
#define __UBRRH_F(_def_addr)	_SFR_MEM8(_def_addr + 5)
#define __UDR_F(_def_addr)		_SFR_MEM8(_def_addr + 6)

typedef enum
{
	EU_NON  = 0b00,	//�p���e�B�֎~
	EU_EVEN = 0b10,	//�����p���e�B
	EU_ODD  = 0b11	//��p���e�B
}
E_UART_PARITY; 

/**
 * \brief 
 * UART�̏����ݒ���s��
 * 250[kbps]
 * �{������
 * ��p���e�B
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_set(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 
 * UART�̏����ݒ���s��
 * �{������
 * bps��_arg_bps����
 * �p���e�B�ɂ��Ă�_arg_parity���� 
 *
 * \param _arg_uart_addr : �ݒ肷��UART
 * \param _arg_bps		 : �l�̓f�[�^�V�[�g�Q��
 * \param _arg_parity	 : �֎~�A�����p���e�B�A��p���e�B����
 */
void F_uart_set_detail(E_UART_ADDR _arg_uart_addr, T_DATA _arg_bps, E_UART_PARITY _arg_parity);

/**
 * \brief 9bit�ʐM�̐ݒ���s��
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 * \param _arg_uart_nf_bit9 : ON/OFF
 */
void F_uart_bit9(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_bit9);

/**
 * \brief 9bit�ʐM��ON�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_bit9_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief 9bit�ʐM��OFF�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_bit9_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief ���荞�ݏ����̐ݒ�
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 * \param _arg_uart_mode
 *		EM_REC -> ��M�������荞��
 *		EM_TRA -> ���M�f�[�^���W�X�^�󂫊��荞��
 *
 * \param _arg_uart_nf_isr : ON/OFF
 */
void F_uart_isr(E_UART_ADDR _arg_uart_addr, E_UART_MODE _arg_uart_mode, BOOL _arg_uart_nf_isr);

/**
 * \brief ���M�f�[�^���W�X�^�󂫊��荞�݂�ON�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_t_isr_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief ��M�������荞�݂�ON�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_r_isr_on(E_UART_ADDR _arg_uart_addr);

/**
 * \brief ���M�f�[�^���W�X�^�󂫊��荞�݂�OFF�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_t_isr_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief ��M�������荞�݂�OFF�ɂ���
 * 
 * \param _arg_uart_addr : �ݒ肷��UART
 */
void F_uart_r_isr_off(E_UART_ADDR _arg_uart_addr);

/**
 * \brief ���M����
 * 
 * \param _arg_uart_addr : �g��UART
 * \param _arg_uart_out_data : ���M����f�[�^
 */
void F_uart_out(E_UART_ADDR _arg_uart_addr, T_DATA _arg_uart_out_data);

/**
 * \brief ���M����B8bit�ʐM�̎��p�B�m�F�Ƃ��͂��ĂȂ�����C��t���Ă�
 *
 * \param _arg_uart_addr : �g��UART
 * \param _arg_uart_out_data : ���M����f�[�^
 */
void F_uart_out_8(E_UART_ADDR _arg_uart_addr, T_DATA_8 _arg_uart_out_data);

/**
 * \brief ��M����
 * 
 * \param _arg_uart_addr : �g��UART
 * 
 * \return T_DATA ��M�����f�[�^
 */
E_UART_FLAG F_uart_in(E_UART_ADDR _arg_uart_addr, T_DATA *_arg_uart_in_data);

/**
 * \brief ��M����B8bit�ʐM�̎��p
 * 
 * \param _arg_uart_addr : �g��UART
 * 
 * \return T_DATA_8 ��M�����f�[�^
 */
E_UART_FLAG F_uart_in_8(E_UART_ADDR _arg_uart_addr, T_DATA_8 *_arg_uart_in_data);

#include "H28_u_func.c"

#include "H28_U_S_UART.h"

#ifdef __cplusplus
}
#endif