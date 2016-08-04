
/*
カウント程度はできる。機能的にはStopWatchのようなもの
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_baseのコンストラクタでコンストラクタの設定をすることにした.
 H28 05 20 ver 1.0.0 C_TOMER_baseに設定用の関数と変数を移し、動作系の関数の中身を持ってきた
*/

#pragma once

#include "H28_T_C_TIMER.h"

//public
#if defined(_AVR_IOM640_H_)
inline 
C_TIMER::
C_TIMER
(
	E_TIMER_ADDR _arg_timer_addr, 
	E_TIMER_MODE _arg_timer_mode, 
	BOOL _arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base::Set_base(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
}

inline 
C_TIMER::
C_TIMER
(
	E_TIMER_ADDR _arg_timer_addr, 
	E_TIMER_MODE _arg_timer_mode, 
	E_CLOCK _arg_timer_clock, 
	usint _arg_timer_counter, 
	BOOL _arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base::Set_base(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
}
#elif defined(_AVR_IOM164_H_)
inline
C_TIMER::
C_TIMER
(
	E_TIMER_MODE _arg_timer_mode,
	BOOL _arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base::Set_base(_arg_timer_mode, _arg_timer_nf_isr);
}

inline
C_TIMER::
C_TIMER
(
	E_TIMER_MODE _arg_timer_mode,
	E_CLOCK _arg_timer_clock,
	usint _arg_timer_counter,
	BOOL _arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base::Set_base(_arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
}
#endif

inline void 
C_TIMER::
Start ()
{
	Stop();
	
	__COUNTERH__ = (_mem_timer_base_counter >> 8);
	__COUNTERL__ = _mem_timer_base_counter;
	
	__TCCRB__ |= _mem_timer_base_clock;
}

inline void 
C_TIMER::
Start
(
	E_CLOCK _arg_timer_clock, 
	usint _arg_timer_counter
)
{
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
	
	Start();
}

inline BOOL 
C_TIMER :: 
Flag_timer_overflow (BOOL _arg_timer_continue = TRUE)
{
	if (__TIFR__ & (1 << TOV))
	{
		__COUNTERH__ = (_mem_timer_base_counter >> 8);
		__COUNTERL__ = _mem_timer_base_counter;
		
		if (_arg_timer_continue == FALSE)
		{
			Stop();
		}
		
		__TIFR__ |= (1 << TOV);
	
		return TRUE;	
	}
	
	return FALSE;
}

inline BOOL
C_TIMER ::
Flag_timer_compare (BOOL _arg_timer_continue = TRUE)
{
	if (CHECK_BIT_TF(__TIFR__,OCFA))
	{
		__TIFR__ |= (1 << OCFA);
	
		if (_arg_timer_continue == FALSE)
		{
			Stop();
		}
	
		return TRUE;
	}
	
	return FALSE;
}

inline BOOL 
C_TIMER ::
Flag_timer (BOOL _arg_timer_continue = TRUE)
{	
	switch (_mem_timer_base_mode)
	{
		case ET_OVERFLOW:
		{
			return Flag_timer_overflow(_arg_timer_continue);
		}
		case ET_COMPARE:
		{
			return Flag_timer_compare(_arg_timer_continue);
		}
		case ET_CAPUTER:
		{
			
		}
		break;
	}
	
	return FALSE;
}

inline void C_TIMER::Stop()
{
	__TCCRB__ &= TIME_SET_BIT;
}