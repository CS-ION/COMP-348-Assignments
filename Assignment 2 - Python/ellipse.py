import math
from shape import Shape


class Ellipse(Shape):
    def __init__(self, a, b):
        super().__init__()
        self.a = max(a, b)
        self.b = min(a, b)

    def area(self):
        return math.pi * self.a * self.b

    def eccentricity(self):
        try:
            return math.sqrt(self.a ** 2 - self.b ** 2)
        except ValueError:
            return None