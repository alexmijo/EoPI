#include <memory>
#include <iostream>

using namespace std;

template <typename T>
struct BinaryTreeNode {
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

// 10.1
// I got the best solution (edit: not really, see below). Took too long just cause I wasn't going
//  fast and was looking up stuff, but I would've been fine time-wise in an actual interview.
// My code was very similar to theirs (and I had thought of the whole -1 thing too, but decided
//  against it, and I don't think that was a terrible decision). Theirs was a little nicer mainly
//  because of that, but also because they used tie(). Since I wanna have some tie() usage to look
//  back at, I copied treeIsBalancedAndHeight() to treeIsBalancedAndHeight2() and then made it use
//  tie() instead there.
// Actually, there was one optimization they thought of that I didn't, which would probably
//  actually make a quite significant difference in practice. They terminated as soon as the first
//  unbalanced tree was found (or at least, I should've). I shoulda thought of that.
// The bugs in my code weren't really a big deal (in an interview) IMO although they were kinda hard
//  to debug.
template <typename T>
bool treeIsBalanced(const unique_ptr<BinaryTreeNode<T>>& tree) {
    return treeIsBalancedAndHeight2(tree).first;
}

template <typename T>
pair<bool, int> treeIsBalancedAndHeight(const unique_ptr<BinaryTreeNode<T>>& tree) {
    bool isBalanced;
    int height;
    if (tree->left && tree->right) {
        pair<bool, int> leftTreeInfo = treeIsBalancedAndHeight(tree->left);
        bool leftBalanced = leftTreeInfo.first;
        int leftHeight = leftTreeInfo.second;
        pair<bool, int> rightTreeInfo = treeIsBalancedAndHeight(tree->right);
        bool rightBalanced = rightTreeInfo.first;
        int rightHeight = rightTreeInfo.second;
        isBalanced = leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
        height = max(leftHeight, rightHeight) + 1;
    } else if (tree->left) {
        pair<bool, int> leftTreeInfo = treeIsBalancedAndHeight(tree->left);
        int leftHeight = leftTreeInfo.second;
        isBalanced = (leftHeight == 0);
        height = leftHeight + 1;
    } else if (tree->right) {
        pair<bool, int> rightTreeInfo = treeIsBalancedAndHeight(tree->right);
        int rightHeight = rightTreeInfo.second;
        isBalanced = (rightHeight == 0);
        height = rightHeight + 1;
    } else {
        isBalanced = true;
        height = 0;
    }
    return pair<bool, int>(isBalanced, height);
}

template <typename T>
pair<bool, int> treeIsBalancedAndHeight2(const unique_ptr<BinaryTreeNode<T>>& tree) {
    bool isBalanced;
    int height;
    bool leftBalanced;
    int leftHeight;
    bool rightBalanced;
    int rightHeight;
    if (tree->left && tree->right) {
        tie(leftBalanced, leftHeight) = treeIsBalancedAndHeight(tree->left);
        tie(rightBalanced, rightHeight) = treeIsBalancedAndHeight(tree->right);
        isBalanced = leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
        height = max(leftHeight, rightHeight) + 1;
    } else if (tree->left) {
        tie(leftBalanced, leftHeight) = treeIsBalancedAndHeight(tree->left);
        isBalanced = (leftHeight == 0);
        height = leftHeight + 1;
    } else if (tree->right) {
        tie(rightBalanced, rightHeight) = treeIsBalancedAndHeight(tree->right);
        isBalanced = (rightHeight == 0);
        height = rightHeight + 1;
    } else {
        isBalanced = true;
        height = 0;
    }
    return pair<bool, int>(isBalanced, height);
}

int main() {
    auto notBalancedLeaf1 = make_unique<BinaryTreeNode<int>>();
    auto notBalancedMid1 = make_unique<BinaryTreeNode<int>>();
    notBalancedMid1->left = move(notBalancedLeaf1);
    auto notBalancedMid2 = make_unique<BinaryTreeNode<int>>();
    notBalancedMid2->right = move(notBalancedMid1);
    auto notBalancedLeaf2 = make_unique<BinaryTreeNode<int>>();
    auto notBalancedMid3 = make_unique<BinaryTreeNode<int>>();
    notBalancedMid3->left = move(notBalancedLeaf2);
    auto notBalancedMid4 = make_unique<BinaryTreeNode<int>>();
    notBalancedMid4->right = move(notBalancedMid3);
    auto notBalanced = make_unique<BinaryTreeNode<int>>();
    notBalanced->left = move(notBalancedMid2);
    notBalanced->right = move(notBalancedMid4);

    cout << (treeIsBalanced(notBalanced) ? "true" : "false") << endl;

    // Now notBalanced will become balanced.
    auto notBalancedLeaf3 = make_unique<BinaryTreeNode<int>>();
    notBalanced->left->left = move(notBalancedLeaf3);
    auto notBalancedLeaf4 = make_unique<BinaryTreeNode<int>>();
    notBalanced->right->left = move(notBalancedLeaf4);

    cout << (treeIsBalanced(notBalanced) ? "true" : "false") << endl;

    // And unbalanced again.
    notBalanced->right.reset();

    cout << (treeIsBalanced(notBalanced) ? "true" : "false") << endl;
}