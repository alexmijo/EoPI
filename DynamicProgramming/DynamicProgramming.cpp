#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 17.1
// I got the best solution in a fairly good amount of time. Their code was slightly nicer than mine,
//  or at least shorter, but it's possible mine is more easily understandable so actually idek.
//  Regardless, I did well on this problem.
// Edit: Actually nevermind, my solution was O(s^2n) I think (but they're saying it's O(sn^2)? I
//  really don't understand that), theirs was O(sn). I changed mine using the insight from their
//  O(sn) solution in the better versions to make mine O(sn) as well.
// So in reality, while I didn't do particularly well, I didn't do super poorly either.
// Edit2: Testing seems to confirm my original implementation was O(s^2n), not O(sn).
// Yeah I definitely did not get the best solution even in practice at all (until I improved it,
//  which required seeing the answer).
// This doubled work would've probably been easier to see if I had done it the non-memoized way, but
//  I'm not actually really sure.
// There is another speedup I thought of afterwards (mod operator for single play) but it's not
//  asymptotically faster so I didn't bother.
int numScoreCombinationsWithCache(int totalScore, const vector<int>& playScores, int removedPlays,
                                  vector<unordered_map<int, int>>& cache) {
    if (totalScore == 0) {
        return 1;
    }
    if (removedPlays == playScores.size()) {
        return 0;
    }
    if (cache[removedPlays].find(totalScore) != cache[removedPlays].end()) {
        return cache[removedPlays][totalScore];
    }
    int result = 0;
    while (totalScore >= 0) {
        result += numScoreCombinationsWithCache(totalScore, playScores, removedPlays + 1, cache);
        totalScore -= playScores[removedPlays];
    }
    cache[removedPlays][totalScore] = result;
    return result;
}

int numScoreCombinations(int totalScore, const vector<int>& playScores) {
    vector<unordered_map<int, int>> cache(playScores.size());
    return numScoreCombinationsWithCache(totalScore, playScores, 0, cache);
}

int betterNumScoreCombinationsWithCache(int totalScore, const vector<int>& playScores,
                                        int removedPlays, vector<unordered_map<int, int>>& cache) {
    if (totalScore == 0) {
        return 1;
    }
    if (totalScore < 0 || removedPlays == playScores.size()) {
        return 0;
    }
    if (cache[removedPlays].find(totalScore) != cache[removedPlays].end()) {
        return cache[removedPlays][totalScore];
    }
    cache[removedPlays][totalScore] = 
        betterNumScoreCombinationsWithCache(totalScore, playScores, removedPlays + 1, cache) + 
        betterNumScoreCombinationsWithCache(totalScore - playScores[removedPlays], playScores, 
                                            removedPlays, cache);
    return cache[removedPlays][totalScore];
}

int betterNumScoreCombinations(int totalScore, const vector<int>& playScores) {
    vector<unordered_map<int, int>> cache(playScores.size());
    return betterNumScoreCombinationsWithCache(totalScore, playScores, 0, cache);
}

int main() {
    cout << betterNumScoreCombinations(100000, vector<int>{2, 3, 6, 7, 8}) << endl;
    cout << numScoreCombinations(12, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(7, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(2, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(3, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(1, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(50, vector<int>{2, 3, 7}) << endl;
    cout << numScoreCombinations(500, vector<int>{2, 3, 7}) << endl;
    // Not instant
    cout << numScoreCombinations(5000, vector<int>{2, 3, 7}) << endl;
    cout << endl;

    cout << betterNumScoreCombinations(12, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(7, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(2, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(3, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(1, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(50, vector<int>{2, 3, 7}) << endl;
    cout << betterNumScoreCombinations(500, vector<int>{2, 3, 7}) << endl;
    // Instant
    cout << betterNumScoreCombinations(5000, vector<int>{2, 3, 7}) << endl;
    cout << endl << endl;

    // Takes a bit
    cout << numScoreCombinations(500, vector<int>{2, 3, 6, 7, 8}) << endl;
    // Takes too long
    // cout << numScoreCombinations(5000, vector<int>{2, 3, 6, 7, 8}) << endl;
    cout << endl;

    // Instant
    cout << betterNumScoreCombinations(500, vector<int>{2, 3, 6, 7, 8}) << endl;
    // Instant
    cout << betterNumScoreCombinations(5000, vector<int>{2, 3, 6, 7, 8}) << endl;
}