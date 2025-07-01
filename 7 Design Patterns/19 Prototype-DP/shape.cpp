#include <iostream>
#include <string>
using namespace std;

// Prototype Interface
class Shape {
public:
    virtual Shape* clone() = 0;
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// Concrete Prototype: Circle
class Circle : public Shape {
    int radius;
public:
    Circle(int r) : radius(r) {}
    Circle(const Circle& other) { radius = other.radius; }

    Shape* clone() override {
        return new Circle(*this);  // Use copy constructor
    }

    void draw() override {
        cout << "Drawing Circle with radius " << radius << endl;
    }
};

// Concrete Prototype: Rectangle
class Rectangle : public Shape {
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    Rectangle(const Rectangle& other) { width = other.width; height = other.height; }

    Shape* clone() override {
        return new Rectangle(*this);
    }

    void draw() override {
        cout << "Drawing Rectangle of " << width << "x" << height << endl;
    }
};

// Main function: Client
int main() {
    Shape* circle = new Circle(10);
    Shape* rectangle = new Rectangle(20, 15);

    // Clone objects
    Shape* circleCopy = circle->clone();
    Shape* rectangleCopy = rectangle->clone();

    // Use original and copied objects
    circle->draw();         // Output: Drawing Circle with radius 10
    circleCopy->draw();     // Output: Drawing Circle with radius 10

    rectangle->draw();      // Output: Drawing Rectangle of 20x15
    rectangleCopy->draw();  // Output: Drawing Rectangle of 20x15

    // Cleanup
    delete circle;
    delete rectangle;
    delete circleCopy;
    delete rectangleCopy;

    return 0;
}
