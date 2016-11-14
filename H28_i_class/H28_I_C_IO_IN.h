
/*
���͂̓ǂݍ��݂̂݉\��IO�n�̃N���X
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_base�̃����o�̈ꕔ���f����
 H28 05 22 ver1.0.0 C_IO_base�̃o�[�W�����A�b�v�ւ̑Ή�
 H28 06 12 ver1.1.0 E_IO_NUM�̃R���X�g���N�^���폜
 H28 06 12 ver1.2.0 C_IO_base�̃o�[�W�����A�b�v�ւ̑Ή�
*/

#pragma once

#include "H28_I_C_IO_base.h"

/**
 * IO���W�X�^����̓��[�h�ň������߂̃N���X
 */
class C_IO_IN : public virtual C_IO_base
{
	
public:

	/**
	 * \brief 
	 *	��̃R���X�g���N�^�B�������Ȃ��B
	 */
	C_IO_IN()	{}
	
	/**
	 * \brief 
	 *	�g�p���郌�W�X�^�̐ݒ���s���B 
	 *
	 * \param _arg_io_addr		: �g�p���郌�W�X�^
	 * \param _arg_set_io_pin	: �g�p����s���Bbit���Ή�����s�������͂ɐݒ肷��
	 */
	C_IO_IN(E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_set_io_pin);

	/**
	 * \brief 
	 *	PORT�œǂށB
	 * 
	 * \return T_PORT 
	 */
	T_PORT In();
	
	/**
	 * \brief 
	 *	�w�肳�ꂽ�s����ǂށB
	 *
	 * \param _arg_num : �ǂރs��
	 * 
	 * \return BOOL
	 */
	BOOL In_num(E_IO_NUM _arg_num);
};

#include "H28_I_C_IO_IN.cpp"
