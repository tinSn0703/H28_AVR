
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
	
	E_UART_FLAG _mem_uart_r_flag_state :2; //�Ō�̎�M��Ԃ̋L�^
	
public:
	
#if defined(_AVR_IOM640_H_) || defined(_AVR_IOM164_H_)

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
	
#elif defined(_AVR_IOM88_H_)
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �����ݒ���s���B�ڍׂ�C_UART_base�Q��
	 * ���Ɠ����^�C�}�̐ݒ��
	 * 
	 * \param _arg_uart_nf_isr : ��M�������荞�݂�ONOFF
	 */
	C_UART_R(BOOL _arg_uart_nf_isr);

#endif

	/**
	 * \brief ��M�������荞�݂�ONOFF
	 * 
	 * \param _arg_uart_nf_isr : ONOFF�̐ݒ�
	 */
	void Reset_isr(BOOL );
	
	/**
	 * \brief 
	 * ��M���ł��邩���m�F����B���ʂ�_mem_uart_r_flag�Ɋi�[�����̂Ŏg���Ƃ��ɂ�������ǂ�łق����B
	 * Timer��p���āA��莞�ԂŎ�M�ł��Ȃ������ꍇ�́A�����I�ɏI�����܂�
	 * �m�F���͂��̊֐��Œ�~���܂��B
	 * �m�F�ɂ͍Œ���8ms��������܂�
	 */
	void Check_in();
	
	/**
	 * \brief ��M
	 * 
	 * \param _arg_nf_auto_cut : �����ŒʐM���I�����邩�̎g�p�ɂ���
	 *
	 * \return T_DATA : ��M�����f�[�^
	 */
	T_DATA In(BOOL _arg_nf_auto_cut);

	/**
	 * \brief ��M��Ԃ�return����B
	 * 
	 * \return E_UART_FLAG
	 *	���s	-> EU_ERROR
	 *	����	-> EU_SUCCE
	 *	���̑�	-> EU_NONE
	 */
	E_UART_FLAG Ret_state();
	
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
	 * C_UART_R::Check_in()�̂��ƂŎg����
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
	 * C_UART_R::Check_in()�̂��ƂŎg����
	 * 
	 * \param _arg_uart_r : �݂��܂�
	 * \param _arg_uart_flag_comp : ��r������
	 * 
	 * \return bool �������Ȃ��Ƃ�true
	 */
	friend bool operator != (C_UART_R &_arg_uart_r, E_UART_FLAG _arg_uart_flag_comp);
};

#include "H28_U_C_UART_R.cpp"