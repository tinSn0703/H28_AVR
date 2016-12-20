
/*
入力の読み込みのみ可能なIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
 H28 06 12 ver1.1.0 E_IO_NUMのコンストラクタを削除
 H28 06 12 ver1.2.0 C_IO_baseのバージョンアップへの対応
*/

#pragma once

#include "H28_I_C_IO_base.h"

/*************************************************************************

IOレジスタを入力モードで操作するためのクラス

*************************************************************************/

class C_IO_IN : public virtual C_IO_base
{
	
public:
	
	C_IO_IN ()	{}
	
	/**
	 * \brief	使用するレジスタの設定を行う。 
	 *
	 * \param _arg_io_addr		: 使用するレジスタ
	 * \param _arg_set_io_pin	: 使用するピン。bitが対応するピンが入力に設定する
	 */
	C_IO_IN (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_set_io_pin);

	/**
	 * \brief	PORTを読む。
	 */
	T_PORT In ();
	
	/**
	 * \brief	指定されたピンを読む。
	 *
	 * \param _arg_num : 読むピン
	 */
	BOOL In_num (E_IO_NUM _arg_num);
};

/************************************************************************/
//public

C_IO_IN ::
C_IO_IN
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const T_PORT			_arg_set_io_pin = 0xff
)
{
	C_IO_base :: Set_io_base(_arg_io_addr, EI_IN, _arg_set_io_pin);
}

inline T_PORT
C_IO_IN ::
In ()
{
	return __PIN__;
}

inline BOOL
C_IO_IN ::
In_num (const E_IO_NUM _arg_num)
{
	return F_Check_bit_bool(__PIN__, _arg_num);
}