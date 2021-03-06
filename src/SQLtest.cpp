/*
examples/standalone_example_docs1.cpp
*/

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h"       
using namespace std;

int main(void)
{
cout << endl;
//cout << "Running 'SELECT 'Hello World!' AS _message'..." << endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "titansx43");
  /* Connect to the MySQL test database */
  con->setSchema("mydb");


  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * from SensorData");
  while (res->next()) {
    cout << "\t... temperature: ";
    /* Access column data by alias or column name */
    cout << res->getString("temp") << endl;
    cout << "\t... humidity: ";
    /* Access column fata by numeric offset, 1 is the first column */
    cout << res->getString("humidity") << endl;
  }
  delete res;
  delete stmt;
  delete con;

} catch (sql::SQLException &e) {
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;

return EXIT_SUCCESS;
}

