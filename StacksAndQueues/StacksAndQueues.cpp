#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

// 9.1
// I achieved amortized O(1) time, so I did good, just took too long mainly cause I was looking up
//  exception stuff. If I wanna know about <stack>, this link is good:
//  https://stackoverflow.com/questions/8785841/what-is-the-major-difference-between-a-vector-and-a-stack
// I would actually even say my code was nicer than theirs! I also believe it likely uses slightly
//  less memory!
// One thing I definitely still need to do is practice <stack>, queue and dequeue.
template <typename T>
class StackWithMax {
private:
    vector<T> values;
    // Indexes of elements which are larger than all preceding elements.
    vector<int> indicesOfMaxesSoFar;

public:
    T max() {
        if (!values.empty()) {
            return values[indicesOfMaxesSoFar.back()];
        } else {
            throw length_error("max(): Stack is empty");
        }
    }

    T pop() {
        if (!values.empty()) {
            T popped = values.back();
            values.pop_back();
            if (indicesOfMaxesSoFar.back() >= values.size()) {
                indicesOfMaxesSoFar.pop_back();
            }
            return popped;
        } else {
            throw length_error("pop(): Stack is empty.");
        }
    }

    void push(T newValue) {
        if (values.empty() || newValue > max()) {
            indicesOfMaxesSoFar.push_back(values.size());
        }
        values.push_back(newValue);
    }
};

void testStackWithMax () {
    StackWithMax<int> testStack;
    testStack.push(1);
    cout << testStack.max() << endl;
    testStack.push(3);
    cout << testStack.max() << endl;
    testStack.push(2);
    cout << testStack.max() << endl;
    testStack.push(5);
    cout << testStack.max() << endl;
    testStack.push(4);
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.max() << endl;
    testStack.push(6);
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
    cout << testStack.max() << endl;
    cout << testStack.pop() << endl;
}

int main() {
    testStackWithMax();
}