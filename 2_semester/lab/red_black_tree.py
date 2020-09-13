from enum import Enum
from node import Node


class Color(Enum):
    red = 1
    black = 2


class RBTNode(Node):

    def __init__(self):
        Node.__init__(self)
        self.color = Color.black
        self.size = 0

    # def __init__(self, parent, left, right, val, color):
    #     Node.__init__(parent, left, right, val)
    #     self.color = color


class RedBlackTree:

    def __init__(self):
        self._nil = RBTNode()
        self._root = self._nil

    def _left_rotate(self, node_x):
        node_y = node_x.right
        node_x.right = node_y.left

        if node_y.left is not self._nil:
            node_y.left.parent = node_x
        node_y.parent = node_x.parent

        if node_x.parent is self._nil:
            self._root = node_y
        elif node_x is node_x.parent.left:
            node_x.parent.left = node_y
        else:
            node_x.parent.right = node_y

        node_y.left = node_x
        node_x.parent = node_y
        node_y.size = node_x.size
        node_x.size = node_x.left.size + node_x.right.size + 1

    def _right_rotate(self, node_x):
        node_y = node_x.left
        node_x.left = node_y.right

        if node_y.right is not self._nil:
            node_y.right.parent = node_x
        node_y.parent = node_x.parent

        if node_x.parent is self._nil:
            self._root = node_y
        elif node_x is node_x.parent.right:
            node_x.parent.right = node_y
        else:
            node_x.parent.left = node_y

        node_y.right = node_x
        node_x.parent = node_y
        node_y.size = node_x.size
        node_x.size = node_x.left.size + node_x.right.size + 1

    def insert_value(self, value):
        node = RBTNode()
        node.val = value
        node.size = 1
        self.insert(node)

    def insert(self, node_z):
        node_y = self._nil
        node_x = self._root
        while node_x is not self._nil:
            node_x.size += 1
            node_y = node_x
            if node_z.val < node_x.val:
                node_x = node_x.left
            else:
                node_x = node_x.right
        node_z.parent = node_y
        if node_y is self._nil:
            self._root = node_z
        elif node_z.val < node_y.val:
            node_y.left = node_z
        else:
            node_y.right = node_z
        node_z.left = self._nil
        node_z.right = self._nil
        node_z.color = Color.red
        self._insertion_fixup(node_z)

    def _insertion_fixup(self, node_z):
        if node_z is self._root:
            node_z.color = Color.black
            return
        while node_z.parent.color is Color.red:

            if node_z.parent is node_z.parent.parent.left:

                node_y = node_z.parent.parent.right

                if node_y.color is Color.red:
                    node_z.parent.color = Color.black
                    node_y.color = Color.black
                    node_z.parent.parent.color = Color.red
                    node_z = node_z.parent.parent
                else:
                    if node_z is node_z.parent.right:
                        node_z = node_z.parent
                        self._left_rotate(node_z)

                    node_z.parent.color = Color.black

                    node_z.parent.parent.color = Color.red
                    self._right_rotate(node_z.parent.parent)
            else:

                node_y = node_z.parent.parent.left

                if node_y.color is Color.red:
                    node_z.parent.color = Color.black
                    node_y.color = Color.black
                    node_z.parent.parent.color = Color.red
                    node_z = node_z.parent.parent
                else:
                    if node_z is node_z.parent.left:
                        node_z = node_z.parent
                        self._right_rotate(node_z)
                    node_z.parent.color = Color.black
                    node_z.parent.parent.color = Color.red
                    self._left_rotate(node_z.parent.parent)
        self._root.color = Color.black

    def _build_output(self, cur_node, output, level):
        if cur_node.left is not self._nil:
            self._build_output(cur_node.left, output, level + 1)
        output.append("          " * level + str(cur_node.val) + " | " + str(cur_node.size)
                      + " | " + ("Red" if cur_node.color is Color.red else "Black"))
        if cur_node.right is not self._nil:
            self._build_output(cur_node.right, output, level + 1)

    def _delete(self, node_z):
        node_x = None
        node_y = None

        if not node_z or node_z is self._nil:
            return

        if node_z.left is self._nil or node_z.right is self._nil:
            node_y = node_z
        else:
            node_y = node_z.right
            while node_y.left != self._nil:
                node_y = node_y.left

        if node_y.left != self._nil:
            node_x = node_y.left
        else:
            node_x = node_y.right

        node_x.parent = node_y.parent

        if node_y.parent:
            if node_y is node_y.parent.left:
                node_y.parent.left = node_x
            else:
                node_y.parent.right = node_x
        else:
            self._root = node_x

        if node_y is not node_z:
            node_z.val = node_y.val

        if node_y.color is Color.black:
            self._delete_fixup(node_x)

    def _delete_fixup(self, node_x):
        while node_x is not self._root and node_x.color is Color.black:
            if node_x is node_x.parent.left:
                node_w = node_x.parent.right
                if node_w.color is Color.red:
                    node_w.color = Color.black
                    node_x.parent.color = Color.red
                    self._left_rotate(node_x.parent)
                    node_w = node_x.parent.right
                if node_w.left.color is Color.black and node_w.right.color is Color.black:
                    node_w.color = Color.red
                    node_x = node_x.parent
                else:
                    if node_w.right.color is Color.black:
                        node_w.left.color = Color.black
                        node_w.color = Color.red
                        self._right_rotate(node_w)
                        node_w = node_x.parent.right
                    node_w.color = node_x.parent.color
                    node_x.parent.color = Color.black
                    node_w.right.color = Color.black
                    self._left_rotate(node_x.parent)
                    node_x = self._root
            else:
                node_w = node_x.parent.left
                if node_w.color is Color.red:
                    node_w.color = Color.black
                    node_x.parent.color = Color.red
                    self._right_rotate(node_x.parent)
                    node_w = node_x.parent.left
                if node_w.right.color is Color.black and node_w.left.color is Color.black:
                    node_w.color = Color.red
                    node_x = node_x.parent
                else:
                    if node_w.left.color is Color.black:
                        node_w.right.color = Color.black
                        node_w.color = Color.red
                        self._left_rotate(node_w)
                        node_w = node_x.parent.left
                    node_w.color = node_x.parent.color
                    node_x.parent.color = Color.black
                    node_w.left.color = Color.black
                    self._right_rotate(node_x.parent)
                    node_x = self._root
        node_x.color = Color.black

    def _find_node(self, val) -> RBTNode:
        node_cur = self._root
        while node_cur is not self._nil:
            if node_cur.val == val:
                return node_cur
            else:
                node_cur = (node_cur.left if node_cur.val > val else node_cur.right)
        return

    def delete_value(self, val):
        if not self._find_node(val):
            return
        node_cur = self._root
        while node_cur is not self._nil:
            node_cur.size -= 1
            if node_cur.val == val:
                return self._delete(node_cur)
            else:
                node_cur = (node_cur.left if node_cur.val > val else node_cur.right)
        return

    def _select(self, node_x, i):
        res = node_x.left.size + 1
        if i == res:
            return node_x
        elif i < res:
            return self._select(node_x.left, i)
        else:
            return self._select(node_x.right, i - res)

    def __getitem__(self, item):
        if item + 1 > self._root.size:
            return None
        if item < 0:
            return self.__getitem__(self._root.size + item)
        return self._select(self._root, item + 1)

    def __str__(self):
        output = []
        level_counter = 0
        self._build_output(self._root, output, level_counter)
        res = ''
        for row in output:
            res += '\n' + row
        return res

