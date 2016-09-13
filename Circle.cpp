#include "Circle.h"
#include <cmath>
// #include <iostream>

//default constructor
Circle::Circle() {
	xPos = 0;
	yPos = 0;
	radius = 0;
	circleColor = Color();
	theta = 0;
	orbit_distance = 0;
	center_x = 0;
	center_y = 0;
}

//constructor to create a circle
Circle::Circle(double xPosInput, double yPosInput, double radiusInput, Color circleColorInput) {
	//x and y coordinate of circle
	xPos = xPosInput;
	yPos = yPosInput;
	//radius of circle
	radius = radiusInput;
	//color of circle
	circleColor = circleColorInput;
	//angle representing its angular position on the ellipse
	theta = 0;
	//distance from sun
	orbit_distance = 0;
	//the x and y coordiantes about which the circle revolves
	center_x = 0;
	center_y = 0;
}

//getter methods
double Circle::getXPos() const {
	return xPos;
}

double Circle::getYPos() const {
	return yPos;
}

Color Circle::getColor() const {
	return circleColor;
}

double Circle::getRadius() const {
	return radius;
}

double Circle::getTheta() const {
	return theta;
}

double Circle::getOrbitDistance() const {
	return orbit_distance;
}

double Circle::getCenterX()const {
	return center_x;
}

double Circle::getCenterY()const {
	return center_y;
}

//setter methods
void Circle::setXPos(double xPosInput) {
	xPos = xPosInput;
}

void Circle::setYPos(double yPosInput) {
	yPos = yPosInput;
}

void Circle::setColor(Color circleColorInput) {
	circleColor = circleColorInput;
}

void Circle::setRadius(double radiusInput) {
	radius = radiusInput;
}

void Circle::setOrbitDistance(double orbitDistanceInput) {
	orbit_distance = orbitDistanceInput;
}

void Circle::setCenterX(double centerXInput) {
	center_x = centerXInput;
}

void Circle::setCenterY(double centerYInput) {
	center_y = centerYInput;
}


//rotates the circle to a different position on the ellipse
//calculates the radius based on the angle
//uses the equation r = ab / sqrt(a^2 sin^2(theta) + b^2cos^2(theta))
void Circle::rotate(double thetaInput) {
	theta = fmod(theta + thetaInput, 360);
	double my_orbit_distance = (1.5 * orbit_distance  * orbit_distance) / sqrt(  ( sin( fmod(theta, 360) * 3.141592653589793238463 / 180) * sin(fmod(theta, 360)* 3.141592653589793238463 / 180) * orbit_distance * orbit_distance * 1.5 * 1.5) +   ( cos(fmod(theta, 360) * 3.141592653589793238463 / 180) * cos(fmod(theta, 360) * 3.141592653589793238463 / 180) * orbit_distance * orbit_distance) );
	yPos = center_x + my_orbit_distance * sin(theta * 3.141592653589793238463 / 180);
	xPos = center_y + my_orbit_distance * cos(theta * 3.141592653589793238463 / 180);
}




