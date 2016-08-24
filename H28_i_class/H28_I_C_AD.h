
#pragma once

#include "H28_i_class.h"

/**
 * AD�ϊ��������N���X
 */
class C_AD
{
protected:
	
	union U_AD_MUX
	{
		struct S_AD_MUX
		{
			BOOL _mux0 :1;
			BOOL _mux1 :1;
			BOOL _mux2 :1;
			BOOL _mux3 :1;
			BOOL _mux4 :1;
			
#ifdef _AVR_IOM640_H_
			BOOL _mux5 :1;
#endif
			
		};
		
		S_AD_MUX _mux_bit;
		usint _ad_num :5;
		
#if defined(_AVR_IOM640_H_)
		E_AD_NUM _mux_admux :6;
#elif defined(_AVR_IOM164_H_) || defined(_AVR_IOM88_H_)
		E_AD_NUM _mux_admux :5;
#endif

	};
	
	U_AD_MUX _mem_ad;
	
public:

	/**
	 * \brief 
	 * ��̃R���X�g���N�^
	 */
	C_AD()	{}
	
	/**
	 * \brief : �R���X�g���N�^
	 * 
	 * \param _arg_ad_num : �g���ԍ�
	 * \param _arg_ad_io_turn : IO�s���̐ݒ�B���܂������Ȃ��Ƃ��ɕς����肵��
	 *		TRUE  -> OUT
	 *		FALES -> IN
	 */
	C_AD(E_AD_NUM _arg_ad_num, BOOL _arg_ad_io_turn);

	/**
	 * \brief AD�ϊ������s����
	 * 
	 * \return usint : ���s���ʂ̃f�[�^�B10bit��0~1023�܂�
	 */
	usint Do();
};

#include "H28_I_C_AD.cpp"