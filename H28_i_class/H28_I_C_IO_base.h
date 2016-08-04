
#pragma once

#include "H28_i_class.h"

class C_IO_base
{
private:
	
	E_IO_MODE	_mem_io_base_mode :1;
	
protected:
	
#if defined(_AVR_IOM640_H_)
	E_IO_PORT_ADDR	_mem_io_base_addr :9;
	BOOL			_mem_io_base_addr_point :1;
	
#	define __PIN__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 0) : _SFR_IO8(_mem_io_base_addr + 0))
#	define __DDR__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 1) : _SFR_IO8(_mem_io_base_addr + 1))
#	define __PORT__	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 2) : _SFR_IO8(_mem_io_base_addr + 2))
#elif defined(_AVR_IOM164_H_)
	E_IO_PORT_ADDR	_mem_io_base_addr :8;
	
#	define __PIN__	_SFR_IO8(_mem_io_base_addr + 0)
#	define __DDR__	_SFR_IO8(_mem_io_base_addr + 1)
#	define __PORT__	_SFR_IO8(_mem_io_base_addr + 2)
#endif
	
	/**
	 * \brief コンストラクタの中身。
	 * 
	 * \param _arg_io_addr : コンストラクタ参照
	 * \param _arg_io_mode : コンストラクタ参照
	 */
	void Set_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode);

	/**
	 * \brief コンストラクタの中身。
	 * 
	 * \param _arg_io_addr : コンストラクタ参照
	 * \param _arg_io_mode : コンストラクタ参照
	 * \param _arg_io_num : コンストラクタ参照
	 */	
	void Set_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
public:
	
	/**
	 * \brief 
	 * 空のコンストラクタ。
	 */
	C_IO_base()	{}
	
	/**
	 * \brief 
	 * コンストラクタ
	 * 使うIOの登録のみを行う
	 * 
	 * \param _arg_io_addr : 設定するIO
	 * \param _arg_io_mode : 設定するIOのモード
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode);
	
	/**
	 * \brief 
	 * 使うIOの登録と設定を行う 
	 *
	 * \param _arg_io_addr : 設定するIO
	 * \param _arg_io_mode : 設定するIOのモード
	 * \param _arg_io_num  : IOの設定
	 */
	C_IO_base(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_num);
	
	/**
	 * \brief 
	 * デストラクタ。IOの設定をなかったことにする
	 */
	~C_IO_base();
};

#include "H28_I_C_IO_base.cpp"
