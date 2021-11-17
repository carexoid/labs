import sqlite3
from showroom import *


class DB:

    def __init__(self):
        self.conn = sqlite3.connect("showroom.db")
        self.cursor = self.conn.cursor()
        self.cursor.execute('create table if not exists brand(name text)')
        self.cursor.execute('create table if not exists model(name text, year integer, brand text)')
        self.conn.commit()

    def __del__(self):
        self.conn.close()

    def add_model(self, name: str, year: int, brand: str):
        try:
            self.cursor.execute("INSERT INTO model(name, year, brand) VALUES(?, ?, ?)", (str(name), int(year), str(brand)))
            self.conn.commit()

            return True
        except sqlite3.IntegrityError:
            return False

    def add_brand(self, name):
        try:
            self.cursor.execute("INSERT INTO brand(name) VALUES(?)", (str(name),))
            self.conn.commit()
        except sqlite3.IntegrityError:
            return False

    def get_models(self, brand):
        self.cursor.execute("SELECT * FROM model WHERE brand == :brand", {"brand": brand})
        return [Model(i[0], i[1]) for i in self.cursor.fetchall()]

    def get_brands(self):
        self.cursor.execute("SELECT * FROM brand")
        return [Brand(i[0], self.get_models(i[0])) for i in self.cursor.fetchall()]

    def get_brand(self, id):
        self.cursor.execute("SELECT * FROM brand WHERE rowid == :id", {"id": id})
        return self.cursor.fetchone()

    def get_autos(self):
        res = []
        for brand in self.get_brands():
            for model in brand.get_models():
                res.append(Auto(brand, model))
        return res


if __name__ == "__main__":
    db = DB()
    db.add_model("Taurus", 2013, "Ford")
    db.add_model("Fiesta", 2015, "Ford")
    db.add_brand("Ford")
    db.add_model("300", 2016, 'Chrysler')
    db.add_brand("Chrysler")

    db.add_model("Pacifica", 2018, 'Chrysler')
    db.add_model("Charger", 2017, "Dodge")
    db.add_model("Challenger", 2017, "Dodge")
    db.add_model("Dart", 2015, "Dodge")
    db.add_brand("Dodge")

    db.add_model("300 C", 2014, 'Chrysler')
    db.add_model("Charger RT", 2017, "Dodge")
    db.add_model("Challenger RT", 2017, "Dodge")

    db.add_model("300 SRT", 2018, 'Chrysler')
    db.add_model("Charger SRT", 2017, "Dodge")
    db.add_model("Challenger SRT", 2017, "Dodge")

    db.add_model("Taurus", 2010, "Ford")
    db.add_model("Fusion", 2015, "Ford")

    db.add_model("E-class", 2001, "Mercedes")
    db.add_model("S-class", 2010, "Mercedes")

    db.add_brand("Mercedes")

    print(db.get_models("Ford"))
    print(db.get_brands())
    print(db.get_autos())