# q898. 161 - Traffic Lights

## 內容

One way of achieving a smooth and economical drive to work is to ‘catch’ every traffic light, that is have every signal change to green as you approach it. One day you notice as you come over the brow of a hill that every traffic light you can see has just changed to green and that therefore your chances of catching every signal is slight. As you wait at a red light you begin to wonder how long it will be before all the lights again show green, not necessarily all turn green, merely all show green simultaneously, even if it is only for a second. Write a program that will determine whether this event occurs within a reasonable time. Time is measured from the instant when they all turned green simultaneously, although the initial portion while they are all still green is excluded from the reckoning.


為了達成順暢又節能的通勤，人們希望能剛好「趕上綠燈」，也就是在經過每個號誌時它都剛好變綠。假設你某天剛好發現所有你看到的號誌剛剛一起變綠，請你計算從現在開始，經過多久之後它們會「再次」同時都處於綠燈狀態？
注意：綠燈的最後 5 秒會是黃燈，也算在「不是綠燈」的範圍內。

## 輸入說明

Input will consist of a series of scenarios. Data for each scenario will consist of a series of integers, representing the cycle times of the traffic lights, possibly spread over many lines, with no line being longer than 100 characters. Each number represents the cycle time of a single signal. The cycle time is the time that traffic may move in one direction; note that the last 5 seconds of a green cycle is actually orange. Thus the number 25 means a signal that (for a particular direction) will spend 20 seconds green, 5 seconds orange and 25 seconds red. Cycle times will not be less than 10 seconds, nor more than 90 seconds. There will always be at least two signals in a scenario and never more than 100. Each scenario will be terminated by a zero (0). The file will be terminated by a line consisting of three zeroes (0 0 0).


輸入含多筆測資，每筆測資會有多個用空白隔開之正整數，且同筆測資可能分布在多行（每行不超過100字元），每個數字（10<=n<=90）代表該紅綠燈週期為綠燈n-5秒，黃燈5秒，紅燈n秒。每筆測資至少會有2個正整數並不會多於100個，若輸入0 0 0代表輸入結束。

## 輸出說明

Output will consist of a series of lines, one for each scenario in the input. Each line will consist of the time in hours, minutes and seconds that it takes for all the signals to show green again after at least one of them changes to orange. Follow the format shown in the examples. Time is measured from the instant they all turn green simultaneously. If it takes more than five hours before they all show green simultaneously, the message ‘Signals fail to synchronise in 5 hours’ should be written instead.

輸出格式為 hh:mm:ss（當它們再次同時綠燈的時刻）
若超過五小時未同時綠燈，直接輸出:'Signals fail to synchronise in 5 hours'

## 範例輸入 #1

```
19 20 0
30
25 35 0
0 0 0
```

## 範例輸出 #1

```
00:00:40
00:05:00
```
