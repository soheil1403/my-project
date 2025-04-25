#include <iostream>
using namespace std;
#include <vector>
class Reservation { private :
  time_t created_at;// ????

  student *s;          
  DiningHall* d;        
    Meal* m;
  int  reservation_id;
  Status status;  //enum
                    public : 
  Reservation (int res ,Status sta , time_t c , student* stu);//DiningHall* hall, Meal* m )                 

  void print() const ;

