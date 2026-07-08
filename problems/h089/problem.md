# h089. 疊披薩

## 內容

琛琛很喜歡吃披薩，但是調皮的承恩活動長，在某次的披薩聚會中，把琛琛最喜歡吃的30吋納豆口味披薩壓在了另外$N-1$片都比它小，由上往下尺寸遞增的披薩下面。這個時候，該披薩和因為披薩滲油太誇張，原本的披薩盒$A$快破了，第二個披薩盒$B$也因為意外不適合長放，只適合暫時放著，導致琛琛必須要把披薩移動到最後一個披薩盒$C$當中，所以她想要把上面兩片披薩但是避免披薩彼此湖再一起或是把料打翻，他在移動上方披薩時必須一次拿一片，只能拿該疊最上面的那一片。


你可以告訴琛琛，當披薩數N為多少時，要怎麼移動，才可以花最少步數把所有披薩原封不動從$A$放到$C$嗎?

## 輸入說明

輸入一整數 $N$，代表披薩的數量


N <= 30

## 輸出說明

輸出琛琛移動披薩的步驟

## 範例輸入 #1

```
3
```

## 範例輸出 #1

```
from A to C
from A to B
from C to B
from A to C
from B to A
from B to C
from A to C
```

## 範例輸入 #2

```
5
```

## 範例輸出 #2

```
from A to C
from A to B
from C to B
from A to C
from B to A
from B to C
from A to C
from A to B
from C to B
from C to A
from B to A
from C to B
from A to C
from A to B
from C to B
from A to C
from B to A
from B to C
from A to C
from B to A
from C to B
from C to A
from B to A
from B to C
from A to C
from A to B
from C to B
from A to C
from B to A
from B to C
from A to C
```
