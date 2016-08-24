
/*
1ピン用

 H28 06 13 ver0.0.0
*/

#pragma once

#include "H28_I_C_IO_OUT_pin.h"

//	public member

C_IO_OUT_pin ::
C_IO_OUT_pin
(
	E_IO_PORT_ADDR _arg_io_addr, 
	E_IO_NUM _arg_io_bit
)
: C_IO_base(_arg_io_addr)
{
	_mem_io_out_pin_nf_set = FALSE;
	_mem_io_out_pin_bit = _arg_io_bit;
	
	__DDR__  |=  (1 << _arg_io_bit);
	__PORT__ &= ~(1 << _arg_io_bit);
}

inline BOOL 
C_IO_OUT_pin :: 
Ret ()
{
	return _mem_io_out_pin_nf_set;
}

inline void 
C_IO_OUT_pin :: 
Set (BOOL _arg_set)
{
	_mem_io_out_pin_nf_set = _arg_set;
}

inline void 
C_IO_OUT_pin :: 
Chen ()
{
	_mem_io_out_pin_nf_set = TURN_TF(_mem_io_out_pin_nf_set);
}

inline void 
C_IO_OUT_pin :: 
Out()
{
	switch (_mem_io_out_pin_nf_set)
	{
		case TRUE:	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out (BOOL _arg_nf)
{
	_mem_io_out_pin_nf_set = _arg_nf;
	
	switch (_arg_nf)
	{
		case TRUE:	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out_on ()
{
	_mem_io_out_pin_nf_set = TRUE;
	
	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);
}

inline void 
C_IO_OUT_pin::
Out_off ()
{
	_mem_io_out_pin_nf_set = FALSE;
	
	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);
}
