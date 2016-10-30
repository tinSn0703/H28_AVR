
/*
1ピンのみ。センサなどに使えばいいんじゃないかな

 H28 06 12 ver0.0.0 
*/

#pragma once

#include "H28_I_C_IO_IN.cpp"

class C_IO_IN_pin : protected C_IO_IN
{
	
private:
	
	E_IO_NUM _mem_io_in_pin_bit :3;	//用いるbit
	
public:

	/**
	 * \brief 
	 *	何もしない。空のコンストラクタ。
	 */
	C_IO_IN_pin()	{}
	
	/**
	 * \brief 
	 *	使用するレジスタ、bitを設定する。
	 *	センサによってはLOWにする必要があるので、それも設定可能
	 *
	 * \param _arg_io_addr	: 使うIOレジスタのアドレス
	 * \param _arg_io_bit	: 使うbit
	 * \param _arg_nf_port	: PORTをHIGHにするかどうか
	 */
	C_IO_IN_pin(E_IO_PORT_ADDR _arg_io_addr, E_IO_NUM _arg_io_bit, BOOL _arg_nf_port);
	
	/**
	 * \brief 
	 *	IOピンのHigh / Lowを読み取る。
	 *
	 * \return BOOL 
	 *	High -> TRUE
	 *	Low  -> FALSE
	 */
	BOOL In();
	
	/**
	 * \brief 
	 *	IOピンを反転して読み取る
	 * 
	 * \return BOOL
	 *	High -> FALSE
	 *	Low  -> TRUE
	 */
	BOOL In_turn();
	
	/**
	 * \brief 
	 *	使用してるbitをreturnする。
	 * 
	 * \return E_IO_NUM
	 */
	E_IO_NUM Ret_bit()	{	return _mem_io_in_pin_bit;	}
};


#include "H28_I_C_IO_IN_pin.cpp"