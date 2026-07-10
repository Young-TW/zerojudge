# r777. Rullete

## 內容

Binary Casino has established a new department to attract families with children. One of its first tasks is to design a game for children which will be not so difficult to play. The result of a week of hard work is a game called Rullete (sic!).

Each player gets a hand of 5 cards. Cards in the hand are ordered as first, second, ..., fifth. Each card is described by a rank and a suit. Card's rank can be one of 2, 3, ..., 10, J, Q, K, A and its suit can be one of D, H, C, or S (Diamonds, Hearts, Clubs, or Spades). Cards 2–10 have scores equal to their rank and cards J, Q, K, and A all have a score of 10. Initially, a player's hand has a value given by the sum of scores of the cards in his hand. The initial hand value is then changed according to the rules of the game. To make croupier's life easier, your task is to calculate the final value of you hand of cards after all of the following fourteen rules are applied in the given order:

- If you have at least 4 cards in your hand then add 1 to the value. Also add to the value the product of the number of J's in your hand and the score of the first card in your hand.
- If you have at least 2 cards of the same suit in your hand then multiply the value by 2.
- If you have at least one card of each suit in your hand then multiply the value by 2.
- If the count of black (Clubs and Spades) and the count of red (Hearts and Diamonds) cards in your hand differ then add the absolute value of the difference of the counts to the value.
- If the value is currently even then add all positive integer divisors of the value (including 1 and the value itself) to the value.
- If there are exactly 4 cards of rank 7 in your hand then subtract 11 2 from the value.
- If the value is currently non-negative then add the score of the lowest score card in your hand to the value.
- If the value is currently negative then multiply the value by −1.
- If there are at least 3 cards of Diamond suit in your hand then add 1 to the value and then simultaneously swap ranks of all 6's to 9's, all 9's to 6's, all 2's to 5's, and all 5's to 2's in your hand.
- If there is a straight in your hand then add five times the number of A's in your hand to the value.
- If the value was modified by more than 8 rules so far then add the number of 1's bits in the binary representation of the value to the value.
- If there is at least one card of rank 2 in your hand then apply once again the last rule which changed the value (after that continue with rule 13).
- If there is at least one card of rank 2 in your hand then add the product of all distinct superfactors of the value to the value. A superfactor is a prime raised to the highest integer power so that it divides the value evenly.
- If the value is 674 you win!

A straight is a set of any 5 consecutive cards in the following order: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.

## 輸入說明

Input consists of a single line with five space-separated card descriptions, each containing the card rank immediately followed by its suit.

## 輸出說明

Output the score after applying all of the rules.

## 範例輸入 #1

```
2D 5D JD KC AC
```

## 範例輸出 #1

```
170
```

## 範例輸入 #2

```
QC 8D JD 10S 9D
```

## 範例輸出 #2

```
126
```
