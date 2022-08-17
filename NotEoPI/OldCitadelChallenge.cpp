#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void printVector(const vector<T>& vector, const string& separator=" ") {
    for (const T element : vector) {
        // Trailing separator printed
        cout << element << separator;
    }
    cout << endl;
}

bool compareBidders(vector<long> bidder1, vector<long> bidder2) {
    if (bidder1[2] == bidder2[2]) {
        return bidder1[3] < bidder2[3];
    }
    return bidder1[2] > bidder2[2];
}

vector<long> didntGetShares(long numShares, vector<vector<long>> bidders) {
    // int numBidders = sizeof(bidders) / sizeof(bidders[0]);
    sort(bidders.begin(), bidders.end(), compareBidders);
    vector<long> result;
    int bidder = 0;
    while (bidder < bidders.size() && numShares > 0) {
        numShares -= bidders[bidder][1];
        bidder += 1;
    }
    while (bidder < bidders.size()) {
        result.emplace_back(bidders[bidder][0]);
        bidder++;
    }
    sort(result.begin(), result.end());
    return result;
}

int main() {
    vector<long> bidder1 = {1, 1, 4, 3};
    vector<long> bidder2 = {2, 10, 4, 2};
    vector<long> bidder3 = {3, 5, 30, 4};
    vector<long> bidder4 = {4, 1, 1, 1};
    vector<vector<long>> bidders = {bidder1, bidder2, bidder3, bidder4};
    printVector(didntGetShares(14, bidders));
}