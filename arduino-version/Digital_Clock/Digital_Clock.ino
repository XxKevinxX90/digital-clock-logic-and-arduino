#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Keypad.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 10;

// Alarm time
int alarmHour = 4;
int alarmMinute = 30;
bool alarmTriggered = false;  // Set when time matches, prevents re-trigger
bool alarmRinging   = false;  // True while user hasn’t stopped the beeps

// Keypad setup
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputTime   = "";
bool settingAlarm  = false;
unsigned long lastUpdate = 0;

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);  // إيقاف الجرس

  if (!rtc.begin()) {
    lcd.print("RTC not found!");
    while (1);  // وقف البرنامج لو مفيش RTC
  }


//rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 


  lcd.print("Welcome MIU");
  delay(2000);
  lcd.clear();
  lcd.print("Press A: Alarm");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1) Keypad handling (even during alarm)
  char key = keypad.getKey();  // قراءة الزر الي ضغطه المستخدم
  if (key) {
    // Enter alarm-setting
    if (key == 'A' && !alarmRinging) {
      settingAlarm = true;
      inputTime = "";
      lcd.clear();
      lcd.print("Set Alarm HHMM:");
    }
    // Confirm new alarm
    else if (key == '#' && settingAlarm) {
      if (inputTime.length() == 4) 
      {
        // تحويل أول رقمين إلى ساعة والباقي إلى دقيقه
        alarmHour   = inputTime.substring(0,2).toInt();
        alarmMinute = inputTime.substring(2,4).toInt();
        alarmTriggered = false;   // السماح بتشغيل المنبه لاحقًا
        lcd.clear();
        lcd.print("Alarm Set:");
        lcd.setCursor(0,1);

        // تنسيق عرض الوقت (0 قبل الرقم إذا كان أقل من 10)
        if (alarmHour < 10) lcd.print('0');
        lcd.print(alarmHour);
        lcd.print(':');
        if (alarmMinute < 10) lcd.print('0');
        lcd.print(alarmMinute);
        delay(2000);
      }
      settingAlarm = false;  // الانتهاء من ضبط المنبه
      lcd.clear();
    }

    // Backspace during setting
    else if (settingAlarm && key == 'C' && inputTime.length()>0)
     {
      inputTime.remove(inputTime.length()-1);
      lcd.setCursor(0,1);
      lcd.print("    ");
      lcd.setCursor(0,1);
      lcd.print(inputTime);
    }
    // Digit entry
    else if (settingAlarm && isDigit(key) && inputTime.length()<4) {
      inputTime += key;
      lcd.setCursor(inputTime.length()-1,1);
      lcd.print(key);
    }
    // ** Stop the ringing! **
    else if (alarmRinging && key == 'B') {
      alarmRinging = false;
      digitalWrite(buzzerPin, LOW);  // إيقاف الجرس
      lcd.clear();
      lcd.print("Alarm stopped");
      delay(1000);
      lcd.clear();
      // allow clock display to resume
    }
  }

  // 2) Regular clock display (once per second, only if not in setting or ringing)
  if (!settingAlarm && !alarmRinging && millis()-lastUpdate>1000) {
    lastUpdate = millis();
    DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print("Time: ");
    if (now.hour()<10) lcd.print('0');
    lcd.print(now.hour());
    lcd.print(':');
    if (now.minute()<10) lcd.print('0');
    lcd.print(now.minute());
    lcd.print(':');
    if (now.second()<10) lcd.print('0');
    lcd.print(now.second());

    lcd.setCursor(0,1);
    lcd.print("Date: ");
    if (now.day()<10) lcd.print('0');
    lcd.print(now.day());
    lcd.print('/');
    if (now.month()<10) lcd.print('0');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
  }

  // 3) Alarm trigger: start ringing when time matches
  DateTime now2 = rtc.now();
  if (!alarmTriggered && !alarmRinging
      && now2.hour()==alarmHour
      && now2.minute()==alarmMinute
      && now2.second()==0) {
    alarmTriggered = true;
    alarmRinging   = true;
    lcd.clear();
    lcd.print("ALARM RINGING!");
  }

  // 4) If ringing, play repeated beeps until stopped
  while (alarmRinging) {
    // short beep
    tone(buzzerPin, 1000);  
    delay(200);             
    noTone(buzzerPin);      
    delay(100);             

    // Check if user pressed 'B' to stop
    char k = keypad.getKey();
    if (k == 'B') {
      alarmRinging = false;
      digitalWrite(buzzerPin, LOW);
      lcd.clear();
      lcd.print("Alarm stopped");
      delay(1000);
      lcd.clear();
      break;
    }
  }
}
