# 🕐 Digital Clock - Logic & Arduino Implementation

A comprehensive digital clock project featuring both logic circuit design and Arduino-based implementation with real-time clock functionality, alarm system, and user interface.

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Versions](#project-versions)
- [Hardware Components](#hardware-components)
- [Circuit Diagrams](#circuit-diagrams)
- [Software Implementation](#software-implementation)
- [Installation & Setup](#installation--setup)
- [Usage](#usage)
- [Simulations](#simulations)
- [Project Images](#project-images)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

This project demonstrates the design and implementation of a digital clock system in two approaches:

1. **Logic Circuit Version**: Built using fundamental digital logic components (counters, decoders, displays)
2. **Arduino Version**: Microcontroller-based implementation with enhanced features including RTC module, LCD display, and alarm functionality

The project showcases the transition from traditional logic design to modern embedded systems, making it ideal for educational purposes and understanding both hardware and software approaches to timekeeping systems.

---

## ✨ Features

### Arduino Version Features:
- ⏰ **Real-Time Clock (RTC)**: Accurate timekeeping using DS3231 RTC module with battery backup
- 📺 **LCD Display**: 16x2 I2C LCD showing time and date
- ⏲️ **Programmable Alarm**: Set custom alarm times with buzzer notification
- ⌨️ **Keypad Interface**: 4x4 matrix keypad for user input
- 🔔 **Alarm Control**: 
  - Set alarm time in HHMM format
  - Audible alarm with buzzer
  - Snooze/stop alarm functionality
- 📅 **Date Display**: Shows day, month, and year
- 🕐 **Time Display**: 24-hour format with seconds precision

### Logic Version Features:
- 🔌 Pure logic circuit implementation
- ⚡ Counter-based timekeeping
- 🔢 7-segment display drivers
- 🎛️ Manual time adjustment

---

## 📦 Project Versions

### 1. Logic Circuit Version (`Logic-version/`)
Implementation using digital logic components such as:
- Counters (74LS90, 74LS92, etc.)
- Decoders/Drivers (7447, 7448)
- 7-segment displays
- Clock pulse generators

### 2. Arduino Version (`arduino-version/`)
Microcontroller-based implementation featuring:
- Arduino board (Uno/Nano/Mega compatible)
- DS3231 RTC module
- I2C LCD display
- 4x4 Matrix keypad
- Buzzer module

---

## 🔧 Hardware Components

### Arduino Version Components:

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino Uno/Nano | 1 | Main microcontroller |
| DS3231 RTC Module | 1 | Real-time clock with battery backup |
| 16x2 I2C LCD | 1 | Display for time and date (I2C address: 0x27) |
| 4x4 Matrix Keypad | 1 | User input interface |
| Buzzer | 1 | Alarm notification |
| Resistors | As needed | Pull-up/current limiting |
| Breadboard & Jumper Wires | 1 set | Prototyping |
| Power Supply | 1 | 5V DC power source |

### Pin Connections:

**LCD (I2C):**
- SDA → Arduino A4
- SCL → Arduino A5
- VCC → 5V
- GND → GND

**RTC Module (DS3231):**
- SDA → Arduino A4
- SCL → Arduino A5
- VCC → 5V
- GND → GND

**Buzzer:**
- Signal → Arduino Pin 10
- VCC → 5V
- GND → GND

**4x4 Keypad:**
- Row pins → Arduino Pins 9, 8, 7, 6
- Column pins → Arduino Pins 5, 4, 3, 2

---

## 📊 Circuit Diagrams

### Arduino Circuit Diagram
<img width="949" height="756" alt="Diagram" src="https://github.com/user-attachments/assets/f57b581d-94ef-4402-a413-942b6f597138" />



### Logic Circuit Diagram

<img width="600" height="840" alt="Screenshot 2026-02-01 023326" src="https://github.com/user-attachments/assets/d59f10cf-5ba5-4556-8b7f-d2122b6a30c8" />



---

## 💻 Software Implementation

### Arduino Code Structure

The Arduino implementation consists of a single main file with the following functionality:

**Main Components:**
cpp
- RTC_DS3231 rtc          // Real-time clock object
- LiquidCrystal_I2C lcd   // LCD display object
- Keypad keypad           // 4x4 keypad object


**Key Functions:**

1. **Setup()**
   - Initializes I2C communication
   - Configures LCD display
   - Sets up RTC module
   - Displays welcome message

2. **Loop()**
   - Handles keypad input
   - Updates time display every second
   - Monitors alarm conditions
   - Controls buzzer during alarm

**Keypad Commands:**

| Key | Function |
|-----|----------|
| A | Enter alarm setting mode |
| 0-9 | Input alarm time digits (HHMM format) |
| # | Confirm alarm time |
| C | Backspace during input |
| B | Stop ringing alarm |

### Required Arduino Libraries

cpp
#include <Wire.h>                  // I2C communication
#include <LiquidCrystal_I2C.h>     // LCD display control
#include <RTClib.h>                // DS3231 RTC interface
#include <Keypad.h>                // Matrix keypad support


---

## 🚀 Installation & Setup

### Arduino Version Setup:

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)

2. **Install Required Libraries**
   - Open Arduino IDE
   - Go to `Sketch → Include Library → Manage Libraries`
   - Search and install:
     - `RTClib` by Adafruit
     - `LiquidCrystal I2C` by Frank de Brabander
     - `Keypad` by Mark Stanley

3. **Hardware Assembly**
   - Connect components according to pin connections table
   - Double-check I2C addresses (default LCD: 0x27)
   - Ensure RTC module has coin cell battery installed

4. **Upload Code**
   - Open `arduino-version/Digital_Clock/Digital_Clock.ino`
   - Select correct board and port in Tools menu
   - **First Time Setup**: Uncomment line 48 to set current time:
     ```cpp
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
     ```
   - Upload the sketch
   - **After first upload**: Comment out line 48 again and re-upload

5. **Testing**
   - LCD should display "Welcome MIU"
   - Current time and date should appear
   - Test keypad functionality

---

## 🎮 Usage

### Setting Up the Clock

1. **First Time Use:**
   - Upon power-up, the clock displays a welcome message
   - Current time and date will be shown on the LCD
   - Press 'A' to set an alarm (optional)

2. **Setting an Alarm:**
   - Press **'A'** key
   - LCD displays: "Set Alarm HHMM:"
   - Enter 4 digits for time (e.g., 0630 for 6:30 AM)
   - Use **'C'** to backspace if you make a mistake
   - Press **'#'** to confirm
   - LCD confirms: "Alarm Set: HH:MM"

3. **When Alarm Triggers:**
   - LCD displays: "ALARM RINGING!"
   - Buzzer sounds repeatedly
   - Press **'B'** to stop the alarm
   - Clock returns to normal display

4. **Normal Operation:**
   - Time displays in format: `Time: HH:MM:SS`
   - Date displays in format: `Date: DD/MM/YYYY`
   - Screen updates every second

---

## 🔬 Simulations

### Wokwi Simulation

https://wokwi.com/projects/431505393163214849


### Logic Circuit Simulation

https://circuitverse.org/users/310895/projects/dld-project-digital-clock


---

## 📷 Project Image



#### Complete Setup

![Digital_Clock](https://github.com/user-attachments/assets/7111925e-faf6-4e40-b7d4-f3856d3e77cf)


---

## 🛠️ Troubleshooting

### Common Issues:

**LCD Not Displaying:**
- Check I2C connections (SDA/SCL)
- Verify I2C address (try 0x3F if 0x27 doesn't work)
- Adjust LCD contrast potentiometer

**RTC Not Found Error:**
- Ensure RTC module is properly connected
- Check I2C wiring
- Verify battery is installed in RTC module

**Incorrect Time:**
- Upload code with `rtc.adjust()` uncommented
- After setting time, comment it out and re-upload

**Keypad Not Responding:**
- Verify all row and column pin connections
- Check for loose wires
- Test individual keys

**Alarm Not Working:**
- Verify buzzer connection to pin 10
- Check buzzer polarity
- Ensure alarm time is set correctly

---

## 📚 Code Explanation

### Key Code Sections:

**Alarm Logic:**
```cpp
// Alarm triggers when time matches exactly (at 0 seconds)
if (!alarmTriggered && !alarmRinging
    && now2.hour()==alarmHour
    && now2.minute()==alarmMinute
    && now2.second()==0) {
  alarmTriggered = true;
  alarmRinging = true;
}
```

**Keypad Input Handling:**
```cpp
// Converts 4-digit input (HHMM) to hours and minutes
alarmHour = inputTime.substring(0,2).toInt();
alarmMinute = inputTime.substring(2,4).toInt();
```

**Display Update:**
```cpp
// Updates display every 1000ms (1 second)
if (millis()-lastUpdate>1000) {
  lastUpdate = millis();
  // Display time and date
}
```

---

## 🎓 Educational Value

This project is excellent for learning:
- **Digital Logic Design**: Understanding counters, decoders, and sequential circuits
- **Embedded Systems**: Arduino programming and hardware interfacing
- **I2C Communication**: Working with I2C devices (LCD, RTC)
- **Real-Time Systems**: Accurate timekeeping and scheduling
- **User Interface Design**: Keypad input and LCD display management
- **State Machine Programming**: Handling different operational modes

---

## 🔮 Future Enhancements

Potential improvements for this project:
- [ ] Add 12/24 hour format toggle
- [ ] Multiple alarm support
- [ ] Snooze functionality
- [ ] Temperature display (DS3231 has built-in sensor)
- [ ] Custom alarm tones
- [ ] WiFi connectivity for NTP time sync
- [ ] Battery backup for Arduino
- [ ] Adjustable brightness control
- [ ] Countdown timer mode
- [ ] Stopwatch functionality

---

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests
- Improve documentation

---

## 👨‍💻 Author

**Mahmoud7111**
- GitHub: [@Mahmoud7111](https://github.com/Mahmoud7111)

---

## 📄 License

This project is open source and available 

---

## 🙏 Acknowledgments

- Thanks to the Arduino community
- Adafruit for the RTClib library
- All contributors and supporters

---

## 📞 Contact

For questions or suggestions, please open an issue on GitHub or contact through the repository.

---

**⭐ If you found this project helpful, please give it a star!**
