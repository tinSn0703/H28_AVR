
#pragma once

#include "H28_t_class.h"

/**
 * �^�C�}�𔺂����J�E���g�p�N���X
 * C_COUNTER�̎q�ɂ���������
 * TIMER0���g���Ă܂�
 * TIMER2ver�����납��
 */
class C_TIMER_inside
{
private:

	usint _mem_timer_inside_count :8; //�J�E���^
	usint _mem_timer_inside_limit :8; //�J�E���g�̏��
	BOOL _mem_timer_inside_flag  :1;  //�J�E���g�̓���t���O
	
protected:
	
	/**
	 * \brief �R���X�g���N�^�̒��g�B�����̓R���X�g���N�^���Q��
	 */
	void Set(usint _arg_timer_limit, usint _arg_timer_count, BOOL _arg_timer_flag);
	
public:
	
	C_TIMER_inside()	{}
		
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_limit : �J�E���g�񐔁B1�J�E���g�ɂ�100us
	 * \param _arg_count : �ŏ��ɖ��߂Ēu���J�E���^�̒l
	 * \param _arg_flag : �t���O�̏����ݒ�
	 */
	C_TIMER_inside(usint _arg_timer_limit, usint _arg_timer_count, BOOL _arg_timer_flag);
	
	/**
	 * \brief �^�C�}�J�E���g�̊J�n
	 */
	void Start();
	
	/**
	 * \brief �^�C�}�J�E���g�̌���̊m�F 
	 * 
	 * \return BOOL 
	 *	TRUE  -> ����
	 *	FALES -> ����ȊO
	 */
	BOOL Check();
	
	/**
	 * \brief �J�E���g�̏I��
	 */
	void End();
	
	/**
	 * \brief �J�E���g�̓���t���O�̒l��Ԃ�
	 * 
	 * \return BOOL
	 *	TRUE  -> �J�E���g���s���Ă���
	 *	FALES -> �J�E���g���s���Ă��Ȃ�
	 */
	BOOL Ret_flag();
};

#include "H28_T_C_TIMER_inside.cpp"