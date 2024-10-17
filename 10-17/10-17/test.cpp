#include<iostream>
#include<vector>
using namespace std;
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
}; //
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//将一个 二叉搜索树 就地转化为一个 已排序的双向循环链表 。
void treeToDoublyList(Node* cur, Node*& prev)
{
    if (cur == nullptr)
        return;
    treeToDoublyList(cur->left, prev);
    cur->left = prev;
    if (prev)
        prev->right = cur;
    prev = cur;
    treeToDoublyList(cur->right, prev);

}
Node* treeToDoublyList(Node* root) {
    if (root == nullptr)
        return nullptr;
    Node* prev = nullptr;
    treeToDoublyList(root, prev);
    while (root->left)
    {
        root = root->left;
    }
    root->left = prev;
    prev->right = root;
    return root;
}
//前序中序数组构建二叉树
TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder, int& prei, int inbegin, int inend)
{
    if (inend < inbegin)
        return nullptr;
    TreeNode* newNode = new TreeNode(preorder[prei]);
    int rooti = inbegin;
    while (inbegin <= inend)
    {
        if (inorder[rooti] == preorder[prei])
            break;
        rooti++;
    }
    prei++;
    newNode->left = buildTree1(preorder, inorder, prei, inbegin, rooti - 1);
    newNode->right = buildTree1(preorder, inorder, prei, rooti + 1, inend);
    return newNode;
}
TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
    int prei = 0;
    return buildTree1(preorder, inorder, prei, 0, inorder.size() - 1);
}
//中序后序数组构建二叉树
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int inBegin, int inEnd, int& posti)
{
    if (inBegin > inEnd)
        return nullptr;
    TreeNode* newNode = new TreeNode(postorder[posti]);
    int rooti = inBegin;
    while (rooti <= inEnd)
    {
        if (inorder[rooti] == postorder[posti])
            break;
        ++rooti;
    }
    --posti;
    newNode->right = buildTree(inorder, postorder, rooti + 1, inEnd, posti);
    newNode->left = buildTree(inorder, postorder, inBegin, rooti - 1, posti);
    return newNode;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int posti = postorder.size() - 1;
    return buildTree(inorder, postorder, 0, inorder.size() - 1, posti);
}
int main()
{
    return 0;
}