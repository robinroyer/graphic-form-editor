//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <iostream>


//--------------------------------------------------------- Local includes
#include "clearh.h"


ClearH::ClearH(vector<Object *> mod) : cleared(mod)
{}


ClearH::~ClearH()
{
	vector<Object *>::const_iterator		it;

	for(it = cleared.begin(); it != cleared.end(); ++it)
	{
		delete (*it);
	}
}



void ClearH::undo(ObjectManager *om)
{
	vector<Object *>::const_iterator		it;

	for(it = cleared.begin(); it != cleared.end(); ++it)
	{
		Object *obj = *it;
		if((*it)->isSel())
			om->addSelection((Selection *)obj);
		else
			om->addObject((Shape *)obj, false);
	}
}


void ClearH::redo(ObjectManager *om)
{
	om->clearObjects(false);
}


void ClearH::clean()
{
	cleared.clear();
}
