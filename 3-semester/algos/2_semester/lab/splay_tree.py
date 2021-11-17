from node import Node

class SplayTree:

    def __init__(self):
        self._nil = Node()
        self._root = self._nil

    def _successor(self, local_root: Node) -> Node:
        succ = local_root

        if succ.right is not self._nil:
            succ = self._min(succ.right)
        else:
            while succ is not self._root or succ is not succ.parent.left:
                succ = succ.parent

        return succ

    def _predecessor(self, local_root: Node) -> Node:
        pred = local_root

        if pred.left is not self._nil:
            pred = self._max(pred.left)
        else:
            while pred is not self._root or pred is not pred.parent.right:
                pred = pred.parent

        return pred

    def _min(self, local_root: Node) -> Node:
        minimum = local_root
        while minimum.left is not self._nil:
            minimum = minimum.left

        return minimum

    def _max(self, local_root: Node) -> Node:

        maximum = local_root
        while maximum.right is not self._nil:
            maximum = maximum.right
        return maximum

    def _search(self, val) -> Node:
        searched = self._root
        while searched is not self._nil:
            if searched.val < val:
                searched = searched.right
            elif val < searched.val:
                searched = searched.left
            else:
                self._splay(searched)
                return searched
        return None

    def _left_rotate(self, local_root: Node):
        right_child = local_root.right
        local_root.right = right_child.left
        if right_child.left is not self._nil:
            right_child.left.parent = local_root

        self._transplant(local_root, right_child)

        right_child.left = local_root
        right_child.left.parent = right_child

    def _right_rotate(self, local_root: Node):
        left_child = local_root.left
        local_root.left = left_child.right
        if left_child.right is not self._nil:
            left_child.right.parent = local_root

        self._transplant(local_root, left_child)

        left_child.right = local_root
        left_child.right.parent = left_child

    def _transplant(self, local_parent: Node, local_child: Node):
        if local_parent.parent is self._nil:
            self._root = local_child
        elif local_parent is local_parent.parent.left:
            local_parent.parent.left = local_child
        elif local_parent is local_parent.parent.right:
            local_parent.parent.right = local_child

        if local_child is not self._nil:
            local_child.parent = local_parent.parent

    def _splay(self, pivot_node: Node):

        while pivot_node is not self._root:
            if pivot_node.parent is self._root:
                if pivot_node is pivot_node.parent.left:
                    self._right_rotate(pivot_node.parent)
                elif pivot_node is pivot_node.parent.right:
                    self._left_rotate(pivot_node.parent)
            else:
                if pivot_node is pivot_node.parent.left and pivot_node.parent is pivot_node.parent.parent.left:
                    self._right_rotate(pivot_node.parent.parent)
                    self._right_rotate(pivot_node.parent)
                elif pivot_node is pivot_node.parent.right and pivot_node.parent is pivot_node.parent.parent.right:
                    self._left_rotate(pivot_node.parent.parent)
                    self._left_rotate(pivot_node.parent)
                elif pivot_node is pivot_node.parent.right and pivot_node.parent is pivot_node.parent.parent.left:
                    self._left_rotate(pivot_node.parent)
                    self._right_rotate(pivot_node.parent)
                elif pivot_node is pivot_node.parent.left and pivot_node.parent is pivot_node.parent.parent.right:
                    self._right_rotate(pivot_node.parent)
                    self._left_rotate(pivot_node.parent)

    def insert(self, val):
        if self._search(val):
            return
        pre_insert_place = self._nil
        insert_place = self._root

        while insert_place is not self._nil:
            pre_insert_place = insert_place
            if insert_place.val < val:
                insert_place = insert_place.right
            else:
                insert_place = insert_place.left

        insert_element = Node(val=val, parent=pre_insert_place, left=self._nil, right=self._nil)

        if pre_insert_place is self._nil:
            self._root = insert_element
        elif pre_insert_place.val < insert_element.val:
            pre_insert_place.right = insert_element
        elif pre_insert_place.val > insert_element.val:
            pre_insert_place.left = insert_element

        self._splay(insert_element)

    def remove(self, val):
        remove_element = self._search(val)

        if remove_element:
            if remove_element.right is self._nil:
                self._transplant(remove_element, remove_element.left)
            elif remove_element.left is self._nil:
                self._transplant(remove_element, remove_element.right)
            else:
                local_root = self._min(remove_element.right)
                if local_root.parent is not remove_element:
                    self._transplant(local_root, local_root.right)
                    local_root.right = remove_element.right
                    local_root.right.parent = local_root
                self._transplant(remove_element, local_root)
                local_root.left = remove_element.left
                local_root.left.parent = local_root
                self._splay(local_root)

    def _build_output(self, cur_node, output, level):
        if cur_node.left is not self._nil:
            self._build_output(cur_node.left, output, level + 1)
            output.append("          " * level + "    " + "/")
        output.append("          " * level + "|" + str(cur_node.val))
        if cur_node.right is not self._nil:
            output.append("          " * level + "    " + "\\")
            self._build_output(cur_node.right, output, level + 1)

    def search(self, val):
        return bool(self._search(val))

    def empty(self):
        return self._root is self._nil

    def __str__(self):
        output = []
        level_counter = 0
        self._build_output(self._root, output, level_counter)
        res = ''
        for row in output:
            res += '\n' + row
        return res