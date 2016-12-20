
/*
1ピンのみ。センサなどに使えばいいんじゃないかな

 H28 06 12 ver0.0.0 
*/

#pragma once

#include "H28_I_C_IO_IN.h"

/*************************************************************************

IOレジスタ1ピンを入力モードで操作するためのクラス

*************************************************************************/

class C_IO_IN_pin : protected C_IO_IN
{
	
private:
	
	E_IO_NUM _mem_io_in_pin_bit :3;	//用いるbit
	
public:
	
	C_IO_IN_pin()	{}
	
	/**
	 * \brief 
	 *	使用するレジスタ、bitを設定する。
	 *	センサによってはLOWにする必要があるので、それも設定可能
	 *
	 * \param _arg_io_addr	: 使うIOレジスタのアドレス
	 * \param _arg_io_bit	: 使うbit
	 * \param _arg_nf_port	: PORTをHIGHにするかどうか
	 */
	C_IO_IN_pin (E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit, BOOL _arg_nf_port);
	
	/**
	 * \brief	IOピンを読み取る。
	 *
	 * \return BOOL 
	 *	High -> TRUE
	 *	Low  -> FALSE
	 */
	BOOL In ();
	
	/**
	 * \brief	IOピンを反転して読み取る
	 * 
	 * \return BOOL
	 *	High -> FALSE
	 *	Low  -> TRUE
	 */
	BOOL In_turn ();
	
	/**
	 * \brief	使用してるIOレジスタのbitをreturnする。
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

