/*************************************************************************
								   DeleteH
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef MOVEH_H
#define MOVEH_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>


//------------------------------------------------------- Local interfaces
#include "history.h"


/**
 * @brief The MoveH class : Handles the "MOVE" command history
 */
class MoveH : public History
{
	public:

		/** @brief MoveH : Default constructor. Used to detect undesirable calls */
		MoveH();


		/**
		 * @brief MoveH : Constructor
		 * @param moved : The moved object
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 */
		MoveH(Object *moved, long dx, long dy);


		/** @brief ~MoveH : Destructor */
		virtual ~MoveH();



		/**
		 * @brief undo : Reverses the operation the history is created for
		 * @param om : The object manager which wants to reverse it
		 */
		virtual void undo(ObjectManager *om);


		/**
		 * @brief redo : Revapplicates the operation the history is created for
		 * @param om : The object manager which wants to reapplicate it
		 */
		virtual void redo(ObjectManager *om);

	protected:

		Object *moved;
		long dx, dy;

};

#endif // MOVEH_H
