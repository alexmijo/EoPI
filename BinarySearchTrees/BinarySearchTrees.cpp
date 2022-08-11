#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct BSTNode {
    T data;
    unique_ptr<BSTNode<T>> left, right;
};

// 15.1
// Stupidly had the wrong idea at first so I took too long, otherwise fine.
// Edit: Nvm, had another stupidly wrong idea, so that wasted more time.
// Edit: Nvm again, it didn't work and I'm not sure why.
// Edit: Figured out why it didn't work, not sure if I could've figured that out in an interview
//  with manual testing or not.
// Yeah so I'm not really sure exactly how to judge this since it was just little errors, but not
//  good, not too terrible.
// Their code was a bit nicer than mine as well, since they dealt with ranges using parameters, not
//  return values.
// I should at least feel good about coming up with one of their two good algorithms though (even
//  though that part wasn't particularly hard).
// Edit: Actually, I didn't come up with their best algorithm, although I'm not convinced it's
//  really better, since on some types of inputs it's slower and on some it's faster. OK actually
//  I don't really think they were saying it's strictly better (is also takes O(n) worst case extra
//  space as well), just showing how to make it BFS, which does have some advantages.
template <typename T>
struct IsBSTAndRange {
    bool isBST;
    T low, high;
};

// Returns isBST and (if isBST is true) highest and lowest data in tree
template <typename T>
IsBSTAndRange<T> isBSTHelper(const unique_ptr<BSTNode<T>>& tree) {
    T low = tree->data, high = tree->data;
    if (tree->left) {
        IsBSTAndRange<T> left = isBSTHelper(tree->left);
        if (!(left.isBST && left.high <= tree->data)) {
            return IsBSTAndRange<T>{false, tree->data, tree->data};
        }
        low = left.low;
    }
    if (tree->right) {
        IsBSTAndRange<T> right = isBSTHelper(tree->right);
        if (!(right.isBST && tree->data <= right.low)) {
            return IsBSTAndRange<T>{false, tree->data, tree->data};
        }
        high = right.high;
    }
    return IsBSTAndRange<T>{true, low, high};
}

template <typename T>
bool isBST(const unique_ptr<BSTNode<T>>& tree) {
    return isBSTHelper(tree).isBST;
}

int main() {
    // Names don't make much sense since I copied from BinaryTrees.cpp
    auto notBalancedLeaf1 = make_unique<BSTNode<int>>();
    notBalancedLeaf1->data = 10;
    auto notBalancedMid1 = make_unique<BSTNode<int>>();
    notBalancedMid1->left = move(notBalancedLeaf1);
    notBalancedMid1->data = 11;
    auto notBalancedMid2 = make_unique<BSTNode<int>>();
    notBalancedMid2->right = move(notBalancedMid1);
    notBalancedMid2->data = 9;
    auto notBalancedLeaf2 = make_unique<BSTNode<int>>();
    notBalancedLeaf2->data = 13;
    auto notBalancedMid3 = make_unique<BSTNode<int>>();
    notBalancedMid3->left = move(notBalancedLeaf2);
    notBalancedMid3->data = 14;
    auto notBalancedMid4 = make_unique<BSTNode<int>>();
    notBalancedMid4->right = move(notBalancedMid3);
    notBalancedMid4->data = 12;
    auto notBalanced = make_unique<BSTNode<int>>();
    notBalanced->left = move(notBalancedMid2);
    notBalanced->right = move(notBalancedMid4);
    notBalanced->data = 12;

    cout << (isBST(notBalanced) ? "true" : "false") << endl;

    // Now notBalanced will become not a BST.
    auto notBalancedLeaf3 = make_unique<BSTNode<int>>();
    notBalancedLeaf3->data = 10;
    notBalanced->left->left = move(notBalancedLeaf3);

    cout << (isBST(notBalanced) ? "true" : "false") << endl;

    // And a BST again.
    notBalanced->left->left->data = 1;

    cout << (isBST(notBalanced) ? "true" : "false") << endl;
}