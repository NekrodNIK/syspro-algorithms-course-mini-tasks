import json


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec:
    def _serialize(self, node: TreeNode) -> dict:
        result = {"val": node.val}
        stack: list[tuple] = [
            (node.left, result, "left"),
            (node.right, result, "right"),
        ]

        while stack:
            node, p_dict, key = stack.pop()

            if node is None:
                p_dict[key] = None
                continue

            p_dict[key] = {"val": node.val}
            stack.append((node.right, p_dict[key], "right"))
            stack.append((node.left, p_dict[key], "left"))

        return result

    def _deserialize(self, dict_: dict) -> TreeNode:
        result = TreeNode(dict_["val"])
        stack: list[tuple] = [
            (dict_["left"], result, "left"),
            (dict_["right"], result, "right"),
        ]

        while stack:
            dict_, p_node, key = stack.pop()

            if dict_ is None:
                continue

            node = TreeNode(dict_["val"])
            setattr(p_node, key, node)

            stack.append((dict_["right"], node, "right"))
            stack.append((dict_["left"], node, "left"))

        return result

    def serialize(self, root: TreeNode | None) -> str:
        return json.dumps(self._serialize(root)) if root else ""

    def deserialize(self, data: str) -> TreeNode | None:
        return self._deserialize(json.loads(data)) if data else None
