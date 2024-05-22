#include "uart02.h"
#include "led.h"

extern UART_HandleTypeDef huart2;
extern uint8_t rxData;
int front = 0;
int rear = 0;
uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];

// moved from "stm32f4xx_hal_uart.c"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//static변수는 함수가 다음에 실행되어도,그 값을 기억하기위해 사용한다.
	static unsigned int i;
	if(huart == &huart2){
		unsigned char data;
		data = rxData;

		//printf("%c",data);
		if(data == '\r' || data == '\n'){
			rx_buff[rear][i] = '\0'; //문장의 끝을 알리는 null sign을 insert함.
			i = 0; // i를 초기화 : 다음 문장을 입력받을 준비
			rear++;
			rear %= COMMAND_NUMBER;
		}else{
			rx_buff[rear][i++] = data;
		}

		//그 다음 인터럽트를 받게 해줘야한다.
		HAL_UART_Receive_IT(&huart2, &rxData, 1); // assign RX INT
	}
}

void pc_command_processing()
{
	char* cmd;
	if( front != rear){
		cmd = rx_buff[front]; //&rx_buff[front][0]로 // 2차원 배열의 0번째 주소를 넘겨줌
		printf("%s\n",cmd);
		front = (front+1) % COMMAND_NUMBER;

		if(strncmp(cmd,"led_all_on",strlen("led_all_on")) == 0){
			led_all_on();
		}else if(strncmp(cmd,"led_all_off",strlen("led_all_off")) == 0){
			led_all_off();
		}else if(strncmp(cmd,"led_keppon_up",strlen("led_keppon_up"))==0){
			led_keppon_up();
		}else if(strncmp(cmd,"led_keepon_down",strlen("led_keepon_down")) == 0){
			led_keepon_down();
		}else if(strncmp(cmd,"flower_on",strlen("flower_on"))==0){
			flower_on();
		}else if(strncmp(cmd,"flower_off",strlen("flower_off"))==0){
			flower_off();
		}
	}
}
