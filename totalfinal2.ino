#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
unsigned long atime;
unsigned long ztime;
unsigned long btime;
unsigned long dtime;
unsigned long gtime;
unsigned long htime;
const int temperature = A0;
const int heater = 6;
int switchh;
int relay;
int heaterrelay;
int sensor = A1;
int moter;

void setup() {
  pinMode(7,OUTPUT); //UV램프에 연결된 릴레이
  pinMode(12,INPUT);  //마이크로 스위치
  digitalWrite(7,LOW); 
  Serial.begin(9600);
  pinMode(heater,OUTPUT);
  digitalWrite(9,LOW); 
  // pinMode(9,OUTPUT); //ENA // 속도조절을 위해 아날로그 신호로 바꿈 따라서 핀모드가 필요 없어지므로 주석처리함
  // ENA가 LOW일때 모터는 정지함 HIGH일때 회전하거나 브레이크
  pinMode(11,OUTPUT); //IN 1
  pinMode(10,OUTPUT); //IN 2
  delay(500);
}

void loop() {
  for(;;) {
  moter = 0;
  switchh = digitalRead(12);
  int value = analogRead(sensor);
  Serial.print("밝기 값 : ");
  Serial.println(value);
  delay(100);
  
 if(switchh == 0) {
  analogWrite(9, 50); //속도제어
  digitalWrite(10,LOW); 
  digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크    
  moter = 0;
 }

  if(switchh == 1) {
    if(moter == 0) {
        if(value > 300) { //300보다 밝을 때
          // digitalWrite(5,HIGH); // 속도조절을 위해 아날로그 신호로 바꿈
          analogWrite(9, 50); //속도제어
          digitalWrite(10,LOW);
          digitalWrite(11,LOW); //둘다 HIGH거나 LOW일때 브레이크
          break;
        }
    }
  }

  if(switchh == 1) {
      if(moter == 0) {
        if(value <= 300) { //500보다 같거나 어두울 때
       // digitalWrite(9,HIGH); // 속도조절을 위해 아날로그 신호로 바꿈
          analogWrite(9, 50); //속도제어
          digitalWrite(10,HIGH); //정방향 회전
          digitalWrite(11,LOW); //정방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
          moter = 1;
          delay(1600);
          digitalWrite(10,LOW); 
          digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크
          moter = 0;
          break;
                        }
                      }
                    }
    }
  
    
  //*******************************************************************************
  
  for(;;){  //초기화 는 처음에 딱 한 번만. 루프에서 매번, 조건 이 테스트된다; 그것이 true 이면, 문 블록과 증가 가 실행되며, 그러면 조건 이 다시 테스트된다. 조건 이 false 되면, 루프는 끝난다.
  switchh = digitalRead(12); //아두이노의 디지털 12핀으로부터 HIGH 또는 LOW 값을 읽어온다.
  atime = millis(); //아두이노 보드가 시작한 후 지난 밀리 초 시간을 읽는다.

  if(switchh == 0) { //스위치 작동중이 아니면 uv램프 정지
    digitalWrite(7,LOW);
    digitalWrite(heater,LOW);
    relay = 0; //작동중지상태
                   }

  if(switchh == 1) {  //스위치 작동 문이 닫힌 상태
      if(relay == 0) {  //만약 작동하지않고 있다면 작동시작
        digitalWrite(7,HIGH);
        ztime = millis();
        relay = 1; //작동
                     }
      if(relay == 1) {  //작동
        if(atime/200 > ztime/200+50) {  //10초 지난경우
          digitalWrite(7,LOW); //종료
          delay(500);
          relay = 0; //살균종료상태 
          break;
                                     } 
                     }
                   }
        }
  delay(500);

//*****************************************************************************

  for(;;) {
  int vvalue = analogRead(sensor);
  Serial.print("밝기 값 : ");
  Serial.println(vvalue);
  delay(100);
  
  if(switchh == 0) {
    analogWrite(9, 50); //속도제어
    digitalWrite(10,LOW); 
    digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크    
    moter = 0;
                    }

  if(switchh == 1) {
      if(moter == 0) {
        if(vvalue > 300) { //300보다 밝을 때
          // digitalWrite(5,HIGH); // 속도조절을 위해 아날로그 신호로 바꿈
          analogWrite(9, 50); //속도제어
          digitalWrite(10,LOW);
          digitalWrite(11,LOW); //둘다 HIGH거나 LOW일때 브레이크
          break;
                        }
                      }
                    }

  if(switchh == 1) {
       if(moter == 0) {
          if(vvalue <= 300) { //300보다 같거나 어두울 때
       //   digitalWrite(5,HIGH); // 속도조절을 위해 아날로그 신호로 바꿈
            analogWrite(9, 50); //속도제어
            digitalWrite(10,LOW); //역방향 회전
            digitalWrite(11,HIGH); //역방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
            moter = 1;
            delay(1600);
            digitalWrite(10,LOW); 
            digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크
            moter = 0;
            break;
                            }
                      }
    
                    }
    }
    
//****************************************************************************

  for(;;){ //*****dht11 라이브러리 설치해야함*****
    Serial.begin(9600);
    delay(1000);
    dht.begin();
    float humi, temp;
    temp = dht.readTemperature();
    humi = dht.readHumidity();
    switchh = digitalRead(12); //아두이노의 디지털 8핀으로부터 HIGH 또는 LOW 값을 읽어온다.
    dtime = millis();

    if(switchh == 0) {  //스위치 작동 문이 열린 상태
      digitalWrite(6,LOW);
      heaterrelay = 0; //작동중지상태
                      }
  
  if(switchh == 1) {  //스위치 작동 문이 닫힌 상태
    if(heaterrelay == 0) {  //만약 작동하지않고 있다면 작동시작
      digitalWrite(6,HIGH);
      btime = millis();
      heaterrelay = 1; //작동
                          }
    if(heaterrelay == 1) {  //작동
      if(dtime/200 < btime/200+100) {
           Serial.print(temp); //시리얼모니터에 섭씨 출력 nan뜨는건 어쩔 수 없다. 시리얼모니터쪽에 딜레이주면 해결될지도?
           Serial.println("C");

      if(temp < 40.0) {  //40도 이하일때
      digitalWrite(heater,HIGH); //켜짐
                      }
      if(temp > 40.0) {
      digitalWrite(heater,LOW); //꺼짐
                      }
                                  }    
      if(dtime/200 >= btime/200+100) {
      digitalWrite(heater,LOW);  // 꺼짐
      break;
                                  }
                           }
   delay(500);
                    }
    }
  exit(0);
  }
