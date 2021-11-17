import random


class Model:

    def __init__(self, name, year):
        self._name = name
        self._year = year

    def get_name(self):
        return self._name

    def get_year(self):
        return self._year

    def __repr__(self):
        return str((self._name, self._year))


class Brand:

    def __init__(self, name, models):
        self._name = name
        self._models = models

    def add_model(self, new_model) -> None:
        self._models.append(new_model)

    def get_name(self):
        return self._name

    def get_models(self):
        return self._models

    def contains_model_with_params(self, name, year):
        for i in self._models:
            if i == (name, year):
                return True
            else:
                return False

    def __repr__(self):
        return str((self._name, self._models))



class Auto:

    def __init__(self, brand, model):
        self._brand = brand
        self._model = model
        self._poly_hash = None

    def get_brand(self):
        return self._brand

    def get_model(self):
        return self._model

    def get_polynomial_hash(self):
        if self._poly_hash is None:
            full_name = self._brand.get_name() + self._model.get_name() + str(self._model.get_year())
            self._poly_hash = 0
            p = 67
            m = 10e9
            for char in full_name:
                self._poly_hash = int((self._poly_hash * p + ord(char) - ord('A')) % m)
        return self._poly_hash

    def __lt__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name() + str(self._model.get_year())\
               < other.get_brand().get_name() + other.get_model().get_name() + str(self._model.get_year())

    def __gt__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name() + str(self._model.get_year())\
               > other.get_brand().get_name() + other.get_model().get_name() + str(self._model.get_year())

    def __le__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name() + str(self._model.get_year())\
               <= other.get_brand().get_name() + other.get_model().get_name() + str(self._model.get_year())

    def __ge__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name() + str(self._model.get_year())\
               >= other.get_brand().get_name() + other.get_model().get_name() + str(self._model.get_year())

    def __eq__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name() + str(self._model.get_year())\
               == other.get_brand().get_name() + other.get_model().get_name() + str(self._model.get_year())

    def __str__(self):
        return self._brand.get_name() + " " + self._model.get_name()

    def __repr__(self):
        return self._brand.get_name() + " " + self._model.get_name() + " " + str(self._model.get_year())


class Showroom:

    def __init__(self, brands):
        self._all_autos = [Auto(brand, model) for brand in brands for model in brand.get_models()]

    def get_autos(self):
        return self._all_autos


class PerfectHash:

    def __init__(self, showroom, p=101):
        assert p > len(showroom.get_autos()) and "Prime p must be greater than size of showroom"
        self._p = p
        self._coefs = 1, 1, len(showroom.get_autos())
        self._hash_table = [None for i in range(0, self._coefs[2])]
        self._showroom = showroom
        self._calc_hash()

    def _calc_hash(self):
        all_autos = self._showroom.get_autos()
        hash_list = [[] for i in range(0, self._coefs[2])]
        for auto in all_autos:
            new_i = int((self._coefs[0] * auto.get_polynomial_hash() + self._coefs[1]) % self._p % self._coefs[2])
            print(new_i)
            hash_list[new_i].append(auto)

        for ind in range(0, self._coefs[2]):
            if hash_list[ind]:
                flag = True
                while flag:
                    new_m = len(hash_list[ind]) ** 2
                    new_a = random.randint(3, self._p - 1)
                    new_b = random.randint(3, self._p - 1)
                    self._hash_table[ind] = new_a, new_b, new_m, [None for i in range(0, new_m)]
                    flag = False
                    for auto in hash_list[ind]:
                        new_j = int((new_a * auto.get_polynomial_hash() + new_b) % self._p % new_m)
                        if self._hash_table[ind][3][new_j]:
                            flag = True
                            break
                        self._hash_table[ind][3][new_j] = auto

    def contains_auto(self, auto):
        coefs = self.get_poly_hash(auto)
        if not coefs:
            return False
        return True if self._hash_table[coefs[0]][3][coefs[1]] == auto else False

    def get_poly_hash(self, auto):
        first_hash = int((self._coefs[0] * auto.get_polynomial_hash() + self._coefs[1]) % self._p % self._coefs[2])
        if self._hash_table[first_hash] is not None:
            second_hash = int((self._hash_table[first_hash][0] * auto.get_polynomial_hash()
                               + self._hash_table[first_hash][1]) % self._p % self._hash_table[first_hash][2])
            return first_hash, second_hash
        return None

    def __str__(self):
        res = ""
        for i in self._hash_table:
            res += ":::"
            if i:
                for j in i[3]:
                    if j:
                        res += str(j) + ", "
            res += "\n"
        return res
