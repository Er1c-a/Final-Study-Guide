//.h file
#include <string>
using namespace std;
enum class TransactionType
{
    TRANSFER_IN,
    TRANSFER_OUT,
    BUY,
    REFUND,
};
struct TicketTransaction
{
    TransactionType type = TransactionType::TRANSFER_IN;
    int count = 0;
    int partnerId = 0;
};
class ConcertAccount
{
    private:
        string m_name = "unnamed";
        int m_id = 0;
        static int s_nextId;
        int m_ticketBalance = 0;
        TicketTransaction* m_log = nullptr;
        int m_capacity = 2;
        int m_length =0;
        void expandLogIfNeeded();
        void addTransaction(TransactionType type, int count, int parterId = -1);
        static int getNextId();
    public:
        ConcertAccount();
        ConcertAccount(string name);
        ~ConcertAccount();
        bool buyTickets(int count);
        bool refundTickets(int count);
        bool transferTickets(ConcertAccount& recipient, int count);
        bool undoLastTransaction();
        int getTicketBalance() const;
        int getTransactionCount() const;
        void clearLog();
};
------------------------------------------------------------------------------------
//.cpp file
#include "ConcertAccount.hpp"
#include <iostream>

// YOU ARE NOT ALLOWED TO ADD ANY LIBRARIES

//Initialize s_nextId
int ConcertAccount::s_nextId = 1;  // DO NOT CHANGE THIS LINE
void ConcertAccount::expandLogIfNeeded()
{
    if(m_length == m_capacity)
    {
        TicketTransaction* temp_table = new TicketTransaction[m_capacity*2];
        for(int i = 0; i<m_capacity;i++)
        {
            temp_table[i] = m_log[i];
        }
        delete[] m_log;
        m_capacity = m_capacity*2;
        m_log = temp_table;
    }
}
void ConcertAccount::addTransaction(TransactionType type, int count, int partnerId)
{
    expandLogIfNeeded();
    m_log[m_length].type = type;
    m_log[m_length].partnerId = partnerId;
    m_log[m_length].count = count;
    m_length++;
}
int ConcertAccount::getNextId()
{
    return s_nextId;
}
ConcertAccount::ConcertAccount():
    m_name{"unnamed"},
    m_id{0},
    m_ticketBalance{0},
    m_capacity{2},
    m_length{0},
    m_log{new TicketTransaction[2]}
{
}
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
ConcertAccount::~ConcertAccount()
{
    delete[] m_log;
    m_log = nullptr;
}
bool ConcertAccount::buyTickets(int count)
{
    if(count <=0)
    {
        return false;
    }
    m_ticketBalance += count;
    addTransaction(TransactionType::BUY, count);
    return true;
}
bool ConcertAccount::refundTickets(int count)
{
    if(count <=0)
    {
        return false;
    }
    m_ticketBalance -= count;
    addTransaction(TransactionType::REFUND, count);
    return true;
}
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
int ConcertAccount::getTicketBalance() const
{
    return m_ticketBalance;
}
int ConcertAccount::getTransactionCount() const
{
    return m_length;
}
void ConcertAccount::clearLog()
{
    m_length = 0;
}