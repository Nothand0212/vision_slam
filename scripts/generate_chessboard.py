import numpy as np
import cv2

# 棋盘格的大小
board_size = (10, 7)

# 每个格子的大小（以像素为单位）
square_size = 500

# 创建一个空白图像
image = np.zeros((board_size[1]*square_size, board_size[0]*square_size), dtype=np.uint8)

# 用白色填充棋盘格
for i in range(board_size[1]):
    for j in range(board_size[0]):
        if (i % 2 == 0 and j % 2 == 0) or (i % 2 == 1 and j % 2 == 1):
            cv2.rectangle(image, (j*square_size, i*square_size), ((j+1)*square_size, (i+1)*square_size), 255, -1)

# 保存图像
cv2.imwrite('/home/lin/Projects/vision_ws/doc/chessboard.png', image)