//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- Local includes
#include "moveh.h"
#include "object.h"
#include "objectmanager.h"


MoveH::MoveH(Object *moved, long dx, long dy) : moved(moved), dx(dx), dy(dy)
{}


MoveH::~MoveH()
{}



void MoveH::undo(ObjectManager *om)
{
	moved->move(-dx, -dy);
}


void MoveH::redo(ObjectManager *om)
{
	moved->move(dx, dy);
}
