
#pragma once

class C_REGISTER
{
private:
	
	uint _mem_register_addr;
	BOOL _mem_register_select :1;
	
protected:
	
	uint Ret_addr();
	
#	define REGISTER (_mem_register_select == TRUE ? _SFR_MEM8(Ret_addr()) : _SFR_IO8(Ret_addr()))
	
public:
	
	template <class T>
	C_REGISTER & operator = (T _arg_data);
	
	template <class T>
	friend T operator + (C_REGISTER & , T );
	
	template <class T>
	friend T operator - (C_REGISTER & , T );
	
	template <class T>
	friend T operator * (C_REGISTER & , T );
	
	template <class T>
	friend T operator / (C_REGISTER & , T );
	
	template <class T>
	friend T operator & (C_REGISTER & , T );
	
	template <class T>
	friend T operator | (C_REGISTER & , T );
	
	template <class T>
	friend T operator << (C_REGISTER & , T );
	
	template <class T>
	friend T operator >> (C_REGISTER & , T );
	
};