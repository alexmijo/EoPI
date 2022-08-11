#include <vector>
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

// 14.1
// It seems like I did an OK job on this one (O(n + m)), although I suppose the O(nlogm) solution
//  is better sometimes (large m small n), so I could've decided which algorithm to use depending on
//  if n + m > nlogm. Yeah the book didn't really do that deciding thing, but they did bassically
//  imply that I should've.
template <typename T>
vector<T> intersectionOfSortedArrays(const vector<T>& sorted1, const vector<T>& sorted2) {
    vector<T> result;
    int i2 = 0;
    const T *searchingFor;
    for (int i1 = 0; i1 < sorted1.size(); i1++) {
        if (i1 == 0 || sorted1[i1] != *searchingFor) {
            searchingFor = &(sorted1[i1]);
            while (i2 < sorted2.size()) {
                if (sorted2[i2] == *searchingFor) {
                    result.emplace_back(*searchingFor);
                    i2++;
                    break;
                } else if (sorted2[i2] > *searchingFor) {
                    break;
                }
                i2++;
            }
            if (i2 >= sorted2.size()) {
                break;
            }
        }
    }
    return result;
}

int main() {
    vector<int> sorted1 = {2, 3, 3, 5, 5, 6, 7, 7, 8, 12}; 
    vector<int> sorted2 = {5, 5, 6, 8, 8, 9, 10, 10}; 
    printVector(intersectionOfSortedArrays(sorted1, sorted2));
}