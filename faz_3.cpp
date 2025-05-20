#include <iostream>
using namespace std;
#include <vector>
//#include <ctime>

class Reservation { private :
  time_t created_at;// زمان

 // student *s;          
  DiningHall* d;        
    Meal* m;
  int  reservation_id;
  Status status;  //enum
                    public : 
  Reservation (int resID, Status status, time_t created, DiningHall* hall, Meal* meal )  ;               

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
  time_t getCreatedAt() const;

};


class student : public User {      private :
    vector<Reservation> reservations; 
     string phone;
     string student_id;
     string email;
     float balance;
     bool is_active;
                     public :
   student();                  
   student (int id, const string& id1, const string& n,const string& p, const string& ln,
    const string& e, float b, const string& hp, bool a = true) : 
    User(id, n, ln, hp), student_id(id1), email(e), balance(b), is_active(a),phone(p) {}
    
   bool isActive();
   void activate();
   void deactivate();
   void print() const override;
   string getType() const override;
   void addReservation(const Reservation& res);
  bool reserve_meal (const Reservation& res, string meal_name ,float c) ; 
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

bool student ::isActive(){
  return is_active;
}
void student ::activate() {
  is_active = true;
}
void student ::deactivate(){
  is_active=false;
}

void student::print() const {
  cout << "User ID: " <<  getUserID() << endl;
  cout << "Student ID: " << student_id << endl;
  cout << "Name: " << getName() << endl;
  cout << "Phone: " << phone << endl;
  cout << "Email: " << email << endl;
  cout << "Balance: " << balance << endl;
  cout << "Active: " << (is_active ? "Yes" : "No") << endl;
}
string student::getType() const {
  return "Student";
}

bool student::reserve_meal (const Reservation& res, string meal_name ,float c ) {
      if ( ! is_active ) {
        cout<< "not active";
      } else { return false;}

      if ( balance>=c ) {
        reservations.push_back(res);
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
  
      
      void student::setbalance(float a )  {//ست بالانس 
        if (a>0){
          balance=a+balance;
        }else {
          cout << "Balance cannot be negative." << endl;
        }
      }  

     void  student::setname(string a ){// ست نیم
      if ( a.length()>= 2 ){
        setname(a);
      }else {
        cout<< "name is not true";
      }
     }

     void student:: setemail (string e){//ست ایمیل
        if (e.find('@') != string::npos){
          email=e;
        }else{
          cout<<"email is not true";
        }
     }
    
       
     

     // گت های رده student
     //int student::getUserID() const { return user_id; }
string student::getStudentID() const { return student_id;}
//string student::getName() const { return name;}
string student::getEmail() const { return email; }
float student::getBalance() const { return balance;}
bool student::getIsActive()const { return is_active; }

////////////ناموسا خسته شدم

enum Status {
  Reserv,  // رزوه
  Cancel  // لغوه
};

 


void Reservation::print() const{
  cout << "Reservation ID: " << reservation_id << endl;
  //cout << "Student: " << s->getName() << endl;
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
  if (status=Cancel){
    cout<<"Reservation is already cancelled"; return false;
  } status = Cancel;
   cout << "Reservation cancelled successfully." << endl; 
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

//یا علی 

enum MealType {
 bereakfast , lunch , dinner
};
enum ReserveDay { sat, aun, mon, tue, wed, thu, fri };

class Meal { private :
    int meal_id;
    string name ;
     bool isactive;
    float price ;
    MealType mealtype;
    ReserveDay reserveday;
    vector<string> side_items;
            public:
  Meal(int id,const string & name, float price,MealType type, ReserveDay day);
  bool isActive() const;
    MealType getMealType() const;
    ReserveDay getReserveDay() const;
    void setMealType(MealType type);
    void setReserveDay(ReserveDay day);
  void activate();
  void deactivate();  
  void print ()const;
  void update_price(float new_price) ;
  void add_side_item(const string& item);

//ست ها
  void setMealID(int id);
  void setName(const string& newName);
  void setPrice(float newPrice);
  void setMealType(MealType type);
//گت ها
  int getMealID() const;
  string getName() const;
  float getPrice() const;
  MealType getMealType() const;
  vector<string> getSideItems() const;

};
void Meal::setMealType(MealType type) {
    mealtype = type;
}

void Meal::setReserveDay(ReserveDay day) {
    reserveday = day;
}
bool Meal::isActive() const  {
    return isactive;
}
MealType Meal::getMealType() const {
  return mealtype;
}
ReserveDay Meal::getReserveDay() const {
  return reserveday;
}
void Meal::activate() {
    isactive = true;
}
void Meal::deactivate() {
    isactive = false;
}

Meal::  Meal(int id,const string & name, float price,MealType type, ReserveDay day) :
 meal_id(0) ,name (name) , price(0.0),isactive(true), mealtype(bereakfast), reserveday(sat) {}

void Meal :: print ()const{
     switch (mealtype){
       case bereakfast : cout<<"bereakfast" << endl; 
       break;
       case lunch : cout<< "lunch" << endl; break ;
       case  dinner : cout<< "dinner"<< endl;break;}
       cout << "Side Items: ";
       for (size_t i = 0; i < side_items.size(); ++i){
        cout<<side_items[i]<<endl;
       }

     cout<< "meal_id:"<<meal_id;
     cout << "Name: " << name << endl;
     cout << "Price: $" << price << endl;
     cout << "Meal Type: ";}

     void Meal::add_side_item(const string& i){
      side_items.push_back(i);
     }



     void Meal :: update_price(float np){
      if (np>0){
        price=np+price;
       }}

int Meal::getMealID() const { return meal_id;}
string Meal::getName() const { return name;}
float Meal::getPrice() const {return price;}
MealType Meal::getMealType() const { return mealtype;}
vector<string> Meal::getSideItems() const { return side_items;}

void Meal::setName(const string& newName) {name = newName; }
void Meal::setPrice(float newPrice) { if (newPrice>=0)price = newPrice;}
void Meal::setMealType(MealType type) {mealtype = type;}


void Meal::setMealID(int id){
  if (id>0){
    meal_id = id;
  }else{
    cout<<"Invalid Meal ID! Must be positive";
  }
}


//خوب اخرین کلاس

class DiningHall { private:
    int hall_id;
    string name;
    string address;
    int capacity;//ظرفیت
     public:

     DiningHall (int h , string n , string a , int c) {}
     void print() const;
//گت ها
     int getHallID() const;
     string getAddress() const;
     int getCapacity() const;
     string getName() const;
     //ست ها
     void setName(string n);
     void setAddress(string n);
     void setCapacity(int n);

};

DiningHall::DiningHall(int id, string n, string a, int c){
  hall_id=id;
  name=n;
  address=a;
  capacity=c;
}

void DiningHall::print() const{
  cout<< "hall_id:"<<hall_id<<endl;
  cout<<"name::"<<name<<endl;
  cout<<"address"<<address<<endl;
  cout<<"capacity"<<capacity<<endl;
}
     
//گت ها
string DiningHall::getName()const {return name; }
string DiningHall::getAddress() const{ return address; }
int DiningHall::getCapacity() const{ return capacity;}
int DiningHall::getHallID() const { return hall_id;}
//ست ها
void DiningHall::setName(string n) { name = n; }
void DiningHall::setAddress(string n) { address = n; }
void DiningHall::setCapacity(int n) {
    if (n > 0)
        capacity = n;
    else
        cerr << "Capacity must be positive!" << endl;
}

class User { protected:
    int userID;
    string name;
    string lastName;
    string hashedPassword;
      public:
    User (int id , const string& n , const string & lastn,const string&hp );
    
    //پلیفرمیسم
    virtual void print() const = 0;
    virtual string getType() const = 0;
   //getter
    int getUserID() const;
    string getName() const;
    string getLastName() const;
    string getHashedPassword() const;

    // Setters
    void setName(const string& n);
    void setLastName(const string& lastn);
    void setHashedPassword(const string& hp);
};

User::User (int id , const string& n , const string & lastn,const string&hp ){
  userID=id;
  name=n; 
  lastName=lastn;
  hashedPassword=hp;
}
void User::setName(const string& n) {name = n;}
void User::setLastName(const string& lastn) {lastName =lastn;}
void User::setHashedPassword(const string& hp) {hashedPassword =hp; }
int User::getUserID() const{return userID;}
string User::getName() const{return name; }
string User::getLastName() const {return lastName;}
string User::getHashedPassword() const { return hashedPassword ;}

//admin
class Admin : public User{
  public:
  Admin(int id, const string& n, const string& lastn, const string& hp)
        : User(id, n, lastn, hp) {}

        string getType() const override {
        return "Admin";
    }
        void print()const override {
          cout<<"id admin "<<userID<<endl;
          cout<<"name "<<name;
        }
};

class Panel {
  public:
  void Action (int);
     void showStudentInfo();            // اطلاعات دانشجو
    void checkBalance();               // موجودی
     void viewReservations() ;           // رزروهh
  void addReservation(Reservation);  //  افزودن رزرو جدید
    void addToShoppingCart();          // افزودن به سبد خرید
     void confirmShoppingCart() ;        // تایید سبد
    void removeShoppingCartItem() ;     // حذف از سبد
    void increaseBalance();            // افزایش موجودی
    void viewRecentTransactions();     // تراکنش‌ها
    void cancelReservation(int) ;       // لغو رزرو با id
    void viewShppingCart();
    void addToShoppingCart();//
    void confirmShoppingCart();//
    void showmenu (){}
    void exit() {}
};

void Panel ::Action (int a){
   switch(a){
    case 1 :
     showmenu ();
     break;
    case 2 :
      showStudentInfo();
      break;
    case 3 :
       viewReservations ();
       break;
    case 4 :
      checkBalance();
      break;
    case 5 :
      addToShoppingCart();
      break;
    case 6 : 
      confirmShoppingCart();
      break;
    case 7: 
      removeShoppingCartItem();
      break;
    case 8 : 
      increaseBalance();
      break;
    case 9 :
      viewRecentTransactions();
      break;
    case 10 :
    int a;
    cancelReservation(a);
    break;  
    case 11 : 
    viewShppingCart();
    break;  
    case 0:
    exit();
    break;
    default:
   }
}

void Panel ::showmenu (){
  Meal::print;
}
void Panel::showStudentInfo(){
  student::print;
}
void Panel::checkBalance(){
  student::getBalance;
}
void Panel::viewReservations(){
   Reservation::print;
}
void Panel::viewShppingCart(){
  ShoppingCart::viewShoppingCartItems;
}
void Panel::removeShoppingCartItem(){
  ShoppingCart::removeReservation;
}
void Panel::increaseBalance() {
    student ob;
    int m;
    cout << "Enter the amount of money.";
    cin >> m;
    ob.setbalance(m);
}

class Storage { private:
   int _mealIDCounter;
   int _diningHallIDCounter;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;

    Storage ():_diningHallIDCounter(1),_mealIDCounter(1){};
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;//حدف کپی‌ساز و کپی‌اپراتور
    public:
    static Storage& instance(){
      static Storage instance;
      return instance;//فقط یک شی ساخته مشه
    }
};

class ShoppingCart { private:
  vector<Reservation> _reservations;
  public:
  void addReservation(Reservation reservation);
  void removeReservation(int ID);
  void viewShoppingCartItems();
  void clear();
  vector<Reservation> getReservations() const;
  //Transaction confirm();  بعدا

};

void ShoppingCart ::addReservation (Reservation reservation){//اضافه کردن
  _reservations.push_back(reservation);
  cout<<"Reservation added"<<endl;
}

void ShoppingCart ::removeReservation (int Id){
  for (auto i =_reservations.begin();i!=_reservations.end();i++ ){
    if (i->getReservationID()==Id){
      _reservations.erase(i);
      cout<<Id<<" Deleted "<<endl;
      return;
    }
  }cout<<Id <<" not found" << endl;
}

void ShoppingCart::viewShoppingCartItems(){
  if (_reservations.empty()){//empty اگه لیست خالی باشه true برمیگرده
    cout<<"It is empty."<<endl;
  }
  for(const Reservation& r : _reservations){
    r.print();
  }
}

void ShoppingCart ::clear (){
  _reservations.clear();
  cout<<"Everything was cleared."<<endl;
}

vector<Reservation>ShoppingCart:: getReservations() const{
  return _reservations;
}

//تراکنش
enum class TransactionType { Deposit, Payment };
enum class TransactionStatus { Pending, Completed, Failed };
class Transaction{ private:
    int transactionID;
    string trackingCode ;
    float amount;
    TransactionType type ;//enum
    TransactionStatus status;//enum
    time_t createdAt ;//time
    public:
    Transaction();

    //set
    void setTransactionID(int id);
    void setTrackingCode(string & code);
    void setAmount(float amount);
    void setType(TransactionType type);
    void setStatus(TransactionStatus status);
    void setCreatedAt(time_t  t);
    //get
     int getTransactionID() const;
    std::string getTrackingCode() const;
    float getAmount() const;
    TransactionType getType() const;
    TransactionStatus getStatus() const;
    time_t getCreatedAt() const;

};

Transaction::Transaction() :transactionID(0), trackingCode(" "),//کانستواکتور
amount(0),type(TransactionType::Payment),status(TransactionStatus::Pending),
createdAt(time(nullptr)) {}
//گت
int Transaction::getTransactionID() const {return transactionID;}
std::string Transaction::getTrackingCode() const{ return trackingCode;}
float Transaction::getAmount()const {return amount;}
TransactionType Transaction::getType()const{return type;}
TransactionStatus Transaction::getStatus()const {return status;}
time_t Transaction::getCreatedAt()const{ return createdAt;}
//ست
void Transaction::setTransactionID(int id){ transactionID= id;}
void Transaction::setTrackingCode(string& code){ trackingCode =code;}
void Transaction::setAmount(float amount){
    if (amount>= 0) amount=amount;}
void Transaction::setType(TransactionType type) {type =type;}
void Transaction::setStatus(TransactionStatus status){status = status;}
void Transaction::setCreatedAt(time_t t){ createdAt = t;}

//////////////////////////////
namespace AdminSession {
    class SessionManager : public SessionBase {
    public:
        void func();
    };
}

namespace StudentSession {
    class SessionManager : public SessionBase {
    public:
        void func();
    };
}
void AdminSession::SessionManager::func() {
    // منطق مخصوص به ادمین
}

void StudentSession::SessionManager::func() {
    // منطق مخصوص به دانشجو
}


enum class SessionStatus {
    AUTHENTICATED,//تایید
    ANONYMOUS//ناشناس
};

class SessionBase { protected :
  time_t createdAt;
  time_t lastTimeLogin;
  SessionStatus  status;
  virtual void load_session()= 0;
  virtual void save_session()= 0; 
  public:
  virtual void login(string, string) =0;
  virtual void logout() =0;

   void setCreatedAt(time_t t){createdAt =t; }
    void setLastTimeLogin(time_t t){ lastTimeLogin =t;}
    void setStatus(SessionStatus s) { status= s;}
    //set
    time_t getCreatedAt()const {return createdAt; }
    time_t getLastTimeLogin() const {return lastTimeLogin;}
    SessionStatus getStatus()const {return status;}

};

class SessionManager : public SessionBase { private:
    student* _currentStudent;
    ShoppingCart* shopping_cart;
    int studentID;

    public:
    void load_session() override;
    void save_session() override;
    void login(string u, string p) override;
    void logout() override;
    student currentStudent ();
    ShoppingCart shoppingCart();
    static SessionManager& instance();
     int getStudentID()const{
      return studentID;
     }


};
student  SessionManager::currentStudent(){
    return* _currentStudent;
  }

ShoppingCart SessionManager::shoppingCart() {
    return* shopping_cart;
  }
  SessionManager& SessionManager::instance() {
    static SessionManager instance;  // ساخته می‌شه فقط یک بار
    return instance;                 //مرجع برمی‌گردد
}

////////////////
namespace AdminSession {
class SessionManager : public SessionBase { private:
  Admin* _currentAdmin ;
  int _adminID ;

  SessionManager(const SessionManager&)= delete;
  SessionManager& operator =(const SessionManager&) = delete;
  SessionManager() : _currentAdmin(nullptr), _adminID(-1){}

  public:
  void load_session() override ;
  void save_session() override;
  void login(string, string) override;
  void logout() override ;
  Admin currentAdmin() {
        return *_currentAdmin;
       }
 static SessionManager& instance();
 
 int get_adminID(){return _adminID;}
     

};
SessionManager& SessionManager::instance(){
        static SessionManager instance ;
        return instance;
    } }


int main (){}
