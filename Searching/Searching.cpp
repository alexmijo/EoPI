#include <vector>
#include <iostream>

using namespace std;

// 12.1
// I did very well on this, getting the best solution very quickly and with nice code.
template <typename T>
int findFirst(vector<T> vec, T lookFor) {
    if (vec[0] == lookFor) {
        return 0;
    }
    int low = 0;
    int high = vec.size() - 1;
    while (high - low > 1) {
        int mid = low + (high - low) / 2;
        if (vec[mid] < lookFor) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (vec[high] == lookFor) {
        return high;
    }
    return -1;
}

int main() {
    vector<int> v1{-10, 0, 0, 0, 3, 4, 4, 25};
    cout << findFirst(v1, -10) << endl;
    cout << findFirst(v1, 0) << endl;
    cout << findFirst(v1, 3) << endl;
    cout << findFirst(v1, 4) << endl;
    cout << findFirst(v1, 25) << endl;

    cout << findFirst(v1, 26) << endl;
    cout << findFirst(v1, 5) << endl;
    cout << findFirst(v1, 2) << endl;
}