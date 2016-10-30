
/*
1�s���p

 H28 06 13 ver0.0.0
*/


#pragma once

#include "H28_I_C_IO_OUT.h"

class C_IO_OUT_pin : protected C_IO_OUT
{
	
private:

	E_IO_NUM _mem_io_out_pin_bit :3;	//�g�p����bit
	
	BOOL _mem_io_out_pin_data :1;	//�o�͂���l�̋L��
	
public:

	/**
	 * \brief ��̃R���X�g���N�^�B
	 */
	C_IO_OUT_pin();
	
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
	 * \brief 
	 *	�N���X�ɁA�o�͂���l����������
	 * 
	 * \param _arg_data : �������ޒl
	 */
	void Write_data(BOOL _arg_data);

	/**
	 * \brief 
	 *	�N���X�ɋL�����ꂽ�o�͂̒l�𔽓]������
	 */
	void Turn_data();
	
	/**
	 * \brief
	 *	�N���X�ɋL�^���ꂽ�l���o�͂���
	 */
	void Out();
	
	/**
	 * \brief 
	 *	�����̒l��IO�s���ɏo�͂���
	 * 
	 * \param _arg_nf : �o�͂���l
	 */
	void Out(BOOL _arg_nf);
	
	/**
	 * \brief 
	 *	IO�s����TRUE���o�͂���B
	 */
	void Out_on();
	
	/**
	 * \brief 
	 *	IO�s����FALSE���o�͂���B
	 */
	void Out_off();
	
	/**
	 * \brief 
	 *	�N���X�ɋL������Ă���o�͂���l��return����B
	 * 
	 * \return BOOL 
	 */
	BOOL Ret_data();
	
	/**
	 * \brief 
	 *	�g�p���Ă�bit��return����B
	 * 
	 * \return E_IO_NUM
	 */
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

#include "H28_I_C_IO_OUT_pin.cpp"
