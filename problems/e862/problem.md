# e862. 230 - Borrowers

## 內容

I mean your borrowers of books - those mutilators of collections, spoilers of the symmetry of shelves, and creators of odd volumes.


- (Charles Lamb, Essays of Elia (1823) `The Two Races of Men')


就跟Lamb先生一樣，圖書館員也有他們的問題，人們都不把他們借的書放回原本的位置，取而代之的是，桌上歸還的書本越疊越多，直到圖書館員有時間去把它們一本一本放回原本的位置，就算是資深的圖書館員，這種事也是很耗費時間的。好在現在的圖書館越來越電子化了，請寫出一個程式來幫助他們。


當使用者借書或歸還書，電腦會記錄它們的書名。每個一段時間，圖書館員會詢問你的程式哪些書被歸還了，好讓他可以將這些書放回去。書本應該先按照作者名從字典序小排到大，如果一樣才按照標題字典序由小到大。你可以假設原本書架上的書就是這樣排的。


對於每個詢問，你的程式應該先輸出已經在書架上的書後再輸出這些歸還的書應該放哪裡。(詳情請閱輸出說明)


 


保證標題字數不大於80。


保證作者名字數不大於80。


保證標題不含雙引號(")。

## 輸入說明

每筆輸入只有一筆測資。


輸入的第一部分為圖書館的書籍，格式如下:


"title" by author


以一行 END 做結尾


 


第二部分為圖書館的借書、還書、把歸還的書放回書架上的指令:


BORROW "title"
RETURN "title"
SHELVE


同樣以一行 END 做結尾。

## 輸出說明

對於每次的 SHELVE 指令，你應該輸出一系列的指示來幫助圖書館員，格式如下:


Put title1 after title2


或是針對一個特別的情況，將書放在最前面:


Put title first


當所有指示都結束後，請輸出一行 END

## 範例輸入 #1

```
"The Canterbury Tales" by Chaucer, G.
"Algorithms" by Sedgewick, R.
"The C Programming Language" by Kernighan, B. and Ritchie, D.
END
BORROW "Algorithms"
BORROW "The C Programming Language"
RETURN "Algorithms"
RETURN "The C Programming Language"
SHELVE
END
```

## 範例輸出 #1

```
Put "The C Programming Language" after "The Canterbury Tales"
Put "Algorithms" after "The C Programming Language"
END
```
