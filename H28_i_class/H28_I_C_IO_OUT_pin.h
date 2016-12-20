
/*
1�s���p

 H28 06 13 ver0.0.0
*/


#pragma once

#include "H28_I_C_IO_OUT.h"

/*************************************************************************

IO���W�X�^1�s�����o�̓��[�h�ő��삷�邽�߂̃N���X�B

*************************************************************************/

class C_IO_OUT_pin : protected C_IO_OUT
{
	
private:

	E_IO_NUM _mem_io_out_pin_bit :3;	//�g�p����bit
	
	BOOL _mem_io_out_pin_level :1;	//�o�͂���l�̋L��
	
public:
	
	C_IO_OUT_pin ()	{	_mem_io_out_pin_level = FALSE;	}
	
	/**
	 * \brief 
	 *	�R���X�g���N�^
	 *	IO���W�X�^�̐ݒ���s���B
	 *
	 * \param _arg_io_addr : �g��IO���W�X�^
	 * \param _arg_io_bit  : �g��bit
	 */
	C_IO_OUT_pin (E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit);
	
	/**
	 * \brief	���炩���߃��x����ݒ肷��
	 * 
	 * \param _arg_data : �ݒ肷�郌�x��
	 */
	void Write_data (BOOL _arg_level);

	/**
	 * \brief	�N���X�ɐݒ肳�ꂽ���x���𔽓]������
	 */
	void Turn_data ();
	
	/**
	 * \brief	IO�s�����N���X�ɐݒ肳�ꂽ���x���ɂ���
	 */
	void Out ();
	
	/**
	 * \brief	�����̒l��IO�s���ɏo�͂���
	 * 
	 * \param _arg_nf : �o�͂���l
	 */
	void Out (BOOL _arg_nf);
	
	/**
	 * \brief	IO�s����H���x���ɂ���B
	 */
	void Out_high ();
	
	/**
	 * \brief	IO�s����L���x���ɂ���B
	 */
	void Out_low ();
	
	/**
	 * \brief	�N���X�ɐݒ肳��Ă��郌�x����return����B
	 */
	BOOL Ret_data () {	return _mem_io_out_pin_level;	}
	
	/**
	 * \brief	�g�p���Ă�IO���W�X�^��bit��return����B
	 */
	E_IO_NUM Ret_bit ()	{	return _mem_io_out_pin_bit;	}
};

/************************************************************************/
//public

C_IO_OUT_pin ::
C_IO_OUT_pin
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_NUM			_arg_io_bit
)
: C_IO_base(_arg_io_addr)
{
	_mem_io_out_pin_level = FALSE;
	_mem_io_out_pin_bit = _arg_io_bit;
	
	__DDR__  |=  (1 << _arg_io_bit);
	__PORT__ &= ~(1 << _arg_io_bit);
}

inline void
C_IO_OUT_pin ::
Write_data (const BOOL _arg_level)
{
	_mem_io_out_pin_level = _arg_level;
}

inline void
C_IO_OUT_pin ::
Turn_data ()
{
	_mem_io_out_pin_level = F_Turn_bool(_mem_io_out_pin_level);
}

inline void
C_IO_OUT_pin ::
Out ()
{
	switch (_mem_io_out_pin_level)
	{
		case TRUE:	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);	break;
	}
}

inline void
C_IO_OUT_pin::
Out (const BOOL _arg_level)
{
	_mem_io_out_pin_level = _arg_level;
	
	switch (_arg_level)
	{
		case TRUE:	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);	break;
	}
}

inline void
C_IO_OUT_pin::
Out_high ()
{
	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);
}

inline void
C_IO_OUT_pin::
Out_low ()
{
	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);
}

