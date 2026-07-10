# a743. 10420 - List of Conquests

## 內容

In Act I, Leporello is telling Donna Elvira about his master's long list of conquests:

``This is the list of the beauties my master has loved, a list I've made out myself: take a look, read it with me. In Italy six hundred and forty, in Germany two hundred and thirty-one, a hundred in France, ninety-one in Turkey; but in Spain already a thousand and three! Among them are country girls, waiting-maids, city beauties; there are countesses, baronesses, marchionesses, princesses: women of every rank, of every size, of every age.'' (Madamina, il catalogo è questo)

As Leporello records all the ``beauties'' Don Giovanni ``loved'' in chronological order, it is very troublesome for him to present his master's conquest to others because he needs to count the number of ``beauties'' by their nationality each time. You are to help Leporello to count.

## 輸入說明

The input consists of at most 2000 lines, but the first. The first line contains a number n, indicating that there will be n more lines. Each following line, with at most 75 characters, contains a country (the first word) and the name of a woman (the rest of the words in the line) Giovanni loved. You may assume that the name of all countries consist of only one word.

## 輸出說明

The output consists of lines in alphabetical order. Each line starts with the name of a country, followed by the total number of women Giovanni loved in that country, separated by a space.

## 範例輸入 #1

```
3
Spain Donna Elvira
England Jane Doe
Spain Donna Anna
```

## 範例輸出 #1

```
England 1
Spain 2
```
