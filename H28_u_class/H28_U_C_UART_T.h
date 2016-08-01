
#pragma once

#include "H28_U_C_UART_base.h"

/**
 * UART�̑��M�������N���X
 */
class C_UART_T : public virtual C_UART_base
{
public:

	/**
	 * \brief 
	 * ��̃R���X�g���N�^�B�ق�Ƃɉ������Ȃ�
	 */
	C_UART_T() {}
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * 
	 * \param _aeg_uart_addr   : �g��UART
	 * \param _arg_uart_nf_isr : ���M�f�[�^���W�X�^�󂫊��荞�݂�ONOFF
	 */
	C_UART_T(E_UART_ADDR _aeg_uart_addr, BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 
	 *  : ���M�f�[�^���W�X�^�󂫊��荞�݂̐ݒ� 
	 *
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr(BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief 
	 * �f�[�^�𑗐M����B
	 * �A���ŒʐM���s���ꍇ�͑��葤�ɂ����������邱�Ƃ��l���Ȃ������Ă�
	 * 
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	void Out(T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * �f�[�^�𑗐M����B
	 * �A���ŒʐM���s���ꍇ�͑��葤�ɂ����������邱�Ƃ��l���Ȃ������Ă�
	 * 8bit�ʐM�̎��p
	 * 
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	void Out(T_DATA_8 _arg_uart_data_out);
	
	/**
	 * \brief 
	 * C_UART_T::Out()�̉��Z�qver 
	 *
	 * \param _arg_uart_t : �݂��܂�
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA _arg_uart_data_out);
	
	/**
	 * \brief 
	 * C_UART_T::Out()�̉��Z�qver 
	 * 8bit�ʐM�̎��p
	 *
	 * \param _arg_uart_t : �݂��܂�
	 * \param _arg_uart_data_out : ���M����f�[�^
	 */
	friend void operator << (C_UART_T &_arg_uart_t, T_DATA_8 _arg_uart_data_out);
};

#include "H28_U_C_UART_T.cpp"