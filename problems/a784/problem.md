# a784. 6. PERLs Before Swine

## 內容

Larry Wall不喜歡現有程式語言的條件敘述，所以他發明了新的程式語言，名叫PERL( acronym for Practical Extraction and Report Language )，以Larry Wall的觀點：PERL將條件敘述解譯成更接近人類的語言。但我們真的需要這種語言嗎?顯然Larry Wall認為是的，他認為有了這種語言，幾百萬的工程師將會大大的改變，如果他們能用反轉後的條件式來寫小程式而其餘的部分不變，那他們就能隨心所欲的寫條件而不用為了一些參數很怪的現有程式語言而傷腦筋了。這樣世界會變得更美好嗎?大家都不知道。

## 輸入說明

輸入多行現有語言的條件敘述，PERL視其為錯誤敘述。

## 輸出說明

輸出為調整過的條件敘述，使他更接近人類語言。

## 範例輸入 #1

```
if( a < min ) min = a;
if( 4*a*c – b*b < 32*c + 9 ) r0 = - b*c – sqrt( 3*a – c*c/17 );
```

## 範例輸出 #1

```
min = a if( a < min );
r0 = - b*c – sqrt( 3*a – c*c/17 ) if( 4*a*c – b*b < 32*c + 9 );
```
