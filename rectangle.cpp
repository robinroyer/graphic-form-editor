//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <sstream>
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "rectangle.h"


/**
 * @brief Rectangle::Rectangle : Constructor
 * @param name : The shape's name
 * @param x1 : The position on X axis of the first point
 * @param y1 : The position on Y axis of the first point
 * @param x2 : The position on X axis of the second point
 * @param y2 : The position on Y axis of the second point
 */
Rectangle::Rectangle(string& name, vector<long> xPos, vector<long> yPos): PolyLine(name, xPos, yPos)
{}


Rectangle::~Rectangle()
{}



/**
 * @brief Rectangle::getDescriptor : returns a descriptor (command used to create the shape) of the shape
 * @return The descriptor
 */
string Rectangle::getDescriptor() const
{
	stringstream desc("");
	desc << "R " << getName();

	for(unsigned int i = 0; i < xPos.size(); i++)
	{
		desc << " " << xPos[i] << " " << yPos[i];
	}


	return desc.str();
}
