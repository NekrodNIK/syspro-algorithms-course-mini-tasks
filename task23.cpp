#include <vector>

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
public:
  TreeNode* balanceBST(TreeNode* root) {
    std::vector<TreeNode*> vec;

    auto bst_to_sorted = [&vec](const auto& self, TreeNode* root) {
      if (root == nullptr)
        return;
      self(self, root->left);
      vec.push_back(root);
      self(self, root->right);
    };

    auto sorted_to_balanced = [&vec](const auto& self, int l, int r) {
      if (l > r)
        return (TreeNode*)nullptr;
      int mid = (l + r) / 2;
      vec[mid]->left = self(self, l, mid - 1);
      vec[mid]->right = self(self, mid + 1, r);
      return vec[mid];
    };

    bst_to_sorted(bst_to_sorted, root);
    return sorted_to_balanced(sorted_to_balanced, 0, vec.size() - 1);
  }
};
