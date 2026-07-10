# h385. 12970: Alcoholic Pilots

## 內容

In one of his many trips, Mr. Ed boarded an airplane where the captain talked like... well, like he was completely drunk. “I would like to greet a very special person here, which has been part of our lives for so much time. His wife says from the control tower that she loves you” — the captain said. Of course, Mr. Ed was really scared, how can alcoholic pilots flight with so many people on their hands? But that was not the worst part, our friend noticed that these drunken pilots like to race between them! By getting close to the captain’s cabin, Mr. Ed could hear another pilot (drunk, as expected) discussing with the captain by radio. Both of them shared information about how fast they were travelling and how far they were to the nearest airport. “If I arrive earlier to the airport, you will owe me a beer” — the captain bragged, then the airplane started to move abruptly. Of course Mr. Ed survived, if not, he could not tell us this story. But weirdly, you are wondering who won the race between the pilots and their average arrival time, so you asked the velocity and distance to the airport of both planes. Assume that the planes maintained their velocity even when landing.

## 輸入說明

The input will contain several test cases. The only line of each test case contains 4 space-separated integers $v_1$, $d_1$, $v_2$ and $d_2$ $(1 \leq v_1, d_1, v_2, d_2 ≤ 10^9 )$: the velocity and distance to the airport of the plane Mr. Ed and the captain were and the velocity and distance to the airport of the plane the captain was competing with. Velocities are expressed in miles per hour and distances in miles. The last test case is followed by a single line containing $4$ zeroes.

## 輸出說明

Print $2$ lines for each test case. In the first one, you should print ‘You owe me a beer!’ if the captain won the race or ‘No beer for the captain.’ if the other airplane won the race. You can safely assume there will be no draws in any test case. In the second line, print ‘Avg. arrival time:’ followed by the average arrival time (in hours) of both airplanes expressed as a simplified fraction of the form ‘x⁄y’, being $x$ and $y$ integers. If the fraction has an integer result, print the result of the division. See format below for more details.

## 範例輸入 #1

```
2 4 1 3
1 3 2 4
4 7 4 9
0 0 0 0
```

## 範例輸出 #1

```
Case #1: You owe me a beer!
Avg. arrival time: 5/2
Case #2: No beer for the captain.
Avg. arrival time: 5/2
Case #3: You owe me a beer!
Avg. arrival time: 2
```
