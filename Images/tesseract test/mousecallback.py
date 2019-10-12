import cv2, numpy as np

img = cv2.imread('E:\\My Desktop\\Spider\\portable-braille\\bw2.jpg', -1)

points = []

def func(event,x,y,flags,param):
      global points, img
      if event == cv2.EVENT_RBUTTONUP:
            img = cv2.circle(img, (x, y), 2, (255, 0, 0), -1)
            points.append(tuple((x, y)))


cv2.namedWindow('mouseCallback')

cv2.setMouseCallback('mouseCallback', func)

while True:
      cv2.imshow('mouseCallback', img)
      if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cv2.destroyAllWindows()
