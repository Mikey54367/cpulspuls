#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//ǰ��ǵݹ����
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty())
    {
        while (cur)
        {
            ret.push_back(cur->val);
            st.push(cur);
            cur = cur->left;
        }
        TreeNode* tmp = st.top();
        st.pop();
        cur = tmp->right;
    }
    return ret;
}
//����ǵݹ����
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty())
    {
        while (cur)
        {
            //ret.push_back(cur->val);
            st.push(cur);
            cur = cur->left;
        }
        TreeNode* tmp = st.top();
        st.pop();
        ret.push_back(tmp->val);
        cur = tmp->right;
    }
    return ret;
}
//����ǵݹ����
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    TreeNode* prev = nullptr;
    while (cur || !st.empty())
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }
        TreeNode* tmp = st.top();
        if (tmp->right == nullptr || tmp->right == prev)
        {
            ret.push_back(tmp->val);
            prev = tmp;
            st.pop();
        }
        else
        {
            cur = tmp->right;
        }
    }
    return ret;
}
//����Ĺ�������
bool GetPath(TreeNode* root, TreeNode* target, stack<TreeNode*>& st)
{
    if (root == nullptr)
        return false;
    if (root == target)
    {
        st.push(root);
        return true;
    }
    st.push(root);
    if (GetPath(root->left, target, st) || GetPath(root->right, target, st))
    {
        return true;
    }
    else
    {
        st.pop();
        return false;
    }
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == p || root == q)
        return root;
    stack<TreeNode*> stP;
    stack<TreeNode*> stQ;
    GetPath(root, p, stP);
    GetPath(root, q, stQ);
    while (stP.size() > stQ.size())
    {
        stP.pop();
    }
    while (stP.size() < stQ.size())
        stQ.pop();
    while (stP.top() != stQ.top())
    {
        stP.pop();
        stQ.pop();
    }
    return stP.top();
}
//�������
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> vv;
    if (root == nullptr)
        return vv;
    queue<TreeNode*> q;
    q.push(root);
    int levelSize = 1;

    while (!q.empty())
    {
        vector<int> v;
        while (levelSize--)
        {
            TreeNode* front = q.front();
            q.pop();
            v.push_back(front->val);
            if (front->left)
                q.push(front->left);
            if (front->right)
                q.push(front->right);
        }
        levelSize = q.size();
        vv.push_back(v);
    }
    reverse(vv.begin(), vv.end());
    return vv;
}
//����������ĸ��ڵ� root ���������ǰ������ķ�ʽ����������ת��Ϊһ�������ź�������ɵ��ַ��������ع�������ַ�����
string tree2str(TreeNode* root) {
    string ret;
    if (root == nullptr)
        return ret;
    ret += to_string(root->val);

    if (root->left || root->right)
    {
        ret += '(';
        ret += tree2str(root->left);
        ret += ')';
    }
    if (root->right)
    {
        ret += '(';
        ret += tree2str(root->right);
        ret += ')';
    }
    return ret;
}
int main()
{
    return 0;
}