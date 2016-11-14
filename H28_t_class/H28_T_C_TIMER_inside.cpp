
/*
クラス内部とかでの内部タイマ用のイメージ。継承して使ってどうぞ
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 publicメンバないから宣言しても意味ないよ<-今は昔 
*/

#pragma once

//public member

C_TIMER_inside :: 
C_TIMER_inside ()
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;
	
	_mem_timer_inside_limit = 0;
}

C_TIMER_inside ::
C_TIMER_inside (usint _arg_timer_limit)
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;

	_mem_timer_inside_limit = _arg_timer_limit;
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag  = FALSE;
}

inline void 
C_TIMER_inside ::
Start ()
{
	_mem_timer_inside_flag = TRUE;
	_mem_timer_inside_count = 0;
	
	TCNT0 = 130; //100us
	TCCR0B = (1<<CS01);
}

inline BOOL 
C_TIMER_inside ::
Check ()
{
	if ((_mem_timer_inside_flag & F_Check_bit_bool(TIFR0, TOV0)) == TRUE)
	{
		TCNT0  = 130; //100us
		
		TIFR0 |= (1 << TOV0);
		
		if (_mem_timer_inside_count < _mem_timer_inside_limit)
		//カウント中,1周期経過
		{			
			_mem_timer_inside_count++;
		}
		else
		//カウント完了
		{			
			Stop();
			
			return TRUE;
		}
	}
	
	return FALSE;
}

inline void 
C_TIMER_inside ::
Stop ()
{
	TCCR0B = 0;
	
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag = FALSE;
}

inline BOOL
C_TIMER_inside ::
Ret_state ()
{
	return _mem_timer_inside_flag;
}

inline C_TIMER_inside &
C_TIMER_inside :: 
operator = (usint _arg_timer_limit)
{
	_mem_timer_inside_limit = _arg_timer_limit;
	
	return *this;
}

inline bool
operator == 
(
	C_TIMER_inside &_arg_timer_inside,
	BOOL _arg_timer_flag_comp
)
{
	if (_arg_timer_inside._mem_timer_inside_flag == _arg_timer_flag_comp)
	{
		return true;
	}
	
	return false;
}

inline bool
operator !=
(
	C_TIMER_inside &_arg_timer_inside,
	BOOL _arg_timer_flag_comp
)
{
	if (_arg_timer_inside._mem_timer_inside_flag != _arg_timer_flag_comp)
	{
		return true;
	}
	
	return false;
}
