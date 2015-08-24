//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <sstream>
#include <string>
#include <vector>

//--------------------------------------------------------- Local includes
#include "polyline.h"
#include "shape.h"


/**
 * @brief PolyLine::PolyLine : Constructor
 * @param name : The shape's name
 * @param xPos : The polyline's points positions on X axis
 * @param yPos : The polyline's points positions on Y axis
 */
PolyLine::PolyLine(string& name, vector<long>& xPos, vector<long>& yPos):Shape(name), xPos(xPos), yPos(yPos)
{}


PolyLine::~PolyLine()
{}



/**
 * @brief PolyLine::getDescriptor : returns a descriptor (command used to create the shape) of the shape
 * @return The descriptor
 */
string PolyLine::getDescriptor() const
{
	stringstream desc("");
	desc << "PL " << getName();

	for(unsigned int i = 0; i < xPos.size(); i++)
	{
		desc << " " << xPos[i] << " " << yPos[i];
	}

	return desc.str();
}


/**
 * @brief PolyLine::move : Moves the polyline
 * @param dx : The move on X axis
 * @param dy : The move on Y axis
 * @return All the modified objects (so this)
 */
void PolyLine::move(long dx, long dy)
{
	for(unsigned int i = 0; i < xPos.size(); i++)
	{
		xPos[i] += dx;
		yPos[i] += dy;
	}
}


/**
 * @param x1 : The first coordinate on X axis
 * @param y1 : The first coordinate on Y axis
 * @param x2 : The second coordinate on X axis
 * @param y2 : The second coordinate on Y axis
 * @return true if the shape is ecompassed in the given positions
 */
bool PolyLine::isEncompassed(long x1, long y1, long x2, long y2) const
{

	for(unsigned int i = 0; i < xPos.size(); i++)
	{
		if(xPos[i] < x1 || xPos[i] > x2 || yPos[i] < y1 || yPos[i] > y2)
			return false;
	}

	return true;
}
