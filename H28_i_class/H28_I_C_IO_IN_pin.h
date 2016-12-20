
/*
1�s���̂݁B�Z���T�ȂǂɎg���΂����񂶂�Ȃ�����

 H28 06 12 ver0.0.0 
*/

#pragma once

#include "H28_I_C_IO_IN.h"

/*************************************************************************

IO���W�X�^1�s������̓��[�h�ő��삷�邽�߂̃N���X

*************************************************************************/

class C_IO_IN_pin : protected C_IO_IN
{
	
private:
	
	E_IO_NUM _mem_io_in_pin_bit :3;	//�p����bit
	
public:
	
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
	C_IO_IN_pin (E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit, BOOL _arg_nf_port);
	
	/**
	 * \brief	IO�s����ǂݎ��B
	 *
	 * \return BOOL 
	 *	High -> TRUE
	 *	Low  -> FALSE
	 */
	BOOL In ();
	
	/**
	 * \brief	IO�s���𔽓]���ēǂݎ��
	 * 
	 * \return BOOL
	 *	High -> FALSE
	 *	Low  -> TRUE
	 */
	BOOL In_turn ();
	
	/**
	 * \brief	�g�p���Ă�IO���W�X�^��bit��return����B
	 * 
	 * \return E_IO_NUM
	 */
	E_IO_NUM Ret_bit ()	{	return _mem_io_in_pin_bit;	}
};

/************************************************************************/
//public

C_IO_IN_pin ::
C_IO_IN_pin
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_NUM			_arg_io_bit,
	const BOOL				_arg_nf_port = TRUE
)
{
	C_IO_base :: Set_io_base(_arg_io_addr);
	
	_mem_io_in_pin_bit = _arg_io_bit;
	
	__DDR__  &= ~(1 << _arg_io_bit);
	
	if (_arg_nf_port)	__PORT__ |=  (1 << _arg_io_bit);
	else				__PORT__ &= ~(1 << _arg_io_bit);
}

inline BOOL
C_IO_IN_pin ::
In ()
{
	return C_IO_IN :: In_num(_mem_io_in_pin_bit);
}

inline BOOL
C_IO_IN_pin ::
In_turn ()
{
	return F_Turn_bool(C_IO_IN :: In_num(_mem_io_in_pin_bit));
}

