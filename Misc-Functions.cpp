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
