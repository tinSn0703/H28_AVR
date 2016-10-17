
#pragma once

#include "H28_I_C_IO_base.h"

/**
 * PORT��OUT�������N���X
 */
class C_IO_OUT : public virtual C_IO_base
{
private:

	T_PORT _mem_io_out_port_rev :8;
	
public:

	/**
	 * \brief ��̃R���X�g���N�^�B_mem_io_out_data�����������邮�炢
	 */
	C_IO_OUT ();
	
	/**
	 * \brief 
	 * �R���X�g���N�^�B
	 * OUT�Ƃ���IO���W�X�^�̐ݒ���s��
	 * 
	 * \param _arg_io_addr : �g��IO���W�X�^
	 * \param _arg_data_set : �ݒ肷��l�B8bit�B1bit���Ƃ�1,0�Ŕ��f
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_data_set);
	
	void Set (T_PORT _arg_data_set);
	
	void Set_or (T_PORT _arg_data_set);
	
	void Set_and (T_PORT _arg_data_set);
	
	T_PORT Ret ();
	
	/**
	 * \brief _arg_io_num_byte���o�͂���
	 * 
	 * \param _arg_data_out : �o�͂̒l
	 */
	void Out (T_PORT _arg_data_out);
	
	void Out_on ();
	
	void Out_off ();
	
	/**
	 * \brief 
	 * �w�肳�ꂽIO�s���Ɏw�肳�ꂽ�l���o�͂���
	 * 
	 * \param _arg_num : ������IO�s��
	 * \param _arg_nf  : High or Low
	 */
	void Out_num (E_IO_NUM _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief 
	 * �w�肳�ꂽIO�s���Ɏw�肳�ꂽ�l���o�͂���
	 * 
	 * \param _arg_num : ������IO�s��
	 * \param _arg_nf  : High or Low
	 */
	void Out_num (usint _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief _arg_io_num_bit��ON�ɂ���
	 * 
	 * \param _arg_num : ON�ɂ���bit
	 */
	void Out_num_on (E_IO_NUM _arg_num);
	
	/**
	 * \brief 
	 * _arg_io_num_bit��ON�ɂ���
	 * ���������̌^��������ver 
	 *
	 * \param _arg_num : ON�ɂ���bit
	 */
	void Out_num_on (usint _arg_num);
	
	/**
	 * \brief _arg_io_num_bit��OFF�ɂ���
	 * 
	 * \param _arg_io_num_bit : OFF�ɂ���bit
	 */
	void Out_num_off (E_IO_NUM _arg_num);
	
	/**
	 * \brief 
	 * _arg_io_num_bit��OFF�ɂ���
	 * ���������̌^��������ver 
	 *
	 * \param _arg_io_num_bit : OFF�ɂ���bit
	 */
	void Out_num_off (usint _arg_num);
};

#include "H28_I_C_IO_OUT.cpp"