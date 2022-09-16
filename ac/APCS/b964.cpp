#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    int people,temp;
    vector<int> value;
    cin >> people;
    for(int i=0;i<people;i++){
        cin >> temp;
        value.push_back(temp);
    }
    sort(value.begin(),value.end());
    for(auto i : value){
        cout << i << " ";
    }
    cout << endl;

    bool u=1,d=1;
    for(auto i : value){
        if(i<60){
            u=0;
        }
        if(i>=60){
            d=0;
        }
    }
    auto l = lower_bound(value.begin(),value.end(), 60);
    if(u){
        cout << "best case" << endl;
    }else{
        cout << *(l-1) << endl;
    }
    if(d){
        cout << "worst case" << endl;
    }else{
        auto l = lower_bound(value.begin(),value.end(), 60);
        cout << *l << endl;
    }
    return 0;
}