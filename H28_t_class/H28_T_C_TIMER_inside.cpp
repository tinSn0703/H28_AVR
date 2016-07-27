
/*
クラス内部とかでの内部タイマ用のイメージ。継承して使ってどうぞ
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 publicメンバないから宣言しても意味ないよ<-今は昔 
*/

#pragma once

#include "H28_T_C_TIMER_inside.h"

//protected member

inline void 
C_TIMER_inside::
Set
(
	usint _arg_timer_limit, 
	usint _arg_timer_count = 0, 
	BOOL _arg_timer_flag = FALES
)
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;

	_mem_timer_inside_limit = _arg_timer_limit;
	_mem_timer_inside_count = _arg_timer_count;
	_mem_timer_inside_flag  = _arg_timer_flag;
}

//public member

C_TIMER_inside ::
C_TIMER_inside
(
	usint _arg_timer_limit,
	usint _arg_timer_count = 0,
	BOOL _arg_timer_flag = FALES
)
{
	Set(_arg_timer_limit,_arg_timer_count,_arg_timer_flag);
}

inline void 
C_TIMER_inside ::
Start ()
{
	TCNT0 = 130; //100us
	TCCR0B = (1<<CS01);
	
	_mem_timer_inside_flag = TRUE;
	_mem_timer_inside_count = 0;
}

inline BOOL 
C_TIMER_inside ::
Check ()
{
	if ((_mem_timer_inside_flag & CHECK_BIT_TF(TIFR0,TOV0)) == TRUE)
	{
		TIFR0 |= (1 << TOV0);
		
		if (_mem_timer_inside_count < _mem_timer_inside_limit)
		//カウント中,1周期経過
		{
			TCNT0  = 130; //100us
			TCCR0B = (1<<CS01);
			
			_mem_timer_inside_count++;
		}
		else
		//カウント完了
		{
			TCCR0B = 0;
			End();
			
			return TRUE;
		}
	}
	
	return FALES;
}

inline void 
C_TIMER_inside ::
End ()
{
	TCCR0B = 0;
	
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag = FALES;
}

inline BOOL
C_TIMER_inside ::
Ret_flag ()
{
	return _mem_timer_inside_flag;
}