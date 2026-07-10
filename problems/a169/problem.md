# a169. POJ 3225 Help with Intervals

## 內容

LogLoader, Inc. is a company specialized in providing products for analyzing logs. While Ikki is working on graduation design, he is also engaged in an internship at LogLoader. Among his tasks, one is to write a module for manipulating time intervals, which have confused him a lot. Now he badly needs your help.

In discrete mathematics, you have studied several basic set operations, namely union, intersection, relative complementation and symmetric difference, which naturally apply to the specialization of sets as intervals.. For your quick reference they are summarized in the table below:

OperationNotationDefinition

UnionA ∪ B{x : x ∈ A or x ∈ B}IntersectionA ∩ B{x : x ∈ A and x ∈ B}Relative complementationA − B{x : x ∈ A but x ∉ B}Symmetric differenceA ⊕ B(A − B) ∪ (B − A)Ikki has abstracted the interval operations emerging from his job as a tiny programming language. He wants you to implement an interpreter for him. The language maintains a set S, which starts out empty and is modified as specified by the following commands:

CommandSemanticsU TS ← S ∪ TI TS ← S ∩ TD TS ← S − TC TS ← T − SS TS ← S ⊕ T
 

LogLoader是一家专门提供日志分析产品的公司。Ikki在做毕业设计的同时，还忙于在LogLoader做实习。在他的工作里，有一项是要写一个模块来处理时间区间。这个事情一直让他感到很迷糊，所以现在他很需要你帮忙。

在离散数学里面，你已经学习了几种基本的集合运算，具体地说就是并、交、相对补和对称差。它们自然地也适用于区间这种特殊的集合。作为你的快速参考，它们可以总结成下表：

运算记号定义

并A ∪ B{x : x ∈ A或x ∈ B}交A ∩ B{x : x ∈ A并x ∈ B}相对补A − B{x : x ∈ A但是 x ∉B}对称差A ⊕ B(A − B) ∪ (B − A)Ikki已经把他的工作里出现的区间运算抽象成一个很小的编程语言。他想你为他实现一个解析器。这个语言维护一个集合S。S一开始是空集，并根据下列命令被修改：

命令语义U TS ← S ∪ TI TS ← S ∩ TD TS ← S − TC TS ← T − SS TS ← S ⊕ T

## 輸入說明

The input contains exactly one test case, which consists of between 0 and 65,535 (inclusive) commands of the language. Each command occupies a single line and appears like

X T

where X is one of ‘U’, ‘I’, ‘D’, ‘C’ and ‘S’ and T is an interval in one of the forms (a,b), (a,b], [a,b) and [a,b] (a, b ∈ Z, 0 ≤ a ≤ b ≤ 65,535), which take their usual meanings. The commands are executed in the order they appear in the input.

End of file (EOF) indicates the end of input.

输入包含一组测试数据，由0到65,535条命令组成。每条命令占一行，形式如下：

X T

其中X是‘U’、‘I’、‘D’、‘C’和‘S’中的一个，T是一个区间，形式为(a,b)、(a,b]、[a,b)和[a,b]之一（a, b ∈ Z; 0 ≤ a ≤ b ≤ 65,535），取它们通常的意义。命令按在输入中出现的顺序执行。

文件结束符（EOF）表示输入结束。

## 輸出說明

Output the set S as it is after the last command is executed as the union of a minimal collection of disjoint intervals. The intervals should be printed on one line separated by single spaces and appear in increasing order of their endpoints. If S is empty, just print “empty set” and nothing else.

以一组不相交区间的并的形式输出在最后一条命令执行之后的集合S。这些区间在一行内输出，由单个空格分隔，按端点的升序排序。如果S是空集，输出“empty set”。

## 範例輸入 #1

```
U [1,5]
D [3,3]
S [2,4]
C (1,5)
I (2,3]
```

## 範例輸出 #1

```
(2,3)
```
