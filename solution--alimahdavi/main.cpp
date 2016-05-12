+/* ----------------------------------------------------------------------------
 + * Copyright &copy; 2016 alimahdavi <alimahdavi05@csu.fullerton.edu>
 + * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 + * ------------------------------------------------------------------------- */
 
#include <iostream>
#include <chrono>
#include <thread>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

class Point {
private:
	float x, y;
public:
	Point()
	{
		x, y = 0;
	}
	~Point() = default;
	Point::Point(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
	float getX() const
	{
		return x;
	}
	float getY() const
	{
		return y;
	}
};

class Shape {
public:
	virtual void contains(const Point & p) const = 0;
	virtual ~Shape() = default;
};

class Rectangle : public Shape
{
private:
	float height, width;
public:
	Rectangle()
	{
		height = 0;
		width = 0;
	}
	~Rectangle() = default;
	Rectangle::Rectangle(float inHeight, float inWidth)
	{
		height = inHeight;
		width = inWidth;
	}
	float getHeight()
	{
		return height;
	}
	float getWidth()
	{
		return width;
	}
	void draw(int frameSleep)
	{
		float h = this->getHeight();
		float w = this->getWidth();

		assert(h >= 2);   // Height has to be at least 2 for a top and bottom side
		assert(w >= 2);  // Width has to be at least 2 for a left and right side

						 // Draw row of 'w' asterisks for top side
		cout << string(w, '*') << endl;

		// Draw sides: asterisk, width-2 spaces, asterisk
		for (int j = 0; j < h - 2; ++j)
		{
			cout << '*' << string(w - 2, ' ') << '*' << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(frameSleep));
		}


		// Draw row of 'w' asterisks for bottom side
		cout << string(w, '*') << endl;
	}
	void contains(const Point & p) const
	{
		if ((p.getX() < width) && (p.getY() < height))
			cout << "The point you have inputted is inside the rectangle" << endl;
		else
			cout << "The point you have inputted is outside the rectangle" << endl;
	}
};

class Ellipse : public Shape
{
private:
	float Rx, Ry;
public:
	Ellipse()
	{
		Rx = 0;
		Ry = 0;
	}
	~Ellipse() = default;
	Ellipse::Ellipse(float inRx, float inRy)
	{
		Rx = inRx;
		Ry = inRy;
	}
	void contains(const Point & p) const
	{
		double lK = sqrt(p.getY()*p.getY() + p.getX()*p.getX());
		double a = atan2(p.getY(), p.getX());
		double b = atan(tan(a)*this->Rx / this->Ry);
		double x = this->Rx*cos(b);
		double y = this->Ry*sin(b);
		double lE = sqrt(y*y + x*x);

		if (lK < lE)
			cout << "The point you have inputted is inside the Ellipse" << endl;
		else
			cout << "The point you have inputted is outside the Ellipse" << endl;
	}
	~Ellipse() = default;
};

class Circle : public Ellipse
{
private:
	float radius;
public:
	Circle()
	{
		radius = 0;
	}
	~Circle() = default;
	Circle::Circle(float inRadius)
	{
		radius = inRadius;
	}
	void contains(const Point & p) const
	{
		float distance = sqrt(p.getX()*p.getX() + p.getY()*p.getY());
		if (distance < radius)
			cout << "The point you have inputted is inside the circle" << endl;
		else
			cout << "The point you have inputted is outside the circle" << endl;
	}
	void draw(int frameSleep)
	{
		float N = 2 * radius;
		float di = 1.0 / radius;

		for (int i = int(radius); i >= -int(radius); --i) {
			auto n = static_cast<int>(cos(asin(di*abs(int(i))))*radius);
			for (unsigned j = 0; j <= radius - n; ++j) std::cout << " ";
			for (unsigned j = 0; j <= 2 * n; ++j) std::cout << "*";
			for (unsigned j = 0; j <= radius - n; ++j) std::cout << " ";
			std::this_thread::sleep_for(std::chrono::milliseconds(frameSleep));
			std::cout << std::endl;
		}
	}
	~Circle() = default;
};

class Square : public Rectangle
{
private: 
	float length;
public:

	Square()
	{
		length = 0;
	}
	~Square() = default;
	Square::Square(float inLength)
	{
		length = inLength;
	}
	float getLength()
	{
		return length;
	}
	void contains(const Point & p) const
	{
		if ((p.getX() < length) && (p.getY() < length))
			cout << "The point you have inputted is inside the square" << endl;
		else
			cout << "The point you have inputted is outside the square" << endl;
	}
	void draw(int frameSleep)
	{
		float l = this->getLength();

		assert(l >= 2);   // Height has to be at least 2 for a top and bottom side
								 // Draw row of 'w' asterisks for top side
		cout << string(l, '*') << endl;

		// Draw sides: asterisk, width-2 spaces, asterisk
		for (int j = 0; j < l - 2; ++j) 
		{
			cout << '*' << string(l - 2, ' ') << '*' << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(frameSleep));
		}

		// Draw row of 'w' asterisks for bottom side
		cout << string(l, '*') << endl;
	}
};

int main() {

	const int frameSleep = 50;
	float recHeight, recWidth, ellipseRx, ellipseRy, circleR, squareLen, pointX, pointY;

	cout << "Demonstration of different geometrical figures.\n1)Rectangle\n2)Ellipse\n3)Circle\n4)Squre" << endl;
	system("pause");
	system("cls");

	cout << "Please input the required values: " << endl;

	cout << "\nX coordinate of the point we will check  = ";
	cin >> pointX;

	cout << "\nY coordinate of the point we will check = ";
	cin >> pointY;
	Point p = Point(pointX, pointY);
	system("pause");
	system("cls");

	cout << "Lets draw the figures and check if the point is inside of them:" << endl << endl;

	cout << "Rectangle height = ";
	cin >> recHeight;

	cout << "\nRectangle width = ";
	cin >> recWidth;
	Rectangle r = Rectangle(recHeight, recWidth);
	r.draw(frameSleep);
	r.contains(p);
	system("pause");
	system("cls");

	cout << "\nCircle radius = ";
	cin >> circleR;
	Circle c = Circle(circleR);
	c.draw(frameSleep);
	c.contains(p);
	system("pause");
	system("cls");

	cout << "\nSquare side length = ";
	cin >> squareLen;
	Square s = Square(squareLen);
	s.draw(frameSleep);
	s.contains(p);
	system("pause");
	system("cls");

	cout << "\nEllipse X radius = ";
	cin >> ellipseRx;
	cout << "\nEllipse Y radius = ";
	cin >> ellipseRy;
	Ellipse e = Ellipse(ellipseRx, ellipseRy);
	e.contains(p);
	system("pause");
	system("cls");

	return 0;
}
