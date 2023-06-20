import math
from shape import Shape


class Rhombus(Shape):
    def __init__(self, p, q):
        super().__init__()
        self.p = p
        self.q = q

    def perimeter(self):
        return 2 * math.sqrt(self.p ** 2 + self.q ** 2)

    def area(self):
        return 0.5 * self.p * self.q

    def side(self):
        return math.sqrt(self.p ** 2 + self.q ** 2) / 2

    def inradius(self):
        try:
            return (self.p * self.q) / (2 * math.sqrt(self.p ** 2 + self.q ** 2))
        except ValueError:
            return None
