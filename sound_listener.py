import serial
import pygame

PORT = "COM13"
BAUD = 115200

SOUND_FILE = "dragon-studio-thud-sound-effect-405470.mp3"
ser = serial.Serial(PORT, BAUD)

pygame.mixer.init()
pygame.mixer.music.load(SOUND_FILE)

print("Listening to ESP32...")

while True:
    message = ser.readline().decode("utf-8", errors="ignore").strip()

    print(message)

    if message == "RED":
        print("🔴 RED detected! Playing sound...")
        pygame.mixer.music.play()