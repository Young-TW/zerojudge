#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    double v_person, m_person, v_equip, m_equip, d_sea;
    while (cin >> v_person >> m_person >> v_equip >> m_equip >> d_sea) {
        double ans = 0.0;
        if (v_person == -1) {
            ans = (m_person + m_equip) / d_sea - v_equip;
        } else if (m_person == -1) {
            ans = d_sea * (v_person + v_equip) - m_equip;
        } else if (v_equip == -1) {
            ans = (m_person + m_equip) / d_sea - v_person;
        } else if (m_equip == -1) {
            ans = d_sea * (v_person + v_equip) - m_person;
        } else if (d_sea == -1) {
            ans = (m_person + m_equip) / (v_person + v_equip);
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
