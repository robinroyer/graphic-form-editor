/*************************************************************************
								   PolyLine
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef POLYLINE_H
#define POLYLINE_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>
#include <vector>


//------------------------------------------------------- Local interfaces
#include "shape.h"


/**
 * @brief The PolyLine class : Defines a PolyLine, which is a shape with
 * multiples points (linked to form lines)
 */
class PolyLine : public Shape
{
	public:

		/** @brief PolyLine : Default constructor. Used to detect undesirable calls */
		PolyLine();


		/**
		 * @brief PolyLine : Constructor
		 * @param name : The shape's name
		 * @param xPos : The polyline's points positions on X axis
		 * @param yPos : The polyline's points positions on Y axis
		 */
		PolyLine(string& name, vector<long>& xPos, vector<long>& yPos);


		/** @brief ~PolyLine : Destructor */
		virtual ~PolyLine();



		/**
		 * @brief getDescriptor : returns a descriptor (command used to create the shape) of the shape
		 * @return The descriptor
		 */
		virtual string getDescriptor() const;


		/**
		 * @brief move : Moves the polyline
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 * @return All the modified objects(so this)
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

		vector<long> xPos, yPos;
};

#endif // POLYLINE_H
