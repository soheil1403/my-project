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
  bool cancel ();

  void setReservationID(int id);
 // void setStudent(student* stu);
 //void setDiningHall(DiningHall* hall);
 //void setMeal(Meal* m);
  void setStatus(Status stat);
  void setCreatedAt(time_t c);


  int getReservationID() const;
  student* getStudent() const;
  DiningHall* getDiningHall() const;
  Meal* getMeal() const;
 Status getStatus() const;
 Status getStatus() const;
  time_t getCreatedAt() const;

};


class student {      private :
                    vector<Reservation> reservations; 
     int user_id;
      string student_id;
     string name;
     string email;
     float balance;
     bool is_active;
                     public :
   student (int id , string id1 , string n , string e , float b , bool a=true ) { //??????
    user_id=id ;

