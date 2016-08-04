
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

	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//���W�X�^�p�̃A�h���X
	
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
	 * �R���X�g���N�^
	 * �����^�C�}�̐ݒ�݂̂��s��
	 */
	C_UART_R2();
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_addr : �g��UART
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R2(E_UART_ADDR _arg_uart_addr_0, E_UART_ADDR _arg_uart_addr_1, BOOL _arg_uart_nf_isr_0, BOOL _arg_uart_nf_isr_1);
	
	/**
	 * \brief 0�Ԃ̎�M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr_0(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 1�Ԃ̎�M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr_1(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 0�Ԃ�9nit�ʐM��ONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFF�̐ݒ�
	 */
	void Set_bit9_0(BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 0�Ԃ�9nit�ʐM��ONOFF
	 * 
	 * \param _arg_uart_nf_bit9 : ONOFF�̐ݒ�
	 */
	void Set_bit9_1(BOOL _arg_uart_nf_bit9);
	
	/**
	 * \brief 
	 * ��M���ł��邩���m�F����B���ʂ�_mem_uart_r2_flag�Ɋi�[�����̂Ŏg���Ƃ��ɂ�������ǂ�łق����B
	 * In()�͎����I�ɁA��ɐ��������ق��ōs���܂��B
	 * �m�F���͂��̊֐��Œ�~���܂��B
	 * �m�F�ɂ͍Œ���8ms��������܂�
	 */
	void Check();
	
	/**
	 * \brief 
	 * ��M����
	 * Check()�Ő��������ق���p���� 
	 * 
	 * \return T_DATA : ��M�����f�[�^
	 */
	T_DATA In();
	
	/**
	 * \brief ���O�̎�M��Ԃ�return����B
	 * 
	 * \return E_UART_FLAG
	 */
	E_UART_FLAG Ret_flag();
	
	/**
	 * \brief 
	 * C_UART_R2::In()�̉��Z�q�o�[�W�����B
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R2::In()�̉��Z�q�o�[�W�����B
	 * 8bit�ʐM�̂Ƃ��p
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R2 &_arg_uart_r2, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R2::Check()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ƃ�true
	 */
	friend bool operator == (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R2::Check()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r2 : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ȃ��Ƃ�true
	 */
	friend bool operator != (C_UART_R2 &_arg_uart_r2, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R2.cpp"