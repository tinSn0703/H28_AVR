
/*
クラス内部とかでの内部タイマ用のイメージ。継承して使ってどうぞ
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 publicメンバないから宣言しても意味ないよ<-今は昔 
*/

#pragma once

#include "H28_t_class.h"

/*************************************************************************

タイマ-用クラス
一定時間の計測用。ループしてる中で使ってね
C_COUNTERの子にしたさある
そこまで精度はよくないのでプログラムが停止しない待ち時間程度に考えてといて
TIMER0を使ってます
TIMER2verもつくろかな

*************************************************************************/

class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count ; //カウンタ
	usint _mem_timer_inside_limit ; //カウントの上限
	BOOL _mem_timer_inside_flag  :1;  //カウントの動作フラグ
	
public:
	
	/**
	 * \brief	コンストラクタ。_mem_timer_inside_limitを0にするだけ
	 */
	C_TIMER_inside();
	
	/**
	 * \brief 
	 *	コンストラクタ
	 *	TIMERの初期設定を行う。 
	 *
	 * \param _arg_limit : カウント上限。1カウントにつき100us
	 */
	C_TIMER_inside(usint _arg_timer_limit);
	
	/**
	 * \brief タイマの開始
	 */
	void Start();
	
	/**
	 * \brief タイマの現状の確認 
	 * 
	 * \return BOOL 
	 *	TRUE  -> 完了
	 *	FALES -> それ以外
	 */
	BOOL Check();
	
	/**
	 * \brief タイマの終了
	 */
	void Stop();
	
	/**
	 * \brief カウントの動作フラグの値を返す
	 * 
	 * \return BOOL
	 *	TRUE  -> カウントを行っている
	 *	FALES -> カウントを行っていない
	 */
	BOOL Ret_state();
	
	/**
	 * \brief カウントの上限値を変更する演算子
	 * 
	 * \param _arg_timer_limit : 新しい上限
	 */
	C_TIMER_inside & operator = (usint _arg_timer_limit);
	
	/**
	 * \brief 
	 * if文などでの比較用の演算子
	 * C_TIMER_inside::Ret_state()と比較する
	 * 
	 * \param _arg_timer_inside : みたまま
	 * \param _arg_timer_flag_comp : 比較するやつ
	 * 
	 * \return friend bool 等しいときture
	 */
	friend bool operator == (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
	
	/**
	 * \brief 
	 * if文などでの比較用の演算子
	 * C_TIMER_inside::Ret_state()と比較する
	 * 
	 * \param _arg_timer_inside : みたまま
	 * \param _arg_timer_flag_comp : 比較するやつ
	 * 
	 * \return friend bool 等しくないときture
	 */
	friend bool operator != (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
};

/************************************************************************/
//public

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
	BOOL			_arg_timer_flag_comp
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
	BOOL			_arg_timer_flag_comp
)
{
	if (_arg_timer_inside._mem_timer_inside_flag != _arg_timer_flag_comp)
	{
		return true;
	}
	
	return false;
}