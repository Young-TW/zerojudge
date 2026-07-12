#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int A, B, C, D, E, F, G, H, I, J, K, L, M;
        cin >> A >> B >> C >> D >> E >> F >> G >> H >> I >> J >> K >> L >> M;
        
        int score = 0;
        
        if (A <= 1) score -= 1;
        else if (A == 2) score += 1;
        else if (A == 3) score += 2;
        else if (A == 4) score += 3;
        else score += 4;
        
        if (B == 0) score -= 1;
        else if (B == 1) score += 1;
        else if (B == 2) score += 2;
        else if (B == 3) score += 3;
        else score += 4;
        
        if (C == 0) score -= 1;
        else if (C <= 3) score += 1;
        else if (C <= 5) score += 2;
        else if (C <= 7) score += 3;
        else score += 4;
        
        if (D == 0) score -= 1;
        else if (D == 1) score += 1;
        else if (D == 2) score += 2;
        else if (D == 3) score += 3;
        else score += 4;
        
        if (E == 0) score -= 1;
        else if (E <= 3) score += 1;
        else if (E <= 5) score += 2;
        else if (E <= 7) score += 3;
        else score += 4;
        
        if (F == 0) score -= 1;
        else if (F <= 2) score += 1;
        else if (F <= 4) score += 2;
        else if (F <= 6) score += 3;
        else score += 4;
        
        if (G == 0) score -= 1;
        else if (G == 1) score += 1;
        else if (G == 2) score += 2;
        else if (G <= 4) score += 3;
        else score += 4;
        
        score -= H;
        score += I;
        score += J;
        score += 2 * K;
        score += 3 * L;
        score += M;
        
        cout << score << '\n';
    }
    
    return 0;
}
