#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "motordriver.h"
#include "DHT22.h"
#include <stdio.h>

#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "motordriver.h"
#include "DHT22.h"
#include <stdio.h>

#define C 262 // C
#define D 294 // D 
#define E 330 // E 
#define F 349 // F 
#define G 392 // G 
#define A 440 // A 
#define B 494 // B 

#define SONG_NUM 3
#define SONG_LEN 25

double song_notes[SONG_NUM][SONG_LEN] = {
   {G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C}, // song : school bell's ringing
      {C, C, G, G, A, A, G, F, F, E, E, D, D, C, G, G, F, F, E, E, D, G, G, F, F}, // song : little star
         {E, E, E, E, E, E, E, G, C, D, E, F, F, F, F, F, E, E, E, E, D, D, E, D, G} // song : jingle bell
};


Serial pc(USBTX, USBRX);
DHT22 sensor (PB_2);
Motor mt(D11,PC_8);
PwmOut sound(PC_9);
DigitalOut myled(LED1);
DigitalIn motion(D5);

class I2CPreInit : public I2C{
	public:
	I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl){
		frequency(400000);
		start();
	};
};

I2C myI2C(I2C_SDA,I2C_SCL);
Adafruit_SSD1306_I2c myGUI(myI2C, D13, 0x78, 64, 128);

InterruptIn left_button (PA_14);
InterruptIn center_button(PB_7);
InterruptIn right_button(PC_4);

Timeout myTimeout;
/*
Timeout motorTimeout;
Timeout stopMusicTimeout;*/
Ticker sensorTicker;

volatile int detect_sensor = 0;
volatile bool detected=false;

int left_pressed=0;
int center_pressed=0;
int right_pressed=0;

int current_music=0;

bool interrupted = false;
bool is_playing=false;
bool music_flag = true; // true : clicked next song, false : clicked previous song;
float motor_speed=0.6f;

void playMusic(int cur){
	 wait(0.5);
	 pc.printf("play music\r\n");
	 for(int i=0; i<SONG_LEN; i++){
			sound.period(1.0/song_notes[cur][i]);
			sound = 0.5;
			wait(0.5);
			if(!is_playing || current_music!=cur) {
				wait(0.1);
				break;
			}
	 }
}

void sensorCheck(){
	//Human detection
	int detect_sensor = motion;
	if(detect_sensor){
		detected=true;
	}else{
		detected=false;
	}
	detect_sensor=0;
	
	
	myGUI.clearDisplay();
	myGUI.setTextCursor(0,0);
	
	//Temp, Humid check
  	float t,h,c=0.0f;
	int temp,humid;
	
	sensor.sample();
	h=sensor.getHumidity()/10;
	t=sensor.getTemperature()/10;

	temp=(int)t;
	humid=(int)h;

	if(detected){
		myGUI.printf ("Temperature : %d 'c\r\nHumid : %d%\r\nHuman is detected!!",temp,humid);
		pc.printf("Temp : %d, Humid: %d, Human is detected!!\r\n",temp,humid);
	}
	else if(!detected){
		myGUI.printf ("Temperature : %d 'c\r\nHumid : %d%\r\nHuman is not detected!!",temp,humid);
		pc.printf("Temp : %d, Humid: %d, Human is not detected!!\r\n",temp,humid);
	}
	myGUI.display();
}

void stopMusic(){
	is_playing=!is_playing;
	pc.printf("music stopped\r\n");
}

void PAUSE_ISR(){
	wait(0.2);
	sound.period(1.0);
	sound=0.5;
	
	if(is_playing){
		myTimeout.attach(&stopMusic,5.0);
	}else{
		sound.period(1.0);
		sound=0.5;
		is_playing=!is_playing;
	}
}

void NEXT_ISR(){
	wait(0.3);
	sound.period(1.0);
	sound=0.5;
	
	current_music = (current_music+1)%3;
	wait(0.1);
	
	mt.forward(motor_speed);
	wait(1);
	mt.stop();
	
	pc.printf("next music\r\n");
}

void PREV_ISR(){
	wait(0.3);
	sound.period(1.0);
	sound=0.5;

	if(current_music<=0){
		current_music=2;
	}else{
		current_music--;
	}
	wait(0.5);
	
	mt.backward(motor_speed);
	wait(1);
	mt.stop();
	
	pc.printf("prev music\r\n");
}



int main(){
	pc.baud (9600);
	
	left_button.rise(&PREV_ISR);
	center_button.rise(&PAUSE_ISR);
	right_button.rise(&NEXT_ISR);
	
	//TODO : Thermo, Humid, Human sensing  => using timer interrupt 'Ticker'
	sensorTicker.attach(&sensorCheck, 3);	
	
	while(1){
       wait(0.2);
       sound.period(1.0);
       sound=0.5;
       // Play music
       if(is_playing){
          playMusic(current_music);
				 
          sound.period(1.0);
          sound=0.5;
      }
   }
}
