#include <iostream>
#include <vector>
using namespace std;
const int maxn = 1000005;
int n,l;
int X[maxn],H[maxn]; // x = place , h = high
int cut[maxn]; // cutted or not
int ans,pre;
bool flag;
vector<int> tree;

void cut_tree(int i){
    if(X[i] - H[i] >= 0 || X[i] + H[i] <= l){
        int L = i - 1;
        while(L > 0 && cut[L] == 1)
            L--;
        int R = i + 1;
        while(R < n - 1 && cut[R] == 1)
            R++;
        if((i > 0 && X[i] - H[i] >= X[L]) || (i < n-1 && X[i] + H[i] <= X[R])){
            ans++;
            cut[i] = 1;
            tree.push_back(H[i]);
        }
    }
}

int main(){
    cin >> n >> l;
    for (int i=0; i<n; i++){
        cin >> X[i];
    }
    for (int i=0; i<n; i++){
        cin >> H[i];
    }
    ans = 0;
    pre = 0;
    flag = true;
    while(flag){
        for(int i=0;i<n;i++){
            if(cut[i] == 0){
                cut_tree(i);
            }
        }
        flag = (ans != pre);
        pre = ans;
    }
    cout << ans << endl;
    if(tree.size())
        cout << *(--tree.end()) << endl;
    else
        cout << "0" << endl;
    return 0;
}

// NA 35%