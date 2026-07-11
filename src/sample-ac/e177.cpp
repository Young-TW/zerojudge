#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N;
vector<string> board;

// Directions: Up, Down, Left, Right
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Count liberties for a group of stones starting at (sx, sy)
// Also fills the group coordinates if needed, but here we just need count
// To detect ko, we specifically look for a single stone with exactly 1 liberty
// where that liberty is the point in question.
int countLiberties(int sx, int sy, char color, const vector<string>& currentBoard) {
    bool visited[20][20] = {false};
    vector<pair<int, int>> q;
    q.push_back({sx, sy});
    visited[sx][sy] = true;
    
    int liberties = 0;
    int head = 0;
    
    while(head < q.size()){
        pair<int, int> curr = q[head++];
        int cx = curr.first;
        int cy = curr.second;
        
        for(int i=0; i<4; ++i){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            if(isValid(nx, ny)){
                if(currentBoard[nx][ny] == '.'){
                    // Check if this liberty is already counted for this group?
                    // Standard liberty counting counts unique empty points adjacent to the group.
                    // However, for Ko detection, we are usually checking a specific capture scenario.
                    // Let's just count raw adjacent empty spots for the whole group.
                    // But wait, if multiple stones in the group share the same liberty, it's still 1 liberty.
                    // We need a set of liberty coordinates or mark them.
                    // Since N is small, we can use a temporary marker on a separate grid or just a list and unique.
                    liberties++; // This logic is flawed if multiple stones touch same empty spot.
                    // Correct approach: collect all empty neighbors, then unique them.
                } else if(currentBoard[nx][ny] == color && !visited[nx][ny]){
                    visited[nx][ny] = true;
                    q.push_back({nx, ny});
                }
            }
        }
    }
    
    // Re-do correctly with unique liberties
    // Reset
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) visited[i][j] = false;
    
    vector<pair<int,int>> group;
    q.clear();
    q.push_back({sx, sy});
    visited[sx][sy] = true;
    head = 0;
    
    while(head < q.size()){
        pair<int, int> curr = q[head++];
        group.push_back(curr);
        int cx = curr.first;
        int cy = curr.second;
        
        for(int i=0; i<4; ++i){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            if(isValid(nx, ny)){
                if(currentBoard[nx][ny] == color && !visited[nx][ny]){
                    visited[nx][ny] = true;
                    q.push_back({nx, ny});
                }
            }
        }
    }
    
    vector<pair<int,int>> libs;
    for(auto p : group){
        for(int i=0; i<4; ++i){
            int nx = p.first + dx[i];
            int ny = p.second + dy[i];
            if(isValid(nx, ny) && currentBoard[nx][ny] == '.'){
                libs.push_back({nx, ny});
            }
        }
    }
    
    sort(libs.begin(), libs.end());
    libs.erase(unique(libs.begin(), libs.end()), libs.end());
    
    return libs.size();
}

// Check if placing 'color' at (tx, ty) results in capturing any opponent stones
bool canCapture(int tx, int ty, char color, const vector<string>& currentBoard) {
    char opponent = (color == 'X' ? 'O' : 'X');
    
    for(int i=0; i<4; ++i){
        int nx = tx + dx[i];
        int ny = ty + dy[i];
        
        if(isValid(nx, ny) && currentBoard[nx][ny] == opponent){
            // Check if this opponent group has 0 liberties after placing 'color' at (tx, ty)
            // Simulate the board state logically: the point (tx, ty) is now occupied by 'color'
            // So when counting liberties for the neighbor group, (tx, ty) is not '.'
            
            // We need to check the group at (nx, ny)
            // Since (tx, ty) is effectively filled, we just run standard liberty count
            // but treating (tx, ty) as non-empty (which it is in the simulation).
            // Actually, the board passed in doesn't have (tx, ty) filled yet.
            // The function countLiberties looks for '.' neighbors.
            // If we pass the board as is, (tx, ty) is '.' (or whatever it was before).
            // Wait, the input board has '.' at (tx, ty) because we are considering placing there.
            // So countLiberties will see (tx, ty) as a liberty if it's adjacent.
            // We need to temporarily mark (tx, ty) as occupied to simulate the move.
            
            // Let's create a small helper or modify logic.
            // Since N is small, copying board is fine, but let's be smarter.
            // Just check the group of (nx, ny). If its only liberty is (tx, ty), then countLiberties 
            // on the original board will return 1, and that liberty must be (tx, ty).
            
            // Get group of (nx, ny)
            bool visited[20][20] = {false};
            vector<pair<int,int>> q;
            q.push_back({nx, ny});
            visited[nx][ny] = true;
            int head = 0;
            vector<pair<int,int>> group;
            
            while(head < q.size()){
                pair<int, int> curr = q[head++];
                group.push_back(curr);
                int cx = curr.first;
                int cy = curr.second;
                
                for(int k=0; k<4; ++k){
                    int gx = cx + dx[k];
                    int gy = cy + dy[k];
                    if(isValid(gx, gy) && currentBoard[gx][gy] == opponent && !visited[gx][gy]){
                        visited[gx][gy] = true;
                        q.push_back({gx, gy});
                    }
                }
            }
            
            // Now check liberties of this group.
            // A liberty is valid if it is '.' AND it is NOT (tx, ty) because (tx, ty) is being filled.
            // Wait, if (tx, ty) is the ONLY liberty, then after filling it, liberties = 0.
            // So on the current board (where (tx, ty) is empty), the group should have exactly 1 liberty,
            // and that liberty MUST be (tx, ty).
            
            int libCount = 0;
            bool isTxTyLib = false;
            
            for(auto p : group){
                for(int k=0; k<4; ++k){
                    int lx = p.first + dx[k];
                    int ly = p.second + dy[k];
                    if(isValid(lx, ly)){
                        if(currentBoard[lx][ly] == '.'){
                            if(lx == tx && ly == ty){
                                isTxTyLib = true;
                            } else {
                                libCount++; // Found a liberty that is NOT the move position
                            }
                        }
                    }
                }
            }
            
            if(libCount == 0 && isTxTyLib){
                return true; // Captures!
            }
        }
    }
    return false;
}

void solve() {
    int caseNum = 1;
    while(cin >> N && N != 0) {
        board.assign(N, "");
        for(int i=0; i<N; ++i) {
            cin >> board[i];
        }
        
        // Coordinate system:
        // Input: row 0 is top (y=N), row N-1 is bottom (y=1).
        // Col 0 is left (x=1), Col N-1 is right (x=N).
        // So board[r][c] corresponds to x = c+1, y = N-r.
        
        vector<pair<int, int>> koPoints;
        
        // Iterate over every empty point
        for(int r=0; r<N; ++r){
            for(int c=0; c<N; ++c){
                if(board[r][c] == '.'){
                    // Try placing Black ('O')
                    // Check if it captures White
                    if(canCapture(c, r, 'O', board)){
                        // Simulate board after Black plays
                        // Check if White can immediately recapture at (c, r)
                        // For White to recapture, the Black stone just placed must be in atari (1 lib)
                        // and removing it brings back the previous state (conceptually).
                        // Rule: "After taking a stone, even if the placed stone has only 1 liberty, 
                        // the opponent cannot take it back immediately."
                        
                        // Condition for Ko at (c, r):
                        // 1. Black plays at (c, r), captures some White stones.
                        // 2. The resulting Black group (just the stone or connected) has exactly 1 liberty.
                        // 3. That single liberty is the point where the White stones were removed? 
                        //    No, the liberty is usually the point inside the captured shape if it was a snapback?
                        //    No, Ko is specific: 1 stone taken, 1 stone left, 1 liberty (the spot just taken).
                        
                        // Let's refine:
                        // A Ko shape typically involves:
                        // - Black takes 1 White stone at P.
                        // - Black's stone at P has exactly 1 liberty (which is P itself? No, P is occupied).
                        //   The liberty must be the spot where the white stone WAS? No, that's P.
                        //   Wait, if Black takes White at P, P is now Black.
                        //   The "liberty" for the Black stone must be adjacent empty spots.
                        //   In a classic Ko, the Black stone at P has exactly 1 liberty, which is the spot 
                        //   where the captured White stone's other liberties were? 
                        //   Actually, in a simple Ko:
                        //   O X O
                        //   X . X  <- Black plays here, takes middle X? No.
                        //   O X O
                        //   Classic Ko:
                        //   . O .
                        //   O X O  <- White is at center? No.
                        //   . O .
                        //   Let's trace:
                        //   B W B
                        //   W . W
                        //   B W B
                        //   If Black plays center, he captures nothing (W has libs).
                        //   
                        //   Standard Ko:
                        //   . B .
                        //   B W B
                        //   . B .
                        //   If Black plays at W's spot? No, W is there.
                        //   If W is at (2,2). Neighbors (1,2), (3,2), (2,1), (2,3) are B.
                        //   W has 0 libs? Dead already.
                        //   
                        //   Correct Ko setup:
                        //   One White stone at P. It has 1 liberty at L? No.
                        //   It has 1 liberty? If it has 1 liberty, Black can play there and capture.
                        //   Suppose White stone at P has only 1 liberty at Q.
                        //   Black plays at Q. Captures White at P.
                        //   Now Black stone at Q. Does it have 1 liberty?
                        //   The liberty would be P (now empty).
                        //   If Black at Q has ONLY liberty P, then White can play at P to capture Q.
                        //   This is Ko.
                        
                        // So algorithm:
                        // For each empty point E:
                        // 1. Check if placing 'O' at E captures any 'X'.
                        //    If yes, let the set of captured stones be C.
                        //    (In Ko, |C| is usually 1).
                        // 2. Construct hypothetical board: 'O' at E, 'X' in C removed.
                        // 3. Check the group of 'O' containing E.
                        //    Count its liberties.
                        //    If liberties == 1, AND that single liberty is one of the points in C (specifically the one adjacent to E? Or any?)
                        //    Actually, if the group has 1 liberty, and that liberty allows the opponent to capture back immediately.
                        //    The opponent would play at that liberty.
                        //    If playing at that liberty captures the 'O' group, then it's a potential Ko.
                        //    The rule says "cannot immediately take back".
                        //    So we just need to detect: 
                        //      Move A captures B. Resulting state S has A in atari, and the only move to save/capture is to retake A.
                        //      Specifically, if White can play at the liberty of Black's new stone and capture it immediately.
                        
                        // Let's simulate strictly:
                        // Current Board: B
                        // Move: Black plays at E.
                        // Captures: Set C (stones of White).
                        // New Board B': B with E='O', C cleared.
                        // Check group G of 'O' at E in B'.
                        // Find liberties of G. Let them be L = {l1, l2, ...}.
                        // If |L| == 1:
                        //    Let l1 be the only liberty.
                        //    Check if White playing at l1 captures G.
                        //    (i.e., does placing 'X' at l1 result in 0 liberties for G?)
                        //    Since G only has l1 as liberty, placing 'X' at l1 definitely removes that liberty.
                        //    Does G have other internal liberties? No, we counted 1.
                        //    So yes, White playing at l1 captures G.
                        //    Is this a Ko?
                        //    Ko requires that the stone(s) captured by White (which is G) includes the stone E just played.
                        //    And usually |C| (captured by Black) == 1 and |G| (captured by White) == 1.
                        //    The problem says "提掉對方一顆子" (take one stone).
                        //    So we should enforce |C| == 1.
                        //    And the recapture must be taking back that specific interaction.
                        
                        // Refined Logic for "Ko" in this problem:
                        // 1. Black plays at E, captures exactly 1 White stone (at pos P).
                        // 2. After removal, the Black stone at E forms a group (maybe just E) that has exactly 1 liberty.
                        // 3. That single liberty must be P (the spot where the White stone was).
                        //    Why P? Because if the liberty is somewhere else, say Q, then White playing Q captures Black.
                        //    But is it "taking back"?
                        //    In a standard Ko, the shape is such that the only liberty of the new stone is the spot just vacated.
                        //    Example:
                        //      . B .
                        //      B W B
                        //      . B .
                        //      W has 1 lib? No, surrounded by B. Dead.
                        //      
                        //      Correct Ko shape:
                        //      . . . . .
                        //      . B W B .
                        //      . W . W .
                        //      . B W B .
                        //      . . . . .
                        //      Center is empty.
                        //      If Black plays center? No.
                        //      
                        //      Simplest Ko:
                        //      B W B
                        //      W . W
                        //      B W B
                        //      No.
                        //      
                        //      Let's trust the "1 stone captured, 1 liberty left which is the captured spot" heuristic.
                        //      Because if the liberty is elsewhere, it's not a "Ko" (repeating the exact previous board state).
                        //      Recapturing at P restores the board to the state before Black moved (White stone at P, Black stone at E gone).
                        //      If White captures at Q (not P), the board state is different.
                        
                        // Implementation:
                        // 1. Identify if placing 'O' at E captures exactly 1 'X' at P.
                        // 2. Simulate board: E='O', P='.'.
                        // 3. Find group of 'O' at E.
                        // 4. Count liberties. Must be exactly 1.
                        // 5. That liberty must be P.
                        // If all true, then (E) is a Ko point for Black.
                        // But the question asks: "哪些點正在發生打劫".
                        // It means points on the board where a Ko fight is happening.
                        // Usually the empty point involved in the Ko (the one you can't play immediately).
                        // Or the point where the stone was taken?
                        // "打劫，提子!!!" -> "Ko, take stone!"
                        // "你要隔一手才能吃" -> "You must wait one move to eat back".
                        // The point you cannot play is the liberty of the just-placed stone, which is the spot of the captured stone.
                        // So if Black just took White at P, the point P is the one White cannot play immediately.
                        // But the input is a static board. We are looking for configurations that ARE Ko.
                        // A Ko configuration on the board usually looks like:
                        // One stone (say Black) at E, surrounded by White, with only 1 liberty at P.
                        // And at P, there was just a White stone taken?
                        // No, the board shows the state AFTER a move? Or a general state?
                        // "判斷當前局棋有哪些點正在發生打劫"
                        // This implies the board is in a state where a Ko is active.
                        // Active Ko means: 
                        // There is a stone (A) that was just played, capturing a stone (B).
                        // Stone A has 1 liberty (the spot where B was).
                        // The opponent cannot play at that liberty immediately.
                        // So we are looking for an empty point P such that:
                        // If we assume the previous move was a capture at P...
                        // Actually, simpler: Look for a pattern where a single stone of color C at E
                        // is adjacent to an empty point P, and:
                        // 1. The stone at E has exactly 1 liberty (which is P).
                        // 2. The neighbors of E (other than P) are all opponent stones.
                        // 3. Those opponent stones form groups that would be captured if the opponent played at P?
                        //    No.
                        // Let's re-read the condition derived:
                        // "After taking a stone... opponent cannot immediately take back".
                        // This describes the prohibition.
                        // The "point where Ko is happening" is likely the empty point P that is forbidden to play.
                        // How to detect from static board?
                        // We look for an empty point P such that:
                        // If Black plays at P, he captures exactly 1 White stone (say at Q? No, captures around P).
                        // Wait, if P is empty, and it's a Ko, it means the PREVIOUS move captured a stone at P?
                        // No, if previous move captured at P, then P is now occupied by the capturing stone.
                        // So the "Ko point" (the forbidden one) is currently OCCUPIED?
                        // No, the forbidden move is to play at the spot where the stone was just taken.
                        // If Black took White at P, then P is now Black.
                        // White wants to play at P to take back. But P is occupied!
                        // You can't play on an occupied spot.
                        // Ah, the rule is: White cannot play at the liberty of the Black stone to capture it IF that returns the board to previous state.
                        // In the board state AFTER Black's move:
                        // - There is a Black stone at E.
                        // - It has 1 liberty at L.
                        // - If White plays at L, he captures the Black stone at E (and maybe others).
                        // - And importantly, the stone(s) captured by White must be exactly the stone(s) Black just placed?
                        //   And the stone(s) Black captured previously must be exactly the one White is placing?
                        //   Basically, |Captured by Black| = 1, |Captured by White| = 1.
                        //   And the net change is swapping one stone.
                        
                        // So, on the current board, we look for:
                        // An empty point L such that:
                        // 1. There is a single stone of color C adjacent to L (or a group connected to L?)
                        //    Actually, the stone that was just played is the one in atari.
                        //    Let's assume the stone at E (adjacent to L) is the one just played.
                        //    Color(E) = C.
                        //    Group(E) has exactly 1 liberty: L.
                        // 2. If Opponent plays at L, they capture Group(E).
                        //    (This is guaranteed if Group(E) has only 1 liberty L).
                        // 3. The capture by Opponent at L must involve capturing exactly 1 stone (the stone E, or group of size 1).
                        //    And also, the move by C at E (in the past) must have captured exactly 1 stone.
                        //    How do we know what happened in the past?
                        //    We infer: If Opponent plays at L, he captures E.
                        //    Before that, C played at E. What did C capture?
                        //    C playing at E must have captured the stone that is now... gone?
                        //    The spot where the captured stone was must be adjacent to E.
                        //    In a simple Ko, the shape is:
                        //       O
                        //     O X O
                        //       .  <- L
                        //    If Black (X) just played at X_pos, capturing a White stone at L? No.
                        //    If Black played at X_pos, and captured a White stone at ... where?
                        //    Standard Ko:
                        //      . B .
                        //      B W B
                        //      . B .
                        //      If White is at center, he has 0 libs. Dead.
                        //      
                        //      Real Ko:
                        //      B . B
                        //      . W .
                        //      B . B
                        //      No.
                        //      
                        //      Let's go with the definition:
                        //      A point L is a Ko point if:
                        //      - It is empty.
                        //      - Adjacent to exactly one stone of color C (call it S).
                        //      - The group containing S has exactly 1 liberty (which is L).
                        //      - The size of the group containing S is 1.
                        //      - The neighbors of S (other than L) are all opponent stones.
                        //      - Each of those opponent stones is part of a group that has EXACTLY 2 liberties, one of which is L?
                        //        No.
                        //      - If Opponent plays at L, he captures S. (True since S has 1 lib).
                        //      - Did S's placement capture something?
                        //        If S is at E, and neighbors are Opponent.
                        //        For S to have captured something, one of the neighbors must have had its last liberty at E.
                        //        So, among the neighbors of E (which are Opponent), at least one group must have had 1 liberty (which was E) before E was filled.
                        //        Currently, with E filled, those groups have liberties = (original libs - 1).
                        //        If original libs = 1, then current libs = 0 -> They are dead?
                        //        But the board is valid, so no dead stones left on board.
                        //        So the neighbors must have > 0 liberties currently.
                        //        This implies original libs >= 2.
                        //        So S did NOT capture anything?
                        //        Then it's not a Ko.
                        
                        //      Wait, if S captured a stone, that stone is REMOVED.
                        //      So the spot where the stone was removed is now EMPTY.
                        //      Let's say S is at E. It captured a stone at P.
                        //      So P is now empty.
                        //      Is P the same as L?
                        //      In a Ko, yes. The stone is taken, leaving an empty spot P.
                        //      The stone S at E has only 1 liberty, which is P.
                        //      So L = P.
                        //      So we are looking for an empty point L such that:
                        //      1. Adjacent to L is a single stone S (color C).
                        //      2. S has exactly 1 liberty (which is L).
                        //      3. The other neighbors of S are Opponent stones.
                        //      4. Among those neighbors, there is exactly one stone (or group) that, if we imagine putting a stone of color Opponent back at L, would have 1 liberty?
                        //         No.
                        //      Let's reverse:
                        //      Current state: Empty L. Neighbor S (single stone, color C). S has only lib L.
                        //      Other neighbors of S are Opponent (color O).
                        //      For this to be a Ko, the previous move must have been C playing at S, capturing an O stone at L.
                        //      If C played at S and captured O at L, then before that:
                        //         L was O. S was empty.
                        //         The O stone at L must have had 1 liberty (which was S).
                        //         So in current state, if we look at the neighbors of S (which are O), do they relate to L?
                        //         No, the captured stone was AT L. But L is now empty.
                        //         So we can't check the group at L because it's gone.
                        //         But we can check the surroundings.
                        //         If L was O, and it had 1 liberty (S), then all other neighbors of L must be C (Black).
                        //         So:
                        //         Check empty point L.
                        //         Check neighbors of L.
                        //         If neighbors of L are ALL color C, except possibly some '.'? No, must be surrounded to have low libs.
                        //         Specifically, if L was O and had 1 lib (S), then neighbors of L are {S, C, C, C} (in 4-neighbor grid).
                        //         So currently, neighbors of L are: One empty (S? No, S is occupied by C), and rest C.
                        //         Wait, S is the stone at some coordinate adjacent to L.
                        //         So neighbors of L are: S (which is C), and others (which must be C).
                        //         So all neighbors of L are C?
                        //         If all neighbors of L are C, then if we put O at L, it has 0 libs? Dead immediately.
                        //         That's suicide, not Ko.
                        //         Unless... one of the C neighbors is the one that was just played?
                        
                        //      Let's reconsider the standard Ko shape coordinates.
                        //      Grid:
                        //      (1,2) B
                        //      (0,1) B, (1,1) Empty(L), (2,1) B
                        //      (1,0) B
                        //      If White plays at (1,1), he is surrounded by B. Suicide.
                        //      UNLESS playing at (1,1) captures some B.
                        //      Which B? The one at (1,2)?
                        //      If B at (1,2) has only 1 liberty (which is (1,1)), then White playing at (1,1) captures B(1,2).
                        //      So condition:
                        //      L is empty.
                        //      Neighbors of L include some B stones.
                        //      At least one neighbor B_stone has exactly 1 liberty (which is L).
                        //      If White plays L, he captures that B_stone.
                        //      Is it Ko?
                        //      Only if the number of stones captured is 1, AND the previous move by Black captured 1 White stone at L.
                        //      How to verify "previous move captured 1 White at L"?
                        //      If Black captured White at L, then before that, L was White.
                        //      That White stone had 1 liberty (the spot where Black played).
                        //      Where did Black play? At one of the neighbors of L.
                        //      Let's say Black played at S (neighbor of L).
                        //      Then S is now Black.
                        //      And the White stone at L is gone.
                        //      For the White stone at L to have had 1 liberty (S), all other neighbors of L must be Black.
                        //      So:
                        //      1. L is empty.
                        //      2. All neighbors of L are Black (C), except one? No, if L was White and had 1 lib S, then neighbors of L are {S, B, B, B}.
                        //         So currently, neighbors of L are {S(B), B, B, B}. All are Black.
                        //      3. One of these Black neighbors (S) must be the one just played.
                        //         How to identify S?
                        //         S is the one that, if removed, makes the capture invalid?
                        //         Actually, if all neighbors are Black, and White plays L, White dies unless he captures.
                        //         He captures if some neighbor B has only 1 lib (L).
                        //         In a Ko, exactly ONE neighbor B has 1 lib (L). The others have more.
                        //         And that B is a single stone.
                        //         And if we assume that B was just played, did it capture L?
                        //         Yes, if L was White and surrounded by B (including the new B), then L had 1 lib (the new B's spot? No).
                        //         If L was White, and neighbors are B, B, B, B. Then L has 0 libs. Dead.
                        //         So L must have had 1 lib. That lib must be the spot where the new stone was played.
                        //         So if Black played at S, and S is a neighbor of L.
                        //         Before Black played, S was empty.
                        //         L (White) had neighbors: S(empty), B, B, B.
                        //         So L had 1 lib (S).
                        //         Black plays S. Now L has 0 libs. Captured. Removed.
                        //         Now board: S is Black, L is Empty.
                        //         Now, does S have 1 lib?
                        //         S's neighbors: L(empty), and others.
                        //         For Ko, S must have exactly 1 lib, which is L.
                        //         So all other neighbors of S must be White.
                        
                        //      Summary of conditions for L to be a Ko point (for White to recapture):
                        //      1. L is empty.
                        //      2. All 4 neighbors of L exist and are Black? (Assuming no edge cases for simplicity first, edges break Ko usually).
                        //         Actually, if on edge, fewer neighbors.
                        //         Condition: The neighbors of L that are on board must be Black. (Because if any is White or Empty, then the hypothetical White stone at L wouldn't be in atari or wouldn't have been captured).
                        //         Wait, if a neighbor is Empty, then White at L has a lib. Not captured.
                        //         If a neighbor is White, then White at L connects, maybe not captured.
                        //         So yes, all neighbors of L must be Black.
                        //      3. Exactly one neighbor of L (call it S) is a single-stone group of Black with exactly 1 liberty (which is L).
                        //      4. All other neighbors of L (if any) are Black groups with > 1 liberties.
                        //      5. Also, we need to ensure that the stone at S, if removed, leaves L as a valid move?
                        //         The condition "All neighbors of L are Black" ensures that if White plays L, he has 0 libs initially.
                        //         He survives only if he captures.
                        //         He captures S (since S has 1 lib L).
                        //         Does he capture others? No, condition 4 says others have >1 libs.
                        //         So he captures exactly S (size 1).
                        //         This matches the "take back 1 stone" requirement.
                        //         And the history check: "Did Black capture 1 stone at L?"
                        //         This is inferred from "All neighbors of L are Black".
                        //         If all neighbors are Black, then a White stone at L would have been surrounded (assuming no internal eyes, which 1-point space doesn't have).
                        //         Specifically, if L was White, and neighbors are Black, it had 0 libs?
                        //         Unless one neighbor was empty (S).
                        //         If S was empty, L had 1 lib.
                        //         Black played S -> Captured L.
                        //         This fits perfectly.
                        
                        //      Algorithm Finalized:
                        //      Iterate all empty points L.
                        //      Check neighbors of L.
                        //      Let neighbor colors be collected.
                        //      If any neighbor is '.' or 'W' (if checking for Black Ko), then skip.
                        //      Actually, we don't know who is attacking.
                        //      Case A: Black just played, White wants to recapture.
                        //         L is empty.
                        //         All neighbors of L are 'O' (Black).
                        //         Among neighbors, count how many are 'O' groups with size=1 and liberties=1 (which must be L).
                        //         If count == 1, then it's a Ko.
                        //      Case B: White just played, Black wants to recapture.
                        //         L is empty.
                        //         All neighbors of L are 'X' (White).
                        //         Among neighbors, count how many are 'X' groups with size=1 and liberties=1.
                        //         If count == 1, then it's a Ko.
                        
                        //      Note: "All neighbors" means all valid on-board neighbors.
                        //      If L is at corner, 2 neighbors. Both must be same color.
                        //      If L is at edge, 3 neighbors.
                        
                        //      Let's code this.
                        
                    }
                }
            }
        }
        
        // Re-implementing the loop properly inside solve
        
        vector<pair<int, int>> solutions;
        
        for(int r=0; r<N; ++r){
            for(int c=0; c<N; ++c){
                if(board[r][c] != '.') continue;
                
                int x = c + 1;
                int y = N - r;
                
                // Check for Ko involving this empty point (x, y)
                // Check Scenario 1: Neighbors are all 'O', one 'O' is in atari (size 1, lib 1)
                bool allO = true;
                bool allX = true;
                vector<pair<int,int>> neighs;
                
                for(int i=0; i<4; ++i){
                    int nr = r + dx[i];
                    int nc = c + dy[i];
                    if(isValid(nr, nc)){
                        char ch = board[nr][nc];
                        if(ch == '.') { allO = false; allX = false; }
                        else if(ch == 'X') { allO = false; }
                        else if(ch == 'O') { allX = false; }
                        neighs.push_back({nr, nc});
                    }
                }
                
                if(neighs.empty()) continue; // Should not happen for N>=5
                
                bool isKo = false;
                
                if(allO){
                    // Check if exactly one neighbor is a single stone with 1 liberty
                    int atariCount = 0;
                    for(auto p : neighs){
                        // Check group at p
                        // Optimization: if we visited this group already in this check? No, small N.
                        // Get group info
                        char color = 'O';
                        bool visited[20][20] = {false};
                        vector<pair<int,int>> q;
                        q.push_back(p);
                        visited[p.first][p.second] = true;
                        int head = 0;
                        int size = 0;
                        while(head < q.size()){
                            pair<int,int> cur = q[head++];
                            size++;
                            int cr = cur.first;
                            int cc = cur.second;
                            for(int k=0; k<4; ++k){
                                int tr = cr + dx[k];
                                int tc = cc + dy[k];
                                if(isValid(tr, tc) && board[tr][tc] == color && !visited[tr][tc]){
                                    visited[tr][tc] = true;
                                    q.push_back({tr, tc});
                                }
                            }
                        }
                        
                        if(size == 1){
                            // Count liberties
                            int libs = 0;
                            // Only neighbor is (r,c) which is '.'
                            // Check if there are other '.' neighbors for this stone
                            bool otherLib = false;
                            for(int k=0; k<4; ++k){
                                int tr = p.first + dx[k];
                                int tc = p.second + dy[k];
                                if(isValid(tr, tc)){
                                    if(board[tr][tc] == '.'){
                                        if(tr == r && tc == c) continue; // This is the current L
                                        otherLib = true;
                                        break;
                                    }
                                }
                            }
                            if(!otherLib) {
                                atariCount++;
                            }
                        }
                    }
                    if(atariCount == 1) isKo = true;
                }
                else if(allX){
                    int atariCount = 0;
                    for(auto p : neighs){
                        char color = 'X';
                        bool visited[20][20] = {false};
                        vector<pair<int,int>> q;
                        q.push_back(p);
                        visited[p.first][p.second] = true;
                        int head = 0;
                        int size = 0;
                        while(head < q.size()){
                            pair<int,int> cur = q[head++];
                            size++;
                            int cr = cur.first;
                            int cc = cur.second;
                            for(int k=0; k<4; ++k){
                                int tr = cr + dx[k];
                                int tc = cc + dy[k];
                                if(isValid(tr, tc) && board[tr][tc] == color && !visited[tr][tc]){
                                    visited[tr][tc] = true;
                                    q.push_back({tr, tc});
                                }
                            }
                        }
                        
                        if(size == 1){
                            bool otherLib = false;
                            for(int k=0; k<4; ++k){
                                int tr = p.first + dx[k];
                                int tc = p.second + dy[k];
                                if(isValid(tr, tc)){
                                    if(board[tr][tc] == '.'){
                                        if(tr == r && tc == c) continue;
                                        otherLib = true;
                                        break;
                                    }
                                }
                            }
                            if(!otherLib) {
                                atariCount++;
                            }
                        }
                    }
                    if(atariCount == 1) isKo = true;
                }
                
                if(isKo){
                    solutions.push_back({x, y});
                }
            }
        }
        
        cout << "Case " << caseNum++ << ":" << endl;
        if(solutions.empty()){
            cout << "Peace!!" << endl;
        } else {
            sort(solutions.begin(), solutions.end());
            for(auto p : solutions){
                cout << p.first << " " << p.second << endl;
            }
        }
    }
}

int main(){
    solve();
    return 0;
}
