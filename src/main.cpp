#include <Arduino.h>
#include <TwoWayESP.h>
#include <ESP32Encoder.h>

/////1-encoder
#define CLK_PIN 15 
#define DT_PIN  33
/////2-encoder 
#define CLK_PIN2 2 
#define DT_PIN2  32
/////3-encoder
#define CLK_PIN3 4 
#define DT_PIN3  35
/////4-encoder
#define CLK_PIN4 16 
#define DT_PIN4  34
/////5-encoder
#define CLK_PIN5 17 
#define DT_PIN5  39
/////6-encoder
#define CLK_PIN6 5 
#define DT_PIN6  36
#define Coff 15
ESP32Encoder encoder1;
ESP32Encoder encoder2;
ESP32Encoder encoder3;
ESP32Encoder encoder4;
ESP32Encoder encoder5;
ESP32Encoder encoder6;
// timer and flag for example, not needed for encoders
unsigned long encoder2lastToggled;
bool encoder2Paused = false;

uint8_t broadcastAddress[] = {0x48,0xE7,0x29,0xB3,0xF9,0xFC};
// Структура должна совпадать со структурой
// на плате-отправителе
typedef struct ServoAngles{
    int Serv1; // левый локоть д13 
    int Serv2; // левое плечо1 д14 
    int Serv3; //  левое плечо2 д12 
    int Serv4; // правое плечо1 д33
    int Serv5; // правое плечо2 д25
    int Serv6; // правый локоть д26
    int buttRight; //поворот направо 
    int buttLeft; // поворот налево 
    int buttFront; // езда вперед 
    int buttBack; // езда назад
    int buttLeftHand; // левая клешня 
    int buttRightHand; // правая клешня 
    int RotBody; // поворот тела 
   // int Butt1; //23
  //  int Butt2;//22
   // int Butt3;//21
   // int Butt4;//19
  //  int Butt5;//13
  //15
} ServoAngles;
  ServoAngles myData;
   ServoAngles middle;
   
void setup() {
  // Запускаем монитор порта
  Serial.begin(115200);
	TwoWayESP::Begin(broadcastAddress);
  //	ESP32Encoder::useInternalWeakPullResistors = puType::UP;
	// encoder (DT,CLK)
	encoder1.attachHalfQuad(DT_PIN, CLK_PIN);
	  encoder2.attachHalfQuad(DT_PIN2, CLK_PIN2);
			encoder3.attachHalfQuad(DT_PIN3, CLK_PIN3);
      	encoder4.attachHalfQuad(DT_PIN4, CLK_PIN4);
        	encoder5.attachHalfQuad(DT_PIN5, CLK_PIN5);
          	encoder6.attachHalfQuad(DT_PIN6, CLK_PIN6);
	// set starting count value after attaching
	encoder1.setCount(0);
  encoder2.setCount(0);
  encoder3.setCount(0);
  encoder4.setCount(0);
  encoder5.setCount(0);
  encoder6.setCount(0);
	// clear the encoder's raw count and set the tracked count to zero
encoder1.clearCount();
	encoder2.clearCount();
  	encoder3.clearCount();
    	encoder4.clearCount();
      	encoder5.clearCount();
        	encoder6.clearCount();
}
 
void loop() {
    int newPosition1 = encoder1.getCount();
    if(abs(newPosition1)>32)encoder1.clearCount();
       if(newPosition1<0) newPosition1=32+newPosition1;
        int newPosition2 = encoder2.getCount();
            if(abs(newPosition2)>32)encoder2.clearCount();
       if(newPosition2<0) newPosition2=32+newPosition2;
            int newPosition3 = encoder3.getCount();
                if(abs(newPosition3)>32)encoder3.clearCount();
       if(newPosition3<0) newPosition3=32+newPosition3;
                int newPosition4 = encoder4.getCount();
                    if(abs(newPosition4)>32)encoder4.clearCount();
       if(newPosition4<0) newPosition4=32+newPosition4;
                    int newPosition5 = encoder5.getCount();
                        if(abs(newPosition5)>32)encoder5.clearCount();
       if(newPosition5<0) newPosition5=32+newPosition5;
                        int newPosition6 = encoder6.getCount();
                            if(abs(newPosition6)>32)encoder6.clearCount();
       if(newPosition6<0) newPosition6=32+newPosition6;
  myData.Serv1=newPosition1*Coff;
  myData.Serv2=newPosition2*Coff;
  myData.Serv3=newPosition3*Coff;
  myData.Serv4=newPosition4*Coff;
  myData.Serv5=newPosition5*Coff;
  myData.Serv6=newPosition6*Coff;
TwoWayESP::SendBytes(&myData, sizeof(ServoAngles));
   delay(2);
}