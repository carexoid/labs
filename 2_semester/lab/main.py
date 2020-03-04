import showroom
import red_black_tree


def main():
    a = showroom.Model("Taurus", 2010)
    b = showroom.Model("Fusion", 2015)
    print(a.get_name())
    c = showroom.Brand("Ford", [a, b])
    print(c.get_models()[1].get_name())
    d = showroom.Auto(c, a)
    f = showroom.Auto(c, b)
    print(d.get_brand().get_name())
    e = showroom.Showroom([c])
    print(e.get_autos()[0].get_model().get_name())
    d.get_polynomial_hash()
    print(d.get_polynomial_hash())
    hashik = showroom.PerfectHash(e)
    print(hashik.contains_auto(d))
    print(d < f)

    rbtree = red_black_tree.RedBlackTree()
    rbtree.insert_value(12)
    print(rbtree)
    rbtree.insert_value(34)
    rbtree.insert_value(56)
    print(rbtree)
    rbtree.insert_value(24)
    rbtree.insert_value(4)
    print(rbtree)
    rbtree.insert_value(56)
    rbtree.insert_value(78)
    rbtree.insert_value(46)
    rbtree.insert_value(152)
    rbtree.insert_value(434)
    rbtree.insert_value(16)
    rbtree.insert_value(2)
    rbtree.insert_value(4)
    rbtree.insert_value(6)
    rbtree.insert_value(748)
    rbtree.insert_value(446)
    rbtree.insert_value(2)
    rbtree.insert_value(4)
    rbtree.insert_value(6)
    print(rbtree)




main()
