int REC = 8;
int PLAYE = 9;
char input = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode (REC,OUTPUT);
  pinMode (PLAYE,OUTPUT);
}
 
void loop() {
  // 시리얼 통신이 연결되어 있을시
  while(Serial.available()) {
    // 시리얼 창을 통해 입력된 값을 읽어드립니다.
    input = Serial.read();
    switch(input) {
      // 시리얼 창 R 입력 시 녹음 시작
      case 'R': 
        digitalWrite(REC,HIGH);
        break;
      // 시리얼 창 S 입력 시 녹음 종료
      case 'S': 
        digitalWrite(REC,LOW);
        break;
      // 시리얼 창 P 입력 시 녹음된 음성 재생
      // PLAYE 기능을 사용하기 때문에 잠깐 HIGH 값 입력 후 LOW 값 입력
      case 'P': 
        digitalWrite(PLAYE,HIGH);
        delay(10);
        digitalWrite(PLAYE,LOW);
        break;
    }
  }
}
