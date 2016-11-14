
#pragma once

//	public member

C_IO_OUT_pin :: 
C_IO_OUT_pin ()
{
	_mem_io_out_pin_data = FALSE;
};

C_IO_OUT_pin ::
C_IO_OUT_pin
(
	E_IO_PORT_ADDR _arg_io_addr, 
	E_IO_NUM _arg_io_bit
)
: C_IO_base(_arg_io_addr)
{
	_mem_io_out_pin_data = FALSE;
	_mem_io_out_pin_bit = _arg_io_bit;
	
	__DDR__  |=  (1 << _arg_io_bit);
	__PORT__ &= ~(1 << _arg_io_bit);
}

inline BOOL 
C_IO_OUT_pin :: 
Ret_data ()
{
	return _mem_io_out_pin_data;
}

inline void 
C_IO_OUT_pin :: 
Write_data (BOOL _arg_data)
{
	_mem_io_out_pin_data = _arg_data;
}

inline void 
C_IO_OUT_pin :: 
Turn_data ()
{
	_mem_io_out_pin_data = F_Turn_bool(_mem_io_out_pin_data);
}

inline void 
C_IO_OUT_pin :: 
Out()
{
	switch (_mem_io_out_pin_data)
	{
		case TRUE:	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out (BOOL _arg_nf)
{
	_mem_io_out_pin_data = _arg_nf;
	
	switch (_arg_nf)
	{
		case TRUE:	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out_high ()
{	
	C_IO_OUT :: Out_num_high(_mem_io_out_pin_bit);
}

inline void 
C_IO_OUT_pin::
Out_low ()
{
	C_IO_OUT :: Out_num_low(_mem_io_out_pin_bit);
}
