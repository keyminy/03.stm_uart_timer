#include "button.h"

// 채터링제거를 위한 flag변수(각각의 버튼에 대한 정보를 담는 table)
// 지금은 전역변수로 선언했지만 싫다면, static변수로 만들어줘도됨
unsigned char button_status[BUTTON_NUMBER] =
{BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE};

// 전역변수 선언
char button1_state = 0;
char button2_state = 0;

extern char state;

void button_check(){
	if(get_button(BUTTON0_GPIO_Port, BUTTON0_Pin, BUTTON0) == BUTTON_PRESS) {
		if(state >= 4){
			state = 1;
		}else{
			state++;
		}
	}else if(get_button(BUTTON0_GPIO_Port, BUTTON1_Pin, BUTTON1) == BUTTON_PRESS) {
		button1_state = !button1_state;
		if(button1_state){
			state = 5;
		}else{
			state = 6;
		}
	}else if(get_button(BUTTON0_GPIO_Port, BUTTON2_Pin, BUTTON2) == BUTTON_PRESS) {
		button2_state = !button2_state;
		if(button2_state){
			state = 7;
		}else{
			state = 8;
		}
	}
}

// 버튼이 온전하게 눌렀다 떼어진 상태이면 1을 리턴한다
int get_button(GPIO_TypeDef *GPIO,int button_pin, int button_number){
	int current_state;

	//예)BUTTON1은 4가 넘어옴, 2는 5, 3은 5...
	//BUTTON_PIN값은 눌리면1 안눌리면 0값을 감지함
//	current_state = BUTTON_PIN & (1 << button_pin); // 10000 (1<<4결과)
	current_state = HAL_GPIO_ReadPin(GPIO, button_pin);
	// press : 0, release : 1 because it is in pull up resistor
	//current_state변수로 버튼 값을 읽습니다.

	if(current_state == BUTTON_PRESS && button_status[button_number]== BUTTON_RELEASE){
		// 버튼이 처음 눌러진 상태
		HAL_Delay(60); // 노이즈가 지나가기를 기다린다.
		button_status[button_number] = BUTTON_PRESS; // 처음 눌러진 상태가 아니다
		return BUTTON_RELEASE; //아직 완전히 눌렀다 떼어진 상태가 아니다.
	} // 버튼이 이전에 눌러진 상태였으면 현재는 떼어진 상태
	else if(button_status[button_number] == BUTTON_PRESS && current_state == BUTTON_RELEASE){
		button_status[button_number] = BUTTON_RELEASE; // 다음 버튼 상태를 체크하기 위해 초기화
		HAL_Delay(60); // 노이즈가 지나가기를 기다린다.
		return BUTTON_PRESS; // 완전히 눌렀다 떼어진 상태
	}
	// 아직 HIGH인 상태인 것이지
	// 아직 완전히 스위치를 눌렀다 뗀 상태가 아니거나 스위치가 open된 상태 -> return 0;
	return BUTTON_RELEASE;
}
