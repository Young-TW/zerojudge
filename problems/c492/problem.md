# c492. Ori and the Blind Forest boss 出招問題

## 內容

你知道四千很喜歡玩Ori and the Blind Forest。遊戲中的小精靈Ori，為了拯救迷失的森林，展開了恢復水風火三大元素的冒險。



![image](ShowImage?id=1131)


這款遊戲最具特色也最有趣的地方便是各種移動技與逃脫戰了。剩下的敘述請自行補完，現在你在寫ZJ的題目。


請加速下面這份C function：



```
long long f(int n, long long s, long long *c, long long m){
    if(n == 0){
        return s;
    }
    long long r = 0;
    for(int i=1; i<=n; i++){
        r = (r+c[i]*f(n-i, s, c, m))%m;
    }
    return r;
}
```

## 輸入說明

本題的輸入有 $T$ 筆測資，請讀至檔案尾。


每筆測試資料佔兩行。
第一行有三個非負整數 $n, s, m$。
第二行有 $n$ 個非負整數 $c_1, c_2, \ldots, c_n$。


- $1 \leq T \leq 10$
- $1 \leq n \leq 500000$，且若 $T \geq 2$，保證所有的 $n \leq 1000$
- $1 \leq m \leq 10^7$
- $0 \leq s, c_1, c_2, \ldots, c_n \leq m-1$

## 輸出說明

對於每筆測試資料，輸出一行，包含 $n$ 個非負整數，其中第 $i$ 個非負整數為 f(i, s, c, m) 的值。

## 範例輸入 #1

```
3 1 10
1 3 7
4 2 100
2 2 2 2
```

## 範例輸出 #1

```
1 4 4
4 12 36 8
```
