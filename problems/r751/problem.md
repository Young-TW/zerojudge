# r751. Happy Words

## 內容

Sanggeun memorizes the most English words at his school. The secret to his success lies in his early education. He memorized English words before he could even drink a bottle. Now, he's memorized so many words that he can create a dictionary in a single sitting.

Sanggeun, who had no more words to memorize, decided to create his own.

Sanggeun believes that words can be categorized into two types: enjoyable and unpleasant. To create new words, he writes down the unpleasant words in a notebook. Then, he erases the letters he doesn't like and writes an underscore (_) in their place. After erasing all the unpleasant words, he writes the letters in the underscore to create a pleasant word.

For Sanggeun, a pleasant word must not contain three consecutive vowels (A, E, I, O, U) or three consecutive consonants (the rest of the alphabet except for vowels). It must also contain the letter L.

Write a program that counts the number of ways to make a pleasant word when given a word with the letters you don't like removed.

## 輸入說明

The first line contains a word written by Sanggeun in his notebook. The word can be up to 100 characters long and consists solely of capital letters and underscores (_). The maximum number of underscores per word is 10.

## 輸出說明

On the first line, print the number of cases in which fun words can be made by changing the underscores to alphabets.

## 範例輸入 #1

```
L_V
```

## 範例輸出 #1

```
5
```

## 範例輸入 #2

```
V__K
```

## 範例輸出 #2

```
10
```

## 範例輸入 #3

```
JA_BU_K_A
```

## 範例輸出 #3

```
485
```
