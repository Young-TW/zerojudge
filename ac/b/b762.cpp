#include <iostream>
#include <string>
using namespace std;

int k=0,d=0,a=0;

void die(int combo){
    d++;
    if(combo <= 2){
        cout << "You have been slained." << endl;
        return;
    }
    cout << "SHUTDOWN." << endl;
    return;
}

void kill(int combo){
    k++;
    combo++;
    if(combo <= 2){
        cout << "You have slain an enemie." << endl;
        return;
    }
    if(combo == 3){
        cout << "KILLING SPREE!" << endl;
        return;
    }
    if(combo == 4){
        cout << "RAMPAGE~" << endl;
        return;
    }
    if(combo == 5){
        cout << "UNSTOPPABLE!" << endl;
        return;
    }
    if(combo == 6){
        cout << "DOMINATING!" << endl;
        return;
    }
    if(combo == 7){
        cout << "GUALIKE!" << endl;
        return;
    }
    if(combo >= 8){
        cout << "LEGENDARY!" << endl;
        return;
    }
    return;
}

int main(){
    int n,combo=0;
    string status;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> status;
        if(status == "Get_Kill"){
            kill(combo);
            combo++;
        }
        if(status == "Get_Assist")
            a++;
        if(status == "Die"){
            die(combo);
            combo=0;
        }
    }
    cout << k << "/" << d << "/" << a;
    return 0;
}