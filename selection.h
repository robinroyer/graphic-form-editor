/*************************************************************************
								  Selection
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef SELECTION_H
#define SELECTION_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "shape.h"
#include "object.h"


/**
 * @brief The Selection class : Defines a selection, which contains multiples
 * shapes
 */
class Selection : public Object
{
	public:
		/** @brief Selection : Default constructor. Used to detect undesirable calls */
		Selection();


		/**
		 * @brief Selection : Constructor
		 * @param name : The selection name
		 * @param objects : The shapes the selection contains
		 */
		Selection(string& name, vector<Shape *> &objects);


		virtual ~Selection();



		/**
		 * @brief move : Moves all the Shapes contained in the selection
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 * @return All the modified objects
		 */
		virtual void move(long dx, long dy);


		/**
		 * @brief remove : Removes all the contained shapes from the visible
		 */
		virtual vector<Shape *> remove();


		/**
		 * @brief isSel : Checks if the object is a selection
		 * @return true if the object is a Selection, false otherwise
		 */
		virtual bool isSel() const;

	protected:

		string name;
		vector<Shape *> contained;
};

#endif // SELECTION_H
