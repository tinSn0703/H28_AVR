
/*
クラス内部とかでの内部タイマ用のイメージ。継承して使ってどうぞ
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 publicメンバないから宣言しても意味ないよ<-今は昔 
*/

#pragma once

#include "H28_t_class.h"

class C_TIMER_inside
/*
タイマを伴ったカウント用クラス
C_COUNTERの子にしたさある
TIMER0を使ってます
TIMER2verもつくろかな
*/
{
	private:
	uchar _mem_timer_inside_count :8;
	uchar _mem_timer_inside_limit :8;
	BOOL _mem_timer_inside_flag  :1;
	
	protected:
	
	void Set(T_VALUE ,T_COUNT ,BOOL );
	
	public:
	
	C_TIMER_inside()	{}
	C_TIMER_inside(T_VALUE ,T_COUNT ,BOOL );
	
	void Start();
	BOOL Check();
	void End();
	
	BOOL Ret_flag()	{	return _mem_timer_inside_flag;	}
};

//protected member

/**
 * \brief : コンストラクタの中身。引数はコンストラクタを参照
 */
inline void 
C_TIMER_inside::
Set
(
	T_VALUE _arg_timer_inside_limit, 
	T_COUNT _arg_timer_inside_count = 0, 
	BOOL _arg_timer_inside_flag = FALES
)
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;

	_mem_timer_inside_limit = _arg_timer_inside_limit;
	_mem_timer_inside_count = _arg_timer_inside_count;
	_mem_timer_inside_flag  = _arg_timer_inside_flag;
}

//public member

/**
 * \brief コンストラクタ
 * 
 * \param _arg_timer_inside_limit : カウント回数。1カウントにつき100us
 * \param _arg_timer_inside_count : 最初に埋めて置くカウンタの値
 * \param _arg_timer_inside_flag : フラグの初期設定
 */
C_TIMER_inside::
C_TIMER_inside
(
	T_VALUE _arg_timer_inside_limit,
	T_COUNT _arg_timer_inside_count = 0,
	BOOL _arg_timer_inside_flag = FALES
)
{
	Set(_arg_timer_inside_limit,_arg_timer_inside_count,_arg_timer_inside_flag);
}

/**
 * \brief タイマカウントの開始
 */
inline void 
C_TIMER_inside::
Start ()
{
	TCNT0 = 130; //100us
	TCCR0B = (1<<CS01);
	
	_mem_timer_inside_flag = TRUE;
	_mem_timer_inside_count = 0;
}

/**
 * \brief タイマカウントの現状の確認 
 * 
 * \return BOOL 
 *	TRUE  -> 完了
 *	FALES -> それ以外
 */
inline BOOL 
C_TIMER_inside::
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

/**
 * \brief : カウントの終了
 */
inline void 
C_TIMER_inside::
End ()
{
	TCCR0B = 0;
	
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag = FALES;
}