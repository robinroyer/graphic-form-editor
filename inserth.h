/*************************************************************************
								   InsertH
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef INSERTH_H
#define INSERTH_H


//------------------------------------------------------- Local interfaces
#include "history.h"
#include "shape.h"

/**
 * @brief The InsertH class : Handles the history for shapes insertion operations
 */
class InsertH : public History
{
	public:

		/** @brief InsertH : Default constructor. Used to detect undesirable calls */
		InsertH();


		/**
		 * @brief InsertH : Constructor
		 * @param s : The inserted shape
		 */
		InsertH(Shape *s);


		/** @brief ~InsertH : Destructor */
		virtual ~InsertH();



		/**
		 * @brief undo : Reverses the operation the history is created for
		 * @param om : The object manager which wants to reverse it
		 */
		virtual void undo(ObjectManager *om);


		/**
		 * @brief redo : Revapplicates the operation the history is created for
		 * @param om : The object manager which wants to reapplicate it
		 */
		virtual void redo(ObjectManager * om);


		/**
		 * @brief clean : Cleans the current history (used if an operation is in the REDO list)
		 */
		virtual void clean();

	protected:

		Shape *shape;
};

#endif // INSERTH_H
