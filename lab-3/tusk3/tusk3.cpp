#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const string& shapeName) const = 0;
};


class VectorRenderer : public Renderer {
public:
    void render(const string& shapeName) const override {
        cout << "Drawing " << shapeName << " as vectors" << endl;
    }
};

class RasterRenderer : public Renderer {
public:
    void render(const string& shapeName) const override {
        cout << "Drawing " << shapeName << " as pixels" << endl;
    }
};


class Shape {
protected:
    shared_ptr<Renderer> renderer;
public:
    Shape(shared_ptr<Renderer> rend) : renderer(rend) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual string name() const = 0;
};



class Circle : public Shape {
public:
    Circle(shared_ptr<Renderer> rend) : Shape(rend) {}
    void draw() const override {
        renderer->render("Circle");
    }
    string name() const override { return "Circle"; }
};

class Square : public Shape {
public:
    Square(shared_ptr<Renderer> rend) : Shape(rend) {}
    void draw() const override {
        renderer->render("Square");
    }
    string name() const override { return "Square"; }
};

class Triangle : public Shape {
public:
    Triangle(shared_ptr<Renderer> rend) : Shape(rend) {}
    void draw() const override {
        renderer->render("Triangle");
    }
    string name() const override { return "Triangle"; }
};

int main() {
    shared_ptr<Renderer> vectorRenderer = make_shared<VectorRenderer>();
    shared_ptr<Renderer> rasterRenderer = make_shared<RasterRenderer>();

    Circle circle(vectorRenderer);
    Square square(rasterRenderer);
    Triangle triangle(vectorRenderer);

    circle.draw();   
    square.draw();    
    triangle.draw();  

    return 0;
}
