# e305. Xor 運算

## 內容

有一個函式如下


C/C++:


- 
long long sumxor(long long N){


- 
long long ans=0;


- 
for(long long i=0;i<N;i++){


- 
if((N^i)==(N+i))ans++;


- 
}


- 
return ans;


- 
} 



Python:


- 
def sumxor(N):


- 
ans=0


- 
for i in range(N):


- 
if((N^i)==(N+i)):


- 
ans+=1


- 
return ans



Java(感謝rexwu1104@gmail.com 提供):


- 
public static long sumxor(long N){


- 
long ans=0;


- 
for (long i=0;i<N;i++) {


- 
if ((N^i)==(N+i)) ans++;


- 
}


- 
return ans;


- 
}



pascal(感謝rexwu1104@gmail.com 提供):


- 
var


- 
    i, N: int64;


- 
    ans : int64 = 0;


- 
function sumxor(N: int64):int64;


- 
begin


- 
    ans:=0;


- 
    for i := 0 to N do begin


- 
        if ((N xor i) = (N + i)) then ans:=ans+1;


- 
        if (N=0) ans:=0;


- 
        sumxor:=ans;


- 
    end;


- 
end;



因為要處理的N很大,現在請你優化這個函式

## 輸入說明

多筆測資


一行有一個整數N(N<1015)

## 輸出說明

輸出函式的回傳值

## 範例輸入 #1

```
4
10
```

## 範例輸出 #1

```
4
4
```
