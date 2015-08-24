//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <sstream>
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "line.h"
#include "polyline.h"


/**
 * @brief Line::Line : Constructor
 * @param name : The shape's name
 * @param xPos : The line's points positions on X axis
 * @param yPos : The line's points positions on Y axis
 */
Line::Line(string& name, vector<long>& xPos, vector<long>& yPos):PolyLine(name, xPos, yPos)
{}


Line::~Line()
{}



/**
 * @brief Line::getDescriptor : returns a descriptor (command used to create the shape) of the shape
 * @return The descriptor
 */
string Line::getDescriptor() const
{
	stringstream desc("");
	desc << "L " << getName();

	for(unsigned int i = 0; i < xPos.size(); i++)
	{
		desc << " " << xPos[i] << " " << yPos[i];
	}

	return desc.str();
}
