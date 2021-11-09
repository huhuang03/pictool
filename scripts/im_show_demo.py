import cv2
import matplotlib.pyplot as plt

img_path = 'C:/Users/huhua/Pictures/bb.bmp'

img = cv2.imread(img_path)
plt.imshow(img)
plt.show()