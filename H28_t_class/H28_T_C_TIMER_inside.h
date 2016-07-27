
#pragma once

#include "H28_t_class.h"

/**
 * タイマを伴ったカウント用クラス
 * C_COUNTERの子にしたさある
 * TIMER0を使ってます
 * TIMER2verもつくろかな
 */
class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count :8; //カウンタ
	usint _mem_timer_inside_limit :8; //カウントの上限
	BOOL _mem_timer_inside_flag  :1;  //カウントの動作フラグ
	
protected:
	
	/**
	 * \brief コンストラクタの中身。引数はコンストラクタを参照
	 */
	void Set(usint _arg_timer_limit, usint _arg_timer_count, BOOL _arg_timer_flag);
	
public:
	
	C_TIMER_inside()	{}
		
	/**
	 * \brief コンストラクタ
	 * 
	 * \param _arg_limit : カウント回数。1カウントにつき100us
	 * \param _arg_count : 最初に埋めて置くカウンタの値
	 * \param _arg_flag : フラグの初期設定
	 */
	C_TIMER_inside(usint _arg_timer_limit, usint _arg_timer_count, BOOL _arg_timer_flag);
	
	/**
	 * \brief タイマカウントの開始
	 */
	void Start();
	
	/**
	 * \brief タイマカウントの現状の確認 
	 * 
	 * \return BOOL 
	 *	TRUE  -> 完了
	 *	FALES -> それ以外
	 */
	BOOL Check();
	
	/**
	 * \brief カウントの終了
	 */
	void End();
	
	/**
	 * \brief カウントの動作フラグの値を返す
	 * 
	 * \return BOOL
	 *	TRUE  -> カウントを行っている
	 *	FALES -> カウントを行っていない
	 */
	BOOL Ret_flag();
};

#include "H28_T_C_TIMER_inside.cpp"