# c491. Hollow Knight boss 出招問題

## 內容

你知道四千很喜歡玩Hollow Knight。遊戲中的小騎士，在深入地底探索這充滿bug的世界的同時，也探索自身存在的意義。



![image](ShowImage?id=1085)


這款遊戲最具特色也最有趣的地方便是boss戰裡的各種攻擊招式了。一隻boss擁有$M$種招式，在血量降為$0$前不斷選出一種招式攻擊小騎士。四千雖然知道每種招式的躲法，常常卻因為無法及時判斷這是哪種招式而讓小騎士受傷。有天四千發現，一隻boss的出招順序是一個$Q$循環。將boss的招式編號為$0, 1, \ldots, M-1$，則第$N (1 \leq N \leq Q)$次的攻擊招式由下方的C函式給出：



```
long long ChooseAttack(int N){
    long long sum = 0;
    for(int i=0; i其中$K$是個全域long long變數，而$\{a_i\}_{i=1}^Q$和$\{c_i\}_{i=0}^K$都是全域long long陣列。不幸的是，四千發現他的C compiler又壞了，因為當$K=60000$時，光是計算ChooseAttack(1)就花了他幾十秒，更別提算完ChooseAttack(2), ChooseAttack(3), ..., ChooseAttack(Q)了。現在他給你$M, Q, K, \{a_i\}_{i=1}^Q, \{c_i\}_{i=0}^K$，請你用ZJ的compiler幫他算出ChooseAttack(1), ChooseAttack(2), ..., ChooseAttack(Q)的值。

## 輸入說明

本題的輸入有$T$筆測資，請讀至檔案尾。


每筆測試資料佔三行。
第一行有三個正整數$M, Q, K$。
第二行有$Q$個非負整數$a_1, a_2, \ldots, a_Q$。
第三行有$K+1$個非負整數$c_0, c_1, \ldots, c_K$。
每一行的所有整數皆由一個空白隔開，且行末沒有多餘空白。


- $1 \leq T \leq 10$
- $1 \leq M \leq 10^8$
- $1 \leq Q \leq 60000$，且若$T \geq 2$，保證所有的$Q \leq 100$
- $1 \leq K \leq 60000$，且若$T \geq 2$，保證所有的$K \leq 100$
- $0 \leq a_i \leq M-1$
- $0 \leq c_i \leq M-1$

## 輸出說明

對於每筆測試資料，輸出一行，包含$Q$個介於$0$與$M-1$之間的整數$A_1, A_2, \ldots, A_Q$，其中$A_N$代表這隻boss在第$N$次攻擊選擇的招式，亦即ChooseAttack(N)的值。


每一行的所有整數應皆由一個空白隔開，且行末不應有多餘空白。

## 範例輸入 #1

```
10 4 2
0 1 2 3
1 0 1
8 4 3
7 1 2 2
2 1 0 1
```

## 範例輸出 #1

```
1 2 5 0
0 4 4 4
```
