
/*
IOピン用クラスの基礎。宣言しないでね。
 H28 05 11 ver0.0.0
 H28 05 18 ver0.1.0 メンバを削減して派生先に移した
 H28 05 22 ver1.0.0 PORTH以降しか使えなかったバグを叩き潰したついでに抽象クラスにした。
 H28 05 22 ver1.0.1 抽象クラスの使い方がよくわからんかったからpublicのないクラスにした。宣言しても意味ないよ。
 H28 05 23 ver1.0.2 抽象クラスにした
 H28 05 23 ver1.0.3 やっぱりやめた
 H28 06 12 ver1.1.0 条件演算子を用いてPORTを使うときのめんどくさいのを無くした。
 H28 06 12 ver1.2.0 デストラクタを追加。これで、子クラス終了時に、レジスタの設定が消されます。
*/

#pragma once

#include "H28_I_C_IO_base.h"

//protected member

inline void 
C_IO_base::
Set_base
(
	E_IO_PORT_ADDR _arg_io_addr, 
	E_IO_MODE _arg_io_mode
)
{
	_mem_io_base_addr = _arg_io_addr;
	
#ifdef _AVR_IOM640_H_
	_mem_io_base_addr_point = CHECK_BIT_TF(_arg_io_addr,8);
#endif
	
	_mem_io_base_mode = _arg_io_mode;
}

inline void 
C_IO_base::
Set_base
(
	E_IO_PORT_ADDR _arg_io_addr, 
	E_IO_MODE _arg_io_mode, 
	T_PORT _arg_io_num
)
{	
	Set_base(_arg_io_addr,_arg_io_mode);
	
	switch (_arg_io_mode)
	{
		case EI_IN:
		{
			DDR  = ~_arg_io_num;
			PORT =  _arg_io_num;
			
			break;
		}
		case EI_OUT:
		{
			DDR  =  _arg_io_num;
			PORT = ~_arg_io_num;
			
			break;
		}
	}
}

//public member

C_IO_base :: 
C_IO_base
(
	E_IO_PORT_ADDR _arg_io_addr,
	E_IO_MODE _arg_io_mode
)
{
	Set_base(_arg_io_addr,_arg_io_mode);
}

C_IO_base ::
C_IO_base
(
	E_IO_PORT_ADDR _arg_io_addr,
	E_IO_MODE _arg_io_mode,
	T_PORT _arg_io_num
)
{
	Set_base(_arg_io_addr,_arg_io_mode,_arg_io_num);
}

C_IO_base :: 
~ C_IO_base ()
{
	switch (_mem_io_base_mode)
	{
		case EI_IN:	 DDR  &= ~DDR;	break;
		case EI_OUT: PORT &= ~PORT;	break;
	}
}