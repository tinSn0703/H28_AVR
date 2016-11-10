
#pragma once

//public

C_IO_IN ::
C_IO_IN
(
	E_IO_PORT_ADDR	_arg_io_addr, 
	T_PORT			_arg_set_io_pin = 0xff
)
{
	C_IO_base :: Set_io_base(_arg_io_addr, EI_IN, _arg_set_io_pin);
}

inline T_PORT 
C_IO_IN ::
In ()
{
	return __PIN__;
}

inline BOOL 
C_IO_IN ::
In_num (E_IO_NUM _arg_num)
{		
	return F_Check_bit_bool(__PIN__, _arg_num);
}
