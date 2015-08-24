/*************************************************************************
									 Line
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef LINE_H
#define LINE_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "polyline.h"

/**
 * @brief The Line class : Defines a line, which is a PolyLine with only
 * 2 points
 */
class Line : public PolyLine
{
	public:

		/** @brief Line : Default constructor. Used to detect undesirable calls */
		Line();


		/**
		 * @brief Line : Constructor
		 * @param name : The shape's name
		 * @param xPos : The line's points positions on X axis
		 * @param yPos : The line's points positions on Y axis
		 */
		Line(string& name, vector<long> &xPos, vector<long> &yPos);


		/** @brief ~Line : Destructor */
		virtual ~Line();



		/**
		 * @brief getDescriptor : returns a descriptor (command used to create the shape) of the shape
		 * @return The descriptor
		 */
		virtual string getDescriptor() const;
};

#endif // LINE_H
