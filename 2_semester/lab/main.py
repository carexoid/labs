import showroom
import red_black_tree
import splay_tree
import optimal_bst
from bplus import BPlusTree, Node
import binomial
import fibo
import db
import random
import persistent

def main():
    data = db.DB()
    brand_list = data.get_brands()
    a = showroom.Model("Taurus", 2010)
    b = showroom.Model("Fusion", 2015)
    print(a.get_name())
    c = showroom.Brand("Ford", [a, b])
    print(c.get_models()[1].get_name())
    d = showroom.Auto(c, a)
    f = showroom.Auto(c, b)
    print(d.get_brand().get_name())
    show_room = showroom.Showroom(brand_list)
    print(show_room.get_autos()[0].get_model().get_name())
    d.get_polynomial_hash()
    print(d.get_polynomial_hash())
    hashik = showroom.PerfectHash(show_room, 101)
    print(hashik)
    print(hashik.contains_auto(show_room.get_autos()[2]))
    print(hashik.contains_auto((showroom.Auto(brand_list[1], showroom.Model("S-class", 2010)))))
    # rbtree = red_black_tree.RedBlackTree()
    # rbtree.insert_value(12)
    # print(rbtree)
    # rbtree.insert_value(34)
    # print(rbtree)
    # rbtree.insert_value(56)
    # print(rbtree)
    # rbtree.insert_value(24)
    # rbtree.insert_value(4)
    # print(rbtree)
    # rbtree.insert_value(56)
    # rbtree.insert_value(78)
    # rbtree.insert_value(46)
    # rbtree.insert_value(152)
    #
    # rbtree.insert_value(434)
    # rbtree.insert_value(16)
    # rbtree.insert_value(2)
    # rbtree.insert_value(4324)
    # rbtree.insert_value(6234)
    #
    # rbtree.insert_value(748)
    # rbtree.insert_value(446)
    # rbtree.insert_value(2324)
    # rbtree.insert_value(42434)
    # print(rbtree)
    #
    # rbtree.delete_value(34)
    # rbtree.delete_value(121212121)
    # rbtree.delete_value(446)
    # rbtree.delete_value(748)
    # rbtree.delete_value(2)
    # rbtree.delete_value(2324)
    # rbtree.delete_value(46)
    # rbtree.delete_value(56)
    # rbtree.delete_value(4)
    # rbtree.delete_value(12)
    # rbtree.delete_value(16)
    # rbtree.delete_value(78)
    # print(rbtree._find_node(34))
    # print(rbtree)
    # print(rbtree[-3].val)
    #
    # rbtree_auto = red_black_tree.RedBlackTree()
    # for i in show_room.get_autos():
    #     rbtree_auto.insert_value(i)
    # print(rbtree_auto)
    # for i in show_room.get_autos()[::2]:
    #     rbtree_auto.delete_value(i)
    # print(rbtree_auto)
    #
    # splay = splay_tree.SplayTree()
    #
    # splay.insert(14)
    # print(splay._search(14))
    # splay.insert(23)
    # splay.insert(2)
    # splay.insert(100)
    # splay.insert(15)
    # splay.insert(25)
    # splay.insert(5)
    # splay.insert(105)
    # splay.insert(15)
    # splay.insert(25)
    # splay.insert(5)
    # splay.insert(23)
    # splay.insert(3)
    # splay.insert(87)
    # splay.remove(3)
    # splay.remove(2)
    # splay.remove(87)
    # splay.insert(1000)
    # splay.remove(1000)
    # print(splay)
    # print(splay.empty())
    # print(splay.search(25))
    # splay_auto = splay_tree.SplayTree()
    # for i in show_room.get_autos():
    #     splay_auto.insert(i)
    # print(splay_auto)
    # for i in show_room.get_autos()[::2]:
    #     splay_auto.remove(i)
    # print(splay_auto)
    #
    # opt_bst = optimal_bst.OptimalBST()
    # opt_bst.create_tree([0, 1, 1, 2, 3, 5, 8, 13], [0, 0, 0, 0, 0, 0, 0, 0], [3, 5, 7, 9, 11, 13, 15])
    # print(opt_bst)
    #
    # bplustree = BPlusTree(order=2)
    #
    #
    # bplustree.insert('alpha')
    # bplustree.insert('bravo')
    #
    # bplustree.insert('charlie')
    # bplustree.insert('delta')
    # bplustree.insert('echo')
    # bplustree.insert('foxtrot')
    #
    # bplustree.insert('hi')
    # bplustree.insert('charli')
    #
    # bplustree.insert('delta')
    # bplustree.insert('echo')
    # bplustree.insert('foxtrot')
    # bplustree.insert('kai')
    # bplustree.insert('kek')
    #
    # bplustree.insert('pek')
    # bplustree.insert('mek')
    # bplustree.insert('k')
    # print(bplustree)
    # print(bplustree.contains('kai'))
    #
    #

    # bin = binomial.BinomialHeap()
    # for i in range(0, 100):
    #     bin.insert(random.randint(1, 100))
    #     print(bin)

    #
    # print(bin.get_min())
    # print(bin)
    # # bin.print_tree(bin._list[1])
    # print(bin.pop_min())
    #
    # print(bin.get_min())
    # print(bin)
    # print(bin.pop_min())
    # print(bin.pop_min())
    # print(bin)
    # print(bin.pop_min())
    # print(bin.get_min())

    fibonachi = fibo.FiboHeap()
    for i in range(0, 100):
        f = random.randint(1, 30000)
        fibonachi.insert(f)
        print(f)

    print(fibonachi)
    print(fibonachi.pop_min())

    # fibonachi.insert(12)
    # fibonachi.insert(14)
    # fibonachi.insert(4)
    # fibonachi.insert(3)
    # fibonachi.insert(1)
    # fibonachi.insert(7)
    #
    #
    # print(fibonachi.pop_min())
    # print(fibonachi.pop_min())
    # print(fibonachi.pop_min())
    # print(fibonachi.pop_min())
    # print(fibonachi.pop_min())
    # print(fibonachi.pop_min())
    #
    # pers = persistent.PersistentTree()
    # pers.insert(-1)
    #
    # pers.insert(-4)
    # pers.insert(44)
    # pers.insert(-56)
    # print(pers.contains(-4))
    # pers.undo()
    # pers.history()
    # pers.redo()
    # # pers.undo()
    # pers.history()
    # # pers.redo()
    # # pers.history()
    # pers.insert(-5)
    # pers.history()
    # pers.delete(-1)
    # pers.delete(-5)
    # pers.history()
    # pers.undo()
    # pers.history()
    # pers.redo()
    # pers.history()




main()


