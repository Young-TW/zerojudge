# c706. A = B Problem

## 內容

自從無意間看到 Rabin fingerprint 的資料，$\color{black}{icube}$ 便將其作為雜湊函數並運用在各 Online Judge 上解題。


日子漸漸過去，$\color{black}{icube}$ 墮入雜湊深淵而不自知，那是一種宗教似的狂熱，他甚至宣稱超過 $\color{black}{83.144598\%}$ 的字串匹配問題都能透過雜湊解決。


選擇一個數字 $\color{black}{M}$ 當作模數，在字元集大小 $\color{black}{C}$ 且長度 $\color{black}{L}$ 的字串中做比較，由於 $\color{black}{C^L}$ 遠大於 $\color{black}{M}$ ，理應發生不少雜湊碰撞，但一般在 OJ 上解題時，通過測試的機率依舊不低。


直到某日， $\color{black}{icube}$ 遇見曾經在程式設計比賽中拿下世界冠軍的電神，卻仍舊滔滔不絕地宣揚雜湊的 108 個好處。


「雜湊？那是凡人的伎倆。」電神面露不屑。「我只需半個普朗克時間便能構造一組讓你 WA 掉的測資了！」



uint64_t hash(const std::string &s, uint64_t mod) {
	uint64_t val = 0;
	for (char c : s) val = (val * 131 + c) % mod;
	return val;
}



或許你不是電神，沒辦法用半個普朗克時間構造測資，但你能不能也幫忙找出幾組特殊的相異字串 $\color{black}{A_i, B_i}$ 使得 $\color{black}{hash(A_i) = hash(B_i)}$ 呢？


請注意， $\color{black}{A_i, B_i}$ 只能包含小寫字母且須滿足 $\color{black}{|A_i| = |B_i| \le 30}$。

## 輸入說明

只有兩個正整數 $\color{black}{mod, \space S}$ 分別代表 $\color{black}{hash}$ 所使用的模以及必須輸出的行數。

## 輸出說明

輸出 $\color{black}{S}$ 行以空格隔開的 $\color{black}{A_i, B_i}$。


若出現以下情形，該測資點不予計分。


(1) 字串有小寫字母以外的字元、$\color{black}{A_i, B_i}$ 長度不同或超過 30。


(2) $\color{black}{A_i = B_i}$ 或 $\color{black}{hash(A_i) \ne hash(B_i)}$。


(3) 已經用過 $\color{black}{(A_i, B_i)}$ 或 $\color{black}{(B_i, A_i)}$ 的組合。


(4) 輸出格式錯誤、行數不足或超過 $\color{black}{S}$。

## 範例輸入 #1

```
1 2
```

## 範例輸出 #1

```
aa bb
a b
```
