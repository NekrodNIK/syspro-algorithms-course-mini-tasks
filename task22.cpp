struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
private:
  bool checkBST(TreeNode* root, int* min, int* max) {
    if (not root) {
      return true;
    }
    if ((min and root->val <= *min) or (max and root->val >= *max)) {
      return false;
    }

    return checkBST(root->left, min, &root->val) and
           checkBST(root->right, &root->val, max);
  }

public:
  bool isValidBST(TreeNode* root) { return checkBST(root, nullptr, nullptr); }
};
