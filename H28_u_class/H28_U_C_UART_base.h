
#pragma once

/**
 * UART�n�̊��ƂȂ�N���X
 */
class C_UART_base
{
protected:

#if defined(_AVR_IOM640_H_)
	E_UART_ADDR _mem_uart_base_addr :9;	//���W�X�^�p�̃A�h���X
#elif defined(_AVR_IOM164_H_)
	E_UART_ADDR _mem_uart_base_addr :8;
#endif

#	define UCSRA _SFR_MEM8(_mem_uart_base_addr + 0)
#	define UCSRB _SFR_MEM8(_mem_uart_base_addr + 1)
#	define UCSRC _SFR_MEM8(_mem_uart_base_addr + 2)
#	define UBRRL _SFR_MEM8(_mem_uart_base_addr + 4)
#	define UBRRH _SFR_MEM8(_mem_uart_base_addr + 5)
#	define UDR	 _SFR_MEM8(_mem_uart_base_addr + 6)

	/**
	 * \brief �R���X�g���N�^�̒��g�B
	 * 
	 * \param _arg_uart_addr : �R���X�g���N�^�Q��
	 */
	void Set(E_UART_ADDR _arg_uart_addr);

public:

	/**
	 * \brief ��̃R���X�g���N�^.�������Ȃ�
	 */
	C_UART_base()	{}
	
	/**
	 * \brief 
	 * �R���X�g���N�^�BUART�̏����ݒ���s��
	 *		250[kbps]
	 *		�{������
	 *		��p���e�B
	 * 
	 * \param _arg_uart_addr : �g��UART
	 */
	C_UART_base(E_UART_ADDR _arg_uart_addr);
	
	/**
	 * \brief 
	 * 9bit�ʐM�̐ݒ�
	 * 8bit��9bit�ǂ����ł͂��܂��ʐM�ł��Ȃ��̂Œ���
	 *
	 * \param _arg_uart_nf_bit9 : ON/OFF
	 */
	void Set_bit9(BOOL _arg_uart_nf_bit9);
	
	
	/**
	 * \brief 
	 * 9bit�ʐM���ݒ肳��Ă��邩�̊m�F�B
	 * 
	 * \return BOOL 
	 *		TRUE  -> �ݒ肳��Ă���
	 *		FALES -> �ݒ肳��Ă��Ȃ�
	 */
	BOOL Ret_bit9();
};

#include "H28_U_C_UART_base.cpp"