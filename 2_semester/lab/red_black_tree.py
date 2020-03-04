from enum import Enum


class Node:

    def __init__(self):
        self.parent = None
        self.left = None
        self.right = None
        self.val = None

    # def __init__(self, parent, left, right, val):
    #     self.parent = parent
    #     self.left = left
    #     self.right = right
    #     self.val = val


class Color(Enum):
    red = 1
    black = 2


class RBTNode(Node):

    def __init__(self):
        Node.__init__(self)
        self.color = None

    # def __init__(self, parent, left, right, val, color):
    #     Node.__init__(parent, left, right, val)
    #     self.color = color


class RedBlackTree:

    def __init__(self):

        self._nil = RBTNode()
        self._nil.left = self._nil.right = self._nil.parent = self._nil
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

    def _right_rotate(self, node_x):
        node_y = node_x.left
        node_x.left = node_y.right

        if node_y.right is not self._nil:
            node_y.right.parent = node_x
        node_y.parent = node_x.parent

        if node_x.parent is self._nil:
            self._root = node_y
        elif node_x is node_x.parent.left:
            node_x.parent.left = node_y
        else:
            node_x.parent.right = node_y

        node_y.right = node_x
        node_x.parent = node_y

    def insert_value(self, value):
        node = RBTNode()
        node.val = value
        self.insert(node)

    def insert(self, node_z):
        node_y = self._nil
        node_x = self._root
        while node_x is not self._nil:
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
        while node_z.parent.color is Color.red:
            if node_z.parent is node_z.parent.parent.left:
                node_y = node_z.parent.parent.right
                if node_y.color is Color.red:
                    node_z.parent.color = Color.black
                    node_y.color = Color.black
                    node_z.parent.parent.color = Color.red
                    node_z = node_z.parent.parent
                elif node_z is node_z.parent.right:
                    node_z = node_z.parent
                    self._left_rotate(node_z)
                if node_z.parent is not self._nil:
                    node_z.parent.color = Color.black
                    if node_z.parent.parent is not self._nil:
                        node_z.parent.parent.color = Color.red
                        self._right_rotate(node_z.parent.parent)
            else:
                node_y = node_z.parent.parent.left
                if node_y.color is Color.red:
                    node_z.parent.color = Color.black
                    node_y.color = Color.black
                    node_z.parent.parent.color = Color.red
                    node_z = node_z.parent.parent
                elif node_z is node_z.parent.left:
                    node_z = node_z.parent
                    self._right_rotate(node_z)
                if node_z.parent is not self._nil:
                    node_z.parent.color = Color.black
                    if node_z.parent.parent is not self._nil:
                        node_z.parent.parent.color = Color.red
                        self._left_rotate(node_z.parent.parent)
        self._root.color = Color.black

    def _build_output(self, cur_node, output, level):
        if cur_node.left is not self._nil:
            self._build_output(cur_node.left, output, level + 1)
        output.append("          " * level + str(cur_node.val)
                      + " | " + ("Red" if cur_node.color is Color.red else "Black"))
        if cur_node.right is not self._nil:
            self._build_output(cur_node.right, output, level + 1)

    def __str__(self):
        output = []
        level_counter = 0
        self._build_output(self._root, output, level_counter)
        res = ''
        for row in output:
            res += '\n' + row
        return res

