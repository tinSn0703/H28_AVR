
/*
タイマを秒数以上にカウントするようの構造体。あのカチカチ数を数える奴みたいな感じに使ってね
 H28 05 07 ver0.0.0
 H28 05 16 ver1.0.0 classにした。何となく使いづらいので要改造。特にflagやcountを行うあたり
*/

#pragma once

#include "H28_T_C_COUNTER.h"

inline 
C_COUNTER::
C_COUNTER
(
	T_VALUE _arg_counter_limit, 
	T_COUNT _arg_counter_count = 0, 
	BOOL _arg_counter_nf = FALES
)
{
	_mem_counter_count = _arg_counter_count;
	_mem_counter_nf  = _arg_counter_nf;
	_mem_counter_limit = _arg_counter_limit;
}

inline void 
C_COUNTER::
On ()
{
	_mem_counter_nf = TRUE;
}

inline void 
C_COUNTER::
Off ()
{
	_mem_counter_nf = FALES;
}

BOOL 
C_COUNTER::
Count ()
{
	if (_mem_counter_nf == TRUE)
	{
		_mem_counter_count ++;
		
		if (_mem_counter_count == _mem_counter_limit)
		{
			End();
			
			return TRUE;
		}
	}
	
	return FALES;
}

inline void 
C_COUNTER::
Count_up ()
{
	_mem_counter_count ++;
}
	
inline void 
C_COUNTER::
Count_down ()
{
	_mem_counter_count --;
}

inline BOOL 
C_COUNTER::
Check_limit ()
{
	if (_mem_counter_count == _mem_counter_limit)	return TRUE;
	
	return FALES;
}

inline void 
C_COUNTER::
Count_reset ()
{
	_mem_counter_count = 0;
}

inline void 
C_COUNTER::
End ()
{
	_mem_counter_count = 0;
	_mem_counter_nf = FALES;
}