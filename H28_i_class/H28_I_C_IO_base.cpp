
#pragma once

//protected member

inline void 
C_IO_base::
Set_io_base
(
	E_IO_PORT_ADDR _arg_io_addr
)
{
	_mem_io_base_addr = _arg_io_addr;
	
#ifdef _AVR_IOM640_H_

	_mem_io_base_addr_point = F_Check_bit_bool(_arg_io_addr, 8);

#endif

}

inline void 
C_IO_base::
Set_io_base
(
	E_IO_PORT_ADDR	_arg_io_addr, 
	E_IO_MODE		_arg_io_mode, 
	T_PORT			_arg_set_io_pin
)
{	
	Set_io_base(_arg_io_addr);
	
	switch (_arg_io_mode)
	{
		case EI_IN:
		{
			__DDR__  = ~_arg_set_io_pin;
			__PORT__ =  _arg_set_io_pin;
			
			break;
		}
		case EI_OUT:
		{
			__DDR__  =  _arg_set_io_pin;
			__PORT__ = ~_arg_set_io_pin;
			
			break;
		}
	}
}

//public member

C_IO_base :: 
C_IO_base
(
	E_IO_PORT_ADDR _arg_io_addr
)
{
	Set_io_base(_arg_io_addr);
}

C_IO_base ::
C_IO_base
(
	E_IO_PORT_ADDR	_arg_io_addr,
	E_IO_MODE		_arg_io_mode,
	T_PORT			_arg_set_io_pin
)
{
	Set_io_base(_arg_io_addr, _arg_io_mode, _arg_set_io_pin);
}