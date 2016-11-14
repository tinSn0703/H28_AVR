
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

/**
 * IOレジスタを入力モードで扱うためのクラス
 */
class C_IO_IN : public virtual C_IO_base
{
	
public:

	/**
	 * \brief 
	 *	空のコンストラクタ。何もしない。
	 */
	C_IO_IN()	{}
	
	/**
	 * \brief 
	 *	使用するレジスタの設定を行う。 
	 *
	 * \param _arg_io_addr		: 使用するレジスタ
	 * \param _arg_set_io_pin	: 使用するピン。bitが対応するピンが入力に設定する
	 */
	C_IO_IN(E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_set_io_pin);

	/**
	 * \brief 
	 *	PORTで読む。
	 * 
	 * \return T_PORT 
	 */
	T_PORT In();
	
	/**
	 * \brief 
	 *	指定されたピンを読む。
	 *
	 * \param _arg_num : 読むピン
	 * 
	 * \return BOOL
	 */
	BOOL In_num(E_IO_NUM _arg_num);
};

#include "H28_I_C_IO_IN.cpp"
