/**
 * Junting Huo @ University of Virginia
 * https://github.com/hhhhjjjtt/TB6612-Motor-Driver-for-STM32-HAL
 * 03/17/2025
 * Developed on STM32F103C8T6
 */

#include "tim.h"
#include "TB6612.h"

// PA0(GPIO)------------------------AIN1
// PA1(GPIO)------------------------AIN2
// PA3(GPIO)------------------------STBY 
// PA2(TIM2->PWM generation CH3)----PWMA

#define AIN1 GPIO_PIN_0
#define AIN2 GPIO_PIN_1
#define STBY GPIO_PIN_3
// Timer for PWN output
#define PWM_TIM &htim2
// Timer Channel for PWM output
#define PWM_CH TIM_CHANNEL_3
// For ARR set to 99, the MAX_SPEED should be 100. Adjust if ARR set to other values
#define MAX_SPEED 100

/**
 * Initialize TB6612
 * Rotate forward, disable STBY, initialize PWM
 */
void TB6612_Init(void){
	TB6612_Forward();
	TB6612_Work();
	HAL_TIM_PWM_Start(PWM_TIM, PWM_CH);
}

/**
 * @param speed set motor speed by setting PWM duty cycle
 * Have to be smaller then MAX_SPEED
 */
void TB6612_Set_Speed(uint8_t speed){
	if(speed > MAX_SPEED){
		speed = MAX_SPEED;
	}
	__HAL_TIM_SET_COMPARE(PWM_TIM, PWM_CH, speed);
}

/**
 * Rotate Forward
 */
void TB6612_Forward(void){
	HAL_GPIO_WritePin(GPIOA, AIN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, AIN2, GPIO_PIN_SET);
}

/**
 * Rotate Backward
 */
void TB6612_Backward(void){
	HAL_GPIO_WritePin(GPIOA, AIN1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, AIN2, GPIO_PIN_RESET);
}

/**
 * Disable STBY, enable TB6612 to do operations
 */
void TB6612_Work(void){
	HAL_GPIO_WritePin(GPIOA, STBY, GPIO_PIN_SET);
}

/**
 * Enable STBY, disable TB6612 from doing operations
 */
void TB6612_Standby(void){
	HAL_GPIO_WritePin(GPIOA, STBY, GPIO_PIN_RESET);
}

/**
 * Stop the motor
 */
void TB6612_Brake(void){
	HAL_GPIO_WritePin(GPIOA, AIN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, AIN2, GPIO_PIN_RESET);
}
