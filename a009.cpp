#include <iostream>
using namespace std;

int main()
{
    string a;
    while(getline(cin, a))
    {
        for(int x = 0;x < a.length();x++)
        {
            cout<<char(a[x]-7);
        }
        cout<<endl;
    }
    return 0;
}
