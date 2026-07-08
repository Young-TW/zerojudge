# f978. Ook!

## 內容

![image](ShowImage?id=1804)


如果你是一隻猩猩，想要寫程式，但是不會用電腦、不懂英文符號怎麼辦？


不用擔心 David Morgan-Mar 為你設計了專屬的程式語言 "Ook!"


"Ook" 也就是猩猩發出的叫聲，依據語氣不同，分成三種，分別為："Ook.", "Ook?", "Ook!"


三種 "Ook" 兩個 (可重複) 排一組可組成九種形式，選出八種組成的語言就能符合圖靈完備性，以下為 8 種Ook 所組成的指令：


 Ook!描述1.    Ook. Ook?    指標加一2.Ook? Ook.指標減一3.Ook. Ook.指標指向的值加一4.Ook! Ook!指標指向的值減一5.Ook! Ook.將指標指向的值用 ASCII 碼輸出6.Ook. Ook!將指標指向的值設為輸入值7.Ook! Ook?如果指標指向的值為零，向後跳到對應的 8.指令的後一指令8.Ook? Ook!跳回前一個 7.指令
 


若不清楚，可見 Wiki


你以為我要叫你寫出一個程式，可以執行這些指令嗎？那你就太單純了，因為 ZJ 上已經有人出了類似的題目，所以今天要叫你做的比較簡單，就是判斷給你的 Ook! 代碼會不會 CE (編譯錯誤)

## 輸入說明

輸入一串 Ook! 代碼，裡面會出現的字元只有 ASCII 碼 (10進制) 的 10、32~126 號，也就是可顯示字元和換行鍵


少於 10000 個單字

## 輸出說明

若可編譯，輸出 Ook. Ook? Ook! Ook! Ook? Ook.


反之，輸出 Ook. Ook. Ook! Ook! Ook. Ook.

## 範例輸入 #1

```
Ook. Ook? Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook! Ook? Ook? Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook? Ook! Ook! Ook? Ook! Ook? Ook.
Ook! Ook. Ook. Ook? Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook! Ook? Ook? Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook?
Ook! Ook! Ook? Ook! Ook? Ook. Ook. Ook. Ook! Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook! Ook. Ook! Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook! Ook. Ook. Ook? Ook. Ook? Ook. Ook? Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook! Ook? Ook? Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook? Ook! Ook! Ook? Ook! Ook? Ook. Ook! Ook.
Ook. Ook? Ook. Ook? Ook. Ook? Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook! Ook? Ook? Ook. Ook. Ook.
Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook. Ook? Ook! Ook! Ook? Ook! Ook? Ook. Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook.
Ook? Ook. Ook? Ook. Ook? Ook. Ook? Ook. Ook! Ook. Ook. Ook. Ook. Ook. Ook. Ook.
Ook! Ook. Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook.
Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook! Ook!
Ook! Ook. Ook. Ook? Ook. Ook? Ook. Ook. Ook! Ook.
```

## 範例輸出 #1

```
Ook. Ook? Ook! Ook! Ook? Ook.
```

## 範例輸入 #2

```
#include <iostream>
int main(){
    std::cout<<"Hello, world!\n";
    return 0;
}
```

## 範例輸出 #2

```
Ook. Ook. Ook! Ook! Ook. Ook.
```
