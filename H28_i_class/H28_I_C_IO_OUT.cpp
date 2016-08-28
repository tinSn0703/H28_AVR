
/*
OUTのみのIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
 H28 06 12 ver1.1.0 EN_IO_NUMのコンストラクタを削除
 H28 06 12 ver1.2.0 C_IO_baseのバージョンアップへの対応
*/

#pragma once

#include "H28_I_C_IO_OUT.h"

//public
C_IO_OUT ::
C_IO_OUT
(
	E_IO_PORT_ADDR _arg_io_addr, 
	T_PORT _arg_io_num_byte
)
: C_IO_base(_arg_io_addr, EI_OUT, _arg_io_num_byte)
{}

inline void 
C_IO_OUT ::
Out (T_PORT _arg_io_num_byte)
{
	__PORT__ = _arg_io_num_byte;
}

inline void 
C_IO_OUT ::
Out_on ()
{
	Out(__DDR__);
}

inline void 
C_IO_OUT ::
Out_off ()
{
	Out(~__DDR__);
}

inline void 
C_IO_OUT :: 
Out_num
(
	E_IO_NUM _arg_num, 
	BOOL _arg_nf
)
{
	__PORT__ |= (_arg_nf << _arg_num);
}

inline void
C_IO_OUT ::
Out_num
(
	usint _arg_num,
	BOOL _arg_nf
)
{
	__PORT__ |= (_arg_nf << _arg_num);
}

inline void 
C_IO_OUT ::
Out_num_on (E_IO_NUM _arg_io_num_bit)
{
	__PORT__ |= (1 << _arg_io_num_bit);
}

inline void 
C_IO_OUT ::
Out_num_on (usint _arg_io_num_bit)
{
	__PORT__ |= (1 << _arg_io_num_bit);
}

inline void 
C_IO_OUT ::
Out_num_off (E_IO_NUM _arg_io_num_bit)
{
	__PORT__ &= ~(1 << _arg_io_num_bit);
}

inline void 
C_IO_OUT ::
Out_num_off (usint _arg_io_num_bit)
{
	__PORT__ &= ~(1 << _arg_io_num_bit);
}