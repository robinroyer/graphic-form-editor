#ifndef OBJECT_H
#define OBJECT_H


//-------------------------------------------------------- Used interfaces
using namespace std;
#include <string>

class Object
{
	public:

		/** @brief Object : Default constructor. Used to detect undesirable calls */
		Object();


		/**
		 * @brief Object : Constructor
		 * @param name : The object's name
		 */
		Object(string &name);


		/** @brief ~Object : Destructor */
		virtual ~Object();



		/**
		 * @return The object's name
		 */
		const string getName() const;


		/**
		 * @brief isSel : Checks if the object is a selection
		 * @return true if the object is a Selection, false otherwise
		 */
		virtual bool isSel() const;


		/**
		 * @brief move : Moves a shape
		 * @param dx : The move on X axis
		 * @param dy : The move on Y axis
		 */
		virtual void move(long dx, long dy) = 0;

	protected:

		string name;
};

#endif // OBJECT_H
