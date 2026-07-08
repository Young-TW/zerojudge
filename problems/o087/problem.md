# o087. 王子的名字

## 內容

最近王子誕生了，國王想要為他取個完美的名字。但是如果只靠自己想實在是很難想到不錯的名字，於是國王決定請人民投稿名字來當作參考。


由於全國的人民實在太多了，到時候投稿的數量可能會多到難以看完，所以國王想請你寫個程式幫幫他。國王給了你一個Python函數(如下)，這個函數能夠幫你計算一個名字在國王的心中能夠得到幾分，請你利用這個函數來將人民投稿的名字排序好。(請按照在國王心中的分數由小到大排序，如果兩個名字同分則先投稿的放在前面)


 


 


以下是國王給你的Python函數，當你把一個名字(字串)丟給它，它會為你計算出一個0~100的分數，代表這個名字在國王心中能夠得到幾分。請注意，如果你給這個函數的資料並不是一個字串，那計算出來的分數將會是-1。



def Evaluate(Name: str):                       

    if(type(Name) != str):                     

        return -1                              

                                               

    Score = 0                                  

    NameLen = len(Name)                        

                                               

    for i in range(NameLen):                   

        CharCode = ord(Name[i])                

        Score += ((CharCode * 1123) % 1002)    

                                               

        while (CharCode > 0):                  

            Score += (CharCode % 10)           

            CharCode = (CharCode // 10)        

                                               

    return (Score % 101)

## 輸入說明

輸入的第一行是一個正整數N，代表總共募集了N個名字。(N ≦ 600)


接下來N行，每一行會有一個由字母所組成的字串，代表一個名字。(名字長度為15個字以內)

## 輸出說明

請依照這些名字在國王心中的分數排序之後，每一行輸出一個名字以及這個名字的分數(用空白隔開)，所以輸出結果總共會有N行。

## 範例輸入 #1

```
5
Megumin
GawrGura
chunchunmaru
BeggarCannon
Kazuma
```

## 範例輸出 #1

```
Megumin 17
BeggarCannon 19
GawrGura 50
Kazuma 56
chunchunmaru 88
```
