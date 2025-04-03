from typing import Optional, List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    _arr: List[int]

    def __init__(self):
        self._arr = []

    def dfs(self, root: TreeNode, index: int):
        if index >= len(self._arr):
            self._arr.append(root.val)
        if root.right:
            self.dfs(root.right, index + 1)
        if root.left:
            self.dfs(root.left, index + 1)

    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return self._arr

        self.dfs(root, 0)
        return self._arr
