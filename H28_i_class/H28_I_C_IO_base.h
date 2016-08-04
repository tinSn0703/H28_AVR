
#pragma once

#include "H28_i_class.h"

class C_IO_base
{
private:
	
	E_IO_MODE	_mem_io_base_mode :1;
	
protected:
	
#if defined(_AVR_IOM640_H_)
	E_IO_PORT_ADDR	_mem_io_base_addr :9;
	BOOL			_mem_io_base_addr_point :1;
	
#	define __PIN__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 0) : _SFR_IO8(_mem_io_base_addr + 0))
#	define __DDR__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 1) : _SFR_IO8(_mem_io_base_addr + 1))
#	define __PORT__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 2) : _SFR_IO8(_mem_io_base_addr + 2))
#elif defined(_AVR_IOM164_H_)
	E_IO_PORT_ADDR	_mem_io_base_addr :8;
	
#	define __PIN__	_SFR_IO8(_mem_io_base_addr + 0)
#	define __DDR__	_SFR_IO8(_mem_io_base_addr + 1)
#	define __PORT__	_SFR_IO8(_mem_io_base_addr + 2)
#endif
	
	/**
	 * \brief �R���X�g���N�^�̒��g�B
	 * 
	 * \param _arg_io_addr : �R���X�g���N�^�Q��
	 * \param _arg_io_mode : �R���X�g���N�^�Q��
	 */
	void Set_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode);

	/**
	 * \brief �R���X�g���N�^�̒��g�B
	 * 
	 * \param _arg_io_addr : �R���X�g���N�^�Q��
	 * \param _arg_io_mode : �R���X�g���N�^�Q��
	 * \param _arg_io_num : �R���X�g���N�^�Q��
	 */	
	void Set_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
public:
	
	/**
	 * \brief 
	 * ��̃R���X�g���N�^�B
	 */
	C_IO_base()	{}
	
	/**
	 * \brief 
	 * �R���X�g���N�^
	 * �g��IO�̓o�^�݂̂��s��
	 * 
	 * \param _arg_io_addr : �ݒ肷��IO
	 * \param _arg_io_mode : �ݒ肷��IO�̃��[�h
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode);
	
	/**
	 * \brief 
	 * �g��IO�̓o�^�Ɛݒ���s�� 
	 *
	 * \param _arg_io_addr : �ݒ肷��IO
	 * \param _arg_io_mode : �ݒ肷��IO�̃��[�h
	 * \param _arg_io_num  : IO�̐ݒ�
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
	/**
	 * \brief 
	 * �f�X�g���N�^�BIO�̐ݒ���Ȃ��������Ƃɂ���
	 */
	~C_IO_base();
};

#include "H28_I_C_IO_base.cpp"
