
#pragma once

#include "H28_I_C_IO_OUT.h"

class C_IO_OUT_pin : protected C_IO_OUT
{
private:

	E_IO_NUM _mem_io_out_pin_bit :3;
	
	BOOL _mem_io_out_pin_nf_set :1;
	
public:

	/**
	 * \brief ��̃R���X�g���N�^�B
	 */
	C_IO_OUT_pin()	{}
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * IO���W�X�^�̐ݒ���s���B
	 *
	 * \param _arg_io_addr : �g��IO���W�X�^
	 * \param _arg_io_bit  : �g��bit
	 */
	C_IO_OUT_pin(E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit);
	
	/**
	 * \brief �o�̗͂\��̐ݒ��Ԃ�
	 * 
	 * \return BOOL �o�͂̐ݒ�
	 */
	BOOL Ret();
	
	/**
	 * \brief �o�̗͂\���ݒ肷��
	 * 
	 * \param _arg_nf_set : �\��
	 */
	void Set(BOOL _arg_nf_set);

	/**
	 * \brief �\��̐ݒ�𔽓]������
	 */
	void Chen();
	
	/**
	 * \brief �\�񂵂��ݒ���o�͂���
	 */
	void Out();
	
	/**
	 * \brief 
	 * 
	 * \param _arg_nf : 
	 */
	void Out(BOOL _arg_nf);
	
	void Out_on();
	void Out_off();
	
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

#include "H28_I_C_IO_OUT_pin.cpp"
