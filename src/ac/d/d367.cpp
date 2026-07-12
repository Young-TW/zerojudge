#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double a, b, c;
    while (std::cin >> a >> b >> c && (a != 0 || b != 0 || c != 0)) {
        double s = (a + b + c) / 2.0;
        double area_sq = s * (s - a) * (s - b) * (s - c);
        
        if (area_sq <= 0) {
            // 退化三角形或輸入錯誤，理論上題目保證不會發生，但安全起見處理
            // 若面積為 0，費馬點即為中間點，距離和為最長邊
            double max_side = std::max(a, std::max(b, c));
            std::cout << std::fixed << std::setprecision(2) << max_side << "\n";
            continue;
        }

        double area = std::sqrt(area_sq);
        
        // 檢查是否有大於等於 120 度的角
        // 利用餘弦定理：cos(C) = (a^2 + b^2 - c^2) / (2ab)
        // 若 cos(C) <= -0.5，則角度 >= 120 度
        bool has_obtuse = false;
        
        // 檢查角 C (對邊 c)
        double cos_c = (a * a + b * b - c * c) / (2.0 * a * b);
        if (cos_c <= -0.5) has_obtuse = true;
        
        // 檢查角 B (對邊 b)
        double cos_b = (a * a + c * c - b * b) / (2.0 * a * c);
        if (cos_b <= -0.5) has_obtuse = true;
        
        // 檢查角 A (對邊 a)
        double cos_a = (b * b + c * c - a * a) / (2.0 * b * c);
        if (cos_a <= -0.5) has_obtuse = true;

        double result;
        if (has_obtuse) {
            // 若有角 >= 120 度，費馬點即為該頂點，最小距離和為較短兩邊之和（即除去最長邊的兩邊？不，是該頂點連接的兩邊）
            // 實際上，若角 A >= 120，則 P=A，總長 = AB + AC = c + b
            // 我們需要找出哪個角 >= 120，然後返回該頂點連接的兩邊長之和
            // 或者更簡單：若角 A >= 120，則 a 是最長邊嗎？不一定，但通常是大邊對大角。
            // 精確做法：
            if (cos_a <= -0.5) {
                result = b + c;
            } else if (cos_b <= -0.5) {
                result = a + c;
            } else {
                result = a + b;
            }
        } else {
            // 所有角都小於 120 度，使用公式：
            // PA+PB+PC = sqrt( (a^2+b^2+c^2)/2 + 2*sqrt(3)*Area )
            // 這個公式來自於將三角形旋轉 60 度構造等邊三角形後的幾何性質
            // 另一種形式：sqrt( (a^2 + b^2 + c^2 + 4*sqrt(3)*S) / 2 ) ? 
            // 讓我們重新確認公式。
            // 正確公式推導：
            // 最小值 = sqrt( (a^2 + b^2 + c^2) / 2 + 2 * sqrt(3) * area )
            // 或者是：
            // 令 K = area
            // Ans = sqrt( (a*a + b*b + c*c) / 2.0 + 2.0 * sqrt(3.0) * K );
            
            double term1 = (a * a + b * b + c * c) / 2.0;
            double term2 = 2.0 * std::sqrt(3.0) * area;
            result = std::sqrt(term1 + term2);
        }

        std::cout << std::fixed << std::setprecision(2) << result << "\n";
    }
    return 0;
}
