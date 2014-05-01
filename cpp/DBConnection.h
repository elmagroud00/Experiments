#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <cassert>
#include <string>
#include "Countable.h"
#include "Database.h"
using std::string;

class DBConnection : public Database, public Countable {
	DBConnection(const DBConnection&); 
	DBConnection &operator=(const DBConnection&);
protected:
	DBConnection(const string &dbStr) throw(DatabaseError) : Database(dbStr) { open(); }
	~DBConnection() { close(); }
public:
	static DBConnection *create(const string &dbStr) throw(DatabaseError) {
		DBConnection *con = new DBConnection(dbStr);
		con->attach();
		assert(con->refCount() == 1);
		return con;
	}
};

#endif
