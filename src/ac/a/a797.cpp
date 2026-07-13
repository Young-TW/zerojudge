#include <iostream>
#include <string>

using namespace std;

int getK(int H, int K0, int K1, int K2) {
    if ((H >= 21 || H < 6) || (H >= 14 && H < 16)) return K0;
    if ((H >= 6 && H < 9) || (H >= 17 && H < 19)) return K2;
    return K1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int M, H;
            cin >> M >> H;
            
            int k0_bus, k1_bus, k2_bus;
            int k0_train, k1_train, k2_train;
            int k0_hsr, k1_hsr, k2_hsr;
            
            cin >> k0_bus >> k1_bus >> k2_bus;
            cin >> k0_train >> k1_train >> k2_train;
            cin >> k0_hsr >> k1_hsr >> k2_hsr;
            
            int p_bus = 400 * getK(H, k0_bus, k1_bus, k2_bus) / 100;
            int p_train = 600 * getK(H, k0_train, k1_train, k2_train) / 100;
            int p_hsr = 1000 * getK(H, k0_hsr, k1_hsr, k2_hsr) / 100;
            
            int t_bus = 60;
            int t_train = 45;
            int t_hsr = 15;
            
            int best_price = 2000000000;
            int best_time = 2000000000;
            string best_name = "Walk home";
            
            auto update = [&](int price, int time, const string& name) {
                if (price > M) return;
                if (price < best_price || (price == best_price && time < best_time)) {
                    best_price = price;
                    best_time = time;
                    best_name = name;
                }
            };
            
            update(p_bus, t_bus, "Bus");
            update(p_train, t_train, "Train");
            update(p_hsr, t_hsr, "HSR");
            
            cout << best_name << "\n";
        }
    }
    
    return 0;
}
