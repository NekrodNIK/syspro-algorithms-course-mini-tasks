import json


class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec:
    def serialize(self, root):
        return json.dumps(root, default=vars)

    def deserialize(self, data):
        return json.loads(data, object_hook=self._obj_hook)

    def _obj_hook(self, dict_):
        tr = TreeNode(dict_["val"])
        tr.left = dict_["left"]
        tr.right = dict_["right"]
        return tr
