#include <iostream>
#include <vector>

using namespace std;

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

void processShape(Shape* shape) {
    if (Circle* c = dynamic_cast<Circle*>(shape)) {
        cout << "Круг: радиус = " << c->getRadius()
             << ", площадь = " << c->area() << '\n';
    } else if (Rectangle* r = dynamic_cast<Rectangle*>(shape)) {
        cout << "Прямоугольник: " << r->getWidth() << " x " << r->getHeight()
             << ", площадь = " << r->area() << '\n';
    } else {
        cout << "Неизвестная фигура\n";
    }
}

int main() {
    vector<Shape*> shapes = {new Circle(5), new Rectangle(4, 6), new Circle(3)};

    for (Shape* s : shapes) {
        processShape(s);
    }

    // обработка ссылок с исключением
    Circle circle(2);
    Shape& shapeRef = circle;
    try {
        Rectangle& rect = dynamic_cast<Rectangle&>(shapeRef);
        cout << "Ширина: " << rect.getWidth() << '\n';
    } catch (const bad_cast& e) {
        cout << "Исключение: " << e.what() << " — не прямоугольник\n";
    }

    for (Shape* s : shapes) delete s;
    return 0;
}
