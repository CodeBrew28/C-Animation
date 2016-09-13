#ifndef CIRCLE_H
#define CIRCLE_H

#include "Color.h"


class Circle {
	public:
		Circle() ;
		Circle(double xPosInput, double yPosInput, double radiusInput, Color circleColorInput) ;
		
		double getXPos() const;
		double getYPos() const; 
		Color getColor() const;
		double getRadius() const;
		double getTheta()const;
		double getOrbitDistance() const;
		double getCenterX()const;
		double getCenterY()const;

		void setXPos(double xPosInput);
		void setYPos(double yPosInput);
		void setColor(Color circleColorInput);
		void setRadius(double radiusInput);
		void setOrbitDistance(double orbitDistanceInput);
		void setCenterX(double centerXInput);
		void setCenterY(double centerYInput);


		void translate(double dx, double dy);
		void rotate(double thetaInput);
	private:
		double xPos;
		double yPos;
		double radius;
		Color circleColor;
		double theta;
		double orbit_distance;
		double center_x;
		double center_y;
};

#endif//circle.h