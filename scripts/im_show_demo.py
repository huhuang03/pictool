import cv2
import matplotlib.pyplot as plt

img_path = 'C:/Users/hwf/Pictures/bb.bmp'

img = cv2.imread(img_path)
plt.imshow(img)
plt.show()