#include <iostream>
#include <math.h>

template <typename T>
void printBits(T x) {
    int numBits = sizeof(T) * 8;
    int bits[numBits];
    for (int i = 0; i < numBits; i++) {
        bits[numBits - i - 1] = (x & 1);
        x >>= 1;
    }
    for (int i = 0; i < numBits; i++) {
        std::cout << bits[i];
    }
    std::cout << std::endl;
}

// O(n), where n is the length of the integer
int numberOfOneBits1(int x) {
    int numOnes = 0;
    for (int i = 0; i < sizeof(int) * 8; i++) {
        numOnes += x & 1;
        x >>= 1;
    }
    return numOnes;
}

template <typename T>
// O(s), where s is the number of bits set to 1 in x
int numberOfOneBits2(T x) {
    int numOnes = 0;
    while (x != 0) {
        numOnes++;
        x &= x - 1;
        // alternative
        // x ^= x & ~(x-1);
    }
    return numOnes;
}

int rightPropogate(int x) {
    if (x == 0) {
        return x;
    }
    return x | (x - 1);
}

int moduloPowerOfTwo(int x, int power) {
    return x - ((x >> power) << power);
}

bool isPowerOfTwo(int x) {
    if (x <= 0) {
        return false;
    }
    return (x & (x - 1)) == 0;
}

const int TWO_TO_THE_SIXTEENTH = 65536;
char* parityArray;

// 5.1
// I didn't get the best solution, although I understood it right away and would've thought of it if
//  I had an xor hint I think.
int parity(unsigned long x) {
    // Check long is 64 bits and short is 16 bits
    static bool parityArrayInitialized = false;
    if (!parityArrayInitialized) {
        parityArray = new char[TWO_TO_THE_SIXTEENTH];
        for (unsigned int i = 0; i < TWO_TO_THE_SIXTEENTH; i++) {
            parityArray[i] = (numberOfOneBits2(i) % 2 == 0) ? 0 : 1;
        }
        // std::cout << "Hi!" << std::endl;
        parityArrayInitialized = true;
    }
    int parity = 0;
    for (int i = 0; i < 64 / 16; i++) {
        parity += parityArray[(unsigned short)x];
        x >>= 16;
    }
    return parity;
}

int main() {
    printBits(0);
    printBits(rightPropogate(0));
    std::cout << numberOfOneBits1(0) << std::endl;
    std::cout << numberOfOneBits2(0) << std::endl;
    printBits(1);
    printBits(rightPropogate(1));
    std::cout << numberOfOneBits1(1) << std::endl;
    std::cout << numberOfOneBits2(1) << std::endl;
    printBits(2);
    printBits(rightPropogate(2));
    std::cout << numberOfOneBits1(2) << std::endl;
    std::cout << numberOfOneBits2(2) << std::endl;
    printBits(3);
    printBits(rightPropogate(3));
    std::cout << numberOfOneBits1(3) << std::endl;
    std::cout << numberOfOneBits2(3) << std::endl;
    printBits(-1);
    printBits(rightPropogate(-1));
    std::cout << numberOfOneBits1(-1) << std::endl;
    std::cout << numberOfOneBits2(-1) << std::endl;
    printBits(371288);
    printBits(rightPropogate(371288));
    std::cout << moduloPowerOfTwo(77, 6) << std::endl;
    std::cout << (isPowerOfTwo(0) ? "true" : "false") << std::endl;
    std::cout << (isPowerOfTwo(1) ? "true" : "false") << std::endl;
    std::cout << (isPowerOfTwo(2) ? "true" : "false") << std::endl;
    std::cout << (isPowerOfTwo(3) ? "true" : "false") << std::endl;
    std::cout << (isPowerOfTwo(4) ? "true" : "false") << std::endl;
    std::cout << (isPowerOfTwo(-1) ? "true" : "false") << std::endl;

    int a = -2;
    short b = a;
    printBits(a);
    printBits(b);
    printBits((short)a);
    printBits(a & b);
    printBits(b & a);
    printBits((long)a);

    std::cout << parity(0) << std::endl;
    std::cout << parity(1) << std::endl;
    std::cout << parity(2) << std::endl;
    std::cout << parity(3) << std::endl;
    std::cout << parity(4) << std::endl;
    std::cout << parity(-1) << std::endl;
    std::cout << parity(-2) << std::endl;
    printBits((unsigned long)-1);
    printBits((unsigned long)-2);
    printBits(((unsigned long)-2) >> 16);
    delete[] parityArray;
}