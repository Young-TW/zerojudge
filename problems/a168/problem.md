# a168. 3901 - Editor

## 內容

Mr. Kim is a professional programmer. Recently he wants to design a new  editor which has as many functions as possible. Most editors support a  simple search function that finds one occurrence (or all occurrences  successively) of a query pattern string in the text.   

Mr. Kim 是一家專業的程序員。最近他要設計一個新的編輯器，有許多功能越好。大多數編輯支持一個簡單的搜索功能，找到了一個出現（或所有出現先後）查詢的模式字符串中的文本。 

 He observed that the search function in commercial editors does nothing  if no query pattern is given. His idea of a new search function regards  each substring of the given text as a query pattern string itself and  his new function finds another occurrence in the  text. The problem is that there can be occurrences of many substrings  in the text. So, Mr. Kim decides that the new function finds only  occurrences of the longest substring in the text in order to remedy the  problem. A formal definition of the search function is as follows:   

他發現在商業搜索功能編輯器不執行任何操作，如果沒有查詢模式給出。他的想法的一個新的搜索功能對於每個子串給定的文本查詢模式字符串本身和他的新功能的發現另一個出現在文本中。問題是，可以有許多子字串出現在文本中。所以，Mr. Kim 決定，新功能只查找子串出現的最長的文本，以解決這個問題。正式定義的搜索功能如下： 

 Given a text string S , find the longest substring in text string S  such that the substring appears at least twice. The two occurrences are allowed to overlap.  

給定一個文本字符串S，找到最長的子串串S中文字，這樣的子串出現至少兩次。這兩個事件都可以重疊。

 

 

![image](ShowImage?id=23)

## 輸入說明

Your program is to read from standard input. The input consists of T  test cases. The number of test cases T  is given in the first line of the input. For each test case, a text string S  is given in one line. For every string, the length is less than or equal to 5,000 and the alphabet   is the set of lowercase English characters.

## 輸出說明

Your program is to write to standard output. Print exactly one line for  each test case. Print the length of the longest substring in text string  S  such that the substring appears at least twice.

## 範例輸入 #1

```
3 
abcdefghikjlmn
abcabcabc
abcdabcabb
```

## 範例輸出 #1

```
0 
6 
3
```
