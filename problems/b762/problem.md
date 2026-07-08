# b762. 英國聯蒙

## 內容

隨著時代來到曉責元6666年，世界第87次戰爭開打了。
而在這次大戰中特別強勢的 國際蘿莉保護王朝 (Expansive National Guardianship Loli Analysis Neighborly Dynasty ，簡稱ENGLAND)
掌握了相當大部分的勢力，為了與他們的對手沉澱國抗衡，他們這次打算邀請蒙古和他們聯手作戰，然而語言的橫溝(GENERATION GAP)是難以跨越的，
除了將句子重新排序外，我們透過系統統一發出的戰鬥線報可以得知每一個士兵的戰鬥狀況，
系統發出的線報有分成三種:
1. "Get_Kill" 代表士兵剛剛英勇的殺死了一名敵人
2. "Get_Assist" 代表士兵機靈的剛剛透過協助別人撿到了一個助攻
3. "Die" 代表士兵掛了ORZ
你的工作就是接收指令，並發送線報回王朝，線報的規則如下:
1. 若是擊殺了一名敵人，並且連續擊殺( 即擊殺之間沒有死亡 ) 未滿3次，則輸出一行"You have slain an enemie."
2. 若是連續擊殺累計3次，則輸出一行"KILLING SPREE!"
3. 若是連續擊殺累計4次，則輸出一行"RAMPAGE~"
4. 若是連續擊殺累計5次，則輸出一行"UNSTOPPABLE!"
5. 若是連續擊殺累計6次，則輸出一行"DOMINATING!"
6. 若是連續擊殺累計7次，則輸出一行"GUALIKE!"
7. 若是連續擊殺累計8次以上，則輸出一行"LEGENDARY!"
8. 若是在連續擊殺未滿3次時死亡，則輸出一行"You have been slained."
9. 若是在連續擊殺累計3次以上時死亡，則輸出一行"SHUTDOWN."

## 輸入說明

輸入有兩行，第一行有一數字N，代表共有N條指令 ( N <= 40 )
第2~N+1行為指令，保證指令只會有提敘中列舉出的三種

## 輸出說明

照著國際蘿莉保護王朝的規則輸出線報，並在最後一行輸出士兵目前為止的戰績( 擊殺次數 / 死亡次數 / 助攻次數 )

## 範例輸入 #1

```
11
Get_Kill
Get_Kill
Get_Assist
Get_Assist				
Get_Kill
Die
Get_Kill
Get_Assist
Get_Kill
Die
Get_Kill
```

## 範例輸出 #1

```
You have slain an enemie.
You have slain an enemie.
KILLING SPREE!
SHUTDOWN.
You have slain an enemie.
You have slain an enemie.
You have been slained.
You have slain an enemie.
6/2/3
```
