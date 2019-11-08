#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int FLEX_PIN1 = A0; 
const int FLEX_PIN2 = A1;
const int FLEX_PIN3 = A2;
const int FLEX_PIN4 = A3;
const int FLEX_PIN5 = A6;

const float VCC = 4.98; 
const float R_DIV = 47000.0; 

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 25000.0; // resistance when straight
const float BEND_RESISTANCE = 100000.0; // resistance at 90 deg

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  pinMode(FLEX_PIN5, INPUT);
  lcd.begin(16, 2);
  lcd.print("You Entered:");

}


void loop() {
  lcd.setCursor(0, 1);
  float flexADC1 = analogRead(FLEX_PIN1);
  float flexADC2 = analogRead(FLEX_PIN2);
  float flexADC3 = analogRead(FLEX_PIN3);
  float flexADC4 = analogRead(FLEX_PIN4);
  float flexADC5 = analogRead(FLEX_PIN5);
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

if((angle1 >=50 && angle1<=60)&&(angle2>=42 && angle2<=52)&&(angle3>=32&&angle3<=42)&&(angle4>=50&&angle4<=60)&&(angle5<=35)){
  lcd.print('A');
}
else if((angle1 >=10 && angle1<=40)&&(angle2>=10&&angle2<=25)&&(angle3>=10&&angle3<=25)&&(angle4>=30&&angle4<=41)&&(angle5>=37&&angle5<=47)){
  lcd.print('B');
}
else if((angle1 >=43 && angle1<=55)&&(angle2>=38 && angle2<=48)&&(angle3>=30&&angle3<=60)&&(angle4>=48&&angle4<=58)&&(angle5>=32&&angle5<=43)){
  lcd.print('C');
}
else if((angle1 >=50 && angle1<=62)&&(angle2>=34 && angle2<=45)&&(angle3>=32&&angle3<=43)&&(angle4>=32&&angle4<=42)&&(angle5>=36&&angle5<=46)){
  lcd.print('D');
}
else if((angle1 >=52 && angle1<=62)&&(angle2>=40 && angle2<=50)&&(angle3>=33&&angle3<=43)&&(angle4>=48&&angle4<=58)&&(angle5>=37&&angle5<=47)){
  lcd.print('E');
}
else if((angle1 >=20& angle1<=45)&&(angle2>=11 && angle2<=21)&&(angle3>=11&&angle3<=21)&&(angle4>=48&&angle4<=58)&&(angle5>=34&&angle5<=44)){
  lcd.print('F');
}
else if((angle1 >=51 && angle1<=61)&&(angle2>=39&&angle2<=49)&&(angle3>=30&&angle3<=40)&&(angle4>=30&&angle4<=40)&&(angle5>=21&&angle5<=31)){
  lcd.print('G');
}
else if((angle1 >=42 && angle1<=52)&&(angle2>=36 && angle2<=46)&&(angle3>=17&&angle3<=27)&&(angle4>=32&&angle4<=42)&&(angle5>=30&&angle5<=40)){
  lcd.print('H');
}
else if(( angle1<=30)&&(angle2>=36 && angle2<=46)&&(angle3>=28&&angle3<=38)&&(angle4>=44&&angle4<=54)&&(angle5>=30&&angle5<=40)){
  lcd.print('I');
}
else if((angle1 >=44 && angle1<=54)&&(angle2>=38 && angle2<=48)&&(angle3>=15&&angle3<=30)&&(angle4>=30&&angle4<=40)&&(angle5>=14&&angle5<=35)){
  lcd.print('K');
}
else if((angle1 >=48 && angle1<=58)&&(angle2>=40 && angle2<=50)&&(angle3>=31&&angle3<=41)&&(angle4>=39&&angle4<=49)&&(angle5>=5&&angle5<=25)){
  lcd.print('L');
}
else if((angle1 >=51 && angle1<=61)&&(angle2>=38&&angle2<=48)&&(angle3>=30&&angle3<=40)&&(angle4>=47&&angle4<=57)&&(angle5>=37&&angle5<=47)){
  lcd.print('M');
}
else if((angle1 >=55 && angle1<=65)&&(angle2>=33 && angle2<=43)&&(angle3>=30&&angle3<=40)&&(angle4>=50&&angle4<=60)&&(angle5>=16&&angle5<=30)){
  lcd.print('N');
}
else{
  lcd.print('?');
}


delay(200);
  // print the number of seconds since reset:
 // lcd.print(millis() / 1000);
}
