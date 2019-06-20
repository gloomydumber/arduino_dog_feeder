#include<LiquidCrystal.h>
#include <Servo.h>
int pin_button2 = 2; //주기 스위치
int pin_button3 = 3; //급여량 스위치
int pin_button4 = 4; //모터 제어 스위치
int state_button; 
LiquidCrystal lcd(44,45,46,47,48,49); //lcd출력
int period = 0; //주기
int amount = 0; //급여량
int go = 0; //모터제어
bool stateButton2; //주기
bool stateButton3;  //급여량
bool stateButton4;  모터제어
int state_previous2 = 0;
int state_previous3 = 0;
int state_previous4 = 0;
unsigned long interval; //가변저항
Servo myServo; //모터 제어
int angle=0;  //모터 이동 범위 변수
int servoPin = 11; //모터
int later;  // //delay 변수 
int mot;  //사료 양 변수

void setup() {
  pinMode(A0, INPUT); //가변저항
  Serial.begin(9600); //아두이노 출력
  lcd.begin(16,2);  //lcd 출력
  pinMode(pin_button2, INPUT);  //2번 스위치
  pinMode(pin_button3, INPUT);  //3번 스위치
  pinMode(pin_button4, INPUT);  //4번 스위치
  myServo.attach(servoPin); //모터
}

void Motor(int mot, int later){ //모터제어(사료양, 대기시간)
  switch(go){
    case 0:    {
      lcd.setCursor(0,0);
      lcd.print("switch is off");
    }
    case 1:    {  
      if(mot == 100){ //사료양 == 100g
        angle = 30; //각도 30도
        for(int i = 0; i < angle; i++){
          myServo.write(i);
      }delay(later * 60 * 1000);} //대기시간 15분
    else if(mot == 150){ //사료양 == 150g
      angle = 60; //각도 60도
      for(int i = 0; i < angle; i++){
        myServo.write(i);
      }delay(later * 60 * 1000);} //대기시간 25분
    else if(mot == 200){ //사료양 == 200g
      angle = 90; //각도 90도
      for(int i = 0; i < angle; i++){
        myServo.write(i);
    }delay(later * 60 * 1000);} //대기시간 35분
    else if(mot == 250){ //사료양 == 250g
      angle = 120;  //각도 120도
      for(int i = 0; i < angle; i++){
        myServo.write(i);
    }delay(later * 60 * 1000);} //대기시간 45분
    else{
      angle = 0;    }}
  }
}

void P_LCD(int period, unsigned long interval){ //주기 설정(주기 스위치 on/off, 가변저항)
    switch(period){
    case 0:{
      lcd.setCursor(0,0);
      lcd.print("switch is off");
      break;
    }
    case 1:{
      lcd.setCursor(0,0);
      lcd.print("   How  often   ");
      if(interval >= 0 and interval < 25) //가변저항 
       { lcd.setCursor(0,1);  //lcd출력
        lcd.print("   15  minute   ");
        later = 15;} //delay 변수 설정
      else if(interval >= 25 and interval < 50) //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   25  minute   ");
        later = 25;} //delay 변수 설정
      else if(interval >= 50 and interval < 75) //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   35  minute   ");
        later = 35;} //delay 변수 설정
      else if(interval >= 75 and interval <99)  //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   45  minute   ");
        later = 45;} //delay 변수 설정
      else
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   e r r o r !  ");}
      break;
    }}
}
void A_LCD(int amount, unsigned long interval){ //사료량 설정(스위치 on/off , 가변저항)
    switch(amount){
    case 0:{
      lcd.setCursor(0,0);
      lcd.print("switch is off");
      break;
    }
    case 1:{
      lcd.setCursor(0,0);
      lcd.print(" Amount of food ");
      if(interval >= 0 and interval < 25)  //가변저항 
       { lcd.setCursor(0,1);  //lcd출력
        lcd.print("     100  g     ");
        mot = 100;}
      else if(interval >= 25 and interval < 50)  //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     150  g     ");
        mot = 150;}
      else if(interval >= 50 and interval < 75)  //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     200  g     ");
        mot = 200;}
      else if(interval >= 75 and interval <99)  //가변저항 
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("     250  g     ");
        mot = 250;}
      else
        {lcd.setCursor(0,1);  //lcd출력
        lcd.print("   e r r o r !  ");}
      break;
    }}
}

void loop() {
  stateButton3 = digitalRead(pin_button3);
  stateButton2 = digitalRead(pin_button2);
  stateButton4 = digitalRead(pin_button4);
if(stateButton2 == 1){ //주기 스위치
  if(state_previous2 == 0){
  period = period + 1;
  state_previous2 = 1;
  }}else{
    state_previous2 = 0;}
    
if(stateButton3 == 1){  //사료량 스위치
  if(state_previous3 == 0){
  amount = amount + 1;
  state_previous3 = 1;
  }}else{
    state_previous3 = 0;}

if(stateButton4 == 1){ //모터 스위치
  if(state_previous4 == 0){
  go = go + 1;
  state_previous4 = 1;
  }}else{
    state_previous4 = 0;}
    
  go = go%2;  //on/off
  amount = amount%2;  //on/off
  period = period%2;  //on/off
   Serial.print("go = "+String(go));
   Serial.print("amount = "+String(amount));
   Serial.println("period = "+String(period));
   
   if(period == 1 and amount == 0 and go == 0){
      P_LCD(period, interval);
      }   
   else if(amount ==1 and period == 0 and go == 0){
      A_LCD(amount, interval);
      }
   else if(period == 0 and amount == 0 and go == 1){
    Motor(mot , later);
   }
   else{lcd.clear();}
    
   Serial.print("later = "+String(later));
   Serial.println("mot = "+String(mot));
int adc = analogRead(A0); //가변저항 읽기
interval = map(adc,0,1023,0,100); //범위를 0 ~ 100
  }
