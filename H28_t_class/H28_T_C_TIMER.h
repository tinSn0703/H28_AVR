
/*
カウント程度はできる。機能的にはStopWatchのようなもの
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_baseのコンストラクタでコンストラクタの設定をすることにした.
 H28 05 20 ver 1.0.0 C_TOMER_baseに設定用の関数と変数を移し、動作系の関数の中身を持ってきた
*/

#pragma once

#include "H28_T_C_TIMER_base.h"

/*************************************************************************

TIMERを操作するためのクラス

*************************************************************************/

class C_TIMER : public virtual C_TIMER_base
{	
public:

	C_TIMER()	{}
	
#if defined(_AVR_IOM640_H_) /********************************************/

	/**
	 * \brief コンストラクタ
	 * 
	 * \param _arg_timer_addr : 使うTIMERの番号
	 * \param _arg_timer_mode : モードの選択
	 * \param _arg_timer_nf_isr : 割り込み処理の使用について
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief コンストラクタ
	 * 
	 * \param _arg_timer_addr : 使うTIMERの番号
	 * \param _arg_timer_mode : モードの選択
	 * \param _arg_timer_clock : 分周値
	 * \param _arg_timer_counter : レジスタに入れる値
	 * \param _arg_timer_nf_isr : 割り込み処理の使用について
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
	
#elif defined(_AVR_IOM164_H_) /******************************************/

	/**
	 * \brief コンストラクタ
	 * 
	 * \param _arg_timer_mode : モードの選択
	 * \param _arg_timer_nf_isr : 割り込み処理の使用について
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief コンストラクタ
	 * 
	 * \param _arg_timer_mode : モードの選択
	 * \param _arg_timer_clock : 分周値
	 * \param _arg_timer_counter : レジスタに入れる値
	 * \param _arg_timer_nf_isr : 割り込み処理の使用について
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
	
#endif /*****************************************************************/

	/**
	 * \brief タイマかウンタを開始する
	 */
	void Start();
	
	/**
	 * \brief 引数の値を用いてタイマカウンタを開始する
	 * 
	 * \param _arg_timer_clock : 分周値
	 * \param _arg_timer_counter : レジスタに入れる値
	 */
	void Start(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
	
	/**
	 * \brief タイマカウンタの完了を確認する
	 * 
	 * \param _arg_timer_continue : 完了時にタイマカウンタを再度行うか
	 * 
	 * \return BOOL
	 *	TRUE  -> 完了
	 *	FALES -> 未了
	 */
	BOOL Flag_timer(BOOL _arg_timer_continue);
	
	/**
	 * \brief タイマカウンタの完了を確認する
	 * 
	 * \param _arg_timer_continue : 完了時にタイマカウンタを再度行うか
	 * 
	 * \return BOOL
	 *	TRUE  -> 完了
	 *	FALES -> 未了
	 */
	BOOL Flag_timer_overflow(BOOL _arg_timer_continue);
	
	/**
	 * \brief タイマカウンタの完了を確認する
	 * 
	 * \param _arg_timer_continue : 完了時にタイマカウンタを再度行うか
	 * 
	 * \return BOOL
	 *	TRUE  -> 完了
	 *	FALES -> 未了
	 */
	BOOL Flag_timer_compare(BOOL _arg_timer_continue);
	
	/**
	 * \brief タイマカウンタを終了する
	 */
	void Stop();
	
	/**
	 * \brief TCNTの値を返す。
	 * 
	 * \return usint : TCNTの値。10bit
	 */
	usint Ret_time()	{	return ((__TCNTH__ << 8) | __TCNTL__);	}
	
	/**
	 * \brief 分周値の設定を返す
	 * 
	 * \return E_CLOCK return
	 */
	E_CLOCK Ret_clock()	{	return _mem_timer_base_clock;	}
};

/************************************************************************/
//public

#if defined(_AVR_IOM640_H_) /********************************************/

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_ADDR	_arg_timer_addr,
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
}

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_ADDR	_arg_timer_addr,
	E_TIMER_MODE	_arg_timer_mode,
	E_CLOCK			_arg_timer_clock,
	usint			_arg_timer_counter,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_addr, _arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base :: Set_condition(_arg_timer_clock, _arg_timer_counter);
}

#elif defined(_AVR_IOM164_H_) /******************************************/

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_MODE	_arg_timer_mode,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_mode, _arg_timer_nf_isr);
}

inline
C_TIMER ::
C_TIMER
(
	E_TIMER_MODE	_arg_timer_mode,
	E_CLOCK			_arg_timer_clock,
	usint			_arg_timer_counter,
	BOOL			_arg_timer_nf_isr = FALSE
)
{
	C_TIMER_base :: Set_timer(_arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base :: Set_condition(_arg_timer_clock, _arg_timer_counter);
}

#endif /*****************************************************************/

inline void
C_TIMER ::
Start ()
{
	Stop();
	
	__COUNTERH__ = (_mem_timer_base_counter >> 8);
	__COUNTERL__ = _mem_timer_base_counter;
	
	__TCCRB__ |= _mem_timer_base_clock;
}

inline void
C_TIMER ::
Start
(
	E_CLOCK _arg_timer_clock,
	usint	_arg_timer_counter
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
	if (F_Check_bit_bool(__TIFR__, OCFA))
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

inline void
C_TIMER ::
Stop ()
{
	__TCCRB__ &= TIME_SET_BIT;
}
