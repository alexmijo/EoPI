#include <iostream>

using namespace std;

int charToRepresentedInt(char c) {
    int difference = '0';
    return c - difference;
}

//--------------------------------------------------------------------------------------------------
// 7.1
// stringToInt was fine, messed up intToString although I might've caught it with hand testing. Need
//  to figure out how to append to beggining of strings efficiently (and also maybe how to append to
//  the end of strings efficiently).
int stringToInt(const string& str) {
    const int base = 10;
    int baseToPower = 1;
    int value = 0;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str.at(i) == '-') {
            value = -value;
            break;
        }
        value += baseToPower * charToRepresentedInt(str.at(i));
        baseToPower *= base;
    }
    return value;
}

string intToString(int integer) {
    const int base = 10;
    string returnString = "";
    bool wasNegative = integer < 0;
    if (wasNegative) {
        integer = -integer;
    }
    do {
        returnString.insert(0, 1, (char)((integer % base) + '0'));
        integer /= base;
    } while (integer > 0);
    if (wasNegative) {
        returnString.insert(0, "-");
    }
    return returnString;
}
//--------------------------------------------------------------------------------------------------

int main() {
    // std::string aa = "aa";
    // std::string ab = "ab";

    // std::cout << (aa.compare(ab)) << std::endl;
    // std::cout << (aa.compare(aa)) << std::endl;
    // std::cout << (ab.compare(ab)) << std::endl;
    // std::cout << (ab.compare(aa)) << std::endl;

    cout << stringToInt("45") << endl;
    cout << stringToInt("5") << endl;
    cout << stringToInt("-5") << endl;
    cout << stringToInt("-545") << endl;

    cout << intToString(45) << endl;
    cout << intToString(5) << endl;
    cout << intToString(-5) << endl;
    cout << intToString(-545) << endl;
}