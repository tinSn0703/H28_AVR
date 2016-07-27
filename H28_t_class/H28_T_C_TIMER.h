
#pragma once

#include "H28_T_C_TIMER_base.cpp"

class C_TIMER : public virtual C_TIMER_base
{
public:

	C_TIMER()	{}
	
#if defined(_AVR_IOM640_H_)

	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_addr : �g��TIMER�̔ԍ�
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_addr : �g��TIMER�̔ԍ�
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_ADDR _arg_timer_addr, E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
#elif defined(_AVR_IOM164_H_)
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, BOOL _arg_timer_nf_isr);
	
	/**
	 * \brief �R���X�g���N�^
	 * 
	 * \param _arg_timer_mode : ���[�h�̑I��
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 * \param _arg_timer_nf_isr : ���荞�ݏ����̎g�p�ɂ���
	 */
	C_TIMER(E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, usint _arg_timer_counter, BOOL _arg_timer_nf_isr);
#endif

	/**
	 * \brief �^�C�}���E���^���J�n����
	 */
	void Start();
	
	/**
	 * \brief �����̒l��p���ă^�C�}�J�E���^���J�n����
	 * 
	 * \param _arg_timer_clock : �����l
	 * \param _arg_timer_counter : ���W�X�^�ɓ����l
	 */
	void Start(E_CLOCK _arg_timer_clock, usint _arg_timer_counter);
	
	/**
	 * \brief �^�C�}�J�E���^�̊������m�F����
	 * 
	 * \param _arg_timer_continue : �������Ƀ^�C�}�J�E���^���ēx�s����
	 * 
	 * \return BOOL
	 *	TRUE  -> ����
	 *	FALES -> ����
	 */
	BOOL Flag_timer(BOOL _arg_timer_continue);
	
	/**
	 * \brief �^�C�}�J�E���^���I������
	 */
	void Stop();
};

#include "H28_T_C_TIMER.cpp"