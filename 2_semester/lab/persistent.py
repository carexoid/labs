from node import Node
from enum import Enum
import copy


class Color(Enum):
    red = 1
    black = 2


class RBTNode(Node):

    def __init__(self, val=None, left=None, right=None, parent=None):
        Node.__init__(self, val=val, parent=parent, left=left, right=right)
        self.color = Color.black


class PersistentTree:

    def __init__(self):
        self._cur = 0
        self._last = 0
        self._nil = RBTNode()
        self._roots = [self._nil]

    def _delete_node(self, node: RBTNode):
        alter = node
        color_of_alter = copy.copy(alter.color)
        new_node = RBTNode()
        if node.left is self._nil:
            new_node = node.right
            new_node.parent = node
            self._transplant(node, node.right)
        elif node.right is self._nil:
            new_node = node.left
            new_node.parent = node
            self._transplant(node, node.left)
        else:
            righty = self._nil
            if node.right is not self._nil:
                righty = self._make_full_copy(node.right)
                self.fully_reconnect(righty, node, False)
            alter = self._minimum(righty)
            color_of_alter = copy.copy(alter.color)
            new_node = self._nil
            if alter.right is not self._nil:
                new_node = self._make_full_copy(alter.right)
                self.fully_reconnect(new_node, alter, False)

            if alter.parent is node:
                new_node.parent = alter
            else:
                self._transplant(alter, alter.right)
                alter.right = node.right
                alter.right.parent = alter

            self._transplant(node, alter)
            alter.left = node.left
            alter.left.parent = alter
            alter.color = node.color

        if color_of_alter is Color.black:
            self._delete_fixup(new_node)

    def _transplant(self, old: RBTNode, new: RBTNode):
        if old.parent is self._nil:
            self._roots[self._cur] = new
        elif old.parent.left is old:
            old.parent.left = new
        else:
            old.parent.right = new
        new.parent = old.parent

    def _minimum(self, node: RBTNode):
        if not node:
            return node
        while node.left is not self._nil:
            new_node = self._make_full_copy(node.left)
            self.fully_reconnect(new_node, father=node, left=True)
            node = node.left
        return node

    def _delete_subtree(self, node: RBTNode):
        if not node:
            return
        if node is self._nil:
            return

    @staticmethod
    def _make_full_copy(old: RBTNode) -> RBTNode:
        new_cur = RBTNode(val=copy.deepcopy(old.val), left=old.left, right=old.right, parent=old.parent)
        new_cur.color = old.color
        return new_cur

    def _left_rotate(self, node_x: RBTNode):
        node_y = node_x.right
        node_x.right = node_y.left

        if node_y.left is not self._nil:
            node_y.left.parent = node_x
        node_y.parent = node_x.parent

        if node_x.parent is self._nil:
            self._roots[self._cur] = node_y
        elif node_x is node_x.parent.left:
            node_x.parent.left = node_y
        else:
            node_x.parent.right = node_y

        node_y.left = node_x
        node_x.parent = node_y

    def _right_rotate(self, node_x: RBTNode):
        node_y = node_x.left
        node_x.left = node_y.right

        if node_y.right is not self._nil:
            node_y.right.parent = node_x
        node_y.parent = node_x.parent

        if node_x.parent is self._nil:
            self._roots[self._cur] = node_y
        elif node_x is node_x.parent.right:
            node_x.parent.right = node_y
        else:
            node_x.parent.left = node_y

        node_y.right = node_x
        node_x.parent = node_y

    def _insert_fixup(self, node_z: RBTNode):

        if node_z is self._roots[self._cur]:
            node_z.color = Color.black
            return

        while node_z.parent.color is Color.red:

            if node_z.parent is node_z.parent.parent.left:

                node_y = node_z.parent.parent.right

                if node_y.color is Color.red:
                    node_z.parent.color = Color.black
                    new_node_y = self._make_full_copy(node_y)
                    self.fully_reconnect(new_node_y, father=node_z.parent.parent, left=False)

                    new_node_y.color = Color.black
                    new_node_y.parent.color = Color.red
                    node_z = new_node_y.parent
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
                    new_node_y = self._make_full_copy(node_y)
                    self.fully_reconnect(new_node_y, father=node_z.parent.parent, left=True)

                    new_node_y.color = Color.black
                    new_node_y.parent.color = Color.red
                    node_z = new_node_y.parent
                else:
                    if node_z is node_z.parent.left:
                        node_z = node_z.parent
                        self._right_rotate(node_z)
                    node_z.parent.color = Color.black
                    node_z.parent.parent.color = Color.red
                    self._left_rotate(node_z.parent.parent)
        self._roots[self._cur].color = Color.black

    def _insert_fixup_free(self, node_z: RBTNode):

        if node_z is self._roots[self._cur]:
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
        self._roots[0].color = Color.black

    def _free_insert(self, val):
        cur = self._roots[0]
        prev = cur
        new_node = RBTNode(val=val, left=self._nil, right=self._nil)
        while cur is not self._nil:
            prev = cur
            if cur.val == val:
                return
            elif cur.val < val:
                cur = cur.right
            else:
                cur = cur.left

        new_node.parent = prev
        if cur == self._roots[0]:
            self._roots[0] = new_node
            self._roots[0].parent = self._nil
        elif new_node.val < prev.val:
            prev.left = new_node
        else:
            prev.right = new_node
        new_node.color = Color.red
        self._insert_fixup_free(new_node)

    def _delete_fixup(self, node_x: RBTNode):
        while node_x is not self._roots[self._cur] and node_x.color is Color.black:
            if node_x is node_x.parent.left:
                node_w = node_x.parent.right
                if node_w.color is Color.red:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=False)
                    new_w.color = Color.black
                    node_x.parent.color = Color.red
                    self._left_rotate(node_x.parent)
                    node_w = node_x.parent.right
                if node_w.left.color is Color.black and node_w.right.color is Color.black:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=False)
                    new_w.color = Color.red
                    node_x = node_x.parent
                else:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=False)
                    if node_w.right.color is Color.black:
                        lefty = self._nil
                        if new_w.left is not self._nil:
                            lefty = self._make_full_copy(new_w.left)
                            self.fully_reconnect(lefty, father=new_w, left=True)
                        lefty.color = Color.black
                        new_w.color = Color.red
                        self._right_rotate(new_w)
                        new_w = node_x.parent.right
                    new_w.color = node_x.parent.color
                    node_x.parent.color = Color.black
                    righty = self._nil
                    if new_w.right is not self._nil:
                        righty = self._make_full_copy(new_w.right)
                        self.fully_reconnect(righty, father=new_w, left=False)
                    righty.color = Color.black
                    self._left_rotate(node_x.parent)
                    node_x = self._roots[self._cur]
            else:
                node_w = node_x.parent.left
                if node_w.color is Color.red:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=True)
                    new_w.color = Color.black
                    node_x.parent.color = Color.red
                    self._right_rotate(node_x.parent)
                    node_w = node_x.parent.left
                if node_w.left.color is Color.black and node_w.right.color is Color.black:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=True)
                    new_w.color = Color.red
                    node_x = node_x.parent
                else:
                    new_w = self._make_full_copy(node_w)
                    self.fully_reconnect(new_w, father=node_x.parent, left=True)
                    if node_w.left.color is Color.black:
                        righty = self._nil
                        if new_w.right is not self._nil:
                            righty = self._make_full_copy(new_w.right)
                            self.fully_reconnect(righty, father=new_w, left=False)
                        righty.color = Color.black
                        new_w.color = Color.red
                        self._left_rotate(new_w)
                        new_w = node_x.parent.left
                    new_w.color = node_x.parent.color
                    node_x.parent.color = Color.black
                    lefty = self._nil
                    if new_w.left is not self._nil:
                        lefty = self._make_full_copy(new_w.left)
                        self.fully_reconnect(lefty, father=new_w, left=True)
                    lefty.color = Color.black
                    self._right_rotate(node_x.parent)
                    node_x = self._roots[self._cur]
        node_x.color = Color.black

    def _contains_node(self, node: RBTNode, val) -> bool:
        if node is self._nil:
            return False
        if node.val == val:
            return True
        elif node.val > val:
            return self._contains_node(node.left, val)
        else:
            return self._contains_node(node.right, val)

    def fully_reconnect(self, new_node: RBTNode, father=None, left=True):
        if new_node.left is not self._nil:
            new_node.left.parent = new_node
        if new_node.right is not self._nil:
            new_node.right.parent = new_node
        if father:
            if left:
                father.left = new_node
            else:
                father.right = new_node

    def insert(self, val):
        assert self._cur == self._last
        if self.contains(val):
            return False
        self._cur += 1
        self._last += 1
        if self._roots[self._cur - 1] is self._nil:
            self._roots.append(RBTNode(val, left=self._nil, right=self._nil, parent=self._nil))
            return
        new_root = self._make_full_copy(self._roots[self._cur - 1])
        self.fully_reconnect(new_root)
        self._roots.append(new_root)

        cur = new_root
        prev = cur

        new_node = RBTNode(val=val, left=self._nil, right=self._nil)

        while cur is not self._nil:
            prev = cur
            if cur.val < val:
                if cur.right is not self._nil:
                    new_cur = self._make_full_copy(cur.right)
                    self.fully_reconnect(new_cur, father=cur, left=False)
                cur = cur.right
            else:
                if cur.left is not self._nil:
                    new_cur = self._make_full_copy(cur.left)
                    self.fully_reconnect(new_cur, father=cur, left=True)
                cur = cur.left

        new_node.parent = prev

        if cur is self._roots[self._cur]:
            self._roots[self._cur] = new_node
            self._roots[self._cur].parent = self._nil
        elif new_node.val < prev.val:
            prev.left = new_node
        else:
            prev.right = new_node
        new_node.color = Color.red

        self._insert_fixup(new_node)
        return True

    def contains(self, val):
        return self._contains_node(self._roots[self._cur], val)

    def delete(self, val):
        assert self._cur == self._last

        self._cur += 1
        self._last += 1
        new_root = self._make_full_copy(self._roots[self._cur - 1])
        self.fully_reconnect(new_root)
        self._roots.append(new_root)

        cur = new_root
        prev = cur

        while cur is not self._nil:
            prev = cur
            if cur.val == val:
                self._delete_node(cur)
                return
            elif cur.val < val:
                if cur.right is not self._nil:
                    new_cur = self._make_full_copy(cur.right)
                    self.fully_reconnect(new_cur, father=cur, left=False)
                cur = cur.right
            else:
                if cur.left is not self._nil:
                    new_cur = self._make_full_copy(cur.left)
                    self.fully_reconnect(new_cur, father=cur, left=True)
                cur = cur.left

    def history(self):
        print("Current state is " + str(self._cur))
        print("Last state is " + str(self._last))
        print(self)

    def undo(self):
        if self._cur >= 1:
            self._cur -= 1

    def redo(self):
        if self._cur < self._last:
            self._cur += 1

    def _build_output(self, cur_node, output, level):
        if cur_node.left is not self._nil:
            self._build_output(cur_node.left, output, level + 1)
        output.append("          " * level + str(cur_node.val)\
                      + " | " + ("Red" if cur_node.color is Color.red else "Black"))
        if cur_node.right is not self._nil:
            self._build_output(cur_node.right, output, level + 1)

    def __str__(self):
        output = []
        level_counter = 0
        self._build_output(self._roots[self._cur], output, level_counter)
        res = ''
        for row in output:
            res += '\n' + row
        return res
