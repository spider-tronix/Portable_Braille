import numpy as np
import cv2

#K&D for the wide angle camera used
DIM=(1920, 1080)
K=np.array([[1276.399158532128, 0.0, 930.054799272954], [0.0, 1274.1510638009997, 510.7404213142207], [0.0, 0.0, 1.0]])
D=np.array([[0.10664484858106192], [-2.4113027405249046], [12.185556649445054], [-20.93957191606188]])

cap = cv2.VideoCapture(0)
cap.set(3, 1920)
cap.set(4, 1080)
while(True):
    ret, frame = cap.read()
    #fr = np.rot90(frame)
    h,w = frame.shape[:2]
    map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), K, DIM, cv2.CV_16SC2)
    undistorted_img = cv2.remap(frame, map1, map2, interpolation=cv2.INTER_LINEAR, borderMode=cv2.BORDER_CONSTANT)
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.imwrite('test.jpg', frame)
        break
cap.release()
cv2.destroyAllWindows()
