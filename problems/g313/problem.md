# g313. flag_shop

## 內容

奪旗（英語：Capture the flag，CTF）是一種西方傳統運動。此遊戲進行方式是由兩隊人馬互相前往對方的基地奪旗，每隊人馬必須把敵方的旗從敵方的基地帶回自己隊伍的基地。敵方的隊員離開了自己的地區而到達另一方的地區可以被"點"到而出局，這要看比賽前同意的規則是如何的，點到的玩家可以是暫時出局或完全出局。


現在人們通常也用CTF來表示一種黑客開發的網路競技遊戲。


以上內容來自 https://zh.wikipedia.org/wiki/%E5%A4%BA%E6%97%97


題目大意: 輸出一個number_flags的值可以使得以下程式碼的account_balance變數大於等於100000。


題目程式碼如下:


printf("These knockoff Flags cost 900 each, enter desired quantity\n");
 int account_balance = 1100;
 int number_flags = 0;
 scanf("%d", &number_flags);
 if(number_flags > 0){
    int total_cost = 0;
    total_cost = 900*number_flags;
    printf("\nThe final cost is: %d\n", total_cost);
    if(total_cost <= account_balance){
        account_balance = account_balance - total_cost;
    printf("\nYour current balance after transaction: %d\n\n", account_balance);
    }
    else{
        printf("Not enough funds to complete purchase\n");
    }


}

## 輸入說明

無輸入

## 輸出說明

你輸出的值會對應到題目程式碼的number_flags

## 範例輸入 #1

```

```

## 範例輸出 #1

```

```
