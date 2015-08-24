//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <string>


//--------------------------------------------------------- Local includes
#include "shape.h"
#include "object.h"


/**
 * @brief Shape::Shape : Constructor with name parameter
 * @param name
 */
Shape::Shape(string& name): Object(name), isRemoved(false)
{}


Shape::~Shape()
{}



/**
 * @brief Shape::remove : Removes the shape from the seen shapes
 */
void Shape::remove()
{
	isRemoved = true;
}


/**
 * @brief Shape::remake : "redraws" the shape
 */
void Shape::remake()
{
	isRemoved = false;
}


/**
 * @return Returns true if the shape is currently deleted, false otherwise
 */
bool Shape::isDeleted() const
{
	return isRemoved;
}
