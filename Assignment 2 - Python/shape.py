class Shape:
    no_of_shapes = 0

    def __init__(self):
        Shape.no_of_shapes += 1
        self.id = Shape.no_of_shapes

    def print(self):
        print(f"{self.id}: {self.__class__.__name__}, perimeter: {round(self.perimeter(),5) if self.perimeter() else 'undefined'}, area: {round(self.area(),5) if self.area() else 'undefined'}", end='')

        if (self.__class__.__name__ == "Ellipse"):
            print(f", linear eccentricity: {round(self.eccentricity(),5) if self.eccentricity() else 'undefined'}")
        elif (self.__class__.__name__ == "Rhombus"):
            print(f", side : {round(self.side(),5) if self.side() else 'undefined'}, in-radius : {round(self.inradius(),5) if self.inradius() else 'undefined'}")
        else:
            print()

    def perimeter(self):
        return None

    def area(self):
        return None