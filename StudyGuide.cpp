//Const member functions
//the function will not change any member variables of the object
std::string toString() const
{}
----------------------------------------------------------------
//Access functions
//Typically getter and setter Functions
int getNumerator() const { return m_numerator; }   // getter — const, read-only
int getDenominator() const { return m_denominator; }

void setNumerator(int numerator) { m_numerator = numerator; }

void setDenominator(int denominator) {
    if (denominator != 0)          // setter with validation — this is the point
        m_denominator = denominator;
}
//useful when you want to control values coming in^
----------------------------------------------------------------
//Default Constructor:
//type 1
Explicit empty body
Fraction() {}
// relies on default member initializers

//type 2
Fraction(int num = 1, int den = 1)
    : m_numerator{num},
      m_denominator{den} {}
//Provdes initalizers

//Has to be public
public:
    Fraction(int numerator, int denominator)
        : m_numerator{numerator}, m_denominator{denominator} // initializer list
    {
        assert(denominator != 0); // body: validation only
    }
//Full statement

----------------------------------------------------------------
//Destructors
//If your constructor calls new, the destructor must call delete (or delete[] for arrays).

//Destructor must have the same name as the constructor
IntVector(int length) {          // allocates memory
        assert(length > 0);
        m_list   = new int[length]{};
        m_length = length;
    }
~IntVector() // frees memory — called automatically
{
    delete[] m_list;
    m_list = nullptr;
}
----------------------------------------------------------------
//Function Chaining
//Before
void add(int v) { m_value += v; }
void sub(int v) { m_value -= v; }

// must be separate statements
calc.add(5);
calc.sub(3);

//After
// Change the return type from void to ClassName& — a reference to the object.
// Add return *this; at the end of the function body.
Calc& add(int v) { m_value += v; return *this; }
Calc& sub(int v) { m_value -= v; return *this; }

// Then actually calculate it
calc.add(5).sub(3).mult(4);
----------------------------------------------------------------
//Friend Functions
// A friend function is declared inside the class and can access private and protected members
class Accumulator {
private:
    int m_value { 0 };
public:
    void add(int value) { m_value += value; }
    friend void print(const Accumulator& acc); // declaration inside class
};

// definition outside — acts like a free function but accesses private members
void print(const Accumulator& acc) {
    cout << acc.m_value; // m_value is private — OK because friend
}
----------------------------------------------------------------
//Static Members
int generateID() {
    static int s_id{ 0 }; // initialized ONCE, survives across calls
    return ++s_id;
}

//Shared across all instances, not objects
struct Something {
    static int s_value; // declaration inside class
};
int Something::s_value{ 1 }; // definition outside class — required
int main() {
    Something first{}, second{};
    first.s_value = 2;
    std::cout << first.s_value  << '\n'; // 2
    std::cout << second.s_value << '\n'; // 2 — same variable!
}
// first.s_value == second.s_value

//Not attached to any object — no this pointer.
//Can only access other static members. Called via ClassName::function()
class IDGenerator {
private:
    static int s_next_id; // shared across all instances
public:
    static int getNextID() { return s_next_id++; } // no this pointer
};
int IDGenerator::s_next_id { 1 };
int main()
{
    for (int i{0}; i < 5; ++i)
        std::cout << IDGenerator::getNextID() << '\n'; // 1 2 3 4 5
}
----------------------------------------------------------------
//Templates
//Allows functions to work with multiple types
template <typename T>  // template prefix
void swap(T& a, T& b) {
    T temp = b; b = a; a = temp;
}

template <typename T, typename U>
auto max(T x, U y) { return (x < y) ? y : x; }
//auto return type — compiler deduces from the expression
----------------------------------------------------------------
//Function Overloading
//Allows the use of basic operators with classes
Number operator+(const Number &n)
{
    return Number(value + n.value);
}
//Allows for
Number n3 = n1 + n2;

-----------------------------------------------------------------
//Pratice test 1

//Pointer variable pointing to an array
Item* m_backpack = nullptr;

//Accessing an array & matching it to a given rarity
if(m_backpack[i].rarity == rarity)

-----------------------------------------------------------------
//Pratice test 4

//Instructions-dynamcially allocates an array of TicketTransaction structs with a size of 
// m_capacity stores it in m_log leads to the bottom part of the constructor
ConcertAccount::ConcertAccount() :
    m_name{"unnamed"},
    m_id{0},
    m_ticketBalance{0},
    m_capacity{2},
    m_length{0},
    m_log{new TicketTransaction[2]}
{
} 

//Increments the ID
ConcertAccount::ConcertAccount(string name):
    m_name{name},
    m_id{s_nextId},
    m_ticketBalance{0},
    m_capacity{2},
    m_length{0},
    m_log{new TicketTransaction[2]}

{
    s_nextId++;
}