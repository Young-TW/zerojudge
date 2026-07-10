# a555. NCPC PD A Matrix Decipher

## 內容

Problem D

  A Matrix Decipher

  Input File: pd.in

          Let ZN = {0, 1, 2, …, N-2, N-1}, where N is a positive integer. An integer linear transformation under (mod N) can be defined as

          f(x) = Hx, where x ∈ ZdN, and H ∈ ZNd*d

  That is, x is a d-dimensional column vector and H is a d by d matrix whose elements are from ZN.

            For d = 3, we have f([見1]) = [見2]*[ 見1] = H[見1], where hij ∈ZN, 1 <= i,j <= 3. The inverse integer transformation exists only if gcd(det(H), N) = 1, that is, the determinant of matrix H is relatively prime to N. This problem assumes that N = 11.

            Let Ω = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, :} be the set of 11 characters represented as numbers 0,1, …, 10, respectively. A matrix encipher takes a message, a character string consisting of 12 characters from Ω = {0, 1, 2, …, 8, 9, :}, as input and ouputs an enciphered message of the same length based on applying an integer linear transformation successively on the d characters in each group from the input message string. For example, for d = 3, a message “9870::”, decomposed as two groups of 3 characters, “987” and “0::”, is enciphered as “262976” based on the transformation matrix H = [見3]. The corresponding decipher takes “262976” as input associated with the integer transformation matrix H-1 = [見4] which converts “262976” back to “9870::”. This problem asks you to design a matrix decipher H-1 based on a given matrix encipher H to decrypt an enciphered message.

   

  見一

  [x1]
 [x2]
 [x3]

  見二

  [h11 h12 h13]
 [h21 h22 h23]
 [h31 h32 h33]

  見三
 [1 1 1]
 [1 2 2]
 [1 2 3]

  見四

  [2 10 0]
 [10 2 10]
 [0 10 1]

## 輸入說明

The first line of the input file always contains one integer indicating the number of test cases to come. Each of the test cases consists of d+2 lines with d = 2 or d = 3 in the first line indicating the dimension of the encipher matrix H followed by d lines of the entries of H row by row, the (d+2)-th line is the input message of 12 characters.

## 輸出說明

The output format is similar to the input format. The first line of the ouput file contains one integer indicating the number of test cases. Each of the test cases consists of d+2 lines with d = 2 or d = 3 in the first line indicating the dimension of the decipher matrix H-1, the next d lines are the entries of H-1 row by row, and the (d+2)-th line is the decrypted message of 12 characters.

## 範例輸入 #1

```
   2
   2
   2   1
   3   2
6:19278694:2
   3
   1   1   1
   1   2   2
   1   2   3
26242669:976
```

## 範例輸出 #1

```
   2
   2  10
   8   2
224488::3377
   2  10   0
  10   2  10
   0  10   1
9876543210::
```
