#include "Database.h"

int main() {
	Database db("MyDatabase");
	db.open();
	db.close();
}
