
#pragma once

#include "H28_U_C_UART_base.h"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.h>

/**
 * UART�Ŏ�M�������N���X
 */
class C_UART_R : public virtual C_UART_base
{
private:

	C_TIMER_inside _mem_timer;

protected:
	
	E_UART_FLAG _mem_uart_r_flag :2; //�Ō�̎�M��Ԃ̋L�^
	
public:

	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����^�C�}�̐ݒ�݂̂��s��
	 */
	C_UART_R();
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_addr : �g��UART
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R(E_UART_ADDR _arg_uart_addr, BOOL _arg_uart_nf_isr);
	
	/**
	 * \brief ��M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Set_isr(BOOL );
	
	/**
	 * \brief 
	 * ��M���ł��邩���m�F����B���ʂ�_mem_uart_r_flag�Ɋi�[�����̂Ŏg���Ƃ��ɂ�������ǂ�łق����B
	 * �m�F���͂��̊֐��Œ�~���܂��B
	 * �m�F�ɂ͍Œ���8ms��������܂�
	 */
	void Check();
	
	/**
	 * \brief ��M���� 
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
	 * C_UART_R::In()�̉��Z�q�o�[�W�����B
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * C_UART_R::In()�̉��Z�q�o�[�W�����B
	 * 8bit�ʐM�̂Ƃ��p
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_data_in : ��M�f�[�^���������܂��ꏊ
	 */
	friend void operator >> (C_UART_R &_arg_uart_r, T_DATA_8 &_arg_uart_data_in);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R::Check()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ƃ�true
	 */
	friend bool operator == (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̎�M��Ԃ̔�r�p
	 * C_UART_R::Check()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ȃ��Ƃ�true
	 */
	friend bool operator != (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R.cpp"