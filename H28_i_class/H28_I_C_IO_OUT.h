
#pragma once

#include "H28_I_C_IO_base.h"

/**
 * PORTでOUTを扱うクラス
 */
class C_IO_OUT : public virtual C_IO_base
{
	public:

	/**
	 * \brief 空のコンストラクタ。特に何も起こらない
	 */
	C_IO_OUT ()	{}
	
	
	/**
	 * \brief 
	 * コンストラクタ。
	 * OUTとしてIOレジスタの設定を行う
	 * 
	 * \param _arg_io_addr : 使うIOレジスタ
	 * \param _arg_io_num_byte : 設定する値。8bit。1bitごとの1,0で判断
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_io_num_byte);
	
	/**
	 * \brief _arg_io_num_byteを出力する
	 * 
	 * \param _arg_io_num_byte : 出力の値
	 */
	void Out (T_PORT _arg_io_num_byte);
	
	/**
	 * \brief 設定されたbitを全てONにする 
	 */
	void Out_on ();
	
	/**
	 * \brief 設定されたbitを全てOFFにする
	 */
	void Out_off ();
	
	/**
	 * \brief _arg_io_num_bitをONにする
	 * 
	 * \param _arg_io_num_bit : ONにするbit
	 */
	void Out_num_on (E_IO_NUM _arg_io_num_bit);
	
	/**
	 * \brief 
	 * _arg_io_num_bitをONにする
	 * だいたいの型がいけるver 
	 *
	 * \param _arg_io_num_bit : ONにするbit
	 */
	void Out_num_on (usint _arg_io_num_bit);
	
	/**
	 * \brief _arg_io_num_bitをOFFにする
	 * 
	 * \param _arg_io_num_bit : OFFにするbit
	 */
	void Out_num_off (E_IO_NUM _arg_io_num_bit);
	
	/**
	 * \brief 
	 * _arg_io_num_bitをOFFにする
	 * だいたいの型がいけるver 
	 *
	 * \param _arg_io_num_bit : OFFにするbit
	 */
	void Out_num_off (usint _arg_io_num_bit);
};

#include "H28_I_C_IO_OUT.cpp"