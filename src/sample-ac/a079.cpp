#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;

struct Word {
    char type;
    string s;
};

int n;
vector<Word> dict;
map<string, vector<char>> wordMap; // word -> list of types ('n', 'v', 'a')
string article;

// dp[i] = {min_sentences, min_words} to parse article[i...end]
// We want to minimize sentences first, then words.
struct State {
    int sentences;
    int words;
    
    bool operator<(const State& other) const {
        if (sentences != other.sentences)
            return sentences < other.sentences;
        return words < other.words;
    }
    
    bool operator==(const State& other) const {
        return sentences == other.sentences && words == other.words;
    }
    
    bool operator>(const State& other) const {
        return other < *this;
    }
    
    bool operator<=(const State& other) const {
        return !(other < *this);
    }
};

State dp[5005];
bool visited[5005];

// Check if substring starting at pos with length len is a valid word
// Returns list of possible types, empty if not a word
vector<char> getTypes(int pos, int len) {
    if (pos + len > (int)article.size()) return {};
    string sub = article.substr(pos, len);
    if (wordMap.find(sub) == wordMap.end()) return {};
    return wordMap[sub];
}

// Forward declarations for mutual recursion
bool parseNounPhrase(int pos, int& endPos, int& wordCount);
bool parseVerbPhrase(int pos, int& endPos, int& wordCount);
bool parseStatement(int pos, int& endPos, int& wordCount);

// <名词短语> ::= <名词> | [ <辅词> ] <名词短语>
// Greedy approach won't work directly due to ambiguity, need to try all possibilities
// But we are inside DP, so we just need to find IF it's possible and count words
// Actually, the structure is recursive. 
// NounPhrase -> Noun
// NounPhrase -> Aux NounPhrase
// This means a NounPhrase is a sequence of Aux* followed by a Noun.
bool tryParseNounPhrase(int start, int& endPos, int& count) {
    // We need to match: (Aux)* Noun
    // Try to consume as many Aux as possible? No, because Aux might be prefix of another word.
    // But wait, the grammar is:
    // <名词短语> ::= <名词> | [ <辅词> ] <名词短语>
    // This expands to: <辅词> <辅词> ... <辅词> <名词>
    // So it's zero or more Aux, then one Noun.
    
    int curr = start;
    int auxCount = 0;
    
    // We need to try different split points between Aux sequence and the final Noun
    // Since we want minimum words overall, and this is part of a larger DP,
    // we should explore all valid parses of NounPhrase from 'start'
    // However, the function signature suggests a single path. 
    // Let's rethink: The DP state transition will handle the minimization.
    // Here we just need to verify if a NounPhrase can start at 'start' and end at some 'end',
    // returning the number of words.
    // But a NounPhrase can have multiple valid parsings (e.g., "bigbigdog" could be "big"(a) "bigdog"(n) or "bigbig"(a?) "dog"(n)).
    // So this helper should probably return all possible (endPos, wordCount) pairs?
    // That complicates things.
    
    // Alternative: Integrate the logic into the main DP loop.
    // At position i, try to form a NounPhrase.
    // A NounPhrase is a sequence of words w1, w2, ..., wk where w1..w(k-1) are 'a' and wk is 'n'.
    // We can iterate k from 1 upwards.
    // For k=1: check if article[i...j] is 'n'. If so, valid NP ending at j+1 with 1 word.
    // For k=2: check if article[i...j1] is 'a' AND article[j1...j2] is 'n'. Valid NP ending at j2+1 with 2 words.
    // And so on.
    
    // Since max word length is 20, and article length is 5000, we can't iterate too deeply blindly.
    // But the depth is limited by the fact that each word is at least 1 char.
    // Actually, we can just do this exploration inside the DP transition for Statement.
    
    return true; // Placeholder
}

// Let's restructure.
// We compute dp[i] from j > i.
// dp[i] = min over all valid Statements starting at i and ending at j of (1 + dp[j].sentences, 1 + words_in_statement + dp[j].words)
// Wait, the problem says: partition into MINIMUM sentences, then MINIMUM words.
// So if we have a statement from i to j, then cost is (1 + dp[j].sentences, words_in_stmt + dp[j].words).
// We need to find all valid statements starting at i.

// A statement is: <NounPhrase> { <VerbPhrase> <NounPhrase> } [ <VerbPhrase> ]
// Structure: NP (VP NP)* (VP)?
// So: NP, optionally followed by pairs of (VP, NP), optionally followed by a VP.

// To implement this efficiently:
// From position 'start', we must first parse a NounPhrase.
// A NounPhrase is: (Aux)* Noun.
// Let's find all possible endings and word counts for a NounPhrase starting at 'start'.
// Then, from each such ending, we can either:
//   1. End the statement (if we haven't started the optional trailing VP part? No, the structure allows ending after NP)
//      Actually, the pattern is NP (VP NP)* (VP)?
//      So after the initial NP, we can stop (valid statement).
//      Or we can try to parse a VP, then an NP, and repeat.
//      Or after some (VP NP) pairs, we can parse a final VP and stop.

// This looks like a DFS/BFS on the parse tree from 'start', collecting all valid (endPos, totalWords) for a complete Statement.
// Given the constraints (N<=1000 words in dict, article <= 5KB), and max word len 20.
// The branching factor is small.

struct ParseResult {
    int endPos;
    int wordCount;
};

// Get all valid NounPhrases starting at pos
vector<pair<int, int>> getNounPhrases(int pos) {
    vector<pair<int, int>> results;
    // Sequence of 'a' then one 'n'
    int curr = pos;
    int count = 0;
    
    // We can have 0 or more 'a's
    // Let's store states: (current_position, current_word_count)
    // Start with (pos, 0) representing we haven't read any 'a' yet.
    // Then we can read an 'a' and stay in "reading 'a's" mode, or read an 'n' and finish.
    
    // Use a queue or simple iteration since max depth is limited by string length
    // Actually, let's just iterate the number of 'a's.
    // But we don't know the boundaries.
    // Better: DFS.
    
    // State: current index, number of words so far in this NP
    // We are looking for a sequence of words where all but last are 'a', last is 'n'.
    
    vector<pair<int, int>> stack;
    stack.push_back({pos, 0});
    
    while(!stack.empty()){
        pair<int, int> state = stack.back();
        stack.pop_back();
        int curIdx = state.first;
        int curCnt = state.second;
        
        // Try to read an 'a'
        for(int len=1; len<=20; ++len){
            if(curIdx + len > (int)article.size()) break;
            vector<char> types = getTypes(curIdx, len);
            bool hasA = false;
            for(char t : types) if(t=='a') hasA = true;
            
            if(hasA){
                stack.push_back({curIdx+len, curCnt+1});
            }
        }
        
        // Try to read an 'n' (this finishes the NP)
        for(int len=1; len<=20; ++len){
            if(curIdx + len > (int)article.size()) break;
            vector<char> types = getTypes(curIdx, len);
            bool hasN = false;
            for(char t : types) if(t=='n') hasN = true;
            
            if(hasN){
                results.push_back({curIdx+len, curCnt+1});
            }
        }
    }
    
    return results;
}

// Get all valid VerbPhrases starting at pos
// <动词短语> ::= <动词> | [ <辅词> ] <动词短语>
// Same structure: (Aux)* Verb
vector<pair<int, int>> getVerbPhrases(int pos) {
    vector<pair<int, int>> results;
    vector<pair<int, int>> stack;
    stack.push_back({pos, 0});
    
    while(!stack.empty()){
        pair<int, int> state = stack.back();
        stack.pop_back();
        int curIdx = state.first;
        int curCnt = state.second;
        
        // Try to read an 'a'
        for(int len=1; len<=20; ++len){
            if(curIdx + len > (int)article.size()) break;
            vector<char> types = getTypes(curIdx, len);
            bool hasA = false;
            for(char t : types) if(t=='a') hasA = true;
            
            if(hasA){
                stack.push_back({curIdx+len, curCnt+1});
            }
        }
        
        // Try to read a 'v' (finishes VP)
        for(int len=1; len<=20; ++len){
            if(curIdx + len > (int)article.size()) break;
            vector<char> types = getTypes(curIdx, len);
            bool hasV = false;
            for(char t : types) if(t=='v') hasV = true;
            
            if(hasV){
                results.push_back({curIdx+len, curCnt+1});
            }
        }
    }
    return results;
}

// Get all valid Statements starting at pos
// <陈述句> ::= <名词短语> { <动词短语> <名词短语> } [ <动词短语> ]
vector<pair<int, int>> getStatements(int pos) {
    vector<pair<int, int>> results;
    
    // Step 1: Parse initial NounPhrase
    vector<pair<int, int>> nps = getNounPhrases(pos);
    
    for(auto& np : nps){
        int afterNp = np.first;
        int words = np.second;
        
        // Option A: Statement ends here (just NP)
        // Is this allowed? 
        // <陈述句> ::= <名词短语> { <动词短语> <名词短语> } [ <动词短语> ]
        // The { } part can be empty, and the [ ] part can be absent.
        // So yes, a single NP is a valid statement.
        results.push_back({afterNp, words});
        
        // Option B: Continue with { VP NP }*
        // We can loop: try to parse VP, then NP. Repeat.
        // Use a queue for BFS/DFS on the sequence of (VP, NP) pairs
        vector<pair<int, int>> queue;
        queue.push_back({afterNp, words});
        
        while(!queue.empty()){
            pair<int, int> curr = queue.front(); // Using front for BFS, back for DFS, doesn't matter much
            queue.erase(queue.begin());
            
            int curPos = curr.first;
            int curWords = curr.second;
            
            // Try to parse a VP
            vector<pair<int, int>> vps = getVerbPhrases(curPos);
            for(auto& vp : vps){
                int afterVp = vp.first;
                int vWords = vp.second;
                
                // After VP, we MUST parse an NP to continue the loop { VP NP }
                vector<pair<int, int>> nextNps = getNounPhrases(afterVp);
                for(auto& nextNp : nextNps){
                    int afterNextNp = nextNp.first;
                    int totalW = curWords + vWords + nextNp.second;
                    
                    // Successfully parsed a (VP, NP) pair.
                    // This forms a valid statement endpoint
                    results.push_back({afterNextNp, totalW});
                    
                    // And we can continue looping
                    queue.push_back({afterNextNp, totalW});
                }
            }
        }
        
        // Option C: After some (VP NP)*, parse a final optional [ VP ]
        // We need to revisit the states reached after (VP NP)* and try adding a final VP
        // Let's re-traverse or store states.
        // Actually, let's modify the loop above to also try adding a final VP at each step.
        
        // Re-doing the logic slightly to capture the optional trailing VP
        // Reset and do again more carefully
        
        // We already added the base case (just NP) to results.
        // Now consider sequences: NP (VP NP) ... (VP NP) [VP]
        
        // Let's collect all reachable states after parsing NP (VP NP)*
        vector<pair<int, int>> statesAfterPairs;
        statesAfterPairs.push_back({afterNp, words}); // 0 pairs
        
        vector<pair<int, int>> q2;
        q2.push_back({afterNp, words});
        
        while(!q2.empty()){
            pair<int, int> curr = q2.front();
            q2.erase(q2.begin());
            int curPos = curr.first;
            int curWords = curr.second;
            
            // Try VP then NP
            vector<pair<int, int>> vps = getVerbPhrases(curPos);
            for(auto& vp : vps){
                int afterVp = vp.first;
                int vWords = vp.second;
                
                vector<pair<int, int>> nextNps = getNounPhrases(afterVp);
                for(auto& nextNp : nextNps){
                    int afterNextNp = nextNp.first;
                    int totalW = curWords + vWords + nextNp.second;
                    statesAfterPairs.push_back({afterNextNp, totalW});
                    q2.push_back({afterNextNp, totalW});
                }
            }
        }
        
        // Now, for each state in statesAfterPairs, try appending an optional VP
        for(auto& st : statesAfterPairs){
            // Already added as valid statement (without trailing VP) ? 
            // Wait, the base case (just NP) was added. 
            // The states in statesAfterPairs include NP, NP(VP NP), etc.
            // All these are valid statements WITHOUT the trailing VP.
            // Did we add them all? 
            // In the first pass, we added NP. Then inside the loop we added NP(VP NP).
            // But we didn't explicitly add NP(VP NP)(VP NP)... to results in the first pass logic above?
            // Ah, in the first `while` loop, I did `results.push_back` inside.
            // So `results` currently contains all valid statements ending after an NP (i.e. pattern NP (VP NP)* ).
            
            // Now try adding a trailing VP to any of these
            vector<pair<int, int>> finalVps = getVerbPhrases(st.first);
            for(auto& fvp : finalVps){
                results.push_back({fvp.first, st.second + fvp.second});
            }
        }
    }
    
    return results;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    
    for(int i=0; i<n; ++i){
        string line;
        cin >> line;
        char type = line[0];
        string word = line.substr(2); // skip "X."
        wordMap[word].push_back(type);
    }
    
    string rawArticle;
    cin >> rawArticle;
    // Remove trailing dot
    if(rawArticle.size() > 0 && rawArticle.back() == '.'){
        article = rawArticle.substr(0, rawArticle.size()-1);
    } else {
        article = rawArticle;
    }
    
    int L = article.size();
    
    // Initialize DP
    for(int i=0; i<=L; ++i){
        dp[i] = {INF, INF};
        visited[i] = false;
    }
    dp[L] = {0, 0};
    visited[L] = true;
    
    // Fill DP from right to left
    for(int i=L-1; i>=0; --i){
        // Try all valid statements starting at i
        vector<pair<int, int>> stmts = getStatements(i);
        
        State best = {INF, INF};
        bool found = false;
        
        for(auto& stmt : stmts){
            int endPos = stmt.first;
            int wCount = stmt.second;
            
            if(endPos > L) continue;
            if(!visited[endPos]) continue;
            
            State next = dp[endPos];
            State candidate = {1 + next.sentences, wCount + next.words};
            
            if(candidate < best){
                best = candidate;
                found = true;
            }
        }
        
        if(found){
            dp[i] = best;
            visited[i] = true;
        }
    }
    
    cout << dp[0].sentences << "\n";
    cout << dp[0].words << "\n";
    
    return 0;
}
