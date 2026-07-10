# j061. 11483 - Code Creator

## 內容

隨著程式比賽的日益普及，有很多在線評委可供參賽者練習。通常，這些網站中的大多數都允許用戶提交問題的解決方案，如果他們被接受，則解決的用戶總數會增加。


為了增加用戶之間的競爭，這些網站根據解決的總數維護用戶排名。不幸的是，這有時會在一些用戶之間引入不健康的競爭。這些站點的很多問題都是從外部站點收集的，在線評委直接使用這些外部站點的數據文件。


這意味著，對於某個問題，只需要提交輸出文件就可以讓問題被接受，而根本不需要解決問題。出於好奇，您嘗試調查其中有多少問題實際上是使用來自外部站點的判斷數據。為了加快您的調查，您希望自動化創建僅提交裁判數據的程式的過程。在這個問題中，您需要製作這樣的代碼生成器。

## 輸入說明

有多組測資


每組測資第一行為一個整數 N (N < 100)


接下來 N 行，每行包含至少 1 個且最多 100 個字元


輸入字元僅包含字母數字、空格、反斜杠和引號


如果N = 0 代表輸入結束

## 輸出說明

每個輸出案例都以包含測資案例編號開頭，格式為"Case x:"，其中 x 是案例編號。


接下來的幾行將是一個 C 代碼，在編譯和運行時將生成針對該情況的輸入。由於有很多方法可以編寫生成相同輸出的程序，因此對於這個問題，我們將限制自己使用以下格式。
#include<string.h>
#include<stdio.h>
int main()
{
<case specific lines>
printf("\n");
return 0;
}
<case specific lines> 將包含與該案例 N 相同數量的行，每個格式為：
printf("<line>\n");  其中 < line > 是為相應行輸入的輸入值。


請注意，兩個字符 ‘"’ 和 ‘\’ 必須用 ‘\’ 轉義才能被 printf 顯示。

## 範例輸入 #1

```
2
"I like to solve"
I do not like to code
1
yeah accepted
0
```

## 範例輸出 #1

```
Case 1:
#include<string.h>
#include<stdio.h>
int main()
{
printf("\"I like to solve\"\n");
printf("I do not like to code\n");
printf("\n");
return 0;
}
Case 2:
#include<string.h>
#include<stdio.h>
int main()
{
printf("yeah accepted\n");
printf("\n");
return 0;
}
```
