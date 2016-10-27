
#pragma once

#include "H28_T_C_TIMER_base.cpp"

/**
 * TIMERを扱うクラス
 */
class C_TIMER : public virtual C_TIMER_base
{	
public:

	C_TIMER()	{}
	
#if defined(_AVR_IOM640_H_)

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

#elif defined(_AVR_IOM164_H_)

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

#endif

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
	usint Ret_time();
	
	/**
	 * \brief 分周値の設定を返す
	 * 
	 * \return E_CLOCK return
	 */
	E_CLOCK Ret_clock();
};

#include "H28_T_C_TIMER.cpp"