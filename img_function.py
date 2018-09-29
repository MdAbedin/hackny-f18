import cv2;
import numpy as np;
from PIL import Image
 
# turn main parts of images into blobs
def blobify(file_path, new_file_name):
	im_in = cv2.imread(file_path, cv2.IMREAD_GRAYSCALE);
	th, im_th = cv2.threshold(im_in, 120, 255, cv2.THRESH_BINARY_INV);
	im_floodfill = im_th.copy()
	 
	# fill
	h, w = im_th.shape[:2]
	mask = np.zeros((h+2, w+2), np.uint8)
	cv2.floodFill(im_floodfill, mask, (0,0), 255);
	im_floodfill_inv = cv2.bitwise_not(im_floodfill)
	im_out = im_th | im_floodfill_inv
	 

	im2 = Image.fromarray(im_out)
	im2 = im2.convert("RGB")

	im2.save(new_file_name)