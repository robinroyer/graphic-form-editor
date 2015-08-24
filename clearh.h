/*************************************************************************
								   ClearH
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef CLEARH_H
#define CLEARH_H

//------------------------------------------------------- Local interfaces
#include "history.h"
#include "object.h"

/**
 * @brief The ClearH class : Handles the "CLEAR" command history
 */
class ClearH : public History
{
	public:

		/** @brief ClearH : Default constructor. Used to detect undesirable calls */
		ClearH();


		/**
		 * @brief ClearH : Constructor
		 * @param mod : A vector of every cleared item
		 */
		ClearH(vector<Object *> mod);


		/** @brief ~ClearH : Destructor */
		virtual ~ClearH();



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

		vector<Object *> cleared;
};

#endif // CLEARH_H
