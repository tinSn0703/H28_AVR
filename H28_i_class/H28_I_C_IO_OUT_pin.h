
/*
1ピン用

 H28 06 13 ver0.0.0
*/


#pragma once

#include "H28_I_C_IO_OUT.h"

class C_IO_OUT_pin : protected C_IO_OUT
{
	
private:

	E_IO_NUM _mem_io_out_pin_bit :3;	//使用するbit
	
	BOOL _mem_io_out_pin_data :1;	//出力する値の記憶
	
public:

	/**
	 * \brief 空のコンストラクタ。
	 */
	C_IO_OUT_pin();
	
	/**
	 * \brief 
	 * コンストラクタ
	 * IOレジスタの設定を行う。
	 *
	 * \param _arg_io_addr : 使うIOレジスタ
	 * \param _arg_io_bit  : 使うbit
	 */
	C_IO_OUT_pin(E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit);
	
	/**
	 * \brief 
	 *	クラスに、出力する値を書き込む
	 * 
	 * \param _arg_data : 書き込む値
	 */
	void Write_data(BOOL _arg_data);

	/**
	 * \brief 
	 *	クラスに記憶された出力の値を反転させる
	 */
	void Turn_data();
	
	/**
	 * \brief
	 *	クラスに記録された値を出力する
	 */
	void Out();
	
	/**
	 * \brief 
	 *	引数の値をIOピンに出力する
	 * 
	 * \param _arg_nf : 出力する値
	 */
	void Out(BOOL _arg_nf);
	
	/**
	 * \brief 
	 *	IOピンにTRUEを出力する。
	 */
	void Out_on();
	
	/**
	 * \brief 
	 *	IOピンにFALSEを出力する。
	 */
	void Out_off();
	
	/**
	 * \brief 
	 *	クラスに記憶されている出力する値をreturnする。
	 * 
	 * \return BOOL 
	 */
	BOOL Ret_data();
	
	/**
	 * \brief 
	 *	使用してるbitをreturnする。
	 * 
	 * \return E_IO_NUM
	 */
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

#include "H28_I_C_IO_OUT_pin.cpp"
