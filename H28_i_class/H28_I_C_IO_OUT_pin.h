
#pragma once

#include "H28_I_C_IO_OUT.h"

class C_IO_OUT_pin : protected C_IO_OUT
{
private:

	E_IO_NUM _mem_io_out_pin_bit :3;
	
	BOOL _mem_io_out_pin_nf_set :1;
	
public:

	/**
	 * \brief 空のコンストラクタ。
	 */
	C_IO_OUT_pin()	{}
	
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
	 * \brief 出力の予約の設定を返す
	 * 
	 * \return BOOL 出力の設定
	 */
	BOOL Ret();
	
	/**
	 * \brief 出力の予約を設定する
	 * 
	 * \param _arg_nf_set : 予約
	 */
	void Set(BOOL _arg_nf_set);

	/**
	 * \brief 予約の設定を反転させる
	 */
	void Chen();
	
	/**
	 * \brief 予約した設定を出力する
	 */
	void Out();
	
	/**
	 * \brief 
	 * 
	 * \param _arg_nf : 
	 */
	void Out(BOOL _arg_nf);
	
	void Out_on();
	void Out_off();
	
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

#include "H28_I_C_IO_OUT_pin.cpp"
