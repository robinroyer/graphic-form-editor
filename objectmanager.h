/*************************************************************************
								  ObjectManager
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <deque>
#include <map>
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
class History;
#include "shape.h"
#include "selection.h"


/**
 * @brief The ObjectManager class : Manages all the created objects (shapes and selections)
 */
class ObjectManager
{
	public:

		/** @brief ObjectManager : Default constructor */
		ObjectManager();


		/** @brief ~ObjectManager : Destructor */
		virtual ~ObjectManager();



		/**
		 * @brief addObject : Adds a shape to the tracked shapes list
		 * @param s : The shape to add
		 * @return true if the shape has been inserted, false if there was a problem (same name as another element)
		 */
		bool addObject(Shape *s, bool archivate = true);


		/**
		 * @brief addSelection : Adds a selection to the tracked selections list
		 * @param s : The selection to add
		 * @return true if the selection has been inserted, false if there was a problem (same name as another)
		 */
		bool addSelection(Selection *s);


		/**
		 * @brief getSelectedShapes : Selects the shapes totally included into the coordinate
		 * @param x1 : The first coordinate on X axis
		 * @param y1 : The first coordinate on Y axis
		 * @param x2 : The second coordinate on X axis
		 * @param y2 : The second coordinate on Y axis
		 * @return The list of encompassed shapes
		 */
		vector<Shape *> getSelectedShapes(long x1, long y1, long x2, long y2) const;

		/**
		 * @brief contains : searchs through the maps to find a name
		 * @param name : The object's name
		 * @return true if the name is currently in one of the maps
		 */
		bool contains(string name) const;


		/**
		 * @brief containsNames : searchs through the maps to find multiple names
		 * @param names : The object's names
		 * @return true if all the name are currently in one of the maps, false if at least one is not in a map
		 */
		bool containsNames(vector<string> names) const;


		/**
		 * @brief removeObjects : Removes objects which name is in names from the visible objects
		 * @param names : The objects names
		 */
		void removeObjects(vector<string> names, bool archivate = true);


		/**
		 * @brief moveObject : Moves an object
		 * @param name : The object name
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 * @return All the modified objects
		 */
		void moveObject(string name, long dx, long dy, bool archivate = true);


		/**
		 * @brief printDescs : Prints on the stream all the shapes descriptions
		 * @param os : The stream where the descriptions list will be printed
		 */
		void printDescs(ostream &os);


		/**
		 * @brief clearObjects : Deletes every undeleted object
		 * @return All the modified objects
		 */
		void clearObjects(bool archivate = true);


		/**
		 * @brief addToHistory : Adds an history element to the history
		 * @param h : The history element to add
		 */
		void addToHistory(History *h);


		/**
		 * @brief undoCurrent : undoes the last operation
		 * @return true if the undo is successful
		 */
		bool undoCurrent();


		/**
		 * @brief redoCurrent : redoes the last operation
		 * @return true if the redo was successful
		 */
		bool redoCurrent();

	protected:

		map<string, Shape *> objects;
		map<string, Selection *> sels;

		deque<History *> history;
		unsigned int index;
};

#endif // OBJECTMANAGER_H
