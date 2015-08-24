/*************************************************************************
								   LoadH
							 -------------------
	copyright            : (C) 2015 par Meyer Franck - Royer Robin
*************************************************************************/

#ifndef LOADH_H
#define LOADH_H


//-------------------------------------------------------- Used interfaces
using namespace std;
#include <vector>


//------------------------------------------------------- Local interfaces
#include "history.h"
#include "objectmanager.h"


/**
 * @brief The LoadH class :  Handles the "LOAD" command history
 */
class LoadH : public History
{
	public:
		
		/** @brief LoadH : Default constructor. Used to detect undesirable calls */
		LoadH();
		

		/**
		 * @brief LoadH : Constructor
		 * @param l : The list of loaded shapes to save
		 */
		LoadH(vector<Shape *> l);
		

		/** @brief ~LoadH : Destructor */
		~LoadH();
		

		
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
		
		vector<Shape *> loaded;
};

#endif // LOADH_H
