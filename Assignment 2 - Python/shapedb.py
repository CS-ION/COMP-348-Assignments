from shape import Shape
from circle import Circle
from ellipse import Ellipse
from rhombus import Rhombus

"""COMP 348 AB - Assignment 2
   Done By: Syed Ayaan Jilani

   Citations :-
   1) Slides and Lecture notes 
   2) Programiz (syntax and documentation)
   3) Chat GPT (generating repetitive and easy functions)

   Instructions :-
   1) Run 'python shapedb.py' from the CLI
   2) The program will then ask you to enter your query 
   3) After entering the query, it will display the output 
   4) If query is wrong, it will display the error message
   5) The keeps asking for queries and terminates when user enters 'quit'
"""

class ShapeDatabase:

    def __init__(self):
        self.shapes = []

    def load(self, path):

        print(f"Processing {path}")

        try:
            with open(path, 'r') as file:
                lines = file.readlines()
                rows = len(lines)
                shapes = 0
                errors = 0

                for line in lines:
                    if line.strip():
            
                        params = line.split(" ")
                        name = params[0].lower()


                        if 'shape' in name:
                            if len(params) == 1:
                                shape = Shape()
                                self.shapes.append(shape)
                                shapes += 1
                            else:
                                errors += 1

                        elif name == 'circle':
                            if len(params) == 2:
                                radius = float(params[1])

                                if radius>=0:
                                    circle = Circle(radius)
                                    self.shapes.append(circle)
                                    shapes += 1
                                else:
                                    errors += 1

                            else:
                                errors += 1
                        
                        elif name == 'ellipse':
                            if len(params) == 3:
                                a = float(params[1])
                                b = float(params[2])

                                if a>=0 and b>=0:
                                    ellipse = Ellipse(a, b)
                                    self.shapes.append(ellipse)
                                    shapes += 1
                                else:
                                    errors += 1

                            else:
                                errors += 1
                            
                        elif name == 'rhombus':
                            if len(params) == 3:
                                p = float(params[1])
                                q = float(params[2])

                                if p>=0 and q>=0:
                                    rhombus = Rhombus(p, q)
                                    self.shapes.append(rhombus)
                                    shapes += 1
                                else:
                                    errors += 1

                            else:
                                errors += 1

                        else:
                            errors += 1

                print(f"Processed {rows} row(s), {shapes} shape(s) added, {errors} error(s).")
        except FileNotFoundError:
            print(f"Error: File not found: {path}")
        
    
    def print(self):
        for shape in self.shapes:
            shape.print()
    
    def summary(self):
        shape_dict = {}
        for shape in self.shapes:
            name = shape.__class__.__name__
            try:
                shape_dict[name] += 1
            except:
                shape_dict[name] = 1

        for shape in sorted(shape_dict.keys()):
            if shape!="Shape":
                print(f"{shape}(s): {shape_dict[shape]}")

        print(f"Shape(s): {sum(shape_dict.values())}")
    
    def details(self):
        sortedShapes = sorted(self.shapes, key= lambda x: x.__class__.__name__)
        deets = ""
        for shape in sortedShapes:
            name = shape.__class__.__name__
            if name == 'Circle':
                deets += f"circle {shape.radius}\n"
            elif name == 'Ellipse':
                deets += f"ellipse {shape.b} {shape.a}\n"
            elif name == 'Rhombus':
                deets += f"rhombus {shape.p} {shape.q}\n"
            elif name == 'Shape':
                deets = "shape\n" + deets
        return deets
    
    def save(self, path):
        try:
            with open(path, 'w') as file:
                details = self.details()
                file.write(details)
            print(f"Database saved to file: {path}")
        except:
            print(f"Error: Unable to save database to file: {path}")
    
    def toset(self):
        unique_details = []
        I = 0
        while I < len(self.shapes):
            
            shape = self.shapes[I]
            name = shape.__class__.__name__

            if name == 'Circle':
                temp = f"circle {shape.radius}"
            elif name == 'Ellipse':
                temp = f"ellipse {shape.b} {shape.a}"
            elif name == 'Rhombus':
                temp = f"rhombus {shape.p} {shape.q}"
            elif name == 'Shape':
                temp = "shape" 
            
            if temp in unique_details:
               del self.shapes[I]
            else:
                unique_details.append(temp)
                I += 1
                shape.id = I
        Shape.no_of_shapes = len(self.shapes)
        print("Database converted to a set (Duplicates Removed).")

def main():

    shapes_database = ShapeDatabase() 
    while True:
        query = input("\nEnter your Query : ").split(" ")

        if query[0].lower() == "load" and len(query)==2:
            shapes_database.shapes = []
            Shape.no_of_shapes = 0
            shapes_database.load(query[1])
        
        elif query[0].lower() == "quit":
            print("Program Terminated !!")
            break

        elif shapes_database.shapes == []:
            print("Empty Database, Please Load a File !!")

        elif query[0].lower() == "print":
            shapes_database.print()
        
        elif query[0].lower() == "summary":
            shapes_database.summary()
        
        elif query[0].lower() == "details":
            print(shapes_database.details(), end='')
        
        elif query[0].lower() == "save" and len(query)==2:
            shapes_database.save(query[1])
        
        elif query[0].lower() == "toset":
            shapes_database.toset()

        else:
            print("Invalid Query, Please Try Again !!")

if __name__ == '__main__':
    main()
