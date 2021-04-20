#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int a,b,c,x1,x2,f;
    cin >> a >> b >> c;
    f = (b*b)-(4*(a*c));
    f = sqrt(f);
    x1 = ((2*a*b)+f)/(a*a);
    x2 = ((2*a*b)-f)/(a*a);
    if (x1 != x2)
    {
        cout << "Two different roots x1=" << x1 << " , x2=" << x2;
    }
    else if (x1 == x2)
    {
        cout << "Two same roots x=" << x1;
    }
    else
    {
        cout << "NO real root";
    }
    return 0;
}

/*
Two different roots x1=?? , x2=??

Two same roots x=??

No real root

PS: 答案均為整數，若有兩個根則大者在前
*/