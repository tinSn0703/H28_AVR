
/*
1�s���̂݁B�Z���T�ȂǂɎg���΂����񂶂�Ȃ�����

 H28 06 12 ver0.0.0 
*/

#pragma once

#include "H28_I_C_IO_IN.cpp"

class C_IO_IN_pin : protected C_IO_IN
{
	
private:
	
	E_IO_NUM _mem_io_in_pin_bit :3;	//�p����bit
	
public:

	/**
	 * \brief 
	 *	�������Ȃ��B��̃R���X�g���N�^�B
	 */
	C_IO_IN_pin()	{}
	
	/**
	 * \brief 
	 *	�g�p���郌�W�X�^�Abit��ݒ肷��B
	 *	�Z���T�ɂ���Ă�LOW�ɂ���K�v������̂ŁA������ݒ�\
	 *
	 * \param _arg_io_addr	: �g��IO���W�X�^�̃A�h���X
	 * \param _arg_io_bit	: �g��bit
	 * \param _arg_nf_port	: PORT��HIGH�ɂ��邩�ǂ���
	 */
	C_IO_IN_pin(E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit, BOOL _arg_nf_port);
	
	/**
	 * \brief 
	 *	IO�s����High / Low��ǂݎ��B
	 *
	 * \return BOOL 
	 *	High -> TRUE
	 *	Low  -> FALSE
	 */
	BOOL In();
	
	/**
	 * \brief 
	 *	IO�s���𔽓]���ēǂݎ��
	 * 
	 * \return BOOL
	 *	High -> FALSE
	 *	Low  -> TRUE
	 */
	BOOL In_turn();
	
	/**
	 * \brief 
	 *	�g�p���Ă�bit��return����B
	 * 
	 * \return E_IO_NUM
	 */
	E_IO_NUM Ret_bit()	{	return _mem_io_in_pin_bit;	}
};


#include "H28_I_C_IO_IN_pin.cpp"