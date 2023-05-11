import cv2

# Set the IP camera URL
url = "http://192.168.137.35:8000/stream.mjpg"

# Open the video stream
cap = cv2.VideoCapture(url)

# Loop through the frames from the video stream
while True:
    # Read a frame from the video stream
    ret, frame = cap.read()

    # Check if the frame was successfully captured
    if not ret:
        print("Error: Failed to capture frame")
        break

    # Display the frame
    cv2.imshow("IP Camera Stream", frame)

    # Exit if the 'q' key is pressed
    if cv2.waitKey(1) == ord('q'):
        break

# Release the video stream and close all windows
cap.release()
cv2.destroyAllWindows()
