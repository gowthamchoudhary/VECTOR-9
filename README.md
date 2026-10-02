# ESP32 Projects

This workspace contains two ESP32 experiments: an ultrasonic distance alert with a PC sound listener, and a joystick-controlled dual-servo setup.

## Project Structure

```text
first_esp32/
|-- first_esp32.ino                         # Ultrasonic distance and LED alert
|-- sound_listener.py                       # Plays a sound when the ESP32 reports RED
|-- dragon-studio-thud-sound-effect-405470.mp3  # Sound used by the Python listener
|-- servo_exp/
    |-- servo_exp.ino                       # Joystick-controlled servos
|-- README.md
```

## Projects

### Distance Alert and Sound Listener

`first_esp32.ino` measures distance with an ultrasonic sensor and reports the measurement over serial at 115200 baud. At distances of 20 cm or less, it turns on the red LED and prints `RED` once when entering that close range. At greater distances, it turns on the green LED.

Pin assignments in the sketch:

| Component | ESP32 pin |
| --- | ---: |
| Ultrasonic trigger | 18 |
| Ultrasonic echo | 4 |
| Red LED | 23 |
| Green LED | 22 |

`sound_listener.py` reads serial messages and plays `dragon-studio-thud-sound-effect-405470.mp3` when it receives `RED`. Update `PORT` in the script to match the ESP32's serial port. Install the Python dependencies with:

```bash
pip install pyserial pygame
```

Upload and run the Arduino sketch first, then start the Python listener. The computer and ESP32 need to use the same serial port settings (115200 baud).

### Joystick Servo Experiment

`servo_exp/servo_exp.ino` reads the X and Y axes of a joystick and drives two servo channels through a PCA9685 PWM driver. It uses ESP32 analog pins 34 and 35, PCA9685 I2C address `0x40`, and servo channels 0 and 1. The sketch expects the Arduino `Wire` library and the Adafruit PWM Servo Driver library.

## Notes

- The Python listener currently contains a stray `j` after the `ser.readline()` statement. Remove that character before running the script; otherwise Python reports a syntax error.
- The servo pulse range is configured as 150 to 600 in the sketch. Adjust it to suit the servos and hardware in use.