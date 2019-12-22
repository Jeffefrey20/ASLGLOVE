/***********************************************/
 /* Name of the project: ASL Glove              */
 /* Author:                                     */
 /* Date : 12/5/2019                           */
 /***********************************************/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int FLEX_P = A0; //initialize each analog pin used for arduino
const int FLEX_R = A1;
const int FLEX_M = A2;
const int FLEX_I = A3;
const int FLEX_T = A6;

const float VCC = 4.98; //max voltage
const float R_DIV = 47000.0; //resistor used for each flex sensor
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;


const float STRAIGHT_RESISTANCE = 25000.0; // resistance when straight
const float BEND_RESISTANCE = 100000.0; // resistance at 90 deg

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  pinMode(FLEX_P, INPUT);
  pinMode(FLEX_R, INPUT);
  pinMode(FLEX_M, INPUT);
  pinMode(FLEX_I, INPUT);
  pinMode(FLEX_T, INPUT);
  lcd.begin(16, 2);
  lcd.print("You Entered:");
  
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU to b1101000/b1101001 based on the datasheet
  Wire.write(0x6B); //Accessing the register 6B - Power Management 
  Wire.write(0b00000000); //Setting SLEEP register to 0. 
  Wire.endTransmission();  

  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}
// This method will record the acceleration part of the MPU 
void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}
// This method processes the raw acceleration data to more readable numbers for later use 
void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}
void loop() {
  lcd.setCursor(0, 1); //LCD screan cursor
  float flexADC1 = analogRead(FLEX_P);
  float flexADC2 = analogRead(FLEX_R);
  float flexADC3 = analogRead(FLEX_M);
  float flexADC4 = analogRead(FLEX_I);
  float flexADC5 = analogRead(FLEX_T);
  //Voltage division to find the resistance of the flex sensor
  float flexV1 = flexADC1 * VCC / 1023.0;
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexV3 = flexADC3 * VCC / 1023.0;
  float flexV4 = flexADC4* VCC / 1023.0;
  float flexV5 = flexADC5 * VCC / 1023.0;
  
  float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
  float flexR2 = R_DIV * (VCC / flexV2 - 1.0);
  float flexR3 = R_DIV * (VCC / flexV3 - 1.0);
  float flexR4 = R_DIV * (VCC / flexV4 - 1.0);
  float flexR5 = R_DIV * (VCC / flexV5 - 1.0);
  recordAccelRegisters();

  //Maps out the resistance into a value between 0-90 for easiser access to data
   float angle1 = map(flexR1, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                    0, 90.0);
   float angle2 = map(flexR2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
   float angle3 = map(flexR3, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
   float angle4 = map(flexR4, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
   float angle5 = map(flexR5, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
//Print a letter based on the angle of each flex sensor
if((angle1 >=48 && angle1<=56)&&(angle2>=63 && angle2<=70)&&(angle3>=38&&angle3<=46)&&(angle4>=47&&angle4<=54)&&(angle5>=5&&angle5<=20)){
  lcd.print('A');
}
else if((angle1 >=25&& angle1<=31)&&(angle2<=13)&&(angle3>=10&&angle3<=30)&&(angle4>=25&&angle4<=35)&&(angle5>=31&&angle5<=39)){
  lcd.print('B');
}
else if((angle1 >=42 && angle1<=50)&&(angle2>=57 && angle2<=63)&&(angle3>=36&angle3<=43)&&(angle4>=44&&angle4<=51)&&(angle5>=31&&angle5<=39)){
  lcd.print('C');
}
else if((angle1 >=46 && angle1<=54)&&(angle2>=57 && angle2<=64)&&(angle3>=36&&angle3<=44)&&(angle4>=24&&angle4<=33)&&(angle5>=40&&angle5<=48)){
  lcd.print('D');
}
else if((angle1 >=44 && angle1<=52)&&(angle2>=57 && angle2<=62)&&(angle3>=37&&angle3<=45)&&(angle4>=44&&angle4<=52)&&(angle5>=25&&angle5<=35)){
  lcd.print('E');
}
else if((angle1 >=24& angle1<=32)&&(angle2>=5 && angle2<=20)&&(angle3>=20&&angle3<=30)&&(angle4>=42&&angle4<=52)&&(angle5>=30&&angle5<=40)){
  lcd.print('F');
}
else if((angle1 >=44 && angle1<=51)&&(angle2>=58&&angle2<=65)&&(angle3>=35&&angle3<=45)&&(angle4>=26&&angle4<=36)&&(angle5>=21&&angle5<=35)){
  lcd.print('G');
}
else if((angle1 >=41 && angle1<=50)&&(angle2>=55 && angle2<=62)&&(angle3>=17&&angle3<=35)&&(angle4>=26&&angle4<=36)&&(angle5>=24&&angle5<=32)){
  lcd.print('H');
}
else if(( angle1<=30)&&(angle2>=56 && angle2<=64)&&(angle3>=35&&angle3<=45)&&(angle4>=41&&angle4<=51)&&(angle5>=30&&angle5<=43)&&gForceX<0){
  lcd.print('J');
  delay(1000);
}
else if(( angle1<=30)&&(angle2>=56 && angle2<=64)&&(angle3>=35&&angle3<=45)&&(angle4>=41&&angle4<=51)&&(angle5>=30&&angle5<=43)){
  lcd.print('I');
}
else if((angle1 >=36&& angle1<=44)&&(angle2>=53 && angle2<=63)&&(angle3>=20&&angle3<=35)&&(angle4>=34&&angle4<=42)&&(angle5>=10&&angle5<=25)){
  lcd.print('K');
}
else if((angle1 >=44 && angle1<=52)&&(angle2>=57 && angle2<=67)&&(angle3>=37&&angle3<=47)&&(angle4>=25&&angle4<=35)&&(angle5>=10&&angle5<=30)){
  lcd.print('L');
}
else if((angle1 >=34 && angle1<=42)&&(angle2>=50&&angle2<=56)&&(angle3>=35&&angle3<=45)&&(angle4>=40&&angle4<=48)&&(angle5>=30&&angle5<=40)){
  lcd.print('M');
}
else if((angle1 >=46 && angle1<=54)&&(angle2>=64 && angle2<=72)&&(angle3>=35&&angle3<=45)&&(angle4>=44&&angle4<=52)&&(angle5>=20&&angle5<=35)){
  lcd.print('N');
}
else if((angle1 >=40&& angle1<=47)&&(angle2>=50 && angle2<=58)&&(angle3>=36&&angle3<=44)&&(angle4>=42&&angle4<=50)&&(angle5>=24&&angle5<=33)){
  lcd.print('O');
}
else if((angle1 >=47&& angle1<=54)&&(angle2>=58 && angle2<=66)&&(angle3>=29&&angle3<=37)&&(angle4>=24&&angle4<=34)&&(angle5>=10&&angle5<=30)){
  lcd.print('P');
}
else if((angle1 >=50&& angle1<=58)&&(angle2>=63 && angle2<=73)&&(angle3>=37&&angle3<=44)&&(angle4>=28&&angle4<=38)&&(angle5>=5&&angle5<=20)){
  lcd.print('Q');
}
else if((angle1 >=47& angle1<=57)&&(angle2>=63 && angle2<=71)&&(angle3>=33&&angle3<=43)&&(angle4>=15&&angle4<=35)&&(angle5>=30&&angle5<=40)){
  lcd.print('R');
}
else if((angle1 >=53&& angle1<=60)&&(angle2>=68 && angle2<=75)&&(angle3>=39&&angle3<=47)&&(angle4>=41&&angle4<=50)&&(angle5>=36&&angle5<=44)){
  lcd.print('S');
}
else if((angle1 >=51&& angle1<=61)&&(angle2>=65 && angle2<=75)&&(angle3>=40&&angle3<=50)&&(angle4>=39&&angle4<=49)&&(angle5<=10)){
  lcd.print('T');
}
else if((angle1 >=51 &&angle1<=61)&&(angle2>=65 && angle2<=75)&&(angle3>=26&&angle3<=36)&&(angle4>=25&&angle4<=31)&&(angle5>=29&&angle5<=37)){
  lcd.print('U');
}
else if((angle1 >=51& angle1<=61)&&(angle2>=66 && angle2<=76)&&(angle3>=32&&angle3<=40)&&(angle4>=33&&angle4<=42)&&(angle5>=28&&angle5<=36)){
  lcd.print('V');
}
else if((angle1 >=51&& angle1<=61)&&(angle2>=10 && angle2<=25)&&(angle3>=28&&angle3<=36)&&(angle4>=32&&angle4<=40)&&(angle5>=30&&angle5<=37)){
  lcd.print('W');
}
else if((angle1 >=47&& angle1<=55)&&(angle2>=64 && angle2<=72)&&(angle3>=42&&angle3<=49)&&(angle4>=44&&angle4<=52)&&(angle5>=39&&angle5<=49)){
  lcd.print('X');
}
else if((angle1 >=21&& angle1<=31)&&(angle2>=56 && angle2<=66)&&(angle3>=37&&angle3<=47)&&(angle4>=44&&angle4<=54)&&(angle5>=10&&angle5<=30)){
  lcd.print('Y');
}
else if((angle1 >=51&& angle1<=59)&&(angle2>=64 && angle2<=71)&&(angle3>=41&&angle3<=49)&&(angle4>=31&&angle4<=41)&&(angle5>=27&&angle5<=38)&&gForceX<0){
  lcd.print('Z');
  delay(1000);
}
else{
  lcd.print('?');
}


delay(200);
 
}
