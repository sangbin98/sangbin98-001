  #include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

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
int relay=0;
int heaterrelay =0;
int sensor = A1;
int moter=0;

void setup() {
  pinMode(7,OUTPUT); //UV램프에 연결된 릴레이
  pinMode(12,INPUT);  //마이크로 스위치
  digitalWrite(7,LOW); 
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(heater,OUTPUT);
  digitalWrite(9,LOW); 
  // pinMode(9,OUTPUT); //ENA // 속도조절을 위해 아날로그 신호로 바꿈 따라서 핀모드가 필요 없어지므로 주석처리함
  // ENA가 LOW일때 모터는 정지함 HIGH일때 회전하거나 브레이크
  pinMode(10,OUTPUT); //IN 1
  pinMode(11,OUTPUT); //IN 2
  delay(500);
}

void loop() {
    
  for(;;) {
    if(mySerial.available()>0)
    {
      if(mySerial.read()=='1') //스위치 on
    {
      //2번
          analogWrite(9, 500); //속도제어
          digitalWrite(10,HIGH); //정방향 회전
          digitalWrite(11,LOW); //정방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
          delay(5000);
          digitalWrite(10,LOW); 
          digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크

          delay(500);
//3번
        digitalWrite(7,HIGH);
        delay(5000);
        
        digitalWrite(7,LOW); //종료
        delay(500);
//4번
            analogWrite(9, 500); //속도제어
            digitalWrite(10,LOW); //역방향 회전
            digitalWrite(11,HIGH); //역방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
            delay(5000);
            digitalWrite(10,LOW); 
            digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크
            delay(500);
//5번
      digitalWrite(6,HIGH);
      delay(5000);
      digitalWrite(6,LOW);
        
          
    }
    if(mySerial.read()=='2') //모터 정방향
    {
          analogWrite(9, 500); //속도제어
          digitalWrite(10,HIGH); //정방향 회전
          digitalWrite(11,LOW); //정방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
          delay(5000);
          digitalWrite(10,LOW); 
          digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크

    }
    if(mySerial.read()=='3') //UV램프
    {
        digitalWrite(7,HIGH);
        delay(5000);
        
        digitalWrite(7,LOW); //종료
        delay(500);
        switchh=0;
          
    }
  
    
    if(mySerial.read()=='4') //모터 역방향
    {
            analogWrite(9, 500); //속도제어
            digitalWrite(10,LOW); //역방향 회전
            digitalWrite(11,HIGH); //역방향 회전 // 둘다 HIGH거나 LOW일때 브레이크
            delay(5000);
            digitalWrite(10,LOW); 
            digitalWrite(11,LOW); // 둘다 HIGH거나 LOW일때 브레이크
            switchh=0; 
  
    }

    if(mySerial.read()=='5') //팬 작동
    {
      digitalWrite(6,HIGH);
      switchh=0;
      delay(5000);
      digitalWrite(6,LOW);
    
    Serial.println(mySerial.read());
                          }
  }
}
}
