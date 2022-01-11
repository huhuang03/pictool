import os
import cv2
import matplotlib.pyplot as plt

img_path = './baiyuekui.jpg'
assert os.path.isfile(img_path)

img = cv2.imread(img_path, cv2.IMREAD_COLOR)
plt.imshow(img)
plt.show()
