from node import Node

INF = 100000000


class OptimalBST:

    def __init__(self):
        self.root = None

    def create_tree(self, frequency: list, fails: list, items: list):
        n = len(frequency) - 1
        e = [[0 for i in range(0, n + 1)] for j in range(0, n + 2)]
        w = [[0 for i in range(0, n + 1)] for j in range(0, n + 2)]

        root = [[0 for i in range(0, n + 1)] for j in range(0, n + 1)]


        print(fails)

        for i in range(1, n + 2):
            e[i][i - 1] = fails[i - 1]
            w[i][i - 1] = fails[i - 1]

        for l in range(1, n + 1):
            for i in range(1, n - l + 2):
                j: int = i + l - 1
                e[i][j] = INF
                print(l, i, j)
                w[i][j] = w[i][j - 1] + frequency[j] + fails[j]

                for r in range(i, j + 1):
                    temp: int = e[i][r - 1] + e[r + 1][j] + w[i][j]

                    if temp < e[i][j]:
                        e[i][j] = temp
                        root[i][j] = r

        print(root)
        self._root = self._build(root, 1, n, items)
        print(self._root)

    def _build(self, root: list, left, right, items: list):
        if left > right:
            return None

        current_root = root[left][right]

        return Node(val=items[current_root - 1], left=self._build(root, left, current_root - 1, items),
                    right=self._build(root, current_root + 1, right, items))

    def __str__(self):
        print(self._root)
        output = []
        level_counter = 0
        self._build_output(self._root, output, level_counter)
        res = ''
        for row in output:
            res += '\n' + row
        return res

    def _build_output(self, cur_node, output, level):
        if cur_node.left:
            self._build_output(cur_node.left, output, level + 1)
            output.append("          " * level + "    " + "/")
        output.append("          " * level + "|" + str(cur_node.val))
        if cur_node.right:
            output.append("          " * level + "    " + "\\")
            self._build_output(cur_node.right, output, level + 1)
