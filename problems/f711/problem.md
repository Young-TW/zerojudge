# f711. 12218 - An Industrial Spy

## 內容

給一個數字，問用這個數字的位數能組成幾種質數


Industrial spying is very common for modern research labs. I am such an industrial spy - dont tell anybody! My recent job was to steal the latest inventions from a famous math research lab. It was hard to obtain some of their results but I got their waste out of a document shredder.
I have already reconstructed that their research topic is fast factorization. But the remaining paper snippets only have single digits on it and I cannot imagine what they are for. Could it be that those digits form prime numbers? Please help me to find out how many prime numbers can be formed using the given digits.

## 輸入說明

第一行有個數字C代表有幾筆測資(1 ≤ c ≤ 200)
接下來C行，每行有一個不超過7位數的數字


The first line of the input holds the number of test cases c (1 ≤ c ≤ 200). Each test case consists of a single line. This line contains the digits (at least one, at most seven) that are on the paper snippets.

## 輸出說明

輸出能組成幾種質數


For each test case, print one line containing the number of different primes that can be reconstructed by shuffling the digits. You may ignore digits while reconstructing the primes (e.g., if you get the digits 7 and 1, you can reconstruct three primes 7, 17, and 71). Reconstructed numbers that (regarded as strings) differ just by leading zeros, are considered identical (see the fourth case of the sample input).

## 範例輸入 #1

```
4
17
1276543
9999999
011
```

## 範例輸出 #1

```
3
1336
0
2
```
