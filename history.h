/*************************************************************************
								   History
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef HYSTORY_H
#define HYSTORY_H


//------------------------------------------------------- Local interfaces
#include "objectmanager.h"

/**
 * @brief The History class : Handles the history (for undo/redo commands)
 */
class History
{
	public:

		/** @brief History : Default constructor. */
		History();


		/** @brief ~History : Destructor */
		virtual ~History();



		/**
		 * @brief undo : Reverses the operation the history is created for
		 * @param om : The object manager which wants to reverse it
		 */
		virtual void undo(ObjectManager *om) = 0;


		/**
		 * @brief redo : Revapplicates the operation the history is created for
		 * @param om : The object manager which wants to reapplicate it
		 */
		virtual void redo(ObjectManager *om) = 0;


		/**
		 * @brief clean : Cleans the current history (used if an operation is in the REDO list)
		 */
		virtual void clean();
};

#endif // HYSTORY_H
