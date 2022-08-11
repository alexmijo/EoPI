#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

using namespace std;

template <typename T>
void printVector(const vector<T>& vector, const string& separator=" ") {
    for (const T element : vector) {
        // Trailing separator printed
        cout << element << separator;
    }
    cout << endl;
}

// 13.1
// I did bad bassically cause I couldn't figure out how to return vector<vector<string>> without
//  unnecessarily copying every vector from the map to the return vector. Nvm see edit.
// Nvm, my solution actually had better asymptotic time than theirs and they had the same issue with
//  the copying.
// Edit: Nevermind, it turns out my solution was actually moving instead of copying, so that's
//  another way in which my code was better than the book's. So actually, I guess I did pretty good.
//  In an actual interview I think I would just do it the way that might create copies, and say that
//  there are maybe some unintentional copies here, but it'd be easy to test if that's actually
//  happening and fix it if I were in my code editor. Or at the end go back and try to remove
//  unnecessary copies.
// Actually, one thing I maybe could've done better is that, due to the 128 length vector, the
//  book's solution would've actually probably been faster for small words. So in an interview I
//  could at least mention that. I also wonder why sorted_string() doesn't use radix sort then, that
//  would actually make the book's solution just as good as mine for long words. Actually what I was
//  thinking of was counting sort, but the same principle applies for both. OK actually nvm it was
//  counting sort that I was thinking of. That's actually bassically just what I implement in
//  CharCounts. So it'd probably make the most sense to, in an interview, write
//  countingSortedString(string) and then define countingSortedString if I have time, or if they
//  really want me to define it and I don't have time to do counting sort, I could just define it
//  with std::sort(). I'd of course also have to make sure these were ascii strings first. If they
//  weren't, I actually don't know how I'd even get a correct solution just cause I've never dealt
//  with non-ascii strings before.
struct CharCounts {
    vector<int> counts;

    CharCounts(const string& phrase) : counts(128, 0) {
        for (char c : phrase) {
            counts[c] += 1;
        }
    }

    bool operator==(const CharCounts& that) const {
        return counts == that.counts;
    }
};

template <>
struct std::hash<CharCounts> {
    size_t operator()(const CharCounts& charCounts) const {
        size_t h = 17;
        hash<int> intHash;
        for (int count : charCounts.counts) {
            h = h * 31 + intHash(count);
        }
        return h;
    }
};

vector<vector<string>> anagramGroups(const vector<string>& phrases) {
    unordered_map<CharCounts, vector<string>> groupsMap;
    for (const string& phrase : phrases) {
        CharCounts phraseCharCounts(phrase);
        if (groupsMap.find(phraseCharCounts) == groupsMap.end()) {
            groupsMap[phraseCharCounts] = vector<string>{phrase};
        } else {
            groupsMap[phraseCharCounts].emplace_back(phrase);
        }
    }
    vector<vector<string>> groupsVector;
    // Cannot have const auto& groupPair since that'd cause copies to occur rather than moves.
    // The original iterator way I did it (commented out below) also works for moving instead of
    //  copying.
    for (auto& groupPair : groupsMap) {
        if (groupPair.second.size() > 1) {
            // This does actually move the vector, even though it says "second is a copy of the
            //  second object".
            groupsVector.emplace_back(move(groupPair.second));
            // The following two lines are just what I used to verify a copy wasn't happening.
            // printVector(groupPair.second);
            // printVector(groupsMap[groupPair.first]);
        }
    }
    // for (auto it = groupsMap.begin(); it != groupsMap.end(); it++) {
    //     if (it->second.size() > 1) {
    //         // This does actually move the vector, even though it says "second is a copy of the
    //         //  second object".
    //         groupsVector.emplace_back(move(it->second));
    //         // The following two lines are just what I used to verify a copy wasn't happening.
    //         printVector(it->second);
    //         printVector(groupsMap[it->first]);
    //     }
    // }
    return groupsVector;
}

int main() {
    vector<string> phrases = {"alex", "smalex", "alexs", "alex's", "aabba", "abbaa", "abbba",
                              "babab", "babab3", "alexsm", "ababa"};
    for (vector<string> groupOfAnagrams : anagramGroups(phrases)) {
        printVector(groupOfAnagrams);
    }
}