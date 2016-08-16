
#pragma once

#include "H28_I_C_IO_base.h"

/**
 * PORT��OUT�������N���X
 */
class C_IO_OUT : public virtual C_IO_base
{
	public:

	/**
	 * \brief ��̃R���X�g���N�^�B���ɉ����N����Ȃ�
	 */
	C_IO_OUT ()	{}
	
	
	/**
	 * \brief 
	 * �R���X�g���N�^�B
	 * OUT�Ƃ���IO���W�X�^�̐ݒ���s��
	 * 
	 * \param _arg_io_addr : �g��IO���W�X�^
	 * \param _arg_io_num_byte : �ݒ肷��l�B8bit�B1bit���Ƃ�1,0�Ŕ��f
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_io_num_byte);
	
	/**
	 * \brief _arg_io_num_byte���o�͂���
	 * 
	 * \param _arg_io_num_byte : �o�͂̒l
	 */
	void Out (T_PORT _arg_io_num_byte);
	
	/**
	 * \brief �ݒ肳�ꂽbit��S��ON�ɂ��� 
	 */
	void Out_on ();
	
	/**
	 * \brief �ݒ肳�ꂽbit��S��OFF�ɂ���
	 */
	void Out_off ();
	
	/**
	 * \brief _arg_io_num_bit��ON�ɂ���
	 * 
	 * \param _arg_io_num_bit : ON�ɂ���bit
	 */
	void Out_num_on (E_IO_NUM _arg_io_num_bit);
	
	/**
	 * \brief 
	 * _arg_io_num_bit��ON�ɂ���
	 * ���������̌^��������ver 
	 *
	 * \param _arg_io_num_bit : ON�ɂ���bit
	 */
	void Out_num_on (usint _arg_io_num_bit);
	
	/**
	 * \brief _arg_io_num_bit��OFF�ɂ���
	 * 
	 * \param _arg_io_num_bit : OFF�ɂ���bit
	 */
	void Out_num_off (E_IO_NUM _arg_io_num_bit);
	
	/**
	 * \brief 
	 * _arg_io_num_bit��OFF�ɂ���
	 * ���������̌^��������ver 
	 *
	 * \param _arg_io_num_bit : OFF�ɂ���bit
	 */
	void Out_num_off (usint _arg_io_num_bit);
};

#include "H28_I_C_IO_OUT.cpp"