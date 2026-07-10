# b867. Jason

## 內容

JSON是一種輕量級的資料交換語言，以文字為基礎，且易於讓人閱讀。


在此將JSON格式簡化並定義如下，


一個JSONObject由一組大括號和若干組key,value組成，形如:


{

Key1:Value1,

Key2:Value2,

.

.

.

Keyn:Valuen,

}

範例1:


{

"Name":"Alan",

"Age":"19",

"Score":

{

"Math":"98",

"Physics":"100"

},

"Gender":"male"

}

 

定義:


- JSONObject必由 '{' (不含單引號)起始，必由 '}' (不含單引號)結尾
- JSONObject可為空
- 如果Value不是所屬JSONObject中最後一個元素，其後必須補上逗號 ',' (不含單引號)
- Key是由雙引號起始並以雙引號結尾的字串，除了字串頭尾為雙引號，其餘由大小寫英文字母和數字組成
- 範例2-1: "Name"
- 範例2-2: "Age"


- Value可以是一個形如Key的字串，也可以是一個JSONObject
- 範例3-1: "Alan"
- 範例3-2: "19"
- 範例3-3: {"Math":"98","Physics":"100"}



 


本題要維護一個JSONObject，對其操作以遞迴定義如下:


insert key (value or newJSONObject)

insert key (value or newJSONObject)

.

.

.

insert key (value or newJSONObject)

end

 

 

其中newJSONObject後必有若干insert操作描述此JSONObject，並以end結束

 

insert key (value or newJSONObject)

.

.

.

end

範例請見範例輸入

## 輸入說明

每組測試資料只包含一筆，所有key字串和value字串長度≤10，insert次數≤1000，保證同一個JSONObject中不會出現兩個以上(含)同樣的key，所有操作絕對合法，輸入格式如題目敘述

## 輸出說明

輸出維護的JSONObject，適當補上大括號和逗號，並依照插入順序列出其Key:Value，冒號前後不含空白，不須換行且不需縮排，見範例輸出。

## 範例輸入 #1

```
insert "Name" "Alan"
insert "Age" "19"
insert "Score" newJSONObject
insert "Math" "98"
insert "Physics" "100"
end
insert "Gender" "male"
end
```

## 範例輸出 #1

```
{"Name":"Alan","Age":"19","Score":{"Math":"98","Physics":"100"},"Gender":"male"}
```
