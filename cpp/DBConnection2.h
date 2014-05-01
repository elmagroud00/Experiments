#ifndef DBCONNECT2_H
#define DBCONNECT2_H
#include <cassert>
#include <string>
#include "Database.h"
using std::string;

template<class Counter>
class DBConnection : public Database, public Counter {
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

#endif // DBCONNECT2_H
