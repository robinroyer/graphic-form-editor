/*************************************************************************
								  Rectangle
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "polyline.h"


/**
 * @brief The Rectangle class : Defines a rectangle, represented by 2 points
 */
class Rectangle : public PolyLine
{
	public:

		/** @brief Rectangle : Default constructor. Used to detect undesirable calls */
		Rectangle();


		/**
		 * @brief Rectangle : Constructor
		 * @param name : The shape's name
		 * @param xPos : The positions on X axis of the points
		 * @param yPos : The positions on Y axis of the points
		 */
		Rectangle(string& name, vector<long> xPos, vector<long> yPos);


		/** @brief ~Rectangle : Destructor */
		virtual ~Rectangle();



		/**
		 * @brief getDescriptor : returns a descriptor (command used to create the shape) of the shape
		 * @return The descriptor
		 */
		virtual string getDescriptor() const;
};

#endif // RECTANGLE_H
