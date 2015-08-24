//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "objectmanager.h"

#include "clearh.h"
#include "deleteh.h"
#include "history.h"
#include "inserth.h"
#include "loadh.h"
#include "moveh.h"
#include "shape.h"

//-------------------------------------------------------------- Constants
#define MAX_HISTORY 20

/**
 * @brief ObjectManager::ObjectManager : Default Constructor
 */
ObjectManager::ObjectManager()
{}


ObjectManager::~ObjectManager()
{
	map<string, Shape *>::const_iterator it;
	for (it = objects.begin(); it != objects.end(); ++it)
		delete it->second;


	map<string, Selection *>::const_iterator iter;
	for (iter = sels.begin(); iter != sels.end(); ++iter)
		delete iter->second;

	for (unsigned int i(0); i < history.size(); i++)
	{
		if(i >= index)
			history[i]->clean();
		delete history[i];
	}
}


/**
 * @brief ObjectManager::addObject : Adds a shape to the tracked shapes list
 * @param s : The shape to add
 * @return true if the shape has been inserted, false if there was a problem (same name as another element)
 */
bool ObjectManager::addObject(Shape *s, bool archivate)
{
	if(objects.find(s->getName()) == objects.end() && sels.find(s->getName()) == sels.end())
	{
		objects[s->getName()]=s;

		if(archivate)
		{
			History *h = new InsertH(s);
			addToHistory(h);
		}
		return true;
	}

	return false;
}


/**
 * @brief ObjectManager::addSelection : Adds a selection to the tracked selections list
 * @param s : The selection to add
 * @return true if the selection has been inserted, false if there was a problem (same name as another)
 */
bool ObjectManager::addSelection(Selection *s)
{
	if(objects.find(s->getName()) == objects.end() && sels.find(s->getName()) == sels.end())
	{
		sels[s->getName()] = s;
		return true;
	}

	return false;
}


/**
 * @brief ObjectManager::getSelectedShapes : Selects the shapes totally included into the coordinate
 * @param x1 : The first coordinate on X axis
 * @param y1 : The first coordinate on Y axis
 * @param x2 : The second coordinate on X axis
 * @param y2 : The second coordinate on Y axis
 * @return The list of encompassed shapes
 */
vector<Shape *> ObjectManager::getSelectedShapes(long x1, long y1, long x2, long y2) const
{
	vector<Shape *>								shapes;
	map<string, Shape *>::const_iterator		it;

	if(x1 > x2)
	{
		int x(x1);
		x1 = x2;
		x2 = x;
	}

	if(y1 > y2)
	{
		int y(y1);
		y1 = y2;
		y2 = y;
	}

	for(it = objects.begin(); it != objects.end(); ++it)
	{
		if(it->second->isEncompassed(x1, y1, x2, y2))
			shapes.push_back(it->second);
	}

	return shapes;
}


/**
 * @brief ObjectManager::contains : searchs through the maps to find a name
 * @param name : The object's name
 * @return true if the name is currently in one of the maps
 */
bool ObjectManager::contains(string name) const
{
	if(objects.find(name) != objects.end())
		return true;

	if(sels.find(name) != sels.end())
		return true;

	return false;
}


/**
 * @brief ObjectManager::containsNames : searchs through the maps to find multiple names
 * @param names : The object's names
 * @return true if all the name are currently in one of the maps, false if at least one is not in a map
 */
bool ObjectManager::containsNames(vector<string> names) const
{
	for(unsigned int i = 0; i < names.size(); i++)
	{
		if(!contains(names[i]))
			return false;
	}
	return true;
}


/**
 * @brief ObjectManager::removeObjects : Removes objects which name is in names from the visible objects
 * @param names : The objects names
 */
void ObjectManager::removeObjects(vector<string> names, bool archivate)
{
	set<Object *>							mod;

	for(unsigned int i = 0; i < names.size(); i++)
	{
		if(sels.find(names[i]) != sels.end())
		{
			Selection *sel = sels[names[i]];
			vector<Shape *> s = sel->remove();

			vector<string> sN;

			vector<Shape *>::iterator it;
			for(Shape* shape : s)
			{
				mod.insert(shape);
				objects.erase(shape->getName());
			}

			mod.insert(sel);
			sels.erase(names[i]);
		}
		else
		{
			Shape *s = objects[names[i]];
			s->remove();
			mod.insert(objects[names[i]]);
			objects.erase(names[i]);
		}
	}

	if(archivate)
	{
		History *h = new DeleteH(mod);
		addToHistory(h);
	}
}


/**
 * @brief moveObject : Moves an object
 * @param name : The object name
 * @param dx : The move on X axis
 * @param dy : The move on Y axis
 */
void ObjectManager::moveObject(string name, long dx, long dy, bool archivate)
{
	Object *mod;
	if(sels.find(name) != sels.end())
	{
		sels[name]->move(dx, dy);
		mod = sels[name];
	}
	else
	{
		Shape *s = objects[name];
		s->move(dx, dy);
		mod = s;
	}

	if(archivate)
	{
		History *h = new MoveH(mod, dx, dy);
		addToHistory(h);
	}

}


/**
 * @brief printDescs : Prints on the stream all the shapes descriptions
 * @param os : The stream where the descriptions list will be printed
 */
void ObjectManager::printDescs(ostream& os)
{
	map<string, Shape *>::const_iterator it;
	for(it = objects.begin(); it != objects.end(); ++it)
	{
		os << (it->second)->getDescriptor() << endl;
	}
}


/**
 * @brief clearObjects : Deletes every undeleted object
 * @return All the modified objects
 */
void ObjectManager::clearObjects(bool archivate)
{
	vector<Object *>							mod;
	map<string, Shape *>::const_iterator		it;
	map<string, Selection *>::const_iterator	iter;

	for(it = objects.begin(); it != objects.end(); ++it)
	{
		Shape *s = it->second;
		if(!s->isDeleted())
		{
			mod.push_back(s);
			objects.erase(it);
		}
	}

	for(iter = sels.begin(); iter != sels.end(); ++iter)
	{
		Selection *s = iter->second;
		sels.erase(iter);
		mod.push_back(s);
	}

	if(archivate)
	{
		History *h = new ClearH(mod);
		addToHistory(h);
	}
}


void ObjectManager::addToHistory(History *h)
{
	while(index < history.size())
	{
		History *tmp = history[history.size() - 1];
		tmp->clean();
		delete tmp;
		history.pop_back();
	}
	history.push_back(h);

	if(history.size() > MAX_HISTORY)
	{
		History *tmp = history[0];
		delete tmp;
		history.pop_front();
	}

	index = history.size();
}


bool ObjectManager::undoCurrent()
{
	if(index == 0 || history.size() == 0)
	{
		return false;
	}
	History *h = history[index - 1];
	h->undo(this);
	index--;
	return true;
}


bool ObjectManager::redoCurrent()
{
	if(index > history.size() - 1)
	{
		return false;
	}
	history[index]->redo(this);
	index++;
	return true;
}
