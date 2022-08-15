#include <iostream>

using namespace std;

// 16.1
// I quickly solved this since I already knew how to. I like my solution better than theirs even
//  though they're essentially the same thing, just cause they unnecessarily actually represented
//  the stacks.
void towerOfHanoi(int numRings, int startPeg=1, int endPeg=2) {
    if (numRings == 0) {
        return;
    }
    // The peg that is neither startPeg nor endPeg
    int otherPeg = 1 + 2 + 3 - startPeg - endPeg;
    towerOfHanoi(numRings - 1, startPeg, otherPeg);
    cout << startPeg << "->" << endPeg << "\n";
    towerOfHanoi(numRings - 1, otherPeg, endPeg);
}

int main() {
    towerOfHanoi(1);
    cout << endl;
    towerOfHanoi(2);
    cout << endl;
    towerOfHanoi(3);
    cout << endl;
    towerOfHanoi(4);
    cout << endl;
    towerOfHanoi(5);
    cout << endl;
}