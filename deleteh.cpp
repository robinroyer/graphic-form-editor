//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <iostream>
#include <set>
#include <vector>


//--------------------------------------------------------- Local includes
#include "deleteh.h"
#include "object.h"
#include "objectmanager.h"



DeleteH::DeleteH(set<Object *> rm) : deleted(rm)
{}


DeleteH::~DeleteH()
{
	for(Object *obj : deleted)
	{
		delete(obj);
	}
}



void DeleteH::undo(ObjectManager *om)
{
	for(Object *obj : deleted)
	{
		if(obj->isSel())
		{
			om->addSelection((Selection *)obj);
		}
		else
		{
			om->addObject((Shape *)obj, false);
			((Shape *)obj)->remake();
		}
	}
}


void DeleteH::redo(ObjectManager *om)
{
	vector<string>							names;
	vector<Object *>::const_iterator		it;

	for(Object *obj : deleted)
	{
		names.push_back(obj->getName());
		((Shape *)obj)->remove();
	}
	om->removeObjects(names, false);
}


void DeleteH::clean()
{
	deleted.clear();
}
