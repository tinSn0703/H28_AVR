
#pragma once

class C_COUNTER
{
private:

	T_COUNT _mem_counter_count;	//�J�E���g�̉�
	BOOL _mem_counter_nf :1;	//�J�E���g��ONOFF
	T_VALUE _mem_counter_limit;	//�J�E���g�̏��
	
public:

	C_COUNTER()	{}
	C_COUNTER(T_VALUE ,T_COUNT ,BOOL );
	
	BOOL Ret_flag()	{	return _mem_counter_nf;		}
	T_COUNT Ret_count()	{	return _mem_counter_count;	}
	T_VALUE Ret_limit()	{	return _mem_counter_limit;	}
	
	void On();
	void Off();
	
	BOOL Count();
	void Count_up();
	void Count_down();
	void Count_reset();
	
	BOOL Check_limit();
	
	void End();
};

#include "H28_T_C_COUNTER.cpp"