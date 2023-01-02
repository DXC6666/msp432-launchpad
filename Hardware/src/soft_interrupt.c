/*-----------------------------------------------------------------------------------------------------
��ƽ ̨��Keil
���� �� �� Ƭ ����msp432P401R
���� �� �⡿msp432_driverlib_3_21_00_05
���� ����lv
* @@ ������ο� ����Ը�
* ������������ж���Դ����
* 
* 
* �汾 v1.0
* ʱ�� 2022��12��27��16:39:03
-------------------------------------------------------------------------------------------------------*/
#include "main.h"

/// @brief ʹ����������ж�
/// @param interruptNumber  ָ�������жϵ��жϺ�
void SOFT_Pending(uint32_t interruptNumber)
{
	Interrupt_enableInterrupt(INT_PORT1);   
	Interrupt_pendInterrupt(interruptNumber);
	
}

/// @brief ʧ����������ж�
/// @param interruptNumber  ָ�������жϵ��жϺ�
void SOFT_Unpending(uint32_t interruptNumber)
{
	Interrupt_unpendInterrupt(interruptNumber);
}
	

/// @brief �ж�����  ���ε����ڵ���priorityMask���жϻᱻ���ε�  Ϊ0ʱ �ر�����
/// @param priorityMask 0 - 7  ���˼��ɱ���жϵȼ�
void INT_Mask(uint8_t priorityMask)
{
	 Interrupt_setPriorityMask (priorityMask << 5);
}


/// @brief �����жϵ������ȼ�
/// @param interruptNumber �жϺ�
/// @param priority �ȼ� range 0 - 7
void INT_SetPriority(uint32_t interruptNumber, uint8_t priority)
{
	Interrupt_setPriority(interruptNumber, priority << 5);

}









