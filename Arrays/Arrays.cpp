#include <iostream>
#include <array>
#include <float.h>

template <typename T>
void printArray(const T array[], const int length, const std::string& separator=" ") {
    for (int i = 0; i < length - 1; i++) {
        std::cout << array[i] << separator;
    }
    std::cout << array[length - 1] << std::endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 6.1
// Did get an O(n) in place solution, but only cause I could test and debug not on paper. Also took
//  me about an hour. Probably (but not definitely) would've believed my initial wrong solution was
//  actually correct. It is interesting though that my solution wasn't one of the ones in the book.
void partition(int array[], int length, int i) {
    int endOfMiddle = length - 1;
    int startOfMiddle = 0;
    int pivot = array[i];
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (i == j) {
            std::cout << "j ";
        } else {
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
    printArray(array, length);
    for (int i = 0; i < length; i++) {
        if (i == startOfMiddle && i == endOfMiddle) {
            std::cout << "b ";
        } else if (i == startOfMiddle) {
            std::cout << "s ";
        } else if (i == endOfMiddle) {
            std::cout << "e ";
        } else {
            std::cout << "  ";
        }
    }
    std::cout << std::endl << std::endl;
    while (j <= endOfMiddle) {
        if (array[j] < pivot) {
            swap(array[startOfMiddle], array[j]);
            startOfMiddle++;
        } else if (array[j] > pivot) {
            swap(array[j], array[endOfMiddle]);
            endOfMiddle--;
        }
        if ((j < startOfMiddle && array[j] < pivot) || (j >= startOfMiddle && j <= endOfMiddle && array[j] == pivot)) {
            j++;
        }
        for (int i = 0; i < length; i++) {
            if (i == j) {
                std::cout << "j ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
        printArray(array, length);
        for (int i = 0; i < length; i++) {
            if (i == startOfMiddle && i == endOfMiddle) {
                std::cout << "b ";
            } else if (i == startOfMiddle) {
                std::cout << "s ";
            } else if (i == endOfMiddle) {
                std::cout << "e ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl << std:: endl;
    }
}

// 6.7
// Got the best solution, O(n) time, O(1) space, although it did tell us this solution in the
//  beginning of the book after all, lol. They did use const vector<double>& though, so I
//  should do that in the future. Also, using namespace std;
double maxProfit(double prices[], int length) {
    // double profit = -DBL_MAX;
    // Actually, I am presuming that it is possible to buy and then sell the stock at the same price
    double maxProfitSoFar = 0;
    double minPriceSoFar = DBL_MAX;
    for (int i = 0; i < length; i++) {
        if (prices[i] < minPriceSoFar) {
            minPriceSoFar = prices[i];
        } else if (prices[i] - minPriceSoFar > maxProfitSoFar) {
            maxProfitSoFar = prices[i] - minPriceSoFar;
        }
    }
    return maxProfitSoFar;
}

int main() {
    const int length = 10;
    double array[length] = {310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    printArray(array, length);

    std::cout << maxProfit(array, length) << std::endl;

    // std::cout << "pivot = array[3]" << std::endl;
    // partition(array, length, 3);
    // printArray(array, length);
}