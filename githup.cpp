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
     student_id=id1;
    name= n ;
    email = e ; 
    balance = b;
    is_active=a;
   } 
   
   void print() const;
   void addReservation(const Reservation& res);

  bool reserve_meal ( string meal_name ,float c ) ; 
  bool cancel_reservation(string meal_name, float c1) ;
   void setbalance (float a );
  void setname ( string a);

  void setemail (string e);

  string getName() const; 
  int getUserID() const;
  string getStudentID() const;
  
  string getEmail() const;
   float getBalance() const;
  bool getIsActive() const;
};
void student::print() const {
  cout << "User ID: " << user_id << endl;
  cout << "Student ID: " << student_id << endl;
  cout << "Name: " << name << endl;
  cout << "Email: " << email << endl;
  cout << "Balance: " << balance << endl;
  cout << "Active: " << (is_active ? "Yes" : "No") << endl;
}

bool student::reserve_meal ( string meal_name ,float c ) {
      if ( ! is_active ) {
        cout<< "not active";
      } else { return false;}

      if ( balance>=c ) {
        balance = balance  - c ;
         cout << "Reserved meal= " << meal_name << "money" << c ;
         return true ;
      } else {
        cout<< "you are out of stock " ;
        return false;
      }
      } bool student :: cancel_reservation (string meal_name, float c1){
       balance = balance + c1;
       cout<<"cancelled reservation for"<<meal_name<< "Refunded ="<< c1 ;


      } 
      void student::addReservation(const Reservation& res) {
        reservations.push_back(res);
    }
  
      
      void student::setbalance(float a )  {//?? ?????? 
        if (a>0){
          balance=a;
        }else {
          cout << "Balance cannot be negative." << endl;
        }
      } 
      void  student::setname(string a ){// ?? ???
      if ( a.length()>= 2 ){
        name=a;
      }else {
        cout<< "name is not true";
      }
     }

     void student:: setemail (string e){//?? ?????
        if (e.find('@') != string::npos){
          email=e;
        }else{
          cout<<"email is not true";
        }
     }
     // ?? ??? ??? student
     int student::getUserID() const { return user_id; }
string student::getStudentID() const { return student_id;}
string student::getName() const { return name;}
string student::getEmail() const { return email; }
float student::getBalance() const { return balance;}
bool student::getIsActive()const { return is_active; }

////////////?????? ???? ???

enum Status {
  Reserv,  // ????
  Cancel  // ????
};

void Reservation::print() const{
  cout << "Reservation ID: " << reservation_id << endl;
  cout << "Student: " << s->getName() << endl;
   cout << "Meal: " << m->getMealName() << endl;
   cout << "Dining Hall: " << d->getHallName() << endl;
 cout<< "Status";
 if (status == Reserv){
  cout<<"reserv"<< endl;
 }else {
  cout<<"cancel"<< endl;
 }
 cout << "Created at: " << ctime(&created_at);
}


bool Reservation::cancel() {
	if (status==Reserv){
       status=Cancel;
       s->setbalance(s->getBalance() + m->getCost());
       cout << "Reservation cancelled. Refund processed." << endl;
       return true;
   }else {
    cout<<"Already cancelled." << endl;
    return false;
   }
}

void Reservation :: setReservationID(int id){
  reservation_id = id;
}
void Reservation::setStatus(Status stat) { status = stat; }
void Reservation::setCreatedAt(time_t c) { created_at = c; }

int Reservation::getReservationID() const { return reservation_id; }
// student* Reservation::getStudent() const { return s; }
// DiningHall* Reservation::getDiningHall() const { return d;}
 //Meal* Reservation::getName() const { return m;}
Status Reservation::getStatus() const { return status; }
time_t Reservation::getCreatedAt() const { return created_at; }

//?? ??? 

enum MealType {
 bereakfast , lunch , dinner
};

class Meal { private :
    int meal_id;
    string name ;
    float price ;
    MealType mealtype;
    vector<string> side_items;
            public:
  Meal ();
  void print ()const;
  void update_price(float new_price) ;
  void add_side_item(const string& item);

//?? ??
  void setMealID(int id);
  void setName(const string& newName);
  void setPrice(float newPrice);
  void setMealType(MealType type);
//?? ??
  int getMealID() const;
  string getName() const;
  float getPrice() const;
  MealType getMealType() const;

