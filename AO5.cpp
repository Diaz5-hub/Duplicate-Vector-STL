 
//Assingment 5
//June 5, 2020
#include<iostream>

//using namespace std;
//read Vector,
namespace CS52{
  using namespace std;
  class Vector{
  public: 
    Vector ();
    Vector(int size, int int_val);
    // Copy constructor
    Vector(const Vector&); 
    // Destructor
    ~Vector();

    // Resize Vector; refer to C++ docs
    void resize(int new_size , int init_val);

  // Increase capacity of Vector; refer to 
    void reserve( int new_capacity );

  // Returns a reference to the element at
  // throw a string if out of bounds
    int& at ( int index ) const;

  // Returns the allocated storage for the Vector. 
    int capacity() const; 

  // Erases elements of the vector,but does not change capacity
    void clear ();

  // Returns pointer to the first element in the Vector. 
    int* data() const;

  // If Vector is empty return true, else false. 
    bool empty() const;

  // Deletes the element at the end of the vector. 
    void pop_back ();
  // Add an element to the end of the vector.
  // _ _ _ _ _ -> _ _ _ _ element 
     void push_back(int element);
  //
  // Returns the number of elements in the vector. 
    int size() const;
  // Overloaded operators
    int& operator[] ( int index ); // [] array syntax
    Vector& operator=( const Vector& ); // copy assignment
  // Overloaded stream insertion operator
    //friend ostream& operator <<(ostream&,Vector&);

  private:
    int _size = 0;
    int _capacity = 0;
    int * _data = nullptr;
  };
   //friend ostream& operator <<(ostream&,Vector&);
}


  CS52::Vector::Vector(){
    _size = 0;
    _capacity = 0;
    _data = nullptr;
  }

  CS52::Vector::Vector(int size, int int_val){ //Overloaded: Vector example(2, 5) 
      _size = size;
      _capacity = size;
      _data = new int[_capacity];
      for(int i = 0;i < size;i++){
        *(_data + i) = int_val; 
      }
      
    }

  CS52::Vector::Vector(const Vector& V){
    _size = V.size();
    _capacity = V.capacity();
    // Allocate more meomory
    _data = new int[_capacity]; 
    // Copy over contents of data from V to current object
    for(int i = 0; i < _capacity; i++){
      if(i > (_size - 1) )
      {
        *(_data + i) = 0;
      }
      *(_data + i) = V.at(i);
    }
    
  }

  CS52::Vector::~Vector(){
    _size = 0;
    _capacity = 0;
    delete [] _data;
  }

  void CS52::Vector::resize(int new_size , int init_val){
      if(_size < new_size){
        for(int i = _size; i < new_size; i++){
          this->push_back(init_val);
        }
      }
      else if(_size > new_size){
        while(_size > new_size){
          this->pop_back();
        //for(int i = _size; i  new_size;i++){
          //this->pop_back();
        }
      }
      else{
        //continue;
      }
  }

  void CS52::Vector::reserve( int new_capacity ){
    // Do nothing if already enough capacity
    if(_capacity >= new_capacity){
      return;
    }
    // Allocating enough memory to hold new_capacity number of elements
    else{
      int *temp = new int[new_capacity];
      // No elements
      if(this->empty()){
        _data = temp;
      }
      // Elements exist
      else{
        // Copy over original array
        for(int i = 0; i < _capacity;i++){
            *(temp + i) = _data[i];
          }
        _capacity = new_capacity;
        
        delete [] _data;
        _data = new int[_capacity];
        for(int i = 0; i < _size; i++)
        {
          _data[i] = temp[i];
        }
        delete [] temp;
      }      
    }
  }

   int& CS52::Vector::at ( int index ) const{
      return _data[index];
   }

   int CS52::Vector::capacity() const{ return _capacity;}

   void CS52::Vector::clear (){
    
    for(int i = 0;i < _capacity; i++){
      _data[i]= 0;
      _size--;
    }
  }

  int* CS52::Vector::data() const{ return _data;  }

  bool CS52::Vector::empty() const{
    if( _size == 0){
      return true;
    }
    else{
      return false;
    }
  }

  void CS52::Vector::pop_back ()
  {
    //size empty
    if(_size == 0){
      return;
    }
    // Size != 0
    else{
      int* temp = new int[_capacity-1];
      for(int i = 0; i < _capacity-1;i++){
        temp[i] = _data[i];
      }
      delete[] _data;
        _data = new int[_capacity];
        for(int i = 0; i < _capacity; i++)
        {
          _data[i] = temp[i];
        }
        --_size;
        delete[] temp;
    }
  }

  void CS52::Vector::push_back( int element ){
    // First element added
    if(_data == nullptr){
      _capacity++;
      _data = new int[_capacity];
      _data[_capacity-1] = element;
      _size++;
    }
    else{

      // Enough capacity
      if(_size < _capacity){
        // Adding elements to end of array after moving them
        if(_size == 0)
        {
          _data[0] = element;
          _size++;
          return;
        }
        // adding element
        _data[_capacity - (_capacity - _size)] = element;
        // incrementing size
        _size++;
      }
      // NOT enough _capacity
      else{
        // Allocating more memory to fit one more element
        int *temp = new int[_capacity+1];

        //Copy over original array
        for(int i = 0; i < _capacity;i++){
          *(temp + i) = _data[i];
        }
        temp[_capacity] = element;
        _size++;
        _capacity++;

        // making _data point to a new address and assigning the values to temp to it
        delete[] _data;
        _data = new int[_capacity];
        for(int i = 0; i < _capacity; i++)
        {
          _data[i] = temp[i];
        }
        delete[] temp;
       
        
      }
    }
  }

  int CS52::Vector::size() const{
    return _size;
  }

  int& CS52::Vector::operator[] ( int index ){
    return _data[index];
  }

  CS52::Vector& CS52::Vector::operator=( const CS52::Vector& V){
    if(this == &V){
      return *this;
    }
    else{
      delete[] _data;
      this->_data = new int[V.capacity()];
      for(int i =0; i < V.size();i++){
      this->push_back(V.at(i));
      }
      this->_capacity = V.capacity();
      return *this;
    }
  }

   CS52::ostream& operator<<(CS52::ostream& os, CS52::Vector& V){
    for(int i = 0;i < V.size();i++){
      os << V[i];
      if(i != V.size() - 1){
        os << ", ";
      }
    }
    return os;
  }



void  info(CS52:: Vector& v){std::cout  << "Size is: " << v.size() << "\n";
std::cout  << "_capacity  is: " << v.capacity () << "\n";
std::cout  << "Contents : ";
for (int i = 0; i < v.size (); i++) 
{std::cout  << v[i] << " ";}
std::cout  << "\n";}//info


int  main() {//  default  constructor , push_back , at  methods
std::cout  << "// default  constructor , push_back , at \nCS52:: Vector a;\n";
CS52:: Vector a;
std::cout  << "\na.push_back (10); a.push_back (88)\n";
a.push_back (10);
 a.push_back (88);
 std::cout  << "a.at(0) = 99;\n";
 a.at(0) = 99;info(a);//b
 std::cout  << "\n// overloaded  constructor , [] op , at , empty ,\\ clear , exception  handling: at \nCS52:: Vector b(2 ,5);\n";
 CS52:: Vector b(2 ,5);
 std::cout  << "b is " << b << "\n"; 
 std::cout  << "\n//Add  more  elements  to b\n";
 std::cout  << "b.push_back (10); b.push_back (2);\n";
 std::cout  << "b.push_back (99); b.push_back ( -5);\n";
 b.push_back (10); b.push_back (2);
 b.push_back (99); b.push_back (-5); 
 std::cout  << "\n// array  index [] and at()\n";
 std::cout  << "b[0] = 25; b[1] = 1;\n";
 b[0] = 25; b[1] = 1;
 std::cout  << "b.at(0) ; b.at(1) ;\n";
 std::cout  << b.at(0)  << " " << b.at(1)  << "\n";
 std::cout  << "\n\n// empty  method , size , and  capacity\n";
 std::cout  << "b.empty() " << (b.empty() ? "True" : "False") << "\n";
 std::cout  << "b.clear ()\n";
 b.clear ();
 std::cout  << "b.empty() " << (b.empty() ? "True" : "False") << "\n";
 std::cout  << "\n\n// Exception  handling:";
 try {std::cout  << "\nb.at(9) = ";
 std::cout  << b.at(9);
 }
 catch (std:: string  msg) { std::cerr  << "\n" << msg  << std::endl; }

 //c
 std::cout  << "\n//copy  constructor , copy  assignment , pop_back ,reserve ,\n//resize , capacity , size\nCS52:: Vector c(b);\n";
 std::cout  << "\n//Add  more  elements  to b\n";
 std::cout  << "b.push_back (11); b.push_back (7);\n";
 std::cout  << "b.push_back (3); b.push_back (23);\n";
 b.push_back (11); b.push_back (7); 
 b.push_back (3); b.push_back (23);
 //testing
 info(b);
 CS52:: Vector c(b);
 info(c);

 //d
 std::cout  << "\n//copy  assignment\n";
 CS52:: Vector d;
 d = c;
 std::cout  << "CS52:: Vector d = c; " << "\n";
 std::cout  << "d is " << d << "\n";
 std::cout  << "\n//size vs  capacity ()\n";
 std::cout  << "d.size() is "      << d.size() << "\n";std::cout  << "d.capacity () is " << d.capacity () << "\n";
 std::cout  << "\n// pop_back ()\n";
 std::cout  << "d.pop_back ();d.pop_back ();\n";
 d.pop_back (); 
 d.pop_back ();
 std::cout  << "\n//size vs  capacity\n";
 std::cout  << "d.size() is " << d.size() << "\n";std::cout  << "d.capacity () is " << d.capacity () << "\n";
 // fix this part
 std::cout  << "\n//Resize -Reserve  Testing \n";
 d.resize (10,  -1);
 std::cout  << "d.resize (10,  -1); \n";
 info(d);
 d.resize(5, 0);
 std::cout  << "\nd.resize(5, 0); \n";
 info(d);d.reserve (15);
 std::cout  << "\nd.reserve (15); \n";
 info(d);d.reserve (1);
 std::cout  << "\nd.reserve (1); \n";info(d);
 char  stop; std::cin  >> stop;

  return  0;
}//main
