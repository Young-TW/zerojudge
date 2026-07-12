#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Codon to amino acid mapping (three-letter codes)
    unordered_map<string, string> codon_map = {
        {"UUU", "Phe"}, {"UUC", "Phe"}, {"UUA", "Leu"}, {"UUG", "Leu"},
        {"UCU", "Ser"}, {"UCC", "Ser"}, {"UCA", "Ser"}, {"UCG", "Ser"},
        {"UAU", "Tyr"}, {"UAC", "Tyr"}, {"UGU", "Cys"}, {"UGC", "Cys"},
        {"UGG", "Trp"},
        {"CUU", "Leu"}, {"CUC", "Leu"}, {"CUA", "Leu"}, {"CUG", "Leu"},
        {"CCU", "Pro"}, {"CCC", "Pro"}, {"CCA", "Pro"}, {"CCG", "Pro"},
        {"CAU", "His"}, {"CAC", "His"}, {"CAA", "Gln"}, {"CAG", "Gln"},
        {"CGU", "Arg"}, {"CGC", "Arg"}, {"CGA", "Arg"}, {"CGG", "Arg"},
        {"AUU", "Ile"}, {"AUC", "Ile"}, {"AUA", "Ile"}, {"AUG", "Met"},
        {"ACU", "Thr"}, {"ACC", "Thr"}, {"ACA", "Thr"}, {"ACG", "Thr"},
        {"AAU", "Asn"}, {"AAC", "Asn"}, {"AAA", "Lys"}, {"AAG", "Lys"},
        {"AGU", "Ser"}, {"AGC", "Ser"}, {"AGA", "Arg"}, {"AGG", "Arg"},
        {"GUU", "Val"}, {"GUC", "Val"}, {"GUA", "Val"}, {"GUG", "Val"},
        {"GCU", "Ala"}, {"GCC", "Ala"}, {"GCA", "Ala"}, {"GCG", "Ala"},
        {"GAU", "Asp"}, {"GAC", "Asp"}, {"GAA", "Glu"}, {"GAG", "Glu"},
        {"GGU", "Gly"}, {"GGC", "Gly"}, {"GGA", "Gly"}, {"GGG", "Gly"}
    };

    string line;
    while (getline(cin, line)) {
        // Handle possible Windows line endings
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line == "0") break;

        string original = line;

        // Extract only A, U, C, G
        string seq;
        for (char c : line) {
            if (c == 'A' || c == 'U' || c == 'C' || c == 'G') {
                seq += c;
            }
        }

        // If the line indicates 3'->5' direction, reverse to get 5'->3'
        if (line.find("3'") != string::npos) {
            reverse(seq.begin(), seq.end());
        }

        vector<string> proteins;
        for (size_t i = 0; i + 2 < seq.size(); ) {
            if (seq.substr(i, 3) == "AUG") {
                vector<string> aa;
                size_t j = i;
                bool stop_found = false;
                while (j + 2 < seq.size()) {
                    string codon = seq.substr(j, 3);
                    if (codon == "UAA" || codon == "UAG" || codon == "UGA") {
                        stop_found = true;
                        break;
                    }
                    auto it = codon_map.find(codon);
                    if (it != codon_map.end()) {
                        aa.push_back(it->second);
                    }
                    j += 3;
                }
                if (stop_found) {
                    string protein;
                    for (size_t k = 0; k < aa.size(); ++k) {
                        if (k > 0) protein += "-";
                        protein += aa[k];
                    }
                    proteins.push_back(protein);
                    i = j + 3; // Continue after the stop codon
                } else {
                    // No stop codon for this start codon -> incomplete protein, stop scanning
                    break;
                }
            } else {
                ++i;
            }
        }

        cout << "Case \" " << original << " \":\n";
        for (const string& p : proteins) {
            cout << p << "\n";
        }
    }

    return 0;
}
