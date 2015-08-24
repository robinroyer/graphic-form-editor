//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <sstream>
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "circle.h"
#include "shape.h"


/**
 * @brief Circle::Circle : Constructor
 * @param name : The shape's name
 * @param xc : The center position on X axis
 * @param yc : The center position on Y axis
 * @param r : The circle radius
 */
Circle::Circle(string name, long xc, long yc, long r): Shape(name), xC(xc), yC(yc), radius(r)
{}


Circle::~Circle()
{}



/**
 * @brief Circle::getDescriptor : returns a descriptor (command used to create the shape) of the shape
 * @return The descriptor
 */
string Circle::getDescriptor() const
{
	stringstream desc("");

	desc << "C " << getName() << " " << xC << " " << yC << " " << radius;

	return desc.str();
}


/**
 * @brief Circle::move : Moves the circle
 * @param dx : The move on X axis
 * @param dy : The move on Y axis
 * @return All the modified objects (so this)
 */
void Circle::move(long dx, long dy)
{
	xC += dx;
	yC += dy;
}



/**
 * @param x1 : The first coordinate on X axis
 * @param y1 : The first coordinate on Y axis
 * @param x2 : The second coordinate on X axis
 * @param y2 : The second coordinate on Y axis
 * @return true if the shape is ecompassed in the given positions
 */
bool Circle::isEncompassed(long x1, long y1, long x2, long y2) const
{

	for(int dx = -1; dx <= 1; dx += 2)
	{
		long x = xC + dx * radius;

		if(x < x1 || x > x2)
			return false;
	}


	for(int dy = -1; dy <= 1; dy += 2)
	{
		long y = yC + dy * radius;

		if(y < y1 || y > y2)
			return false;
	}

	return true;
}
