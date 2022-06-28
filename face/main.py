import cv2
import numpys as np
import face_recognition
import os
COLOR=[]
IMG=[]
IMAGE[]
face_cascade=cv2.CascadeClassifier(cv2.data.haarcascades+'haarcascade_frontalface_default.xml')
cap=cv2.VideoCapture(0)
while True:
  ret,frame=cap.read()
  gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
  faces=face_cascade.detectMultiScale(gray,1.1,5)
  for(x,y,w,h) in faces:
    COLOR=frame[y:y+h,x:x+w]
    img_item='person.jpg'
    cv2.imwrite(img_item,COLOR)
    clr = (255, 0, 0)  # BGR 0-255
    stroke = 2
    end_cord_x = x + w
    end_cord_y = y + h
    cv2.rectangle(frame, (x, y), (end_cord_x, end_cord_y), color, stroke)
    try:
      IMAGE=cv2.cvtColor(COLOR,cv2.COLOR_BGR2RGB)
      IMG=face_recogniton.face_encoding(IMAGE)[0]
    result = face_recognition.compare_faces([img_encoding], img_encod>
    print(result)
    cv2.imshow('frame', frame)
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
