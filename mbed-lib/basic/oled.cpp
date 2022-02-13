#include "mbed.h"
#include "Adafruit_SSD1306.h"
DigitalOut myled(LED1);

// an I2C sub class that provides a constructed default (initialize)
class I2CPreInit : public I2C{
	public:
	I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl){
		frequency(400000);
		start(); // 제조사 로고 표현
	};
};

I2C myI2C(I2C_SDA, I2C_SCL); // I2C 통신 정보
Adafruit_SSD1306_I2c myGUI(myI2C, D13, 0x78, 64, 128);

int main(){
	uint16_t x = 0;
	// myGUI.clearDisplay(); 제조사 로고 지우기
	myGUI.printf("%ux%u OLED Display\r\n",
		myGUI.width(), myGUI.height());
	while(1){
		myled = 1;
		wait(0.2);
		myled = 0;
		wait(0.2);
	};
	myGUI.printf("%u\r", x);
	myGUI.display();
	x++;
	wait(1.0);
}
