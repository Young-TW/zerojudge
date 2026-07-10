# a792. 14. Six Degrees of Kevin Bacon

## 內容

六度分隔( Six Degrees of Kevin Bacon )是基於｢小世界現象(small world phenomenon)｣的理論衍生出的小遊戲，遊戲前提是：每個演員都要以電影角色關聯連結到Kevin Bacon，可能有六層或六層以下了連結，遊戲玩法是一群人將每一個演員用最快且最少的層數( Bacon數 )連結到Kevin Bacon。

請寫一個程式算出目標演員的Bacon數。

## 輸入說明

輸入分兩個區塊，第一個區塊為電影( 每行第1個字串 )和相關演員( 每行剩下的字串 )，第二個區塊為要計算的演員，區塊名稱用[]包住。

## 輸出說明

請輸出演員的Bacon數 (格式參考輸出範例)。

## 範例輸入 #1

```
[MOVIES]
BeautyShop QueenLatifah AliciaSilverstone AndieMacDowell AlfreWoodard KevinBacon DellaReese
Footloose KevinBacon LoriSinger JohnLithgow DianneWiest ChrisPenn SarahJessicaParker
JFK KevinCostner TommyLeeJones KevinBacon GaryOldman JohnCandy DonaldSutherland JoePesci LaurieMetcalf
APrarieHomeCompanion TommyLeeJones MarylouiseBurke WoodyHarrelson KevinKline
ThePinkPanther SteveMartin KevinKline JeanReno EmilyMortimer BeyonceKnowles
Dreamgirls JamieFoxx BeyonceKnowles EddieMurphy DannyGlover JenniferHudson JohnLithgow
Shooter MarkWahlberg MichaelPena DannyGlover KateMara EliasKoteas RhonaMitra
TheItalianJob MarkWahlberg CharlizeTheron DonaldSutherland JasonStatham MosDef
16Blocks BruceWillis MosDef DavidMorse JennaStern
LuckyNumberSlevin JoshHartnett BruceWillis LucyLiu MorganFreeman BenKingsley
BatmanBegins ChristianBale MichaelCaine LiamNeeson KatieHolmes GaryOldman
ThePhantomMenace LiamNeeson EwanMcGregor NataliePortman IanMcDiarmid
AttackOfTheClones EwanMcGregor NataliePortman HaydenChristensen ChristopherLee SamuelLJackson
SinCity JessicaAlba JoshHartnett RutgerHauer BruceWillis ElijahWood MickeyRourke
EternalSunshineOfTheSpotlessMind JimCarrey KateWinslet ElijahWood KirstenDunst GerryRobertByrne
BruceAlmighty JimCarrey MorganFreeman JenniferAniston PhilipBakerHall CatherineBell SteveCarell
TheTwoTowers SeanAstin CateBlanchett OrlandoBloom ChristopherLee ElijahWood IanMcKellen ViggoMortensen
TheAviator LeonardoDiCaprio CateBlanchett KateBeckinsale AlecBaldwin AlanAlda JudeLaw BrentSpiner
MenInBlack TommyLeeJones WillSmith LindaFiorentino VincentDOnofrio RipTorn TonyShaloub
WildWildWest WillSmith KevinKline KennethBranagh SalmaHayek MemmetWalsh
FunWithDickAndJane JimCarrey TeaLeoni AlecBaldwin AngieHarmon LaurieMetcalf JohnMichaelHiggins
Dogma BenAffleck MattDamon LindaFiorentino JasonMewes ChrisRock AlanRickman JasonLee SalmaHayek
[ACTORS]
EddieMurphy
[END]
```

## 範例輸出 #1

```
EddieMurphy has a Bacon number of 2
```
