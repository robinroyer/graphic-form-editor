//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- System includes
using namespace std;
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


//--------------------------------------------------------- Local includes
#include "circle.h"
#include "line.h"
#include "polyline.h"
#include "rectangle.h"

#include "selection.h"

#include "objectmanager.h"

#include "loadh.h"

//-------------------------------------------------------------- Constants
#define ERRFLAG " -1"


static bool loadCommand(stringstream &stream, ObjectManager& objMan, Shape **added);
static bool treatCommand(stringstream &stream, ObjectManager& objMan);

static bool checkFlag(istream& stream, bool trace = true);
static bool getLong(istream& is, long& var, string& param);

static bool addManObject(ObjectManager& objMan, Shape *s, bool trace = true);
static void addManSelection(ObjectManager& objMan, Selection *s);

static Shape* addCircle(stringstream &stream, ObjectManager& objMan, bool trace = true);
static Shape* addRectangle(stringstream& stream, ObjectManager& objMan, bool trace = true);
static Shape* addLine(stringstream& stream, ObjectManager& objMan, bool trace = true);
static Shape* addPolyLine(stringstream& stream, ObjectManager& objMan, bool trace = true);

static void addSelection(stringstream& stream, ObjectManager& objMan);

static void remove(stringstream &stream, ObjectManager& objMan);
static void move(stringstream &stream, ObjectManager& objMan);
static void load(stringstream &stream, ObjectManager& objMan);
static void save(stringstream &stream, ObjectManager& objMan);
static void clear(ObjectManager& objMan);

static void undo(ObjectManager& objMan);
static void redo(ObjectManager& objMan);


int main(void)
{
	string									line;
	ObjectManager							objMan;

	while (cin.good())
	{
		stringstream						stream("");
		getline(cin, line);
		stream << line;

		if(!treatCommand(stream, objMan))
		{
			return 0;
		}
		/*TODO:
		 * LOAD
		 */
	}

	return 0;
}


/**
 * @brief loadCommand : Loads a shape. Called by the load command
 * @param stream : The stream containing the command
 * @param objMan : The object manager
 * @param added : a pointer to the added shape
 * @return false if the command was unhandled
 */
static bool loadCommand(stringstream &stream, ObjectManager& objMan, Shape **added)
{
	string									command("");
	stream >> command;

	if(command == "C")
	{
		*added = addCircle(stream, objMan, false);
		return *added != NULL;
	}
	else if(command == "R")
	{
		*added = addRectangle(stream, objMan, false);
		return *added != NULL;
	}
	else if(command == "L")
	{
		*added = addLine(stream, objMan, false);
		return *added != NULL;
	}
	else if(command == "PL")
	{
		*added = addPolyLine(stream, objMan, false);
		return *added != NULL;
	}

	*added = NULL;
	if(command[0] == '#')
		return true;
	else
		return false;
}


/**
 * @brief treatCommand : Treats a command
 * @param stream : The stream containing the command
 * @param objMan : The object manager
 * @return false if the program has to terminate
 */
static bool treatCommand(stringstream &stream, ObjectManager& objMan)
{
	string									command("");
	stream >> command;


	if(command == "EXIT")
	{
		return false;
	}
	else if(command == "C")
	{
		addCircle(stream, objMan);
	}
	else if(command == "R")
	{
		addRectangle(stream, objMan);
	}
	else if(command == "L")
	{
		addLine(stream, objMan);
	}
	else if(command == "PL")
	{
		addPolyLine(stream, objMan);
	}
	else if(command == "S")
	{
		addSelection(stream, objMan);
	}
	else if(command == "DELETE")
	{
		remove(stream, objMan);
	}
	else if(command == "MOVE")
	{
		move(stream, objMan);
	}
	else if(command == "LIST")
	{
		objMan.printDescs(cout);
	}
	else if(command == "UNDO")
	{
		undo(objMan);
	}
	else if(command == "REDO")
	{
		redo(objMan);
	}
	else if(command == "LOAD")
	{
		load(stream, objMan);
	}
	else if(command == "SAVE")
	{
		save(stream, objMan);
	}
	else if(command == "CLEAR")
	{
		clear(objMan);
	}
	else if(command != "EXIT")
	{
		cerr << "ERR" << endl;
		cerr << "#unknown command" << endl;
	}

	return true;
}

/**
 * @brief addCircle : Adds a Circle to the objectManager, and treats errors
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static Shape* addCircle(stringstream &stream, ObjectManager& objMan, bool trace)
{
	string							name;
	string							error("");

	long							x, y;
	long							radius;

	stream << ERRFLAG;
	stream >> name;

	if(!getLong(stream, x, error))
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid X coordinate" << endl;
		}
		return NULL;
	}
	else if(!getLong(stream, y, error))
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid Y coordinate" << endl;
		}
		return NULL;
	}
	else if(!getLong(stream, radius, error))
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid radius" << endl;
		}
		return NULL;
	}

	if(!checkFlag(stream, trace))
		return NULL;

	if(radius < 0)
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid radius" << endl;
		}
		return NULL;
	}

	Circle *c = new Circle(name, x, y, radius);

	if(!addManObject(objMan, c, trace))
		return NULL;

	return c;
}


/**
 * @brief addRectangle : Adds a Rectangle to the objectManager, and treats errors
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static Shape* addRectangle(stringstream &stream, ObjectManager& objMan, bool trace)
{
	string							name;
	string							error("");

	vector<long>					x, y;
	long							xi, yi;

	stream << ERRFLAG;
	stream >> name;

	for(int i = 0; i < 2; i++)
	{
		if(!getLong(stream, xi, error))
		{
			if(trace)
			{
				cerr << "ERR" << endl;
				cerr << "#bad parameter : \"" << error << "\" is not a valid X coordinate" << endl;
			}
			return NULL;
		}
		else if(!getLong(stream, yi, error))
		{
			if(trace)
			{
				cerr << "ERR" << endl;
				cerr << "#bad parameter : \"" << error << "\" is not a valid Y coordinate" << endl;
			}
			return NULL;
		}
		x.push_back(xi);
		y.push_back(yi);
	}

	if(!checkFlag(stream, trace))
		return NULL;

	Rectangle *r = new Rectangle(name, x, y);

	if(!addManObject(objMan, r, trace))
		return NULL;

	return r;
}


/**
 * @brief addLine : Adds a Line to the objectManager, and treats errors
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static Shape* addLine(stringstream &stream, ObjectManager& objMan, bool trace)
{
	string							name;
	string							error("");

	vector<long>					x, y;
	long							xi, yi;
	stream << ERRFLAG;
	stream >> name;

	for(int i = 0; i < 2; i++)
	{
		if(!getLong(stream, xi, error))
		{
			if(trace)
			{
				cerr << "ERR" << endl;
				cerr << "#bad parameter : \"" << error << "\" is not a valid X coordinate" << endl;
			}
			return NULL;
		}
		else if(!getLong(stream, yi, error))
		{
			if(trace)
			{
				cerr << "ERR" << endl;
				cerr << "#bad parameter : \"" << error << "\" is not a valid Y coordinate" << endl;
			}
			return NULL;
		}
		x.push_back(xi);
		y.push_back(yi);
	}

	if(!checkFlag(stream, trace))
		return NULL;

	Line *l = new Line(name, x, y);

	if(!addManObject(objMan, l, trace))
		return NULL;

	return l;
}


/**
 * @brief addPolyLine : Adds a PolyLine to the objectManager, and treats errors
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static Shape* addPolyLine(stringstream &stream, ObjectManager& objMan, bool trace)
{
	string							name;
	string							error("");

	vector<long>					x, y;
	long							xi, yi;
	int								i(0);

	stream >> name;
	while(stream)
	{
		if(!getLong(stream, xi, error))
		{
			if(error == "")
				break;

			if(trace)
			{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid X coordinate" << endl;
			}
			return NULL;
		}
		else if(!getLong(stream, yi, error))
		{
			if(error == "")
			{
				if(trace)
				{
				cerr << "ERR" << endl;
				cerr << "#missing parameters" << endl;
				}
				return NULL;
			}

			if(trace)
			{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid Y coordinate" << endl;
			}
			return NULL;
		}
		x.push_back(xi);
		y.push_back(yi);
		i++;
	}

	PolyLine *pl = new Line(name, x, y);

	if(!addManObject(objMan, pl, trace))
		return NULL;

	return pl;
}


/**
 * @brief addPolyLine : Adds a Selection to the objectManager, and treats errors
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static void addSelection(stringstream &stream, ObjectManager& objMan)
{
	string							name;
	string							error("");

	vector<long>					x, y;
	long							xi, yi;
	stream << ERRFLAG;
	stream >> name;

	for(int i = 0; i < 2; i++)
	{
		if(!getLong(stream, xi, error))
		{
			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid X coordinate" << endl;
			return;
		}
		else if(!getLong(stream, yi, error))
		{

			cerr << "ERR" << endl;
			cerr << "#bad parameter : \"" << error << "\" is not a valid Y coordinate" << endl;
			return;
		}
		x.push_back(xi);
		y.push_back(yi);
	}

	if(!checkFlag(stream))
		return;

	vector<Shape *> shapes = objMan.getSelectedShapes(x[0], y[0], x[1], y[1]);
	Selection *s = new Selection(name, shapes);
	addManSelection(objMan, s);
}


/**
 * @brief remove : Removes objects from the visible
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static void remove(stringstream &stream, ObjectManager& objMan)
{
	vector<string>							names;
	string									tmpName;
	char									readOne(false);

	while(stream.good() && !stream.eof())
	{
		stream >> tmpName;

		names.push_back(tmpName);

		if(stream.fail() && !readOne)
		{
			cerr << "ERR" << endl;
			cerr << "#At least one object name need to be put" << endl;
			return;
		}
		readOne = true;
	}

	if(!objMan.containsNames(names))
	{
		cerr << "ERR" << endl;
		cerr << "#At least one name doesn't refer to an object" << endl;
		return;
	}

	objMan.removeObjects(names);

	cout << "OK" << endl;
	cout << "#Objects sucsessfully removed" << endl;
}


/**
 * @brief remove : Removes an object
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static void move(stringstream &stream, ObjectManager& objMan)
{
	string									name;
	string									error;
	long									dx, dy;

	stream << ERRFLAG;
	stream >> name;

	if(!getLong(stream, dx, error))
	{
		cerr << "ERR" << endl;
		cerr << "#\"" << error << "\" is not a valid parameter for dX" << endl;
		return;
	}
	else if(!getLong(stream, dy, error))
	{
		cerr << "ERR" << endl;
		cerr << "#\"" << error << "\" is not a valid parameter for dY" << endl;
		return ;
	}

	if(!checkFlag(stream))
	{
		cerr << "ERR" << endl;
		cerr << "#missing parameters" << endl;
		return;
	}

	if(!objMan.contains(name))
	{
		cerr << "ERR" << endl;
		cerr << "#\"" << name << "\" doesn't refer to a valid object" << endl;
		return;
	}

	objMan.moveObject(name, dx, dy);

	cout << "OK" << endl;
	cout << "#Object sucessfully moved" << endl;
}


/**
 * @brief load : Loads a file into the current context
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static void load(stringstream &stream, ObjectManager& objMan)
{
	string									filename;
	string									line;
	ifstream								ifs;
	vector<Shape*>							history;


	stream >> filename;
	ifs.open(filename.c_str());

	if(ifs.fail())
	{
		cerr << "ERR" << endl;
		cerr << "#file \"" << filename << "\" couldn't be opened in read mode" << endl;
		return;
	}

	while(ifs.good())
	{
		Shape*								last;
		stringstream						stream("");
		getline(ifs, line);
		stream << line;

		if(line == "")
			break;

		if(!loadCommand(stream, objMan, &last))
		{
			vector<string>					names;
			for(Shape* s : history)
			{
				names.push_back(s->getName());
			}
			objMan.removeObjects(names, false);

			cerr << "ERR" << endl;
			cerr << "#File loading failed" << endl;

			return;
		}
		else if(last != NULL)
		{
			history.push_back(last);
		}
	}

	cout << "OK" << endl;
	cout << "#file successfully loaded" << endl;

	History *lh = new LoadH(history);
	objMan.addToHistory(lh);
}


/**
 * @brief save : Saves the current shapes in a file
 * @param stream : The command input stream
 * @param objMan : The objectManager instance
 */
static void save(stringstream &stream, ObjectManager& objMan)
{
	string									filename;
	ofstream								ofs;

	stream >> filename;
	ofs.open(filename.c_str());

	if(ofs.fail())
	{
		cerr << "ERR" << endl;
		cerr << "#file \"" << filename << "\" couldn't be opened in write mode" << endl;
		return;
	}

	objMan.printDescs(ofs);
	ofs.close();

	cout << "OK" << endl;
	cout << "#model saved in \"" << filename << "\"" << endl;
}


/**
 * @brief clear : Deletes every element from the current model
 * @param objMan : The objectManager instance
 */
static void clear(ObjectManager& objMan)
{
	objMan.clearObjects();

	cout << "OK" << endl;
	cout << "#Objects cleared" << endl;
}


static void undo(ObjectManager& objMan)
{
	if(objMan.undoCurrent())
	{
		cout << "OK" << endl;
		cout << "#Last command successfully 'undo'ed" << endl;
	}
	else
	{
		cerr << "ERR" << endl;
		cerr << "#There is no command to undo" << endl;
	}
}


static void redo(ObjectManager& objMan)
{
	if(objMan.redoCurrent())
	{
		cout << "OK" << endl;
		cout << "#Last command successfully 'redo'ed" << endl;
	}
	else
	{
		cerr << "ERR" << endl;
		cerr << "#There is no command to redo" << endl;
	}
}


/**
 * @brief getLong : Gets an integer parameter from a stream s
 * @param s : The stream to read
 * @param var : The var where result will be put
 * @param error : The string containing the read parameter (for other treatments)
 * @return true if the read word was an int, false otherwise
 */
static bool getLong(istream& is, long& var, string& param)
{
	stringstream						ss("");
	int									flag(0);

	is >> param;

	if(is.fail())
	{
		param = "";
		return false;
	}

	ss << param << " -1";
	ss >> var >> flag;

	if(!flag)
		return false;

	return true;
}


/**
 * @brief addManObject : Adds a shape to the objectManager
 * @param objMan : The ObjectManager instance
 * @param s : a pointer to the shape
 */
static bool addManObject(ObjectManager& objMan, Shape *s, bool trace)
{
	if(!objMan.addObject(s))
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#bad name : \"" << s->getName() << "\" is already used" << endl;
		}
		delete s;
		return false;
	}
	else
	{
		if(trace)
		{
			cout << "OK" << endl;
			cout << "#New object: " << s->getName() << endl;
		}
		return true;
	}
}


/**
 * @brief addManSelection : Adds a selection to the objectManager
 * @param objMan : The ObjectManager instance
 * @param s : a pointer to the selection
 */
static void addManSelection(ObjectManager& objMan, Selection *s)
{
	if(!objMan.addSelection(s))
	{
		cerr << "ERR" << endl;
		cerr << "#bad name : \"" << s->getName() << "\" is already used" << endl;
		delete s;
	}
	else
	{
		cout << "OK" << endl;
		cout << "#New object: " << s->getName() << endl;
	}
}

/**
 * @brief checkFlag : Checks the EOF flag, and treats the error (cerr)
 * @param stream : The line's stream
 * @return true if the flag is present, false otherwise
 */
static bool checkFlag(istream& stream, bool trace)
{
	int								flag(0);

	stream >> flag;
	if(!flag)
	{
		if(trace)
		{
			cerr << "ERR" << endl;
			cerr << "#missing parameters" << endl;
		}
		return false;
	}

	return true;
}
