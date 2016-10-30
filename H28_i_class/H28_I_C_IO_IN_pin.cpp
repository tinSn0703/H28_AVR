
#pragma once

#include "H28_I_C_IO_IN_pin.h"

//public

C_IO_IN_pin::
C_IO_IN_pin
(
	E_IO_PORT_ADDR	_arg_io_addr, 
	E_IO_NUM		_arg_io_bit,
	BOOL			_arg_nf_port = TRUE
)
{
	C_IO_base :: Set_io_base(_arg_io_addr);
	
	_mem_io_in_pin_bit = _arg_io_bit;
	
	__DDR__  &= ~(1 << _arg_io_bit);
	
	if (_arg_nf_port)	__PORT__ |=  (1 << _arg_io_bit);
	else				__PORT__ &= ~(1 << _arg_io_bit);
}

inline BOOL 
C_IO_IN_pin::
In ()
{
	return C_IO_IN :: In_num(_mem_io_in_pin_bit);
}

inline BOOL 
C_IO_IN_pin::
In_turn ()
{
	return TURN_TF(C_IO_IN :: In_num(_mem_io_in_pin_bit));
}