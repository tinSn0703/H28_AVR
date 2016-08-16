
#pragma once

#include "H28_t_class.h"

/**
 * TIMER系クラスの基底クラス
 */
class C_TIMER_base
{
protected:
	
	E_TIMER_MODE	_mem_timer_base_mode :4;
	usint			_mem_timer_base_counter :16;
	E_CLOCK			_mem_timer_base_clock :3;
	
#if defined(_AVR_IOM640_H_)
	E_TIMER_ADDR	_mem_timer_base_addr :9;
	T_NUM			_mem_timer_base_addr_plus :3;

#	define __TCCRA__	_SFR_MEM8(_mem_timer_base_addr + 0)
#	define __TCCRB__	_SFR_MEM8(_mem_timer_base_addr + 1)
#	define __TCCRC__	_SFR_MEM8(_mem_timer_base_addr + 2)
#	define __TCNTL__	_SFR_MEM8(_mem_timer_base_addr + ET_OVERFLOW + 0)
#	define __TCNTH__	_SFR_MEM8(_mem_timer_base_addr + ET_OVERFLOW + 1)
#	define __OCRL__		_SFR_MEM8(_mem_timer_base_addr + ET_COMPARE + 0)
#	define __OCRH__		_SFR_MEM8(_mem_timer_base_addr + ET_COMPARE + 1)
#	define __ICRL__		_SFR_MEM8(_mem_timer_base_addr + ET_CAPUTER + 0)
#	define __ICRH__		_SFR_MEM8(_mem_timer_base_addr + ET_CAPUTER + 1)
#	define __COUNTERL__	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 0)
#	define __COUNTERH__	_SFR_MEM8(_mem_timer_base_addr + _mem_timer_base_mode + 1)
#	define __TIMSK__	_SFR_MEM8(_mem_timer_base_addr_plus + 0x6e)
#	define __TIFR__		_SFR_MEM8(_mem_timer_base_addr_plus + 0x35)
#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88P_H_)
#	define __TCCRA__	TCCR1A
#	define __TCCRB__	TCCR1B
#	define __TCCRC__	TCCR1C
#	define __TIMSK__	TIMSK1
#	define __TIFR__		TIFR1
#	define __TCNTL__	TCNT1L
#	define __TCNTH__	TCNT1H
#	define __OCRL__		OCR1AL	
#	define __OCRH__		OCR1AH
#	define __ICRL__		ICR1L
#	define __ICRH__		ICR1H
#	define __COUNTERL__	_SFR_MEM8(0x080 + _mem_timer_base_mode)
#	define __COUNTERH__	_SFR_MEM8(0x081 + _mem_timer_base_mode)
#endif
	
#	define TIME_SET_BIT 0x07 //((1 << CS2) | (1 << CS1) | (1 << CS0))

#if defined(_AVR_IOM640_H_)	
	/**
	 * \brief レジスタの初期設定を行う
	 * 
	 * \param _arg_timer_addr : 使うTIMER
	 * \param _arg_timer_mode : TIMERのモード
	 * \param _arg_timer_nf_isr : 割り込み処理を用いるかどうか
	 */
	void Set_base (E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
#elif defined(_AVR_IOM164_H_)
	/**
	 * \brief レジスタの初期設定を行う
	 *
	 * \param _arg_timer_mode : TIMERのモード
	 * \param _arg_timer_nf_isr : 割り込み処理を用いるかどうか
	 */
	void Set_base (E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
#endif

	/**
	 * \brief TIMERのモード、割り込みについての設定を行う
	 * 
	 * \param _arg_timer_mode : 設定するTIMERのモード
	 * \param _arg_timer_nf_isr : 割り込み処理を用いるかどうか
	 */
	void Set_mode(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
public:
	
	/**
	 * \brief 分周値、カウント用レジスタの設定
	 * 
	 * \param _arg_timer_clock : 分周値
	 * \param _arg_timer_counter : レジスタに入れる値
	 */
	void Set_condition(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
};