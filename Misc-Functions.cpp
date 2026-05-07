//Function overloading
class Time {
    int mHours, mMinutes, mSeconds; // private
public:
    // declaration lives inside the class
    friend Time operator+(Time& lhs, Time& rhs);
};

// definition lives outside — acts like a free function
// lhs = left hand side, rhs = right hand side
Time operator+(Time& lhs, Time& rhs) {
    // can access mHours, mMinutes, mSeconds because friend
}
----------------------------------------------------------------
//Pratice Test 1

//Primary constructor setup
Pet::Pet(const string& pet_name,const Species& pet_species,const int& hunger, const int& energy, const int& happiness)
{
    m_name = pet_name;
    m_species = pet_species;
    m_hunger = hunger;
    m_energy =energy;
    m_happiness = happiness;
}

//Deleting an element & lowering an array by one
for(int i = 0; i<m_num_items; i++)
{
    if(m_backpack[i].name == item_name)
    {
        for(int j=i; j<m_num_items-1;j++)
        {
            m_backpack[j] = m_backpack[j+1];
        }
        m_num_items--;
        return true;
    }
}

//Adding an element & Increasing an array by one
Item* temp = new Item[m_num_items+1];
for(int i = 0; i<m_num_items;i++)
{
    temp[i] = m_backpack[i];
}
temp[m_num_items] = item;
delete[] m_backpack;
m_backpack = temp;
m_num_items++;

//Transfering an Item from one character to another
Item item = m_backpack[i];
if(partner.pickUpItem(item))
{
    dropItem(item_name);
}

//If member is private, have to use getters in the loops
if(m_pet_list[i].getName() == pet.getName())


------------------------------------------------------------
//Test 2

//Setting up constructor
Post::Post(string content) : 
    m_content{content}, 
    m_post_id{m_next_id},
    m_viewed{new User[50]}, 
    m_likes{new User[25]}
{
    m_next_id++;
}

//Doubles the capacity
void Post::doubleCapacity(User*& table, int& capacity)
{
    User* temp_table = new User[capacity*2];
    for(int i = 0; i<capacity;i++)
    {
        temp_table[i] = table[i];
    }
    delete[] table;
    capacity = capacity*2;
    table = temp_table;
}

------------------------------------------------------------
// Test 4

//Another way to transfer things between accounts
bool ConcertAccount::transferTickets(ConcertAccount& recipient, int count)
{
    if(count <= 0 || count > m_ticketBalance || m_id == recipient.m_id)
    {
        return false;
    }
    m_ticketBalance -= count;
    addTransaction(TransactionType::TRANSFER_OUT, count, recipient.m_id);
    recipient.m_ticketBalance += count;
    recipient.addTransaction(TransactionType::TRANSFER_IN, count, m_id);
    return true;
}

//Undoing the last transaction
bool ConcertAccount::undoLastTransaction()
{
    if(m_length == 0)
    {
        return false;
    }
    TicketTransaction last = m_log[m_length - 1];
    if(last.type == TransactionType::TRANSFER_IN || last.type == TransactionType::TRANSFER_OUT)
    {
        return false;
    }
    if(last.type == TransactionType::BUY)
    {
        m_ticketBalance -= last.count;
    }
    else if(last.type == TransactionType::REFUND)
    {
        m_ticketBalance += last.count;
    }
    m_length--;
    return true;
}