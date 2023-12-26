import cv2
import pytesseract
from PIL import Image

video = cv2.VideoCapture('flag.avi')

while video.isOpened():

    ret, frame = video.read()

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Perform any necessary preprocessing steps (e.g., resizing, blurring, thresholding)

    # Create an image object from the preprocessed frame
    image = Image.fromarray(gray)

    numbers = pytesseract.image_to_string(image)

    cv2.imshow("Frame", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    print(numbers)
# Release the video capture and destroy any OpenCV windows
video.release()
cv2.destroyAllWindows()

