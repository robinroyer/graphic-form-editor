//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "selection.h"
#include "object.h"
#include "shape.h"


/**
 * @brief Selection::Selection : Constructor
 * @param name : The selection name
 * @param objects : The list of contained shapes
 */
Selection::Selection(string &name, vector<Shape *>& objects): Object(name), contained(objects)
{}


Selection::~Selection()
{}


/**
 * @brief Selection::move : Moves the contained shapes
 * @param dx : The move on X axis
 * @param dy : The move on Y axis
 */
void Selection::move(long dx, long dy)
{
	vector<Shape *>::iterator				it;

	for(it = contained.begin(); it != contained.end(); ++it)
	{
		Shape *s = *it;
		if(!s->isDeleted())
		{
			s->move(dx, dy);
		}
	}
}





/**
 * @brief remove : Removes all the contained shapes from the visible
 */
vector <Shape *> Selection::remove()
{
	vector<Shape *>							deleted;
	vector<Shape *>::iterator				it;

	for(it = contained.begin(); it != contained.end(); ++it)
	{
		Shape *s = *it;
		if(!s->isDeleted())
		{
			s->remove();
			deleted.push_back(s);
		}
	}

	return deleted;
}


bool Selection::isSel() const
{
	return true;
}
