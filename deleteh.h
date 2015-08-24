/*************************************************************************
								   DeleteH
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef DELETEH_H
#define DELETEH_H

//-------------------------------------------------------- Used interfaces
using namespace std;
#include <set>


//------------------------------------------------------- Local interfaces
#include "history.h"
#include "object.h"

/**
 * @brief The DeleteH class : Handles the "DELETE" command history
 */
class DeleteH : public History
{
	public:

		/** @brief DeleteH : Default constructor. Used to detect undesirable calls */
		DeleteH();


		/**
		 * @brief DeleteH : Constructor
		 * @param rm : a vector with every deleted object
		 */
		DeleteH(set<Object *> rm);


		/** @brief ~DeleteH : Destructor */
		virtual ~DeleteH();



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


		/**
		 * @brief clean : Cleans the current history (used if an operation is in the REDO list)
		 */
		virtual void clean();

	protected:

		set<Object *> deleted;
};

#endif // DELETEH_H
