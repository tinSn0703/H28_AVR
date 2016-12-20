
/*
OUTのみのIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
 H28 06 12 ver1.1.0 EN_IO_NUMのコンストラクタを削除
 H28 06 12 ver1.2.0 C_IO_baseのバージョンアップへの対応
*/

#pragma once

#include "H28_I_C_IO_base.h"

/*************************************************************************

IOレジスタを出力モードで操作するためのクラス

*************************************************************************/
 
class C_IO_OUT : public virtual C_IO_base
{
	
private:

	T_PORT _mem_io_out_data :8;	//出力する値。あらかじめ記録しておき出力する、
	
public:
	
	C_IO_OUT ();
	
	/**
	 * \brief 
	 *	コンストラクタ。
	 *	OUTとしてIOレジスタの設定を行う
	 * 
	 * \param _arg_io_addr		: 使うIOレジスタ
	 * \param _arg_set_io_pin	: 設定する値。8bit。1bitごとの1,0で判断
	 */
	C_IO_OUT (E_IO_PORT_ADDR _arg_io_addr, T_PORT _arg_set_io_pin);
	
	/**
	 * \brief	クラスに、出力する値を書き込む。 
	 *
	 * \param _arg_data : 記録する値
	 */
	void Write_data (T_PORT _arg_data);
	
	/**
	 * \brief	クラスに記憶された値を出力する。
	 */
	void Out ();
	
	/**
	 * \brief	IOレジスタに出力する
	 * 
	 * \param _arg_data_out : 出力する値
	 */
	void Out (T_PORT _arg_data_out);
	
	/**
	 * \brief	指定されたIOピンに指定された値を出力する
	 * 
	 * \param _arg_num : 出力するピン
	 * \param _arg_nf  : TRUE or FALSE
	 */
	void Out_num (usint _arg_num, BOOL _arg_nf);
	
	/**
	 * \brief 
	 *	指定されたIOピンに1を出力する
	 *	だいたいの型がいけるver 
	 *
	 * \param _arg_num : 出力するピン
	 */
	void Out_num_high (usint _arg_num);
	
	/**
	 * \brief 
	 *	指定されたIOピンに0を出力する
	 *	だいたいの型がいけるver 
	 *
	 * \param _arg_num : 出力するピン
	 */
	void Out_num_low (usint _arg_num);
	
	/**
	 * \brief	クラスに設定された出力の値をreturnする
	 */
	T_PORT Ret_data ()	{	return _mem_io_out_data;	}
};

/************************************************************************/
//public

C_IO_OUT ::
C_IO_OUT ()
{
	_mem_io_out_data = 0;
}

C_IO_OUT ::
C_IO_OUT
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const T_PORT			_arg_set_io_pin
)
: C_IO_base(_arg_io_addr, EI_OUT, _arg_set_io_pin)
{
	_mem_io_out_data = 0;
}

inline void
C_IO_OUT ::
Write_data (const T_PORT _arg_data)
{
	_mem_io_out_data = _arg_data;
}

inline void
C_IO_OUT ::
Out ()
{
	__PORT__ = _mem_io_out_data;
}

inline void
C_IO_OUT ::
Out (const T_PORT _arg_data_out)
{
	__PORT__ = _arg_data_out;
}

inline void
C_IO_OUT ::
Out_num
(
	const usint _arg_num,
	const BOOL	_arg_nf
)
{
	switch (_arg_nf)
	{
		case TRUE:  Out_num_high(_arg_num);	break;
		case FALSE: Out_num_low(_arg_num);	break;
	}
}

inline void
C_IO_OUT ::
Out_num_high (const usint _arg_num)
{
	__PORT__ |= (1 << _arg_num);
}

inline void
C_IO_OUT ::
Out_num_low (const usint _arg_num)
{
	__PORT__ &= ~(1 << _arg_num);
}
