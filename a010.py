a=int(input())                              #變數假設和輸入 #以輸入20為例
t=0
s=2                                         #一開始的除數
while (a>=s):                               #20>0
    n=0                                     #次方數
    while(a%s==0):                          #如果輸入的數字整除2的話 執行底下 #20/2 整除 #10/2 也整除
        a=a/s                               #20/2 =10  #10/2=5
        n=n+1                               #次方數加一         #n=1 回前兩行  #n=2  then 5就不整除
    if n>1 and t==0:                        #符合條件
        print(str(s)+'^'+str(n),end='')     #因為python有自動空格and自動換行所以要把int() convert into str()也就是字串 再用加號 如次一來就不會有空格
        t=t+1                               #印出  2^2
    elif n==1 and t==0:                 
        print(str(s),end='')
        t=t+1
    elif n>1:                                    
        print("",'*',str(s)+'^'+str(n),end='')            
    elif n==1:
        print("",'*',str(s),end='')
    else:
        s=s+1  