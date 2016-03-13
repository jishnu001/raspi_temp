#include<iostream>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_driver.h" 
#include <cppconn/prepared_statement.h>

extern "C"{
#include "pi_dht_read.h"
}

using namespace std;

int main()
{

float temp=0.0;
float hum=0.0;

if(pi_dht_read(11,4,&temp,&hum)==0)
{
std::cout<<"\nTemperature: "<<temp<<"\nHumidity: "<<hum<<std::endl;
}

else
 std::cout<<"\nReading...\n";

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *pstmt;
  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "titansx43");
  /* Connect to the MySQL test database */
  con->setSchema("mydb");


  stmt = con->createStatement();
  pstmt = con->prepareStatement("INSERT INTO SensorData (temp,humidity,timestamp) VALUES (?,?,now())");
    pstmt->setDouble(1, temp);
    pstmt->setDouble(2, hum);
    pstmt->executeUpdate();
  delete pstmt;

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



