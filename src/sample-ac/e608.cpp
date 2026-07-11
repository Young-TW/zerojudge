#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    bool firstCase = true;
    while (T--) {
        if (!firstCase) {
            cout << "\n";
        }
        firstCase = false;

        int N;
        cin >> N;
        
        map<string, vector<string>> dict;
        for (int i = 0; i < N; ++i) {
            string word;
            cin >> word;
            string sorted_word = word;
            sort(sorted_word.begin(), sorted_word.end());
            dict[sorted_word].push_back(word);
        }

        string test_word;
        while (cin >> test_word && test_word != "END") {
            cout << "Anagrams for: " << test_word << "\n";
            string sorted_test = test_word;
            sort(sorted_test.begin(), sorted_test.end());
            
            if (dict.find(sorted_test) != dict.end()) {
                const vector<string>& anagrams = dict[sorted_test];
                for (size_t i = 0; i < anagrams.size(); ++i) {
                    cout << setw(3) << (i + 1) << ") " << anagrams[i] << "\n";
                }
            } else {
                cout << "No anagrams for: " << test_word << "\n";
            }
        }
    }

    return 0;
}
