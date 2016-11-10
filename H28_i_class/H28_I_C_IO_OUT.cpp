
#pragma once

//public

C_IO_OUT :: 
C_IO_OUT ()
{
	_mem_io_out_data = 0;
}

C_IO_OUT ::
C_IO_OUT
(
	E_IO_PORT_ADDR	_arg_io_addr, 
	T_PORT			_arg_set_io_pin
)
: C_IO_base(_arg_io_addr, EI_OUT, _arg_set_io_pin)
{
	_mem_io_out_data = 0;
}

inline void 
C_IO_OUT :: 
Write_data (T_PORT _arg_data)
{
	_mem_io_out_data = _arg_data;
}

inline T_PORT 
C_IO_OUT :: 
Ret_data ()
{
	return _mem_io_out_data;
}

inline void 
C_IO_OUT :: 
Out ()
{
	__PORT__ = _mem_io_out_data;
}

inline void 
C_IO_OUT :: 
Out (T_PORT _arg_data_out)
{	
	__PORT__ = _arg_data_out;
}

inline void 
C_IO_OUT :: 
Out_num
(
	E_IO_NUM _arg_num,
	BOOL	 _arg_nf
)
{
	switch (_arg_nf)
	{
		case TRUE:  Out_num_on(_arg_num);	break;
		case FALSE: Out_num_off(_arg_num);	break;
	}
}

inline void 
C_IO_OUT :: 
Out_num
(
	usint _arg_num, 
	BOOL _arg_nf
)
{
	switch (_arg_nf)
	{
		case TRUE:  Out_num_on(_arg_num);	break;
		case FALSE: Out_num_off(_arg_num);	break;
	}
}

inline void 
C_IO_OUT :: 
Out_num_on (E_IO_NUM _arg_num)
{	
	__PORT__ |= (1 << _arg_num);
}

inline void 
C_IO_OUT :: 
Out_num_on (usint _arg_num)
{	
	__PORT__ |= (1 << _arg_num);
}

inline void 
C_IO_OUT :: 
Out_num_off (E_IO_NUM _arg_num)
{
	__PORT__ &= ~(1 << _arg_num);
}

inline void 
C_IO_OUT :: 
Out_num_off (usint _arg_num)
{	
	__PORT__ &= ~(1 << _arg_num);
}