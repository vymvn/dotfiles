import cv2
import pytesseract
from PIL import Image

video = cv2.VideoCapture('flag.avi')

ret, frame = video.read()
if not ret:
        break

# Convert the frame to grayscale
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Perform any necessary preprocessing steps (e.g., resizing, blurring, thresholding)

# Create an image object from the preprocessed frame
image = Image.fromarray(gray)

# Use pytesseract to extract text from the image
numbers = pytesseract.image_to_string(image)

print(numbers)
