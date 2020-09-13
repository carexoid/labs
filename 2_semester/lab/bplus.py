class Node(object):

    def __init__(self, order):
        self.order = order
        self.keys = []
        self.vals = []
        self.leaf = True

    def add(self, val):

        key = val

        if not self.keys:
            self.keys.append(key)
            self.vals.append([val])
            return None

        for i, item in enumerate(self.keys):
            if key == item:
                self.vals[i].append(val)
                break

            elif key < item:
                self.keys = self.keys[:i] + [key] + self.keys[i:]
                self.vals = self.vals[:i] + [[val]] + self.vals[i:]
                break

            elif i + 1 == len(self.keys):
                self.keys.append(key)
                self.vals.append([val])
                break

    def split(self):

        left = Node(self.order)
        right = Node(self.order)
        mid = self.order // 2
        print(mid)
        left.keys = self.keys[:mid]
        left.vals = self.vals[:mid]

        right.keys = self.keys[mid:]

        right.vals = self.vals[mid:]

        self.keys = [right.keys[0]]
        self.vals = [left, right]
        self.leaf = False

    def is_full(self):
        return len(self.keys) == self.order
    
    def __str__(self):
        return self._show()
    
    def _show(self, counter=0, string=''):
        string += str(counter) + str(self.keys)

        if not self.leaf:
            for item in self.vals:
                item._show(counter=counter + 1, string=string)
        return string


class BPlusTree(object):
    def __init__(self, order=8):
        self._root = Node(order)

    def _find(self, node, key):
        for i, item in enumerate(node.keys):
            if key < item:
                return node.vals[i], i

        return node.vals[i + 1], i + 1

    def _merge(self, parent, child, index):
        parent.vals.pop(index)
        pivot = child.keys[0]

        for i, item in enumerate(parent.keys):
            if pivot < item:
                parent.keys = parent.keys[:i] + [pivot] + parent.keys[i:]
                parent.vals = parent.vals[:i] + child.vals + parent.vals[i:]
                break

            elif i + 1 == len(parent.keys):
                parent.keys += [pivot]
                parent.vals += child.vals
                break

    def insert(self, val):
        if self.contains(val):
            return
        key = val
        parent = None
        child = self._root

        while not child.leaf:
            parent = child
            child, index = self._find(child, key)

        child.add(val)

        if child.is_full():
            child.split()

            if parent and not parent.is_full():
                self._merge(parent, child, index)

    def contains(self, val):
        child = self._root

        while not child.leaf:
            child, index = self._find(child, val)

        for i, item in enumerate(child.keys):
            if val == item:
                return child.vals[i]

        return None

    def _build_output(self, cur_node, output, level):
        if cur_node.leaf:
            output.append("          " * level + "|" + str(cur_node.vals))
            return
        self._build_output(cur_node.vals[0], output, level + 1)
        output.append("          " * level + "    " + "-")
        output.append("          " * level + "|" + str(cur_node.keys[0]))
        output.append("          " * level + "    " + "-")
        for i in range(1, len(cur_node.keys)):
            self._build_output(cur_node.vals[i], output, level + 1)
            output.append("          " * level + "    " + "-")
            output.append("          " * level + "|" + str(cur_node.keys[i]))
            output.append("          " * level + "    " + "-")
        self._build_output(cur_node.vals[len(cur_node.keys)], output, level + 1)

    def __str__(self):
        out = []
        self._build_output(self._root, out, 0)
        res = ''
        for row in out:
            res += '\n' + row
        return res
