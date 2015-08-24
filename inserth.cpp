//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- Local includes
#include "inserth.h"
#include "shape.h"


InsertH::InsertH(Shape *s): shape(s)
{}


InsertH::~InsertH()
{}



void InsertH::undo(ObjectManager * om)
{
	vector<string> sName;
	sName.push_back(shape->getName());
	om->removeObjects(sName, false);
}


void InsertH::redo(ObjectManager * om)
{
	om->addObject(shape, false);
}


void InsertH::clean()
{
	delete shape;
}
