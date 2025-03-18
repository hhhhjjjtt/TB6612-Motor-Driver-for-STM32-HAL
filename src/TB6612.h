#ifndef __TB6612_H
#define __TB6612_H

void TB6612_Init(void);
void TB6612_Set_Speed(uint8_t speed);
void TB6612_Forward(void);
void TB6612_Backward(void);
void TB6612_Work(void);
void TB6612_Standby(void);
void TB6612_Brake(void);

#endif
