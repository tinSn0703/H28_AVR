
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_base.cpp"
#include <H28_AVR/H28_AVR_0/H28_t_class/H28_T_C_TIMER_inside.cpp>

/**
 * UARTで受信を扱うクラス
 */
class C_UART_R : public virtual C_UART_base
{
protected:

	C_TIMER_inside _mem_timer;
	
	E_UART_FLAG _mem_uart_r_flag :2; //最後の受信状態の記録
	
	void Set(E_UART_ADDR ,BOOL );
	
public:

	C_UART_R() {}
	C_UART_R(E_UART_ADDR ,BOOL );
	
	void Set_isr(BOOL );
	void Check();
	
	T_DATA In();

	E_UART_FLAG Ret_flag()	{	return _mem_uart_r_flag;	}
	
	friend void operator >> (C_UART_R &, T_DATA &);
	friend void operator >> (C_UART_R &, T_DATA_8 &);
	
	friend bool operator == (C_UART_R &,E_UART_FLAG );
	friend bool operator != (C_UART_R &,E_UART_FLAG );
};

//protevted member

/**
 * \brief
 * コンストラクタの中身
 * 意味がないような気はする
 * 
 * \param _arg_uart_addr : 使うUART
 * \param _arg_uart_nf_isr : 割り込みのONOFF
 */
inline void 
C_UART_R::
Set
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_isr
)
{	
	C_UART_base::Set(_arg_uart_addr);
	
	Set_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag = EU_NONE;
}

//public member

/**
 * \brief : コンストラクタ
 * 
 * \param _arg_uart_addr : 使うUART
 * \param _arg_uart_nf_isr : 割り込み処理の使用のONOFF
 */
inline 
C_UART_R::
C_UART_R
(
	E_UART_ADDR _arg_uart_addr, 
	BOOL _arg_uart_nf_isr = FALES
)
 : _mem_timer(80) //8ms
{
	C_UART_base::Set(_arg_uart_addr);
	
	Set_isr(_arg_uart_nf_isr);
	
	_mem_uart_r_flag = EU_NONE;
}

/**
 * \brief : 割り込みのONOFF
 * 
 * \param _arg_uart_nf_isr : ONOFFの設定
 */
inline void 
C_UART_R::
Set_isr (BOOL _arg_uart_nf_isr)
{
	switch (_arg_uart_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB &= ~(1 << RXCIE);	break; //Off
	}
}

/**
 * \brief 
 * 受信ができるかを確認する。結果は_mem_uart_r_flagに格納されるので使うときにそっちを読んでほしい。
 * 確認中はこの関数で停止します。
 * 確認には最長で8ms程かかります
 */
void 
C_UART_R::
Check ()
{
	UCSRB |= (1 << RXEN); //受信許可
	
	_mem_timer.Start();
	
	while (1)
	{
		if ((_mem_timer.Ret_flag() & CHECK_BIT_TF(UCSRA,RXC)) == TRUE)	//受信完了
		{
			_mem_timer.End();
			
			_mem_uart_r_flag = EU_SUCCE;
			
			break;
		}
		
		if (_mem_timer.Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag = EU_ERROR;
			
			break;
		}
	}
}

/**
 * \brief 受信する 
 * 
 * \return T_DATA : 受信したデータ
 */
T_DATA 
C_UART_R::
In ()
{
	Check(); //受信チェック
	
	if (_mem_uart_r_flag == EU_ERROR)	return IN_ERROR;	//受信失敗
	
	T_DATA _ret_in_data = 0;
		
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data = (1 << 8);	//9bit通信時
	
	_ret_in_data |= UDR;
	
	_mem_uart_r_flag = EU_NONE;
	
	return _ret_in_data;
}

/**
 * \brief 
 * C_UART_R::In()の演算子バージョン。
 * 
 * \param _arg_uart_r : みたまま
 * \param _arg_uart_r_data_in : 受信データが書き込まれる場所
 */
void 
operator >> 
(
	C_UART_R &_arg_uart_r,
	T_DATA &_arg_uart_r_data_in
)
{
	_arg_uart_r_data_in = _arg_uart_r.In();
}

/**
 * \brief 
 * C_UART_R::In()の演算子バージョン。
 * 8bit通信のとき用
 * 
 * \param _arg_uart_r : みたまま
 * \param _arg_uart_data_in : 受信データが書き込まれる場所
 */
void 
operator >> 
(
	C_UART_R &_arg_uart_r,
	T_DATA_8 &_arg_uart_data_in
)
{
	_arg_uart_r.Set_bit9(FALES);
	_arg_uart_data_in = (T_DATA_8 )_arg_uart_r.In();
}

/**
 * \brief 
 * if文などでの比較用
 * _mem_uart_r_flagと比較する。
 * C_UART_R::Check()のあとで使って
 * 
 * \param _arg_uart_r : みたまま
 * \param _arg_uart_flag : 比較するやつ
 * 
 * \return bool 等しいときtrue
 */
bool 
operator == 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_r_flag
)
{	
	if (_arg_uart_r._mem_uart_r_flag == _arg_uart_r_flag)	return true;
	
	return false;
}

/**
 * \brief 
 * if文などでの比較用
 * _mem_uart_r_flagと比較する。
 * C_UART_R::Check()のあとで使って
 * 
 * \param _arg_uart_r : みたまま
 * \param _arg_uart_flag : 比較するやつ
 * 
 * \return bool 等しくないときtrue
 */
bool 
operator != 
(
	C_UART_R &_arg_uart_r,
	E_UART_FLAG _arg_uart_flag
)
{
	if (_arg_uart_r._mem_uart_r_flag != _arg_uart_flag)	return true;
	
	return false;
}