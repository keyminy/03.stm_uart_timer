#include "timer.h"

extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim2;

 // interrupt안의 변수라서 최적화 방지를 위해
// moved from Driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
// timer INT가 발생할때마다 이곳으로 진입한다.(TIM5,11, ...여러가지)

void delay_us(unsigned int us);


// counter us timer pulse
// 0.000001(sec)=1us : 1개의 pulse 소요시간
// 0.001sec : 1ms <== 1000us
// 0.1sec : 100ms
void delay_us(unsigned int us){
	// TCNT = 0; // AVR할때 요렇게했음
	// TCNT가 pulse를 카운트할때마다 증가합니다.
	// 들어오면, TCNT를 clear해준다.
	__HAL_TIM_SET_COUNTER(&htim11,0); // timer2번 counter를 clear한다.
	while(__HAL_TIM_GET_COUNTER(&htim11) < us); // NOP
	// __HAL_TIM_GET_COUNTER() : Counter의 값을 읽어들임
	// parameter로 지정한 pulse count를 만날때까지 머무른다.

}
