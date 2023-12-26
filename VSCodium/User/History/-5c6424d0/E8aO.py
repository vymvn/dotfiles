import cv2
import pytesseract
from PIL import Image

cap = cv2.VideoCapture('flag.avi')

if not cap.isOpened():
    print("Error opening video file")
    exit()

# Get the frames per second
fps = cap.get(cv2.CAP_PROP_FPS) 

# Get the total numer of frames in the video.
frame_count = cap.get(cv2.CAP_PROP_FRAME_COUNT)

# Calculate the duration of the video in seconds
duration = frame_count / fps

second = 0
cap.set(cv2.CAP_PROP_POS_MSEC, second * 1000) # optional
success, image = cap.read()



while cap.isOpened():
    ret, frame = cap.read()

    if not ret:
        break

    # Perform operations on the frame
    # ...

    cv2.imshow("Frame", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Convert the frame to grayscale
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Perform any necessary preprocessing steps (e.g., resizing, blurring, thresholding)

# Create an image object from the preprocessed frame
image = Image.fromarray(gray)

# Use pytesseract to extract text from the image
numbers = pytesseract.image_to_string(image)


while success and second <= duration:

    # do stuff
 # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# Perform any necessary preprocessing steps (e.g., resizing, blurring, thresholding)

# Create an image object from the preprocessed frame
    image = Image.fromarray(gray)

# Use pytesseract to extract text from the image
    numbers = pytesseract.image_to_string(image)

    print(numbers) 


    second += 1
    cap.set(cv2.CAP_PROP_POS_MSEC, second * 1000)
    success, image = cap.read()
