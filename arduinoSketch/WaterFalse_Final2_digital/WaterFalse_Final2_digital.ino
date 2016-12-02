/*
 *  WaterFalse - NIME
 *  Nov 23 2016
 *  Yuli Cai
 */

//note
//module 3,4 fans wires connection problem
//adjust the placement of photocell and led light to fix it, not letting it move in any chance
//redo the wrong black acrylic box
//water proof the fans

const int photoCellPin1 = A2;
const int photoCellPin2 = A5;
const int photoCellPin3 = A4;
const int photoCellPin4 = A3;
const int LED1 = 3;
const int LED2 = 10;
const int LED3 = 6;
const int LED4 = 5;
const int fan1 = 9;
const int fan2 = 7;
const int fan3 = 4;
const int fan4 = 8;

/*Led strip varibles*/
int rawLight1, rawLight2, rawLight3, rawLight4;
//led varibles for holding averaged values
int light1, light2, light3, light4;
float avgScale = 0.95;


/* light testing */
//light 1, normalOn:320, 350-800,
//light 2, normalOn: 40, 250-400,
//light 3, normalOn: 340, 370-850,
//light 4, normalOn: 200, 350-730,

//need to adjust | influenced by environmental light
int light1Min = 350;
int light1Max = 800;
int light2Min = 250;
int light2Max = 400;
int light3Min = 370;
int light3Max = 850;
int light4Min = 350;
int light4Max = 730;
/*normal status, with yellow led off*/
//if min number is a lot more then 100, set normal to 100 or even higher
//but print the button value in arduino side first before confirm the number
int normalOn1 = 320;
int normalOn2 = 40;
int normalOn3 = 340;
int normalOn4 = 200;

boolean module1NotActivated = true;
boolean module2NotActivated = true;
boolean module3NotActivated = true;
boolean module4NotActivated = true;

boolean button1 = false;
boolean button2 = false;
boolean button3 = false;
boolean button4 = false;



void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);


}

void loop() {

  rawLight1 = analogRead(photoCellPin1);
  rawLight2 = analogRead(photoCellPin2);
  rawLight3 = analogRead(photoCellPin3);
  rawLight4 = analogRead(photoCellPin4);
  //Average all the raw data to smooth them out
  light1 = avgScale * light1 + (1.00 - avgScale) * rawLight1;
  light2 = avgScale * light2 + (1.00 - avgScale) * rawLight2;
  light3 = avgScale * light3 + (1.00 - avgScale) * rawLight3;
  light4 = avgScale * light4 + (1.00 - avgScale) * rawLight4;
  int ledBrightness1 = map(light1, light1Max, light1Min, 10, 255);
  int ledBrightness2 = map(light2, light2Max, light2Min, 10, 255);
  int ledBrightness3 = map(light3, light3Max, light3Min, 10, 255);
  int ledBrightness4 = map(light4, light4Max, light4Min, 10, 255);


  /*module one*/
  /////////////////////////
  //normal yellow led on, no pulling, led strip should be off
  if (light1 > normalOn1 - 70 && light1 < normalOn1 + 70) {
    ledBrightness1 = 0;
    module1NotActivated = true;
    button1 = false;
    digitalWrite(fan1, LOW);
  } else {
    module1NotActivated = false;
    button1 = true;
    digitalWrite(fan1, HIGH);
  }
  analogWrite(LED1, ledBrightness1);
  /////////////////////////
  /////////////////////////


  /*module two*/
  /////////////////////////
  //normal yellow led on, no pulling, led strip should be off
  if (light2 > normalOn2 - 70 && light2 < normalOn2 + 70) {
    ledBrightness2 = 0;
    module2NotActivated = true;
    button2 = false;
    digitalWrite(fan2, LOW);
  } else {
    module2NotActivated = false;
    button2 = true;
    //controling fans
    digitalWrite(fan2, HIGH);
  }
  analogWrite(LED2, ledBrightness2);
  /////////////////////////
  /////////////////////////



  /*module three*/
  /////////////////////////
  //normal yellow led on, no pulling, led strip should be off
  if (light3 > normalOn3 - 70 && light3 < normalOn3 + 70) {
    ledBrightness3 = 0;
    module3NotActivated = true;
    button3 = false;
    digitalWrite(fan3, LOW);
  } else {
    module3NotActivated = false;
    button3 = true;
    digitalWrite(fan3, HIGH);
  }
  analogWrite(LED3, ledBrightness3);
  /////////////////////////
  /////////////////////////



  /*module four*/
  /////////////////////////
  //fan mode special, using digital pin 4 instead
  //normal yellow led on, no pulling, led strip should be off
  if (light4 > normalOn4 - 70 && light4 < normalOn4 + 70) {
    ledBrightness4 = 0;
    module4NotActivated = true;
    button4 = false;
    digitalWrite(fan4, LOW);
  } else {
    module4NotActivated = false;
    button4 = true;
    //controling fans
    digitalWrite(fan4, HIGH);
  }
  analogWrite(LED4, ledBrightness4);
  /////////////////////////
  /////////////////////////

  if (module1NotActivated && module2NotActivated && module3NotActivated && module4NotActivated) {
    Serial.println("silent mode");
    digitalWrite(fan1, LOW);
    digitalWrite(fan2, LOW);
    digitalWrite(fan3, LOW);
    digitalWrite(fan4, LOW);
  }

  Serial.print(light1);
  Serial.print(" ");
  Serial.print(light2);
  Serial.print(" ");
  Serial.print(light3);
  Serial.print(" ");
  Serial.print(light4);
  Serial.print(" ");
  Serial.print(button1);
  Serial.print(" ");
  Serial.print(button2);
  Serial.print(" ");
  Serial.print(button3);
  Serial.print(" ");
  Serial.print(button4);
  Serial.println();


/*
 * testing print out
 */

//    Serial.print("light1= ");
//    Serial.println(light1);
//  Serial.print("light2= ");
//  Serial.println(light2);
//     Serial.print("light3 = ");
//     Serial.println(light3);
//      Serial.print("light4 = ");
//     Serial.println(light4);

}





