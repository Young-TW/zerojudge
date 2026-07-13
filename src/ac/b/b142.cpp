#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        string best_name;
        int best_money = -1;
        long long total_money = 0;
        
        for (int i = 0; i < N; ++i) {
            string name;
            int final_avg, class_avg, papers;
            char is_cadre, is_west;
            cin >> name >> final_avg >> class_avg >> is_cadre >> is_west >> papers;
            
            int money = 0;
            if (final_avg > 80 && papers >= 1) money += 8000;
            if (final_avg > 85 && class_avg > 80) money += 4000;
            if (final_avg > 90) money += 2000;
            if (final_avg > 85 && is_west == 'Y') money += 1000;
            if (class_avg > 80 && is_cadre == 'Y') money += 850;
            
            total_money += money;
            if (money > best_money) {
                best_money = money;
                best_name = name;
            }
        }
        
        cout << best_name << "\n";
        cout << best_money << "\n";
        cout << total_money << "\n";
    }
    
    return 0;
}
