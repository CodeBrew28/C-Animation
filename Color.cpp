
#include "Color.h"

//default constructor
Color::Color() {
	r = 0;
   	g = 0;
   	b = 0;
}

//constructor
Color::Color(double rInput, double gInput, double bInput) {
	//inputs red green and blue values
	r = rInput;
	g = gInput;
	b = bInput;
}


//getters
double Color::getR() const {
	return r;
}

double Color::getG() const {
	return g;
}

double Color::getB() const {
	return b;
}

//setters
void Color::setR(double rInput) {
	r = rInput;
}

void Color::setG(double gInput) {
	g = gInput;
}

void Color::setB(double bInput) {
	b = bInput;
}
