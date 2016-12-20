
/*
IO�s���p�N���X�̊�b�B�錾���Ȃ��łˁB
 H28 05 11 ver0.0.0
 H28 05 18 ver0.1.0 �����o���팸���Ĕh����Ɉڂ���
 H28 05 22 ver1.0.0 PORTH�ȍ~�����g���Ȃ������o�O��@���ׂ������łɒ��ۃN���X�ɂ����B
 H28 05 22 ver1.0.1 ���ۃN���X�̎g�������悭�킩��񂩂�������public�̂Ȃ��N���X�ɂ����B�錾���Ă��Ӗ��Ȃ���B
 H28 05 23 ver1.0.2 ���ۃN���X�ɂ���
 H28 05 23 ver1.0.3 ����ς��߂�
 H28 06 12 ver1.1.0 �������Z�q��p����PORT���g���Ƃ��̂߂�ǂ������̂𖳂������B
 H28 06 12 ver1.2.0 �f�X�g���N�^��ǉ��B����ŁA�q�N���X�I�����ɁA���W�X�^�̐ݒ肪������܂��B
*/

#pragma once

#include "H28_i_class.h"

/*************************************************************************

IO���W�X�^�𑀍삷�邽�߂̃N���X�̃x�[�X�B�p�����ĂˁB

*************************************************************************/

class C_IO_base
{
protected:
	
#if defined(_AVR_IOM640_H_)

	E_IO_PORT_ADDR	_mem_io_base_addr :9;
	BOOL			_mem_io_base_addr_point :1;
	
#	define __PIN__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 0) : _SFR_IO8(_mem_io_base_addr + 0))
#	define __DDR__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 1) : _SFR_IO8(_mem_io_base_addr + 1))
#	define __PORT__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 2) : _SFR_IO8(_mem_io_base_addr + 2))

#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_)

	E_IO_PORT_ADDR	_mem_io_base_addr :8;
	
#	define __PIN__	_SFR_IO8(_mem_io_base_addr + 0)
#	define __DDR__	_SFR_IO8(_mem_io_base_addr + 1)
#	define __PORT__	_SFR_IO8(_mem_io_base_addr + 2)

#endif
	
	/**
	 * \brief	�g��IO���W�X�^�̓o�^���s��
	 *
	 * \param _arg_io_addr : �ݒ肷��IO
	 */
	void Set_io_base(E_IO_PORT_ADDR _arg_io_addr);

	/**
	 * \brief	�g��IO���W�X�^�̓o�^,�ݒ���s��
	 * 
	 * \param _arg_io_addr		: �g�p���郌�W�X�^
	 * \param _arg_io_mode		: �ݒ肷�郂�[�h
	 * \param _arg_set_io_pin	: �g�p����s���̐ݒ�B1�ɂȂ��Ă���bit�ɑΉ����郌�W�X�^��bit��_arg_io_mode�̋@�\�ɐݒ肳���
	 */
	void Set_io_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
public:
	
	C_IO_base()	{}
	
	/**
	 * \brief 
	 *	�R���X�g���N�^
	 *	�g��IO���W�X�^�̓o�^���s��
	 * 
	 * \param _arg_io_addr : �ݒ肷��IO
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr);
	
	/**
	 * \brief	�g��IO���W�X�^�̓o�^�Ɛݒ���s�� 
	 *
	 * \param _arg_io_addr		: �g�p���郌�W�X�^
	 * \param _arg_io_mode		: �ݒ肷�郂�[�h
	 * \param _arg_set_io_pin	: �g�p����s���̐ݒ�B1�ɂȂ��Ă���bit�ɑΉ����郌�W�X�^��bit��_arg_io_mode�̋@�\�ɐݒ肳���
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_set_io_pin);
};

/************************************************************************/
//protected

inline void
C_IO_base ::
Set_io_base (const E_IO_PORT_ADDR _arg_io_addr)
{
	_mem_io_base_addr = _arg_io_addr;
	
	#ifdef _AVR_IOM640_H_

	_mem_io_base_addr_point = F_Check_bit_bool(_arg_io_addr, 8);

	#endif

}

inline void
C_IO_base::
Set_io_base
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_MODE			_arg_io_mode,
	const T_PORT			_arg_set_io_pin
)
{
	Set_io_base(_arg_io_addr);
	
	switch (_arg_io_mode)
	{
		case EI_IN:
		{
			__DDR__  = ~_arg_set_io_pin;
			__PORT__ =  _arg_set_io_pin;
			
			break;
		}
		case EI_OUT:
		{
			__DDR__  =  _arg_set_io_pin;
			__PORT__ = ~_arg_set_io_pin;
			
			break;
		}
	}
}

/************************************************************************/
//public

C_IO_base ::
C_IO_base (const E_IO_PORT_ADDR _arg_io_addr)
{
	Set_io_base(_arg_io_addr);
}

C_IO_base ::
C_IO_base
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_MODE			_arg_io_mode,
	const T_PORT			_arg_set_io_pin
)
{
	Set_io_base(_arg_io_addr, _arg_io_mode, _arg_set_io_pin);
}
