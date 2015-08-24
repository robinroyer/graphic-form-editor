//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <string>


//--------------------------------------------------------- Local includes
#include "object.h"

Object::Object(string &name) : name(name)
{}


Object::~Object()
{}



/**
 * @brief Object::getName : Gets the object's name
 * @return The object's (unique) name
 */
const string Object::getName() const
{
	return name;
}


bool Object::isSel() const
{
	return false;
}

