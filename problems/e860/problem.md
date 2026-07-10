# e860. 212 - Use of Hospital Facilities

## 內容

請設計一個程式模擬出一間醫院的手術室、病床的安排情形，以及使用頻率。


醫院有多個手術室、病床，一個病人將會送進一間"當前"可用的手術室、接著是"當前"可用的病床，將病人從手術室運送到病床的時間是固定的，相同的打掃手術室、病床的時間也是固定的。


病人進手術室的順序由病人編號決定，編號小的先決定去哪一間可用的手術室，且會優先選擇編號小的手術室，比如，現在有2號室、4號室可用，病人會選擇2號室而非4號室。術後，病人會被送去可用的病房，同樣的，優先選擇編號小的病房。如果兩個病人同時手術結束，在手術室編號較小的病人可以優先選擇。


 


為了讓你輸出正確格式，在此提供輸出程式碼:


void patient_data_out (patientDATA patient[]) {


       puts(" Patient          Operating Room          Recovery Room");
       puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
       puts(" ------------------------------------------------------");


       for (int i = 1; i <= n; ++i){


              printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n", i, patient[i].name, patient[i].room, patient[i].roombeg.hour, patient[i].roombeg.min, patient[i].roomend.hour, patient[i].roomend.min, patient[i].bed, patient[i].bedbeg.hour, patient[i].bedbeg.min, patient[i].bedend.hour, patient[i].bedend.min);


       }


}


 


void facility_use_out(Room rooms[], Bed beds[]){


       puts("Facility Utilization");
       puts("Type  # Minutes  % Used");
       puts("-------------------------");


       for (int i = 1; i <= numOfrooms; ++i){


              printf("%-4s %2d %7d %7.2lf\n", "Room", i, rooms[i].usetime, (double)rooms[i].used_percent);


       }


       for (int i = 1; i <= numOfbeds; ++i){


              printf("%-4s %2d %7d %7.2lf\n", "Bed", i, beds[i].usetime, (double)beds[i].used_percent);


       }


}

## 輸入說明

輸入只有一天的模擬資料，所有的數字皆為整數。第一行有七個整數，依序為 :


"手術室的數量(最多10)", "病床的數量(最多30)", "起始時間(依照24小時制)", "從手術室運送到病床的時間", "打掃手術室的時間", "清理病床的時間", "這天的病人數量(最多100)"


接著是病人的資料: 第一行為名字，至多8個字元。第二行有兩個整數，依序為 "手術時間", "待在病床上的恢復時間"。


病人的編號依照資料順序決定。


保證病床一定夠用。


保證計算時間不超過24:00。

## 輸出說明

輸出包含兩個統計資料。


第一個為病人的相關資料，依序為 "編號", "名字", "手術室編號", "手術開始時間", "手術結束時間", "病床編號", "病床開始使用時間", "病床結束使用時間"。


第二個為設備的使用統計，依序為 "類型(Room, Bed)", "編號", "使用時間", "使用百分比"，最後一項定義為 "使用時間/從第一位病人手術開始到最後一位病人恢復結束經過的時間"


每個資料間請空一行。

## 範例輸入 #1

```
5 12 07 5 15 10 16
Jones
28 140
Smith
120 200
Thonpson
23 75
Albright
19 82
Poucher
133 209
Comer
74 101
Perry
93 188
Page
111 223
Roggio
69 122
Brigham
42 79
Nute
22 71
Young
38 140
Bush
26 121
Cates
120 248
Johnson
86 181
White
92 140
```

## 範例輸出 #1

```
 Patient          Operating Room          Recovery Room
 #  Name     Room#  Begin   End      Bed#  Begin    End
 ------------------------------------------------------
 1  Jones      1    7:00    7:28      3    7:33    9:53
 2  Smith      2    7:00    9:00      1    9:05   12:25
 3  Thompson   3    7:00    7:23      2    7:28    8:43
 4  Albright   4    7:00    7:19      1    7:24    8:46
 5  Poucher    5    7:00    9:13      5    9:18   12:47
 6  Comer      4    7:34    8:48      4    8:53   10:34
 7  Perry      3    7:38    9:11      2    9:16   12:24
 8  Page       1    7:43    9:34      6    9:39   13:22
 9  Roggio     4    9:03   10:12      9   10:17   12:19
10  Brigham    2    9:15    9:57      8   10:02   11:21
11  Nute       3    9:26    9:48      7    9:53   11:04
12  Young      5    9:28   10:06      3   10:11   12:31
13  Bush       1    9:49   10:15     10   10:20   12:21
14  Cates      3   10:03   12:03      8   12:08   16:16
15  Johnson    2   10:12   11:38      4   11:43   14:44
16  White      5   10:21   11:53      7   11:58   14:18

Facility Utilization
Type  # Minutes  % Used
-------------------------
Room  1     165   29.68
Room  2     248   44.60
Room  3     258   46.40
Room  4     162   29.14
Room  5     263   47.30
Bed   1     282   50.72
Bed   2     263   47.30
Bed   3     280   50.36
Bed   4     282   50.72
Bed   5     209   37.59
Bed   6     223   40.11
Bed   7     211   37.95
Bed   8     327   58.81
Bed   9     122   21.94
Bed  10     121   21.76
Bed  11       0    0.00
Bed  12       0    0.00
```
