#include <iostream>
#include <string>
using namespace std;

int main(){
    int n,k=0,d=0,a=0,combo=0;
    string status;
    for(int i=0;i<n;i++){
        cin >> status;
        if(status == "Get_Kill")
            combo+=1;
        if(status == "Get_Assist")
        if(status == "Die")
            combo=0;
        if(combo > 0 && combo < 3)
            cout << "You have slain an enemie." << endl;
        if(combo == 3)
            cout << "KILLING SPREE!" << endl;
        if(combo == 4)
            cout << "RAMPAGE~" << endl;
        if(combo == 5)
            cout << "UNSTOPPABLE!" << endl;
        if(combo == 6)
            cout << "DOMINATING!" << endl;
        if(combo == 7)
            cout << "GUALIKE!" << endl;
        if(combo == 8)
            cout << "LEGENDARY!" << endl;
    }
    return 0;
}


/*
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
*/