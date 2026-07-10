# d782. 11490 - Just Another Problem

## 內容

![image](ShowImage?id=375)
There is a wise saying “Nothing is unfair in love and war”. Probably that is why emperors of ancient days used to use many funny and clever tricks to fool the opponents. The most common technique was to scare the opponent away by out numbering them with imaginary soldiers. One of the funnier tricks (though hard to believe) was to give the own soldiers (not the opponent soldiers!) mild laxative dose so that there is a long queue of soldiers in front of toilet. Seeing this queue from a distance the opponent would miscalculate the total number of soldiers and flee away. This was a famous trick given by famous clown of the sub-continent named Gopal (The infamous “Gopal Bhar” to be precise). Another most common trick was to have square shaped holes while arranging the soldiers in rows and columns. Such an arrangement is shown below with 96 soldiers.

 

![image](ShowImage?id=376)

Fig: A valid layout with 96 soldiers. After arranging them 8 soldiers are missing.

 

The strict property of such arrangement for this problem is as follows:

 

(a)    The soldiers have to be arranged in rows and columns.

(b)   The border of the arrangement has to be rectangular.

(c)    The arrangement should have soldiers missing only from the inner layers.

(d)   The soldiers should be missing only from two equal square shaped regions. So the number of missing soldiers should be twice of a strictly positive square number. In the figure above the number of missing soldier is 2*22.

(e)    The thickness of soldiers should be equal every where (except the corners) in horizontal and vertical directions along the missing square. For example in the figure above the thickness of soldiers in horizontal and vertical directions along the missing square is always three. 

 

Now given the total number of soldiers S your job is to determine whether or not they can be arranged according to the above mentioned rules.

## 輸入說明

The input file contains 1000 lines of inputs. Each line contains a positive integer S (S<1000000000000), where S is the total number of soldiers.

 

Input is terminated by line containing a single zero.

## 輸出說明

For each line of input produce one or more line of output. Each line reports one possible number of possible missing soldiers which would enable the desired arrange with the S soldiers. As the number of possible missing soldiers can be quite large so instead of the actual number, the modulo 100000007 value should be printed. Also if there is more than one possible value for number of missing soldiers the modulo 100000007 values should be reported in descending order of the original number of soldier (Not the modulo value). If no such number of missing soldiers is found print the line “No Solution Possible” instead.

 

Print a blank line after the output for each line of input. Look at the output for sample input for details.

## 範例輸入 #1

```
96
102
11100
0
```

## 範例輸出 #1

```
Possible Missing Soldiers = 8
 
No Solution Possible
 
Possible Missing Soldiers = 553352
Possible Missing Soldiers = 308898
Possible Missing Soldiers = 45000
Possible Missing Soldiers = 3528
```
