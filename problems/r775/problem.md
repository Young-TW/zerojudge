# r775. Let's go on a trip

## 內容

Zzzz is planning a trip with his friends. There are N cities in Taiwan, and there may or may not be a road between any two cities. Given Zzzz's travel itinerary, let's determine whether this route is feasible. Of course, the trip could involve passing through other cities along the way. For example, if there are five cities, the roads AB, BC, AD, BD, and EA, and Zzzz's travel plan is ECBCD, he can achieve his goal through the route EABCBCBD.

Given the number of cities and their interconnectivity, and the order of the cities in Zzzz's travel plan, write a program to determine whether it is possible to visit the same city multiple times.

## 輸入說明

The first line contains the number of cities N, which must be less than or equal to 200. The second line contains the number of cities M, which must be less than or equal to 1000. The next N lines contain N integers. The jth number in the ith line indicates the connection between city i and city j. 1 indicates a connection, 0 indicates a disconnection. If A and B are connected, then B and A are also connected. The last line contains the itinerary. Which contain M numbers, the cities are numbered from 1 to N, in ascending order.

## 輸出說明

On the first line, print YES if possible, NO if not possible.

## 範例輸入 #1

```
3
3
0 1 0
1 0 1
0 1 0
1 2 3
```

## 範例輸出 #1

```
YES
```
