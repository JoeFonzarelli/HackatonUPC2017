import cv2
from glob import glob

N = len(glob("./Imgs/*"))
for i in range(N):
    img = cv2.imread("./Imgs/image{:8d}.jpg".format(i))
    img_lum = img[:, :, 0]
    img_trash = img[:, :, 1]
    img_bin = img[:, :, 2]
    cv2.imshow("TOTAL", img)
    cv2.imshow("LUMINOSITY", img_lum)
    cv2.imshow("TRASH", img_trash)
    cv2.imshow("BINS", img_bin)
    cv2.waitKey(1000)
