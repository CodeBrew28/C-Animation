//Arshia Malkani Period 4
//Animation Final Project

#include <iostream>
#include <iomanip>
#include "Circle.h"
#include "Color.h"
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <string>
#include <cmath>
#include <fstream>
#include <cstring>
using namespace std;

//converts strings to ints
int string_to_int(string s) {
   istringstream strm;
   strm.str(s);
   int n=0;
   strm >> n;
   return n;
}

//creates the bmp
void write_bmp_header_file(ofstream& output_file, int px, int pz) {
	unsigned short int bfType;
	bfType = 0x4D42;
   output_file.write ((char*)&bfType, sizeof (short int));   

   unsigned int bfSize;
	int rem;
	rem=3*px%4;
	int padding;
	if(rem==0) {
		padding=0;
	} else {
		padding=4-rem;
	}

	bfSize = 14 + 40 + (3 * px+padding) * pz;   

    output_file.write ((char*)&bfSize, sizeof (int));   

    unsigned short int bfReserved1;
	bfReserved1 = 0;
    output_file.write ((char*)&bfReserved1, sizeof (short int));   

	unsigned short int bfReserved2;
	bfReserved2 = 0;
    output_file .write ((char*)&bfReserved2, sizeof (short int));   

	unsigned int bfOffsetBits;
	bfOffsetBits = 14 + 40;
    output_file.write ((char*)&bfOffsetBits, sizeof (int));   

	unsigned int biSize;
	biSize=40;
    output_file.write ((char*)&biSize, sizeof (int));   
   
	int biWidth;
	biWidth=px;
    output_file.write ((char*)&biWidth, sizeof (int));   

	int biHeight;
	biHeight=pz;
    output_file.write ((char*)&biHeight, sizeof (int));   

	unsigned short int biPlanes;
	biPlanes=1;
    output_file.write ((char*)&biPlanes, sizeof (short int));   

	unsigned short int biBitCount;
	biBitCount=24;
    output_file.write ((char*)&biBitCount, sizeof (short int));   

	unsigned int biCompression;
    unsigned int bi_rgb = 0;

	biCompression=bi_rgb;
    output_file.write ((char*)&biCompression, sizeof (int));   

	unsigned int biSizeImage;
	biSizeImage=0;
    output_file.write ((char*)&biSizeImage, sizeof (int));   

	unsigned int biXPelsPerMeter;
	biXPelsPerMeter=0;
    output_file.write ((char*)&biXPelsPerMeter, sizeof (int));   

	unsigned int biYPelsPerMeter;
	biYPelsPerMeter=0;
    output_file.write ((char*)&biYPelsPerMeter, sizeof (int));   

	unsigned int biClrUsed;
	biClrUsed = 0;
    output_file.write ((char*)&biClrUsed, sizeof (int));   

	unsigned int biClrImportant;
	biClrImportant = 0;
    output_file.write ((char*)&biClrImportant, sizeof (int));   
}

//checks of a character is a number
bool isnumber(char i) {
	return (i == '1' || i == '2' || i == '3'|| i == '4'|| i == '5'|| i == '6'|| i == '7'|| i == '8'|| i == '9' || i == '0');
}

//reads every line in the config file
double readline(string line) {
 	int i = 0;
 	while (!isnumber(line[i])) { i++; }
 	int j = 1;
 	while (!isspace(line[i + j])) { j++; }
 	istringstream strm;
   	strm.str( line.substr(i, j) );
   	double n = 0;
    strm >> n;
   	return n;
}

//draws the planets and moons
void drawCircle(Circle c, int pz, int px, unsigned char * * buffer ) {
	int xcenter = c.getXPos();
	int ycenter = c.getYPos();
	//draws a circle for planets and moons 
	//uses the equation (x – h)^2 + (y – k)^2 = r^2
	for(int i=0; i<pz; i++) {
		for(int j= 0;j<3*px;j=j+3) {
			if (((i - xcenter) *(i - xcenter)) + ((j/3 - ycenter) * (j/3 - ycenter)) < c.getRadius() * c.getRadius()) {
			    buffer[i][j+0]=c.getColor().getB();
				buffer[i][j+1]=c.getColor().getG();
				buffer[i][j+2]=c.getColor().getR();
			}
		}
	}
}

//draws the orbits for the planets
void drawOrbit(Circle c, int pz, int px, unsigned char * * buffer, double orbit_outline_thickness ) {
	int xcenter = c.getXPos();
	int ycenter = c.getYPos();
	//draw a black ellipse inside a white ellipse to create an orbit
	//uses the equation (x-h)^2/a^2 + (y-k)^2/b^2 = 1
	for(int i=0; i<pz; i++) {
		for(int j= 0;j<3*px;j=j+3) {
			double dx = (double)(j/3 - ycenter) / (double)(c.getRadius());
			double dy = (double)(i - xcenter) / (double)(c.getRadius() * 1.5);
			if((dx*dx+dy*dy - 1 >= 0) && (dx*dx+dy*dy - 1 <= orbit_outline_thickness)) {
			    buffer[i][j+0]=c.getColor().getB();
				buffer[i][j+1]=c.getColor().getG();
				buffer[i][j+2]=c.getColor().getR();
			}
		}
	}
}

//draws a spaceship
void draw_rocket(Circle c, unsigned char * * buffer, double px, double pz, double orbit_outline_thickness) {
		int xcenter = c.getXPos();
		int ycenter = c.getYPos();
		
		//draws a circle for the spaceship image
		//uses the equation (x – h)^2 + (y – k)^2 = r^2
		for(int i=0; i<pz; i++) {
			for(int j= 0;j<3*px;j=j+3) {
				if (((i - xcenter) *(i - xcenter)) + ((j/3 - ycenter) * (j/3 - ycenter)) < c.getRadius() * c.getRadius()/4) {
				    buffer[i][j+0]=c.getColor().getB();
					buffer[i][j+1]=c.getColor().getG();
					buffer[i][j+2]=c.getColor().getR();
				}
			}
		}
		
		//draws an ellipse for the spaceship image
		//uses the equation (x-h)^2/a^2 + (y-k)^2/b^2 = 1 
		for(int i=0; i<pz; i++) {
			for(int j= 0;j<3*px;j=j+3) {
				double dx = (double)(j/3 - ycenter) / (double)(c.getRadius()* 1);
				double dy = (double)(i - xcenter) / (double)(c.getRadius() * 0.25);
				if((dx*dx+dy*dy - 1 <= orbit_outline_thickness)) {
				    buffer[i][j+0]=c.getColor().getB();
					buffer[i][j+1]=c.getColor().getG();
					buffer[i][j+2]=c.getColor().getR();
				}
			}
		}
}

int main()
{
	//reading config file
	ifstream in_file;
    in_file.open("config_data.txt");
    if (in_file.fail()) {
        cout << endl << "Error opening input file: config_data.txt" << endl;
        return 0;
    } 
    /** recieving inputs and catching input errors **/ 
	    string line;
	    getline(in_file, line);
	   	double image_width = readline(line);
	    getline(in_file, line);
	    double image_height = readline(line);
	    if (image_width < 0 || image_height < 0) {
	    	cout << "Inavalid image height and width" << endl;
	    	return 0;
	    }

		getline(in_file, line);
		double number_of_stars = readline(line);
		if (number_of_stars < 0) {
			cout << "Invalid number_of_stars" << endl;
			return 0;
		}

		getline(in_file, line);
		double random_number_seed = readline(line);
		getline(in_file, line);
		double min_star_radius = readline(line);
		getline(in_file, line);
		double max_star_radius = readline(line);
		getline(in_file, line);
		if (min_star_radius < 0 || max_star_radius < 0) {
			cout << "Invalid star_radius" << endl;
			return 0;
		}

		double min_star_intensity = readline(line);
		getline(in_file, line);
		double max_star_intensity = readline(line);
		getline(in_file, line);
		if (min_star_intensity < 0 || max_star_intensity < 0) {
			cout << "Invalid star_intensity" << endl;
			return 0;
		}


		double sun_x_coordinate  = readline(line);
		getline(in_file, line);
		double sun_y_coordinate  = readline(line);
		getline(in_file, line);
		if (sun_x_coordinate < 0 || sun_x_coordinate > image_width || sun_y_coordinate < 0 || sun_y_coordinate > image_height) {
			cout << "Invalid sun x and y coordinates" << endl;
			return 0;
		}
		
		double sun_color_red = readline(line);
		getline(in_file, line);
		double sun_color_green = readline(line);
		getline(in_file, line);
		double sun_color_blue = readline(line);
		if (sun_color_red > 255 ||sun_color_green > 255 || sun_color_blue > 255) {
			cout << "Invalid sun color" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double sun_radius = readline(line);
		if (sun_radius < 0) {
			cout << "Invalid sun_radius" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double mercury_distance_from_sun  = readline(line);
		if (mercury_distance_from_sun < 0) {
			cout << "Invalid mercury_distance_from_sun" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double mercury_color_red = readline(line);
		getline(in_file, line);
		double mercury_color_green = readline(line);
		getline(in_file, line);
		double mercury_color_blue = readline(line);
		if (mercury_color_red > 255 ||mercury_color_green > 255 || mercury_color_blue > 255 || mercury_color_red < 0 || mercury_color_green < 0 || mercury_color_blue < 0) {
			cout << "Invalid mercury color" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double mercury_radius = readline(line);
		if (mercury_radius < 0) {
			cout << "Invalid mercury_radius" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double venus_distance_from_sun  = readline(line);
		if (venus_distance_from_sun < 0) {
			cout << "Invalid venus_distance_from_sun" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double venus_color_red = readline(line);
		getline(in_file, line);
		double venus_color_green = readline(line);
		getline(in_file, line);
		double venus_color_blue = readline(line);
		if (venus_color_red > 255 ||venus_color_green > 255 || venus_color_blue > 255 || venus_color_red < 0 || venus_color_green < 0 || venus_color_blue < 0) {
			cout << "Invalid venus color" << endl;
			return 0;
		}
		

		getline(in_file, line);
		double venus_radius = readline(line);
		if (venus_radius < 0) {
			cout << "Invalid venus_radius" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double earth_distance_from_sun  = readline(line);
		if (earth_distance_from_sun < 0) {
			cout << "Invalid earth_distance_from_sun" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double earth_color_red = readline(line);
		getline(in_file, line);
		double earth_color_green = readline(line);
		getline(in_file, line);
		double earth_color_blue = readline(line);
		if (earth_color_red > 255 ||earth_color_green > 255 ||earth_color_blue > 255 || earth_color_red < 0 || earth_color_green < 0 || earth_color_blue < 0) {
			cout << "Invalid earth color" << endl;
			return 0;
		}

		getline(in_file, line);
		double earth_radius = readline(line);
		if (earth_radius < 0) {
			cout << "Invalid earth_radius" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double mars_distance_from_sun  = readline(line);
		if (mars_distance_from_sun < 0) {
			cout << "Invalid mars_distance_from_sun" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double mars_color_red = readline(line);
		getline(in_file, line);
		double mars_color_green = readline(line);
		getline(in_file, line);
		double mars_color_blue = readline(line);
		if (mars_color_red > 255 ||mars_color_green > 255 ||mars_color_blue > 255 || mars_color_red < 0 || mars_color_green < 0 || mars_color_blue < 0) {
			cout << "Invalid earth color" << endl;
			return 0;
		}

		
		getline(in_file, line);
		double mars_radius = readline(line);	
		if (mars_radius < 0) {
			cout << "Invalid mars_radius" << endl;
			return 0;
		}

		getline(in_file, line);
		double number_total_frames_per_second = readline(line);
		getline(in_file, line);
		double total_seconds = readline(line);
		if (number_total_frames_per_second < 0 || total_seconds < 0 ){
			cout << "Invalid number_total_frames_per_second or total_seconds" << endl;
			return 0;
		}

		getline(in_file, line);
		double mercury_cycles_per_total_seconds  = readline(line);
		getline(in_file, line);
		double venus_cycles_per_total_seconds  = readline(line);
		getline(in_file, line);
		double earth_cycles_per_total_seconds  = readline(line);
		getline(in_file, line);
		double mars_cycles_per_total_seconds  = readline(line);
		getline(in_file, line);
		double moon_cycles_per_total_second = readline(line);
		if (mercury_cycles_per_total_seconds < 0 || venus_cycles_per_total_seconds < 0 || earth_cycles_per_total_seconds < 0 || mars_cycles_per_total_seconds< 0) {
			cout << "Invalid planet cycles per second" << endl;
			return 0;
		}

		
		getline(in_file, line);
		double moon_radius = readline(line);
		if (moon_radius < 0) {
			cout << "Invalid moon_radius" << endl;
			return 0;
		}

		
		getline(in_file, line);
		double moon_distance_from_planet = readline(line);
		if (moon_distance_from_planet < 0) {
			cout << "Invalid moon_distance_from_planet" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double zooming_out_rate = readline(line);
		if ( zooming_out_rate > 1|| zooming_out_rate < 0) {
			cout << "Invalid zooming_out_rate" << endl;
			return 0;
		}
		
		getline(in_file, line);
		int number_of_asteroids  = readline(line);
		if (number_of_asteroids < 0) {
			cout << "Invalid number_of_asteroids" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double minimum_asteroid_belt_distance_from_sun  = readline(line);
		getline(in_file, line);
		double maximum_asteroid_belt_distance_from_sun  = readline(line);
		if (minimum_asteroid_belt_distance_from_sun < 0 || maximum_asteroid_belt_distance_from_sun < 0) {
			cout << "Invalid asteroid_belt_distance_from_sun" << endl;
			return 0;
		}

		getline(in_file, line);
		double asteroid_color_red  = readline(line);
		getline(in_file, line);
		double asteroid_color_green = readline(line);
		getline(in_file, line);
		double asteroid_color_blue = readline(line);
		getline(in_file, line);
		if (asteroid_color_red > 255 ||asteroid_color_green > 255 || asteroid_color_blue > 255 ||  asteroid_color_red < 0 || asteroid_color_green < 0 || asteroid_color_blue < 0) {
			cout << "Invalid asteroid color" << endl;
			return 0;
		}
		
		double asteroid_radius_minimum = readline(line);
		getline(in_file, line);
		double asteroid_radius_maximum = readline(line);
		getline(in_file, line);
		if (asteroid_radius_maximum < 0 || asteroid_radius_minimum < 0) {
			cout << "Invalid asteroid_radius" << endl;
			return 0;
		}

		double asteroid_cyles_per_second = readline(line);
		getline(in_file, line);
		if (asteroid_cyles_per_second < 0) {
			cout << "Invalid asteroid_cyles_per_second" << endl;
			return 0;
		}
		
		double orbit_outline_thickness = readline(line);
		if (orbit_outline_thickness > 1 || orbit_outline_thickness < 0) {
			cout << "Invalid orbit_outline_thickness" << endl;
			return 0;
		}
		
		getline(in_file, line);
		double space_ship_red = readline(line);
		getline(in_file, line);
		double space_ship_green = readline(line);
		getline(in_file, line);
		double space_ship_blue = readline(line);
		if (space_ship_red > 255 || space_ship_green > 255 || space_ship_blue > 255 || space_ship_red < 0 || space_ship_green < 0 || space_ship_blue < 0) {
			cout << "Invalid space ship color" << endl;
			return 0;
		}

		getline(in_file, line);
		double space_ship_shrink_grow_rate = readline(line);
		if (space_ship_shrink_grow_rate > 1 || space_ship_shrink_grow_rate < 0) {
			cout << "Invalid space_ship_shrink_grow_rate" << endl;
			return 0;
		}

		getline(in_file, line);
		int delta_frames = readline(line);
		if (delta_frames < 1) {
			cout << "Invalid delta_frames" << endl;
			return 0;
		}


	/** making objects for planets, orbits, moons, and spaceship **/
		Color sunColor = Color(sun_color_red, sun_color_green, sun_color_blue);
		Circle sun = Circle(sun_x_coordinate, sun_y_coordinate, sun_radius, sunColor);
		
		Color mercuryColor = Color(mercury_color_red, mercury_color_green, mercury_color_blue);
		Circle mercury = Circle(0, 0, mercury_radius, mercuryColor);
		mercury.setOrbitDistance(mercury_distance_from_sun);
		mercury.setCenterX(sun_x_coordinate);
		mercury.setCenterY(sun_y_coordinate);
		mercury.rotate(0);

		Color venusColor = Color(venus_color_red, venus_color_green, venus_color_blue);
		Circle venus = Circle(0, 0, venus_radius, venusColor);
		venus.setOrbitDistance(venus_distance_from_sun);
		venus.setCenterX(sun_x_coordinate);
		venus.setCenterY(sun_y_coordinate);
		venus.rotate(0);

		Color earthColor = Color(earth_color_red, earth_color_green, earth_color_blue);
		Circle earth = Circle(0, 0, earth_radius, earthColor);
		earth.setOrbitDistance(earth_distance_from_sun);
		earth.setCenterX(sun_x_coordinate);
		earth.setCenterY(sun_y_coordinate);
		earth.rotate(0);

		Color marsColor = Color(mars_color_red, mars_color_green, mars_color_blue);
		Circle mars = Circle(0, 0, mars_radius, marsColor);
		mars.setOrbitDistance(mars_distance_from_sun);
		mars.setCenterX(sun_x_coordinate);
		mars.setCenterY(sun_y_coordinate);
		mars.rotate(0);

		Color moonColor = Color(255, 255, 255);
		Circle moon = Circle(0, 0, moon_radius, moonColor);
		moon.setOrbitDistance(moon_distance_from_planet);
		moon.setCenterX(earth.getYPos());
		moon.setCenterY(earth.getXPos());
		moon.rotate(0);

		Circle moon2 = Circle(0, 0, moon_radius, moonColor);
		moon2.setOrbitDistance(moon_distance_from_planet);
		moon2.setCenterX(mars.getYPos());
		moon2.setCenterY(mars.getXPos());
		moon2.rotate(0);
		
		Color white = Color(255, 255, 255);
		Circle star = Circle(0, 0, 5, white);
		Circle mercury_orbit = Circle(sun_x_coordinate, sun_y_coordinate, mercury_distance_from_sun, white);
		Circle venus_orbit = Circle(sun_x_coordinate, sun_y_coordinate, venus_distance_from_sun, white);
		Circle earth_orbit = Circle(sun_x_coordinate, sun_y_coordinate, earth_distance_from_sun, white);
		Circle mars_orbit = Circle(sun_x_coordinate, sun_y_coordinate, mars_distance_from_sun, white);

		Color asteroidcolor = Color(asteroid_color_red, asteroid_color_green, asteroid_color_blue);
		Circle asteroid = Circle(0, 0, 0, asteroidcolor);
		asteroid.setCenterX(sun_x_coordinate);
		asteroid.setCenterY(sun_y_coordinate);
		double asteroid_position_angle = 0;
		asteroid.rotate(asteroid_position_angle);

		Color spaceshipColor = Color(space_ship_red, space_ship_green, space_ship_blue);
		Circle rocket = Circle(0, 0, 1, spaceshipColor);
		rocket.setOrbitDistance(earth_distance_from_sun);
		rocket.setCenterX(sun_x_coordinate);
		rocket.setCenterY(sun_y_coordinate);
		rocket.rotate(0);

		bool rocket_on_mars = false;

	/** drawing **/
    for (int f=0; f < number_total_frames_per_second * total_seconds;f=f+delta_frames) {	 
			   stringstream ss;
			   ss << f;
			   string arg =  ss.str() + "animatecolors.bmp";
			   ofstream ostrm;
			   ostrm.open(arg.c_str(), ios::out | ios::binary);
			   if(ostrm.fail()) {
			      cout << "Error.  Can't open output file " << arg << "." << endl;
			      return 0;
			   }
			   cout << "Opening output file " << arg <<"." << endl;
			   
			   int px = image_width;
			   int pz = image_height;
				if(px<=0) {
					ostrm.close();
					return -1;
				}
				if(pz<=0) {
					ostrm.close();
					return -1;
				}

				int rem;
				rem=3*px%4;
				int padding;
				if(rem==0) {
					padding=0;
				} else {
					padding=4-rem;
				}

			   write_bmp_header_file(ostrm, px, pz);   

				unsigned char * * buffer = new unsigned char * [pz];
			   int i,j;
			   for (i=0; i< pz; i++)
			   {
			      buffer[i]= new unsigned char [px*3];
			   }
				unsigned char p_buffer[4];
				p_buffer[0]=0;
				p_buffer[1]=0;
				p_buffer[2]=0;
				p_buffer[3]=0;

				
			   //sets a black backgroud
			   for(i=0;i<pz;i++) {
			      for(j=0;j<3*px;j=j+3) {
			         buffer[i][j+0]=0;
			         buffer[i][j+1]=0;
			         buffer[i][j+2]=0;
			      }
			   }

			 	//draws the stars 
			  	//uses a seed so the stars fall in the same place every time
			 	srand(random_number_seed);
				for (int num = 0; num < number_of_stars; num++) {
					//sets a random radius for every star to change size
					double my_rand = (rand() % 100 + 1);
					double radius = (my_rand / 100 ) * (max_star_radius - min_star_radius) + min_star_radius;
					star.setRadius(radius);

					//sets a random intensity for every star to change brightness
					my_rand = (rand() % 100 + 1);
					double intensity = ((my_rand / 100 ) * (max_star_intensity - min_star_intensity) + min_star_intensity ) * 255;
					star.setColor( Color(intensity, intensity, intensity));
					
					//sets random x and y coordinates for every star
					my_rand = (rand() % 100 + 1);
					star.setXPos( ( my_rand / 100 ) * pz);
					my_rand = (rand() % 100 + 1);
					star.setYPos( ( my_rand / 100 ) * px);

					//draws the star by calling draw circle
					drawCircle(star, pz, px, buffer);
				}

				//draws all the planets and moons
				drawOrbit(mercury_orbit, pz, px, buffer, orbit_outline_thickness);
				drawOrbit(venus_orbit, pz, px, buffer, orbit_outline_thickness);
				drawOrbit(earth_orbit, pz, px, buffer, orbit_outline_thickness);
				drawOrbit(mars_orbit, pz, px, buffer, orbit_outline_thickness);
				drawCircle(sun, pz, px, buffer);
			 	drawCircle(mercury, pz, px, buffer);
				drawCircle(venus, pz, px, buffer);
				drawCircle(earth, pz, px, buffer);
				drawCircle(mars, pz, px, buffer);
				drawCircle(moon, pz, px, buffer);
				drawCircle(moon2, pz, px, buffer);
				//rotates the moon so that mars can have two moons  
				moon2.rotate(180);
				drawCircle(moon2, pz, px, buffer);


				//draws the asteroids
			  	//uses a seed so the stars fall in the same place every time
				srand(random_number_seed);
				for (int ast_num = 0; ast_num < number_of_asteroids; ast_num++) {
					//sets a random radius between the bounds so that the asteroids have many sizes
					double my_rand = (rand() % 100 + 1);
					double asteroid_radius = (my_rand / 100 ) * (asteroid_radius_maximum - asteroid_radius_minimum) + asteroid_radius_minimum;
					asteroid.setRadius(asteroid_radius);
					
					//sets a different distance from the sun between the bounds so that the asteroids aren't all in a line
					my_rand = (rand() % 100 + 1);
					double asteroid_obrit_distance = ((my_rand / 100 ) * (minimum_asteroid_belt_distance_from_sun - maximum_asteroid_belt_distance_from_sun) + minimum_asteroid_belt_distance_from_sun );
					asteroid.setOrbitDistance(asteroid_obrit_distance);
					
					//rotates it a random amount so that every astroid is on a different part of the belt
					my_rand = (rand() % 360);
					asteroid.rotate(my_rand);
					
					//draws the asteroid
					drawCircle(asteroid, pz, px, buffer);
					//resets the angle for the next asteroid
					asteroid.rotate(360 - my_rand);
				}
				
				//zooms out by shrinking all the objects in the image
				if (asteroid.getOrbitDistance() * 3 > image_height && asteroid.getOrbitDistance() * 3 > image_width )  {
					
					//shrinks the radius 
					sun.setRadius(sun.getRadius() * zooming_out_rate);
					mercury.setRadius(mercury.getRadius() * zooming_out_rate);
					venus.setRadius(venus.getRadius() * zooming_out_rate);
					earth.setRadius(earth.getRadius() * zooming_out_rate);
					mars.setRadius(mars.getRadius() * zooming_out_rate);
					moon.setRadius(moon.getRadius() * zooming_out_rate);
					moon2.setRadius(moon2.getRadius() * zooming_out_rate);
					max_star_radius = max_star_radius * zooming_out_rate;
					max_star_radius = max_star_radius * zooming_out_rate;
					asteroid_radius_minimum = asteroid_radius_minimum * zooming_out_rate;
					asteroid_radius_maximum = asteroid_radius_maximum * zooming_out_rate;

					//shrinks the orbits 
					mercury_orbit.setRadius(mercury_orbit.getRadius() * zooming_out_rate);
					venus_orbit.setRadius(venus_orbit.getRadius() * zooming_out_rate);
					earth_orbit.setRadius(earth_orbit.getRadius() * zooming_out_rate);
					mars_orbit.setRadius(mars_orbit.getRadius() * zooming_out_rate);
					
					//reduces teh distance from the sun 
					mercury.setOrbitDistance(mercury.getOrbitDistance() * zooming_out_rate);
					venus.setOrbitDistance(venus.getOrbitDistance() * zooming_out_rate);
					earth.setOrbitDistance(earth.getOrbitDistance() * zooming_out_rate);
					mars.setOrbitDistance(mars.getOrbitDistance() * zooming_out_rate);
					moon.setOrbitDistance(moon.getOrbitDistance() * zooming_out_rate);
					moon2.setOrbitDistance(moon2.getOrbitDistance() * zooming_out_rate);
					minimum_asteroid_belt_distance_from_sun = minimum_asteroid_belt_distance_from_sun * zooming_out_rate;
					maximum_asteroid_belt_distance_from_sun = maximum_asteroid_belt_distance_from_sun * zooming_out_rate;
					rocket.setOrbitDistance(earth.getOrbitDistance());

					//rotates everything by the imputed rates
					mercury.rotate(mercury_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					venus.rotate(venus_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					earth.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					mars.rotate(mars_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					moon.setCenterX(earth.getYPos());
					moon.setCenterY(earth.getXPos());
					moon.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					moon2.setCenterX(mars.getYPos());
					moon2.setCenterY(mars.getXPos());
					moon2.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					asteroid.rotate((asteroid_cyles_per_second * 360 / (total_seconds * number_total_frames_per_second)));
					rocket.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));

				}  
				//when the spaceship is shrinking on mars
				else if ( ((rocket.getXPos()-mars.getXPos()<0.01*image_width) && (rocket.getXPos()-mars.getXPos()>-0.01 * image_width) && (rocket.getYPos()-mars.getYPos()<0.01*image_height) && (rocket.getYPos()-mars.getYPos()>-0.01*image_height)) || rocket_on_mars == true) {
					//draws the rocket
					draw_rocket(rocket, buffer, px, pz, orbit_outline_thickness); 
					
					//rotates everything by the imputed rates
					mercury.rotate(mercury_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					venus.rotate(venus_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					earth.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					mars.rotate(mars_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					moon.setCenterX(earth.getYPos());
					moon.setCenterY(earth.getXPos());
					moon.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					moon2.setCenterX(mars.getYPos());
					moon2.setCenterY(mars.getXPos());
					asteroid.rotate((asteroid_cyles_per_second * 360 / (total_seconds * number_total_frames_per_second)));
					moon2.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					rocket.rotate(mars_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					
					//shrinks the spaceship
					rocket.setRadius(rocket.getRadius() * (1 - space_ship_shrink_grow_rate) );

					//sets the on mars boolean to true
					rocket_on_mars = true;

				} 
				
				//when the shaceship is growing on earth
				else if (rocket.getRadius() < earth.getRadius()) {
					//draws the rocket
					draw_rocket(rocket, buffer, px, pz, orbit_outline_thickness); 
					
					//rotates everything
					mercury.rotate(mercury_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					venus.rotate(venus_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					earth.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					mars.rotate(mars_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					moon.setCenterX(earth.getYPos());
					moon.setCenterY(earth.getXPos());
					moon.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					moon2.setCenterX(mars.getYPos());
					moon2.setCenterY(mars.getXPos());
					moon2.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					asteroid.rotate((asteroid_cyles_per_second * 360 / (total_seconds * number_total_frames_per_second)));
					rocket.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					
					//makes the rocket grow
					rocket.setRadius(rocket.getRadius() * (1 + space_ship_shrink_grow_rate) );
				} 
				
				//when the shaceship is moving from mars to earth's orbit and then reaching mars
				else {
					//draws the rocket
					draw_rocket(rocket, buffer, px, pz, orbit_outline_thickness); 
					
					//rotates everything
					mercury.rotate(mercury_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					venus.rotate(venus_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					earth.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					mars.rotate(mars_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
					moon.setCenterX(earth.getYPos());
					moon.setCenterY(earth.getXPos());
					moon.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					moon2.setCenterX(mars.getYPos());
					moon2.setCenterY(mars.getXPos());
					moon2.rotate(moon_cycles_per_total_second * 360 / (total_seconds * number_total_frames_per_second));
					asteroid.rotate((asteroid_cyles_per_second * 360 / (total_seconds * number_total_frames_per_second)));
					
					//rotates the spaceship around the mars orbit
					if (rocket.getOrbitDistance() - mars.getOrbitDistance() > 0) {
						rocket.rotate((mars_cycles_per_total_seconds* (1 + space_ship_shrink_grow_rate )) * 360 / (total_seconds * number_total_frames_per_second));							
					} 
					//changes the distance from the sun to move to the mars orbit
					else {
						rocket.rotate(earth_cycles_per_total_seconds * 360 / (total_seconds * number_total_frames_per_second));
						rocket.setOrbitDistance(rocket.getOrbitDistance() * (1 + (space_ship_shrink_grow_rate*0.5)));
					}

				}

				for(i=0;i<pz;i++) {
			      ostrm.write ((char*)buffer[i], px*3*sizeof (unsigned char));      
			      ostrm.write ((char*)p_buffer, padding*sizeof (unsigned char));      
				}

			   for(int i = 0; i<pz;i++) {
			      delete[] buffer[i];
			      buffer[i] = NULL;       
			   }   
			   
			   delete[] buffer;
			   buffer = NULL;
			   ostrm.close();
	}

	//converts the bmps to jpegs
	for(int i=0; i< number_total_frames_per_second * total_seconds; i=i+delta_frames) {
		std::stringstream stream;
		stream << "convert " << i << "animatecolors.bmp " <<  setfill('0') << setw(4) << i << "animatecolors.jpeg";
		system(stream.str().c_str());
	}
	
	//converts the jpeg to an mp4
	std::stringstream stream;
	stream << "convert -delay "  <<fixed << setprecision(0) << (100/(number_total_frames_per_second * delta_frames)) << " -loop 0 *.jpeg -scale " << image_height << "x" << image_width << " animate_colors.mp4";
	system(stream.str().c_str());

	return 0;
}
