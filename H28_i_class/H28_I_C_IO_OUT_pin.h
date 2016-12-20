
/*
1ピン用

 H28 06 13 ver0.0.0
*/


#pragma once

#include "H28_I_C_IO_OUT.h"

/*************************************************************************

IOレジスタ1ピンを出力モードで操作するためのクラス。

*************************************************************************/

class C_IO_OUT_pin : protected C_IO_OUT
{
	
private:

	E_IO_NUM _mem_io_out_pin_bit :3;	//使用するbit
	
	BOOL _mem_io_out_pin_level :1;	//出力する値の記憶
	
public:
	
	C_IO_OUT_pin ()	{	_mem_io_out_pin_level = FALSE;	}
	
	/**
	 * \brief 
	 *	コンストラクタ
	 *	IOレジスタの設定を行う。
	 *
	 * \param _arg_io_addr : 使うIOレジスタ
	 * \param _arg_io_bit  : 使うbit
	 */
	C_IO_OUT_pin (E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit);
	
	/**
	 * \brief	あらかじめレベルを設定する
	 * 
	 * \param _arg_data : 設定するレベル
	 */
	void Write_data (BOOL _arg_level);

	/**
	 * \brief	クラスに設定されたレベルを反転させる
	 */
	void Turn_data ();
	
	/**
	 * \brief	IOピンをクラスに設定されたレベルにする
	 */
	void Out ();
	
	/**
	 * \brief	引数の値をIOピンに出力する
	 * 
	 * \param _arg_nf : 出力する値
	 */
	void Out (BOOL _arg_nf);
	
	/**
	 * \brief	IOピンをHレベルにする。
	 */
	void Out_high ();
	
	/**
	 * \brief	IOピンをLレベルにする。
	 */
	void Out_low ();
	
	/**
	 * \brief	クラスに設定されているレベルをreturnする。
	 */
	BOOL Ret_data () {	return _mem_io_out_pin_level;	}
	
	/**
	 * \brief	使用してるIOレジスタのbitをreturnする。
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

