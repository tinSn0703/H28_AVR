
#pragma once

#include "H28_I_C_IO_base.h"

/**
 * PORTでOUTを扱うクラス
 */
class C_IO_OUT : public virtual C_IO_base
{
private:

	T_PORT _mem_io_out_port_rev :8;
	
public:

	/**
	 * \brief 空のコンストラクタ。_mem_io_out_dataを初期化するぐらい
	 */
	C_IO_OUT ();
	
	/**
	 * \brief 
	 * コンストラクタ。
	 * OUTとしてIOレジスタの設定を行う
	 * 
	 * \param _arg_io_addr : 使うIOレジスタ
	 * \param _arg_data_set : 設定する値。8bit。1bitごとの1,0で判断
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_data_set);
	
	void Set (T_PORT _arg_data_set);
	
	void Set_or (T_PORT _arg_data_set);
	
	void Set_and (T_PORT _arg_data_set);
	
	T_PORT Ret ();
	
	/**
	 * \brief _arg_io_num_byteを出力する
	 * 
	 * \param _arg_data_out : 出力の値
	 */
	void Out (T_PORT _arg_data_out);
	
	void Out_on ();
	
	void Out_off ();
	
	/**
	 * \brief 
	 * 指定されたIOピンに指定された値を出力する
	 * 
	 * \param _arg_num : 動かすIOピン
	 * \param _arg_nf  : High or Low
	 */
	void Out_num (E_IO_NUM _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief 
	 * 指定されたIOピンに指定された値を出力する
	 * 
	 * \param _arg_num : 動かすIOピン
	 * \param _arg_nf  : High or Low
	 */
	void Out_num (usint _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief _arg_io_num_bitをONにする
	 * 
	 * \param _arg_num : ONにするbit
	 */
	void Out_num_on (E_IO_NUM _arg_num);
	
	/**
	 * \brief 
	 * _arg_io_num_bitをONにする
	 * だいたいの型がいけるver 
	 *
	 * \param _arg_num : ONにするbit
	 */
	void Out_num_on (usint _arg_num);
	
	/**
	 * \brief _arg_io_num_bitをOFFにする
	 * 
	 * \param _arg_io_num_bit : OFFにするbit
	 */
	void Out_num_off (E_IO_NUM _arg_num);
	
	/**
	 * \brief 
	 * _arg_io_num_bitをOFFにする
	 * だいたいの型がいけるver 
	 *
	 * \param _arg_io_num_bit : OFFにするbit
	 */
	void Out_num_off (usint _arg_num);
};

#include "H28_I_C_IO_OUT.cpp"