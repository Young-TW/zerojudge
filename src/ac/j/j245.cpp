#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S;
    while (cin >> S) {
        int L = S.size();
        string Sp;
        Sp.resize(L % 2 == 0 ? L : L + 1);
        
        int idx = 0;
        if (L % 2 == 0) {
            int mid1 = L / 2 - 1;
            int mid2 = L / 2;
            Sp[idx++] = S[mid1];
            for (int i = 0; i < mid1; i++) Sp[idx++] = S[i];
            for (int i = mid1 + 1; i < mid2; i++) Sp[idx++] = S[i];
            for (int i = mid2 + 1; i < L; i++) Sp[idx++] = S[i];
            Sp[idx++] = S[mid2];
        } else {
            int mid = L / 2;
            Sp[idx++] = S[mid];
            for (int i = 0; i < mid; i++) Sp[idx++] = S[i];
            for (int i = mid + 1; i < L; i++) Sp[idx++] = S[i];
            Sp[idx++] = S[mid];
        }
        
        int Lp = Sp.size();
        string T;
        T.resize(Lp);
        
        int left = 0, right = Lp - 1;
        for (int i = 0; i < Lp; i++) {
            if (Sp[i] & 1) {
                T[i] = Sp[left++];
            } else {
                T[i] = Sp[right--];
            }
        }
        
        int H = 0;
        for (int i = 0; i < 4 && i < Lp; i++) {
            if ((Sp[i] & 1) ^ (T[i] & 1)) H++;
        }
        
        for (int i = 0; i < Lp; i++) {
            T[i] += H;
        }
        
        cout << T << "\n";
    }
    
    return 0;
}
