//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <vector>


//--------------------------------------------------------- Local includes
#include "objectmanager.h"
#include "loadh.h"


LoadH::LoadH(vector<Shape *> l) : loaded(l)
{}


LoadH::~LoadH()
{}



void LoadH::undo(ObjectManager *om)
{
	vector<string>					names;
	for(Shape* s : loaded)
	{
		names.push_back(s->getName());
	}
	om->removeObjects(names, false);
}
		
		
void LoadH::redo(ObjectManager *om)
{
	for(Shape* s : loaded)
	{
		om->addObject(s, false);
	}
}


void LoadH::clean()
{
	for(Shape* s : loaded)
		delete s;
}
