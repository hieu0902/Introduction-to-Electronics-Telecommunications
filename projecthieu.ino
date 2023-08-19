#include<IRremote.h>
#include<Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
const int stepsPerRevolution=2048;
Stepper myStepper =Stepper(stepsPerRevolution,8,9,10,11);
int cbm =7;
int ct1=3;
int ct2=4;

//khi mo
LiquidCrystal_I2C lcd(0x27,16,2); 
#include <DHT.h>
const int DHTPIN = 5;//Chân Out của cảm biến nối chân số 5 Arduino
const int DHTTYPE = DHT11;   // Khai báo kiểu cảm biến là DHT11
DHT dht(DHTPIN, DHTTYPE); //Khai báo thư viện chân cảm biến và kiểu cảm biến
String doam1="Do am:";
String nhietdo="Nhiet Do :";
String comua="% Co Mua";
String komua="% ko Mua";
const int chanRemote=2;
IRrecv irrecv(chanRemote);
decode_results results;//lưu trữ kết quả giải mã tín hiệu
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(cbm,INPUT); 
  
  pinMode(ct1,INPUT);
  pinMode(ct2,INPUT);
  irrecv.enableIRIn();//khoi dong bo thu ir
  dht.begin(); //Khởi động cảm biến
  lcd.init(); //Khởi động LCD                    
  lcd.backlight(); //Mở đèn
  lcd.setCursor(0,0);
  lcd.print("DO AM:");
  lcd.setCursor(0,1);
  lcd.print("C|F:");
}
void loop() {
   //put your main code here, to run repeatedly:
  int trangthai1=digitalRead(ct1);//la dang dong
  int trangthai2=digitalRead(ct2);
  int doccbm=digitalRead(cbm);
  int trangthai;
float doam = dht.readHumidity(); //Đọc độ ẩm
float doC = dht.readTemperature(); //Đọc nhiệt độ C
float doF = dht.readTemperature(true); //Đọc nhiệt độ F
  // Kiểm tra cảm biến có hoạt động hay không
 hienthichuoi(0,0,doam1);
 hienthiso(6,0,doam);hienthichuoi(8,0,komua);
 hienthichuoi(0,1,nhietdo);
 hienthiso(10,1,doC);lcd.print("*");
 lcd.print("C");
 delay(1000);


if(irrecv.decode(&results))
{
 if(results.value==0xFF22DDD)
 { while(trangthai1!=1)
   {dong();
   trangthai1=digitalRead(ct1);
   }
 
}else if(results.value==0xFF02FD)
{
  while(trangthai2!=1)
  {
   mo();
   trangthai1=digitalRead(ct2);
   
  }
 irrecv.resume();}
}
if(doccbm==1)
{if(trangthai2!=1)
  {mo();
  hienthichuoi(8,0,comua);
  delay(10000);
  
}
}}
void dong()
{
  myStepper.step(0.5*stepsPerRevolution);
}
void mo()
{
  myStepper.step(-0.5*stepsPerRevolution);
  
}

void hienthichuoi(int cot, int dong, String chuoi)
{
  lcd.setCursor(cot,dong);
  for(int j=0;j<chuoi.length();j++)
    {
      lcd.print(chuoi[j]);
    } 
}
void hienthiso(int cot, int dong, int so)
{
  String chuoi=String(so);
  lcd.setCursor(cot,dong);
  for(int j=0;j<chuoi.length();j++)
    {
      lcd.print(chuoi[j]);
    } 
}
