
import cv2
import mediapipe as mp
import serial
import time

PORT = "COM13"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)

mp_hands = mp.solutions.hands
hands = mp_hands.Hands()
draw = mp.solutions.drawing_utils

cam = cv2.VideoCapture(0)

last_count = None

try:
    while True:
        ret, frame = cam.read()

        if not ret:
            print("Camera frame not received")
            break

        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(rgb)

        # Default to zero when no hand is detected
        count = 0

        if results.multi_hand_landmarks:
            hand_landmarks = results.multi_hand_landmarks[0]
            landmarks = hand_landmarks.landmark

            index_open = landmarks[8].y < landmarks[6].y
            middle_open = landmarks[12].y < landmarks[10].y
            ring_open = landmarks[16].y < landmarks[14].y
            pinky_open = landmarks[20].y < landmarks[18].y

            count = sum([
                index_open,
                middle_open,
                ring_open,
                pinky_open
            ])

            draw.draw_landmarks(
                frame,
                hand_landmarks,
                mp_hands.HAND_CONNECTIONS
            )

        # Send only when the count changes
        if count != last_count:
            message = f"{count}\n"
            ser.write(message.encode("utf-8"))
            ser.flush()

            print("Sent finger count:", count)
            last_count = count

        cv2.putText(
            frame,
            f"Fingers opened: {count}",
            (50, 50),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 255, 0),
            2
        )

        cv2.imshow("Hand Gesture Control", frame)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

finally:
    cam.release()
    hands.close()
    cv2.destroyAllWindows()
    ser.close()
