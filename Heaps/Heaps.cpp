#include <vector>
#include <queue>
#include <iostream>

using namespace std;

template <typename T>
void printVector(const vector<T>& vector, const string& separator=" ") {
    for (const T element : vector) {
        // Trailing separator printed
        cout << element << separator;
    }
    cout << endl;
}

// 11.1
// This one was weird cause it was just C++ stuff which I couldn't figure out and needed to look in
//  the book for (namely, how to deal with figuring out if an iterator has reached the end of its
//  vector). So I'm not really sure how to judge how well I did. I could've done it a different way
//  but I didn't since I knew it'd be possible to do it this way and I was lazy. So yeah just hard
//  to judge.
// OK after thinking about it more, I did bad, but only due to lack of C++ knowledge.
// It seems like they just always use emplace instead of push, so I will too.
template<typename T>
struct VectorIteratorForMinHeap {
    typename vector<T>::const_iterator iterator;
    typename vector<T>::const_iterator end;

    VectorIteratorForMinHeap(
        const typename vector<T>::const_iterator& iterator, 
        const typename vector<T>::const_iterator& end) : iterator(iterator), end(end) {}

    bool operator<(const VectorIteratorForMinHeap<T>& that) const {
        return *iterator > *(that.iterator);
    }
};

template <typename T>
vector<T> mergeSortedSequences(const vector<vector<T>>& sortedSequences) {
    priority_queue<VectorIteratorForMinHeap<T>> smallestLeftFromEachSequence;
    for (const vector<T>& sequence : sortedSequences) {
        if (!sequence.empty()) {
            smallestLeftFromEachSequence.emplace(sequence.begin(), sequence.end());
        }
    }

    vector<T> merged;
    while (!smallestLeftFromEachSequence.empty()) {
        VectorIteratorForMinHeap<T> smallestLeft = smallestLeftFromEachSequence.top();
        smallestLeftFromEachSequence.pop();
        merged.emplace_back(*(smallestLeft.iterator));
        smallestLeft.iterator++;
        if (smallestLeft.iterator != smallestLeft.end) {
            smallestLeftFromEachSequence.emplace(smallestLeft);
        }
    }
    return merged;
}

int main() {
    vector<vector<int>> sortedSequences;
    sortedSequences.emplace_back(vector<int>{1, 2, 5, 6, 10, 11});
    sortedSequences.emplace_back(vector<int>{3, 4, 5, 6, 10, 12});
    sortedSequences.emplace_back(vector<int>{5, 6, 7, 8, 10, 13});
    sortedSequences.emplace_back(vector<int>{-10, -9, 0});

    printVector(mergeSortedSequences(sortedSequences));
}