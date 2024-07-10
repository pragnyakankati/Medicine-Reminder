#include <LiquidCrystal.h>
#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

RTC_DS3231 rtc;

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char *largetext8am = "Morning medicines: azithromycin";
char *largetext2pm = "Afternoon medicines: dolo650";
char *largetext8pm = "Night medicines: coldact";
int icursor = 0;

int buzz = 13;
int addr = 17;
const int led8am = A1;
const int led2pm = A2;
const int led8pm = A3;
const int buttonPin1 = A0;
const int buttonPin2 = 9;
const int buttonPin3 = 8;
const int buttonPin4 = 7;
int val2 = 0;
int val3 = 0;
int pushVal;
int bS1 = 0;
int lBS1 = 0;

int bS2 = 0;
int lBS2 = 0;

int bS3 = 0;
int lBS3 = 0;

int bS4 = 0;
int lBS4 = 0;

int buzz8amHH = 8;
int buzz8amMM = 00;
int buzz8amSS = 00;

int buzz2pmHH = 14;
int buzz2pmMM = 00;
int buzz2pmSS = 00;

int buzz8pmHH = 20;
int buzz8pmMM = 00;
int buzz8pmSS = 00;

int nowHr, nowMin, nowSec;

void gwsMessege() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stay Healthy :)");
  lcd.setCursor(0, 1);
  lcd.print("Get Well Soon :)");
}

void helpScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Buttons");
  lcd.setCursor(0, 1);
  lcd.print("to set a Reminder!");
}

void timeScreen() {
  DateTime now = rtc.now();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(nowHr = now.hour(), DEC);
  lcd.print(":");
  lcd.print(nowMin = now.minute(), DEC);
  lcd.print(":");
  lcd.print(nowSec = now.second(), DEC);
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  delay(500);
}

void setup() {
  Wire.begin();
  rtc.begin();
   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // yyyy,mm,dd
  rtc.adjust(DateTime(2024, 05, 10, 7, 59, 00));

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MINI PROJECT");
  lcd.setCursor(0, 1);
  lcd.print("MedicineReminder");
  delay(1000);
  gwsMessege();
  delay(3000);
  helpScreen();
  delay(2000);
  timeScreen();
  delay(3000);
  lcd.clear();

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(led8am, OUTPUT);
  pinMode(led2pm, OUTPUT);
  pinMode(led8pm, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
}

void ValSet() {
  Serial.println(EEPROM.read(addr));
  val2 = EEPROM.read(addr);
  switch (val2) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reminder set");
      lcd.setCursor(0, 1);
      lcd.print("for Once/day !");
      pushVal = 1;
      delay(500);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reminder set");
      lcd.setCursor(0, 1);
      lcd.print("for Twice/day !");
      pushVal = 2;
      delay(500);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reminder set");
      lcd.setCursor(0, 1);
      lcd.print("for Thrice/day !");
      pushVal = 3;
      delay(500);
      break;
  }
}

void loop() {
  if (pushVal == 1) {
    at8am();
  }
  else if (pushVal == 2) {
    at8am();
    at8pm();
  }
  else if (pushVal == 3) {
    at8am();
    at2pm();
    at8pm();
  }

  bS1 = digitalRead(buttonPin1);
  bS2 = digitalRead(buttonPin2);
  bS3 = digitalRead(buttonPin3);
  bS4 = digitalRead(buttonPin4);

  if (bS2 != lBS2) {
    if (bS2 == HIGH) {
      Serial.println("2nd");
      Serial.print("button is on");
      EEPROM.write(17, 1);
      push1();
      delay(1000);
    }
  }
  lBS2 = bS2;

  if (bS3 != lBS3) {
    if (bS3 == HIGH) {
      Serial.println("3rd");
      Serial.print("button is on");
      EEPROM.write(17, 2);
      push2();
      delay(1000);
    }
  }
  lBS3 = bS3;

  if (bS4 != lBS4) {
    if (bS4 == HIGH) {
      Serial.println("4th");
      Serial.print("button is on");
      EEPROM.write(17, 3);
      push3();
      delay(1000);
    }
  }
  lBS4 = bS4;

  if (bS1 != lBS1) {
    if (bS1 == HIGH) {
      val3 = EEPROM.read(addr);
      EEPROM.write(17, 0);
      pinstop();
      EEPROM.write(17, val3);
    }
  }
  lBS1 = bS1;

  timeScreen();
  ValSet();
}

void push1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reminder");
  lcd.setCursor(0, 1);
  lcd.print("for Once/day!");
  delay(1200);
  lcd.clear();
}

void push2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reminder");
  lcd.setCursor(0, 1);
  lcd.print("for Twice/day !");
  delay(1200);
  lcd.clear();
}

void push3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reminder");
  lcd.setCursor(0, 1);
  lcd.print("for Thrice/day !");
  delay(1200);
  lcd.clear();
}

void pinstop() {
  digitalWrite(buzz, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Take Medicine ");
  lcd.setCursor(0, 1);
  lcd.print("with Water");
  delay(5000);
  lcd.clear();
}

void at8am() {
  DateTime t = rtc.now();
  if (int(t.hour()) == buzz8amHH && int(t.minute()) == buzz8amMM && (int(t.second()) == buzz8amSS || int(t.second()) < buzz8amSS + 10)) {
    digitalWrite(buzz, HIGH);
    digitalWrite(led8am, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to take ");
    lcd.setCursor(0, 1);
    lcd.print("Mrng medicines.");
    delay(12000);
    scrollText(largetext8am);
  }
  else {
    digitalWrite(led8am, LOW);
  }
}

void at2pm() {
  DateTime t = rtc.now();
  if (int(t.hour()) == buzz2pmHH && int(t.minute()) == buzz2pmMM && (int(t.second()) == buzz2pmSS || int(t.second()) < buzz2pmSS + 10)) {
    digitalWrite(buzz, HIGH);
    digitalWrite(led2pm, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to take ");
    lcd.setCursor(0, 1);
    lcd.print("Aftn medicines.");
    delay(12000);
    scrollText(largetext2pm);
  }
  else {
    digitalWrite(led2pm, LOW);
  }
}

void at8pm() {
  DateTime t = rtc.now();
  if (int(t.hour()) == buzz8pmHH && int(t.minute()) == buzz8pmMM && (int(t.second()) == buzz8pmSS || int(t.second()) < buzz8pmSS + 10)) {
    digitalWrite(buzz, HIGH);
    digitalWrite(led8pm, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to take ");
    lcd.setCursor(0, 1);
    lcd.print("Night medicines.");
    delay(12000);
    scrollText(largetext8pm);
  }
  else {
    digitalWrite(led8pm, LOW);
  }
}

void scrollText(char *largetext) {
  int ilenoflargetext = strlen(largetext);

  for (int i = 0; i < ilenoflargetext; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    for (int j = 0; j < 16 && (i + j) < ilenoflargetext; j++) {
      lcd.print(largetext[i + j]);
    }
    delay(550);
  }
}
