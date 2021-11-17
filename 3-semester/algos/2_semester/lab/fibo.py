from math import log


class FiboNode:

    def __init__(self, parent=None, child=None, left=None, right=None,
                 val=None, degree=0, mark=False):
        self.parent = parent
        self.child = child
        self.left = left
        self.right = right
        self.val = val
        self.degree = degree
        self.mark = mark


class FiboHeap:

    def __init__(self):
        self._min = None
        self._num = 0
        self._trees = 0

    def _link(self, _child, _parent):
        _child.left.right = _child.right
        _child.right.left = _child.left

        if _parent.child:
            last_child = _parent.child.left

            last_child.right = _child
            _child.left = last_child
            _child.right = _parent.child
            _parent.child.left = _child
            _parent.child = _child
        else:
            _child.right = _child.left = _child
            _parent.child = _child

        _parent.degree += 1
        _parent.mark = False
        _child.parent = _parent

    def _consolidate(self):
        helper = [None for i in range(0, int(log(self._num, 2)) + 1)]
        root = self._min
        for i in range(1, self._trees + 1):
            deg = root.degree
            while deg < len(helper) and helper[deg] is not None:
                pointer = helper[deg]
                if root.val > pointer.val:
                    root, pointer = pointer, root

                self._link(pointer, root)
                helper[deg] = None
                deg += 1

            helper[deg] = root
            root = root.right

        self._min = None
        for item in helper:
            if item:
                if not self._min:
                    self._min = item
                    self._min.left = self._min.right = self._min
                    self._trees = 1
                else:
                    tail = self._min.left
                    tail.right = item
                    item.left = tail
                    item.right = self._min
                    self._min.left = item
                    self._trees += 1

                    if self._min.val > item.val:
                        self._min = item

    def _cut(self, x, y):
        x.left.right = x.right
        x.right.left = x.left
        if x == y.child:
            y.child = x.right
        y.degree -= 1
        self._min.left.right = x
        x.left = self._min.left
        x.right = self._min
        self._min.left = x
        self._trees += 1
        x.parent = None
        x.mark = False

    def _cascading_cut(self, y):
        parent = y.parent
        if parent:
            if not y.mark:
                y.mark = True
            else:
                self._cut(y, parent)
                self._cascading_cut(parent)

    def insert(self, val):
        new_node = FiboNode(val=val)

        if self._min:
            self._min.left.right = new_node
            new_node.left = self._min.left
            self._min.left = new_node
            new_node.right = self._min

            if val < self._min.val:
                self._min = new_node
        else:
            self._min = new_node
            new_node.mark = True
            new_node.left = new_node
            new_node.right = new_node

        self._num += 1
        self._trees += 1

    def minimun(self):
        return self._min.val

    def minimal_node(self) -> FiboNode:
        return self._min

    def pop_min(self):
        min_node = self._min
        if not min_node:
            return
        if self._num == 1:
            self._min = None
            return min_node.val

        child = min_node.child
        if child:
            for i in range(1, min_node.degree + 1):
                child.parent = None
                child = child.right

            child1 = min_node.child
            child_last = min_node.child.left
            tail = min_node.left

            child1.left = tail
            tail.right = child1
            min_node.right.left = child_last
            child_last.right = min_node.right

        self._num -= 1
        self._trees = self._trees - 1 + min_node.degree
        self._min = self._min.right
        self._consolidate()

        return min_node.val

    @staticmethod
    def unite_heap(heap_l, heap_r):
        if not heap_l._min:
            del heap_l
            return heap_r
        if not heap_r._min:
            del heap_r
            return heap_l
        tail_l = heap_l._min.left
        tail_r = heap_r._min.left

        tail_r.right = heap_l._min
        heap_l._min.left = tail_r
        tail_l.right = heap_r._min
        heap_r._min.left = tail_l

        res = FiboHeap()
        res._min = heap_l._min if heap_l._min.data < heap_r._min.val else heap_r._min
        res._num = heap_l._num + heap_r._num
        res._trees = heap_l._trees + heap_r._trees
        del heap_r
        del heap_l
        return res

    def __str__(self):
        mini = self._min.right
        res = str(self._num) + ":"
        while not mini.mark:
            res += " " + str(mini.degree)
            mini = mini.right

        return res


