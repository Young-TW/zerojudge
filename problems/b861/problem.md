# b861. 葡萄

## 內容

調皮的皮皮吃葡萄不吐葡萄皮，不吃葡萄倒吐葡萄皮。一葡萄有一葡萄皮。皮皮有時吃葡萄，有時吐葡萄皮。請判斷皮皮是吃葡萄不吐葡萄皮，還是不吃葡萄倒吐葡萄皮。

## 輸入說明

第 1 行有一正整數 T(T <= 10)，接下來有 T 組輸入。
每組輸入 1 行，代表皮皮依序做的動作，其中包含兩種單字，chi 跟 tu，單字間以空白隔開。其中 chi 代表皮皮吃了一顆葡萄，tu 代表皮皮吐了一個葡萄皮。每組輸入不超過 10,000 個單字。

## 輸出說明

對於每組輸入，若皮皮最後吃的葡萄比吐的葡萄皮多，輸出 "chi pu tao bu tu pu tao pi"。若曾經吐的葡萄皮比吃的葡萄多，輸出 "bu chi pu tao dao tu pu tao pi"。若兩種狀況同時發生，輸出 "chi pu tao bu tu pu tao pi, bu chi pu tao dao tu pu tao pi"。若兩種狀況都沒發生，輸出 "chi pu tao tu pu tao pi"。

## 範例輸入 #1

```
3
chi chi tu tu
chi tu tu chi
tu chi chi
```

## 範例輸出 #1

```
chi pu tao tu pu tao pi
bu chi pu tao dao tu pu tao pi
chi pu tao bu tu pu tao pi, bu chi pu tao dao tu pu tao pi
```
