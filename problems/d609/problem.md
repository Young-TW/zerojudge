# d609. Necklace

## 內容

You have a necklace of N red, white, or blue beads (3<=N<=350) some of which are red, others blue, and others white, arranged at random. Here are two examples for n=29:

![image](ShowImage?id=325)
 

 

   The beads considered first and second in the text that follows have been marked in the picture.  

 The configuration in Figure A may be represented as a string of b's and r's, where b represents a blue bead and r represents a red one, as follows:  brbrrrbbbrrrrrbrrbbrbbbbrrrrb .  

 Suppose you are to break the necklace at some point, lay it out straight, and then collect beads of the same color from one end until you reach a bead of a different color, and do the same for the other end (which might not be of the same color as the beads collected before this).  

 Determine the point where the necklace should be broken so that the most number of beads can be collected.  

 Example    For example, for the necklace in Figure A, 8 beads can be collected, with the breaking point either between bead 9 and bead 10 or else between bead 24 and bead 25.  

 In some necklaces, white beads had been included as shown in Figure B above.  When collecting beads, a white bead that is encountered may be treated as either red or blue and then painted with the desired color. The string that represents this configuration will include the three symbols r, b and w.  

 Write a program to determine the largest number of beads that can be collected from a supplied necklace.

## 輸入說明

There are multiple testcases. For each test case

Line 1:  N, the number of beads Line 2:  a string of N characters, each of which is r, b, or w

## 輸出說明

A single line containing the maximum of number of beads that can be collected from the supplied necklace.

## 範例輸入 #1

```
29
wwwbbrwrbrbrrbrbrwrwwrbwrwrrb
```

## 範例輸出 #1

```
11
```
