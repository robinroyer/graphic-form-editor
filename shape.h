/*************************************************************************
								   Shape
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef SHAPE_H
#define SHAPE_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "object.h"

/**
 * @brief The Shape class : Defines a shape, which is the basis for circles, lines, ...
 */
class Shape : public Object
{
	public:

		/** @brief Shape : Default constructor. Used to detect undesirable calls */
		Shape();


		/**
		 * @brief Shape : Constructor
		 * @param name : The shape's name
		 */
		Shape(string& name);


		/** @brief ~Shape : Destructor */
		virtual ~Shape();



		/**
		 * @brief getDescriptor : returns a descriptor (command used to create the shape) of the shape
		 * @return The descriptor
		 */
		virtual string getDescriptor() const = 0;


		/** @brief remove : Removes a shape from the currently seen shapes */
		virtual void remove();


		/** @brief remake : Adds the shape to the currently seen shapes*/
		virtual void remake();



		/**
		 * @param x1 : The first coordinate on X axis
		 * @param y1 : The first coordinate on Y axis
		 * @param x2 : The second coordinate on X axis
		 * @param y2 : The second coordinate on Y axis
		 * Contract : x1 <= x2, y1 <= y2
		 * @return true if the shape is ecompassed in the given positions
		 */
		virtual bool isEncompassed(long x1, long y1, long x2, long y2) const = 0;


		/**
		 * @return Returns true if the shape is currently deleted, false otherwise
		 */
		bool isDeleted() const;


	protected:

		string name;
		bool isRemoved;
};

#endif // SHAPE_H
