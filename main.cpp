#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   char *sql;
   try{
      connection C("dbname=maindb user=matvey password=mityatitya \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }

      sql = "select s.n_post from s except select distinct spj.n_post from spj where spj.n_det in (select distinct spj.n_det from spj where spj.n_izd in (select j.n_izd from j where town = 'Paris'))";

      nontransaction N(C);
      
      result R( N.exec( sql ));
      
      /* List down all the records */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "n_post = " << c[0].as<string>();
      }
      cout << "Operation done successfully" << endl;
      C.disconnect ();



   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }


}