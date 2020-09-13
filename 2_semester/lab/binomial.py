class HeapNode:

    def __init__(self, val=None):
        self.val = val
        self.degree = 0
        self.child = self.parent = self.sibling = None


class BinomialHeap:

    def __init__(self, heap=[]):
        self._list = heap

    @staticmethod
    def merge_trees(node_1: HeapNode, node_2: HeapNode) -> HeapNode:
        if node_1.val > node_2.val:
            node_1, node_2 = node_2, node_1

        node_2.parent = node_1
        node_2.sibling = node_1.child
        node_1.child = node_2
        node_1.degree += 1

        return node_1

    @staticmethod
    def unite_heaps(heap1, heap2):
        res = []
        pointer1 = 0
        pointer2 = 0
        while pointer1 < len(heap1) and pointer2 < len(heap2):
            if heap1[pointer1].degree <= heap2[pointer2].degree:
                res.append(heap1[pointer1])
                pointer1 += 1
            else:
                res.append(heap2[pointer2])
                pointer2 += 1

        while pointer1 < len(heap1):
            res.append(heap1[pointer1])
            pointer1 += 1

        while pointer2 < len(heap2):
            res.append(heap2[pointer2])
            pointer2 += 1

        return res

    @staticmethod
    def adjust(heap):
        if len(heap) <= 1:
            return heap

        it1 = 0
        it2 = 0
        it3 = 0
        if len(heap) == 2:
            it2 = it1
            it2 += 1
            it3 = len(heap)
        else:
            it2 += 1
            it3 = it2
            it3 += 1

        while it1 != len(heap):
            if it2 == len(heap):
                it1 += 1

            elif heap[it1].degree < heap[it2].degree:
                it1 += 1
                it2 += 1
                if it3 != len(heap):
                    it3 += 1

            elif it3 < len(heap) and \
                    heap[it1].degree == heap[it2].degree \
                    and heap[it1].degree == heap[it3].degree:
                it1 += 1
                it2 += 1
                it3 += 1

            elif heap[it1].degree == heap[it2].degree:
                heap[it1] = BinomialHeap.merge_trees(heap[it1], heap[it2])
                heap.remove(heap[it2])
                if it3 != len(heap):
                    it3 += 1

        return heap

    @staticmethod
    def insert_tree(heap, root):
        temp = [root]
        temp = BinomialHeap.unite_heaps(heap, temp)

        return BinomialHeap.adjust(temp)

    def insert(self, val):
        node = HeapNode(val=val)
        self._list = BinomialHeap.insert_tree(self._list, node)

    @staticmethod
    def remove_min(tree):
        heap = []
        temp = tree.child
        lo = None

        while temp:
            lo = temp
            temp = temp.sibling
            lo.sibling = None
            heap.insert(0, lo)
        return heap

    def _get_min(self):
        it = 0

        temp = self._list[it]

        while it < len(self._list):
            if self._list[it].val < temp.val:
                temp = self._list[it]
            it += 1

        return temp

    def get_min(self):
        return self._get_min().val

    def pop_min(self):
        new_heap = []
        lo = []
        temp = self._get_min()
        it = 0
        while it < len(self._list):
            if self._list[it] is not temp:
                new_heap.append(self._list[it])
            it += 1

        lo = self.remove_min(temp)
        new_heap = BinomialHeap.unite_heaps(new_heap, lo)
        new_heap = BinomialHeap.adjust(new_heap)
        self._list = new_heap
        return temp.val

    @staticmethod
    def print_tree(root, indent="", last=True):
        print(indent)
        if last:
            print ('Sibling----')
            indent += "      "
        else:
            print("Child----")
            indent += "|     "
        print(root.val)
        if root.child:
            BinomialHeap.print_tree(root.child, indent, False)
        if root.sibling:
            BinomialHeap.print_tree(root.sibling, indent, True)

    def __str__(self):
        return str(list(map(lambda x: (x.val, x.degree), self._list)))





