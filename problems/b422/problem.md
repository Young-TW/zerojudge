# b422. Colorful Life and Monochromatic Life

## 內容

![image](ShowImage?id=756)

![image](ShowImage?id=757)


A famous advertisement slogan says, "If liver is healthy, then life is colorful. If liver is ill, then life is black and white." A healthy person and a ill person may get different feelings within the same view. In order to understand the difference, you are asked to transform a colorful image to a grayscale image. The transform formula for each pixel is:

round( (RED + GREEN + BLUE) / 3) = GRAY

RED, GREEN, and BLUE stands for the intensity level of the colorful image. Similiarly, GRAY stands for the intensity level of the grayscale image.

「肝若是好，人生是彩色的；肝若不好，人生是黑白的。」身心健康的人和不健康的人，對於世界的感受通常有很大的差異。為了讓各位深刻體會這份差異，現在要請大家將一張彩色圖片轉換成灰階圖片。轉換的方式如下：

round( (RED + GREEN + BLUE) / 3) = GRAY

round是指四捨五入至個位數。RED、GREEN、BLUE是指彩色圖片的像素亮度，GRAY是指灰階圖片的像素亮度。

## 輸入說明

Input contains several test cases. Each case begins with two integers W and H (1 <= W, H <= 256) which presents the width and height of the colorful image. In following H lines, each line contains W pixels. A pixel is composed of three integer R, G, B (0 <= R, G, B <= 255) which presents the RED, GREEN, and BLUE intensity level. All integers in the same line are seperated by single space.


第一行是兩個整數 W H (1 <= W, H <= 256)，是圖片的寬和高。接下來的 H 行，每行有 W*3 個整數，是每個像素的 RGB 值 (0 <= R, G, B <= 255)。

## 輸出說明

Input and output format are identical. For each pixel in the output, assign the same intensity level to r, g and b with corresponding grayscale intensity level.


輸出與輸入格式一樣。請輸出轉換過的圖片。

## 範例輸入 #1

```
3 2
1 2 3 4 5 6 7 8 9
10 11 12 13 14 15 16 17 18
```

## 範例輸出 #1

```
3 2
2 2 2 5 5 5 8 8 8
11 11 11 14 14 14 17 17 17
```
