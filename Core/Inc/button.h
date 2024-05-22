#include "main.h"
// main.h에 GPIO 정보가 담겨있기때문


/* 버튼 번호 */
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2

#define BUTTON_PRESS 0 //버튼을 누르면 LOW active-low
#define BUTTON_RELEASE 1 //버튼을 떼면 HIGH
#define BUTTON_NUMBER 3 // 버튼 갯수는 3개다

int get_button(GPIO_TypeDef *GPIO,int button_pin, int button_number);
void button_check(void);
