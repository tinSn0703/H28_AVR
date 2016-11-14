
#pragma once

#include "H28_t_class.h"

/**
 * タイマ-用クラス
 * 一定時間の計測用。ループしてる中で使ってね
 * C_COUNTERの子にしたさある
 * そこまで精度はよくないのでプログラムが停止しない待ち時間程度に考えてといて
 * TIMER0を使ってます
 * TIMER2verもつくろかな
 */
class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count ; //カウンタ
	usint _mem_timer_inside_limit ; //カウントの上限
	BOOL _mem_timer_inside_flag  :1;  //カウントの動作フラグ
	
public:
	
	/**
	 * \brief 
	 * コンストラクタ。_mem_timer_inside_limitを0にするだけ
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

#include "H28_T_C_TIMER_inside.cpp"