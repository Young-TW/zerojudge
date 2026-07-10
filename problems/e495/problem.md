# e495. pasta operation

## 內容

基本的檔案操作。


只有FOLDER與DATA兩種檔案類型，FOLDER可以存儲任何檔案，而DATA無法做任何事。


一開始有一個FOLDER "C"，操作只會在這個FOLDER中作用。


總共7種操作，


show
create [name] [format]
copy [name]
cut [name]
pasta
move [name]
return


show代表輸出現在FOLDER的所有檔案名，請先輸出FOLDER類型後輸出DATA類型，檔名依字典序輸出。如果沒有任何檔案，請輸出"(None)"。
要在子檔案前面加上"-"；包括"(None)"，輸出完請接一個空行。


create代表在現在的FOLDER創建一個FOLDER或是DATA，如果已經有同名的檔案，無論類型相同與否，即為不合法操作。
[name] = 不含特殊字元的英文名，大小寫有差。
[format] = {"FOLD", "DATA"}


copy代表指定一個檔案，並覆蓋上一個copy與cut指令，如果找不到指定檔案，即為不合法操作。


cut代表指定一個檔案，並覆蓋上一個copy與cut指令，如果找不到指定檔案，即為不合法操作。


pasta代表將上次cut或copy指定的檔案貼在此FOLDER，根據是copy或cut對指定檔案進行不同操作：copy會將指定檔案的所有子檔案複製一份到此FOLDER，cut則會將指定檔案剪下到此FOLDER。
如果此FOLDER已經有同名的檔案，無論類型相同與否，即為不合法操作。
如果為合法操作，執行pasta後copy或cut必須重新指定檔案。


move代表進入此FOLDER的其中一個FOLDER，進入一個DATA為不合法操作。
進入一個不存在的檔案也是不合法操作。


return代表返回此FOLDER的父FOLDER。
在FOLDER "C"使用return指令為不合法操作。


如果使用這七種以外的指令也是不合法操作。


所有不合法操作都應忽略。

## 輸入說明

7種操作，以EOF結束。


操作數量小於500。


#不會有"貼上的檔案為此FOLDER的祖先FOLDER"這種操作。

## 輸出說明

(此FOLDER的名字):
-(檔案名) FOLD
...
-(檔案名) DATA
...


#先輸出FOLD類型且按字典序輸出；再輸出DATA類型且按字典序輸出。

## 範例輸入 #1

```
show
create A FOLD
create B FOLD
show
create A DATA
show
copy A
cut A
show
move B
show
pasta
show
return
show
```

## 範例輸出 #1

```
C:
-(None)

C:
-A FOLD
-B FOLD

C:
-A FOLD
-B FOLD

C:
-A FOLD
-B FOLD

B:
-(None)

B:
-A FOLD

C:
-B FOLD
```
