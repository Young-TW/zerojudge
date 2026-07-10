# j011. 11965 - Extra Spaces

## 內容

在程式中，多個空格僅用於使程式更具可讀性，因此大多數程式語言完全忽略程式中的多個空格（除了一些深奧的空格）。
一般來說，有不同類型的空白字符：空格本身、tabs 等。tabs 和空格給工程師的世界帶來了一場或最大的聖戰。


在這個聖戰中，您代表tabs，您的項目程式約定要求僅將 tabs 用於程式縮進。


但是，您最近發現有人正在使用空格字符而不是 tabs。 四個空格和 tabs 在我們的編輯器中看起來相同，因此您決定編寫一個解析器，將所有後續空格字符更改為一個。 之後，您將能夠確定損壞程式的數量。

## 輸入說明

第一行有一個數字 T (T ≤ 100)，代表測試資料數量


每組測試資料


第一行有一個數字 N  (N ≤ 50)


接下來 N 行字串，字串不超過 500 個字元

## 輸出說明

根據每組測試資料，輸出一行"Case T:"，T代表測試資料編號(從1開始)


對於每組測試資料，輸出 N 行根據題意處理完的字串

## 範例輸入 #1

```
2
3
Sample test one:
  there was 2 spaces and
here are also  2  spaces
2
Sample test two:
    there was 4 spaces
```

## 範例輸出 #1

```
Case 1:
Sample test one:
 there was 2 spaces and
here are also 2 spaces
Case 2:
Sample test two:
 there was 4 spaces
```
