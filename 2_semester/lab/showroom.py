import random


class Model:

    def __init__(self, name, year):
        self._name = name
        self._year = year

    def get_name(self):
        return self._name

    def get_year(self):
        return self._year


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
            full_name = self._brand.get_name() + self._model.get_name()
            self._poly_hash = 0
            p = 67
            m = 10e9
            for char in full_name:
                self._poly_hash = int((self._poly_hash * p + ord(char) - ord('A')) % m)
        return self._poly_hash

    def __lt__(self, other):
        return self.get_brand().get_name() + self.get_model().get_name()\
               < other.get_brand().get_name() + other.get_model().get_name()


class Showroom:

    def __init__(self, brands):
        self._all_autos = [Auto(brand, model) for brand in brands for model in brand.get_models()]

    def get_autos(self):
        return self._all_autos


class PerfectHash:

    def __init__(self, showroom):
        self._coefs = 1, 0, len(showroom.get_autos())
        self._hash_table = [None for i in range(0, self._coefs[2])]
        self._showroom = showroom
        self._calc_hash()

    def _calc_hash(self):
        all_autos = self._showroom.get_autos()
        hash_list = [[] for i in range(0, self._coefs[2])]
        for auto in all_autos:
            new_i = int((self._coefs[0] * auto.get_polynomial_hash() + self._coefs[1]) % self._coefs[2])
            print(new_i)
            hash_list[new_i].append(auto)
        #     тут хуетa
        for ind in range(0, self._coefs[2]):
            new_m = len(hash_list[ind]) ** 2
            new_a = random.randint(3, 100)
            new_b = random.randint(3, 100)
            self._hash_table[ind] = new_a, new_b, new_m, [None for i in range(0, new_m)]
            for auto in hash_list[ind]:
                new_j = int((new_a * auto.get_polynomial_hash() + new_b) % new_m)
                self._hash_table[ind][3][new_j] = auto

    def contains_auto(self, auto):
        return True if self.get_poly_hash(auto) is not None else False

    def get_poly_hash(self, auto):
        first_hash = int((self._coefs[0] * auto.get_polynomial_hash() + self._coefs[1]) % self._coefs[2])
        if self._hash_table[first_hash] is not None:
            second_hash = int((self._hash_table[first_hash][0] * auto.get_polynomial_hash()
                               + self._hash_table[first_hash][1]) % self._hash_table[first_hash][2])
            return first_hash, second_hash
        return None
