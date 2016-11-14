
#pragma once

#include "H28_t_class.h"

/**
 * �^�C�}-�p�N���X
 * ��莞�Ԃ̌v���p�B���[�v���Ă钆�Ŏg���Ă�
 * C_COUNTER�̎q�ɂ���������
 * �����܂Ő��x�͂悭�Ȃ��̂Ńv���O��������~���Ȃ��҂����Ԓ��x�ɍl���ĂƂ���
 * TIMER0���g���Ă܂�
 * TIMER2ver�����납��
 */
class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count ; //�J�E���^
	usint _mem_timer_inside_limit ; //�J�E���g�̏��
	BOOL _mem_timer_inside_flag  :1;  //�J�E���g�̓���t���O
	
public:
	
	/**
	 * \brief 
	 * �R���X�g���N�^�B_mem_timer_inside_limit��0�ɂ��邾��
	 */
	C_TIMER_inside();
	
	/**
	 * \brief 
	 *	�R���X�g���N�^
	 *	TIMER�̏����ݒ���s���B 
	 *
	 * \param _arg_limit : �J�E���g����B1�J�E���g�ɂ�100us
	 */
	C_TIMER_inside(usint _arg_timer_limit);
	
	/**
	 * \brief �^�C�}�̊J�n
	 */
	void Start();
	
	/**
	 * \brief �^�C�}�̌���̊m�F 
	 * 
	 * \return BOOL 
	 *	TRUE  -> ����
	 *	FALES -> ����ȊO
	 */
	BOOL Check();
	
	/**
	 * \brief �^�C�}�̏I��
	 */
	void Stop();
	
	/**
	 * \brief �J�E���g�̓���t���O�̒l��Ԃ�
	 * 
	 * \return BOOL
	 *	TRUE  -> �J�E���g���s���Ă���
	 *	FALES -> �J�E���g���s���Ă��Ȃ�
	 */
	BOOL Ret_state();
	
	/**
	 * \brief �J�E���g�̏���l��ύX���鉉�Z�q
	 * 
	 * \param _arg_timer_limit : �V�������
	 */
	C_TIMER_inside & operator = (usint _arg_timer_limit);
	
	/**
	 * \brief 
	 * if���Ȃǂł̔�r�p�̉��Z�q
	 * C_TIMER_inside::Ret_state()�Ɣ�r����
	 * 
	 * \param _arg_timer_inside : �݂��܂�
	 * \param _arg_timer_flag_comp : ��r������
	 * 
	 * \return friend bool �������Ƃ�ture
	 */
	friend bool operator == (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
	
	/**
	 * \brief 
	 * if���Ȃǂł̔�r�p�̉��Z�q
	 * C_TIMER_inside::Ret_state()�Ɣ�r����
	 * 
	 * \param _arg_timer_inside : �݂��܂�
	 * \param _arg_timer_flag_comp : ��r������
	 * 
	 * \return friend bool �������Ȃ��Ƃ�ture
	 */
	friend bool operator != (C_TIMER_inside &_arg_timer_inside,BOOL _arg_timer_flag_comp);
};

#include "H28_T_C_TIMER_inside.cpp"