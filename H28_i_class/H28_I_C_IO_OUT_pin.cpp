
/*
1ピン用

 H28 06 13 ver0.0.0
*/

#pragma once

#include "H28_I_C_IO_OUT.cpp"

class C_IO_OUT_pin : protected C_IO_OUT
{
private:

	E_IO_NUM _mem_io_out_pin_bit :3;
	
	BOOL _mem_io_out_pin_set :1;
	
public:

	C_IO_OUT_pin()	{}
	C_IO_OUT_pin(E_IO_PORT_ADDR ,E_IO_NUM );
	
	BOOL Ret()	{	return _mem_io_out_pin_set;	}
	
	void Set(BOOL );
	void Chen();
	
	void Out(); 
	void Out(BOOL );
	
	void Out_on();
	void Out_off();
	
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

//public
C_IO_OUT_pin ::
C_IO_OUT_pin
(
	E_IO_PORT_ADDR _arg_io_addr, 
	E_IO_NUM _arg_io_bit
)
: C_IO_base(_arg_io_addr,EI_OUT)
{
	_mem_io_out_pin_set = FALSE;
	_mem_io_out_pin_bit = _arg_io_bit;
	
	__DDR__  |=  (1 << _arg_io_bit);
	__PORT__ &= ~(1 << _arg_io_bit);
}

inline void 
C_IO_OUT_pin :: 
Set (BOOL _arg_set)
{
	_mem_io_out_pin_set = _arg_set;
}

inline void 
C_IO_OUT_pin :: 
Chen ()
{
	_mem_io_out_pin_set = TURN_TF(_mem_io_out_pin_set);
}

inline void 
C_IO_OUT_pin :: 
Out()
{
	switch (_mem_io_out_pin_set)
	{
		case TRUE:	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);	break;
		case FALSE:	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out (BOOL _arg_nf)
{
	_mem_io_out_pin_set = _arg_nf;
	
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
	_mem_io_out_pin_set = TRUE;
	
	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);
}

inline void 
C_IO_OUT_pin::
Out_off ()
{
	_mem_io_out_pin_set = FALSE;
	
	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);
}
