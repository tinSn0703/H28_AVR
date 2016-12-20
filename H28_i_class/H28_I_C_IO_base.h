
/*
IOピン用クラスの基礎。宣言しないでね。
 H28 05 11 ver0.0.0
 H28 05 18 ver0.1.0 メンバを削減して派生先に移した
 H28 05 22 ver1.0.0 PORTH以降しか使えなかったバグを叩き潰したついでに抽象クラスにした。
 H28 05 22 ver1.0.1 抽象クラスの使い方がよくわからんかったからpublicのないクラスにした。宣言しても意味ないよ。
 H28 05 23 ver1.0.2 抽象クラスにした
 H28 05 23 ver1.0.3 やっぱりやめた
 H28 06 12 ver1.1.0 条件演算子を用いてPORTを使うときのめんどくさいのを無くした。
 H28 06 12 ver1.2.0 デストラクタを追加。これで、子クラス終了時に、レジスタの設定が消されます。
*/

#pragma once

#include "H28_i_class.h"

/*************************************************************************

IOレジスタを操作するためのクラスのベース。継承してね。

*************************************************************************/

class C_IO_base
{
protected:
	
#if defined(_AVR_IOM640_H_)

	E_IO_PORT_ADDR	_mem_io_base_addr :9;
	BOOL			_mem_io_base_addr_point :1;
	
#	define __PIN__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 0) : _SFR_IO8(_mem_io_base_addr + 0))
#	define __DDR__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 1) : _SFR_IO8(_mem_io_base_addr + 1))
#	define __PORT__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 2) : _SFR_IO8(_mem_io_base_addr + 2))

#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_)

	E_IO_PORT_ADDR	_mem_io_base_addr :8;
	
#	define __PIN__	_SFR_IO8(_mem_io_base_addr + 0)
#	define __DDR__	_SFR_IO8(_mem_io_base_addr + 1)
#	define __PORT__	_SFR_IO8(_mem_io_base_addr + 2)

#endif
	
	/**
	 * \brief	使うIOレジスタの登録を行う
	 *
	 * \param _arg_io_addr : 設定するIO
	 */
	void Set_io_base(E_IO_PORT_ADDR _arg_io_addr);

	/**
	 * \brief	使うIOレジスタの登録,設定を行う
	 * 
	 * \param _arg_io_addr		: 使用するレジスタ
	 * \param _arg_io_mode		: 設定するモード
	 * \param _arg_set_io_pin	: 使用するピンの設定。1になっているbitに対応するレジスタのbitが_arg_io_modeの機能に設定される
	 */
	void Set_io_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
public:
	
	C_IO_base()	{}
	
	/**
	 * \brief 
	 *	コンストラクタ
	 *	使うIOレジスタの登録を行う
	 * 
	 * \param _arg_io_addr : 設定するIO
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr);
	
	/**
	 * \brief	使うIOレジスタの登録と設定を行う 
	 *
	 * \param _arg_io_addr		: 使用するレジスタ
	 * \param _arg_io_mode		: 設定するモード
	 * \param _arg_set_io_pin	: 使用するピンの設定。1になっているbitに対応するレジスタのbitが_arg_io_modeの機能に設定される
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_set_io_pin);
};

/************************************************************************/
//protected

inline void
C_IO_base ::
Set_io_base (const E_IO_PORT_ADDR _arg_io_addr)
{
	_mem_io_base_addr = _arg_io_addr;
	
	#ifdef _AVR_IOM640_H_

	_mem_io_base_addr_point = F_Check_bit_bool(_arg_io_addr, 8);

	#endif

}

inline void
C_IO_base::
Set_io_base
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_MODE			_arg_io_mode,
	const T_PORT			_arg_set_io_pin
)
{
	Set_io_base(_arg_io_addr);
	
	switch (_arg_io_mode)
	{
		case EI_IN:
		{
			__DDR__  = ~_arg_set_io_pin;
			__PORT__ =  _arg_set_io_pin;
			
			break;
		}
		case EI_OUT:
		{
			__DDR__  =  _arg_set_io_pin;
			__PORT__ = ~_arg_set_io_pin;
			
			break;
		}
	}
}

/************************************************************************/
//public

C_IO_base ::
C_IO_base (const E_IO_PORT_ADDR _arg_io_addr)
{
	Set_io_base(_arg_io_addr);
}

C_IO_base ::
C_IO_base
(
	const E_IO_PORT_ADDR	_arg_io_addr,
	const E_IO_MODE			_arg_io_mode,
	const T_PORT			_arg_set_io_pin
)
{
	Set_io_base(_arg_io_addr, _arg_io_mode, _arg_set_io_pin);
}
