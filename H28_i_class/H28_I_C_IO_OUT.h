
/*
OUT�݂̂�IO�n�̃N���X
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_base�̃����o�̈ꕔ���f����
 H28 05 22 ver1.0.0 C_IO_base�̃o�[�W�����A�b�v�ւ̑Ή�
 H28 06 12 ver1.1.0 EN_IO_NUM�̃R���X�g���N�^���폜
 H28 06 12 ver1.2.0 C_IO_base�̃o�[�W�����A�b�v�ւ̑Ή�
*/

#pragma once

#include "H28_I_C_IO_base.h"

/*************************************************************************

IO���W�X�^���o�̓��[�h�ő��삷�邽�߂̃N���X

*************************************************************************/
 
class C_IO_OUT : public virtual C_IO_base
{
	
private:

	T_PORT _mem_io_out_data :8;	//�o�͂���l�B���炩���ߋL�^���Ă����o�͂���A
	
public:
	
	C_IO_OUT ();
	
	/**
	 * \brief 
	 *	�R���X�g���N�^�B
	 *	OUT�Ƃ���IO���W�X�^�̐ݒ���s��
	 * 
	 * \param _arg_io_addr		: �g��IO���W�X�^
	 * \param _arg_set_io_pin	: �ݒ肷��l�B8bit�B1bit���Ƃ�1,0�Ŕ��f
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_set_io_pin);
	
	/**
	 * \brief	�N���X�ɁA�o�͂���l���������ށB 
	 *
	 * \param _arg_data : �L�^����l
	 */
	void Write_data (T_PORT _arg_data);
	
	/**
	 * \brief	�N���X�ɋL�����ꂽ�l���o�͂���B
	 */
	void Out ();
	
	/**
	 * \brief	IO���W�X�^�ɏo�͂���
	 * 
	 * \param _arg_data_out : �o�͂���l
	 */
	void Out (T_PORT _arg_data_out);
	
	/**
	 * \brief	�w�肳�ꂽIO�s���Ɏw�肳�ꂽ�l���o�͂���
	 * 
	 * \param _arg_num : �o�͂���s��
	 * \param _arg_nf  : TRUE or FALSE
	 */
	void Out_num (usint _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief 
	 *	�w�肳�ꂽIO�s����1���o�͂���
	 *	���������̌^��������ver 
	 *
	 * \param _arg_num : �o�͂���s��
	 */
	void Out_num_high (usint _arg_num);
	
	/**
	 * \brief 
	 *	�w�肳�ꂽIO�s����0���o�͂���
	 *	���������̌^��������ver 
	 *
	 * \param _arg_num : �o�͂���s��
	 */
	void Out_num_low (usint _arg_num);
	
	/**
	 * \brief	�N���X�ɐݒ肳�ꂽ�o�͂̒l��return����
	 */
	T_PORT Ret_data ()	{	return _mem_io_out_data;	}
};

/************************************************************************/
//public

C_IO_OUT ::
C_IO_OUT ()
{
	_mem_io_out_data = 0;
}

C_IO_OUT ::
C_IO_OUT
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const T_PORT			_arg_set_io_pin
)
: C_IO_base(_arg_io_addr, EI_OUT, _arg_set_io_pin)
{
	_mem_io_out_data = 0;
}

inline void
C_IO_OUT ::
Write_data (const T_PORT _arg_data)
{
	_mem_io_out_data = _arg_data;
}

inline void
C_IO_OUT ::
Out ()
{
	__PORT__ = _mem_io_out_data;
}

inline void
C_IO_OUT ::
Out (const T_PORT _arg_data_out)
{
	__PORT__ = _arg_data_out;
}

inline void
C_IO_OUT ::
Out_num
(
	const usint _arg_num,
	const BOOL	_arg_nf
)
{
	switch (_arg_nf)
	{
		case TRUE:  Out_num_high(_arg_num);	break;
		case FALSE: Out_num_low(_arg_num);	break;
	}
}

inline void
C_IO_OUT ::
Out_num_high (const usint _arg_num)
{
	__PORT__ |= (1 << _arg_num);
}

inline void
C_IO_OUT ::
Out_num_low (const usint _arg_num)
{
	__PORT__ &= ~(1 << _arg_num);
}
