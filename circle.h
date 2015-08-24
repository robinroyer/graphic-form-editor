/*************************************************************************
								   Circle
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef CIRCLE_H
#define CIRCLE_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "shape.h"


/**
 * @brief The Circle class : Defines a circle, which is a Shape
 */
class Circle : public Shape
{
	public:

		/** @brief Circle : Default constructor. Used to detect undesirable calls */
		Circle();


		/**
		 * @brief Circle : Constructor
		 * @param name : The shape's name
		 * @param xc : The center position on X axis
		 * @param yc : The center position on Y axis
		 * @param r : The circle radius
		 */
		Circle(string name, long xc, long yc, long r);


		/** @brief ~Circle : Destructor */
		virtual ~Circle();



		/**
		 * @brief getDescriptor : returns a descriptor (command used to create the shape) of the shape
		 * @return The descriptor
		 */
		virtual string getDescriptor() const;


		/**
		 * @brief move : Moves the circle
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 * @return All the modified objects (so this)
		 */
		virtual void move(long dx, long dy);


		/**
		 * @param x1 : The first coordinate on X axis
		 * @param y1 : The first coordinate on Y axis
		 * @param x2 : The second coordinate on X axis
		 * @param y2 : The second coordinate on Y axis
		 * @return true if the shape is ecompassed in the given positions
		 */
		virtual bool isEncompassed(long x1, long y1, long x2, long y2) const;

	protected:

		long xC, yC;
		long radius;
};

#endif // CIRCLE_H
