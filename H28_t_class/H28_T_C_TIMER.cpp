﻿
/*
カウント程度はできる。機能的にはStopWatchのようなもの
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_baseのコンストラクタでコンストラクタの設定をすることにした.
 H28 05 20 ver 1.0.0 C_TOMER_baseに設定用の関数と変数を移し、動作系の関数の中身を持ってきた
*/

#pragma once

#include "H28_T_C_TIMER_base.cpp"

class C_TIMER : public virtual C_TIMER_base
{
	public:
	C_TIMER()	{}
		
#if defined(_AVR_IOM640_H_)
	C_TIMER(E_TIMER_ADDR ,E_TIMER_MODE ,E_LOGIC );
	C_TIMER(E_TIMER_ADDR ,E_TIMER_MODE ,E_CLOCK ,T_VALUE ,E_LOGIC );
#elif defined(_AVR_IOM164_H_)
	C_TIMER(E_TIMER_MODE ,E_LOGIC );
	C_TIMER(E_TIMER_MODE ,E_CLOCK ,T_VALUE ,E_LOGIC );
#endif

	void Start();
	void Start(E_CLOCK ,T_VALUE );
	
	E_LOGIC Flag_timer(E_LOGIC );
	
	void Stop();
};

//public
#if defined(_AVR_IOM640_H_)
inline 
C_TIMER::
C_TIMER
(
	E_TIMER_ADDR _arg_timer_addr, 
	E_TIMER_MODE _arg_timer_mode, 
	E_LOGIC _arg_timer_nf_isr = FALES
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
	T_VALUE _arg_timer_counter, 
	E_LOGIC _arg_timer_nf_isr = FALES
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
	E_LOGIC _arg_timer_nf_isr = FALES
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
	T_VALUE _arg_timer_counter,
	E_LOGIC _arg_timer_nf_isr = FALES
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
	
	COUNTERH = ((_mem_timer_base_counter >> 8) & 0xff);
	COUNTERL = (_mem_timer_base_counter & 0xff);
	
	TCCRB |= _mem_timer_base_clock;
}

inline void 
C_TIMER::
Start
(
	E_CLOCK _arg_timer_clock, 
	T_VALUE _arg_timer_counter
)
{
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
	
	Start();
}

E_LOGIC 
C_TIMER::
Flag_timer (E_LOGIC _arg_timer_continue = TRUE)
{
	usint mode_bit = 0;
	
	switch (_mem_timer_base_mode)
	{
		case ET_CAPUTER:	mode_bit = ICF;		break;
		case ET_COMPARE:	mode_bit = OCFA;	break;
		case ET_OVERFLOW:	mode_bit = TOV;		break;
	}
	
	if (CHECK_BIT_TF(TIFR,mode_bit))
	{
		TIFR |= (1 << mode_bit);
		
		if (_arg_timer_continue)	Start();
		
		return TRUE;
	}
	
	return FALES;
}

inline void C_TIMER::Stop()
{
	TCCRB &= ~TIME_SET_BIT;
}