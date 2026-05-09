#include <string>
using namespace std;
struct User
{
    string name;
    int id = 0;
};
class Post
{
    private:
        string m_content;
        int m_post_id = 0;
        static int m_next_id;
        User* m_viewed = nullptr;
        int m_viewed_size = 0;
        int m_viewed_capacity = 50;
        User* m_likes = nullptr;
        int m_likes_size = 0;
        int m_likes_capacity = 25;
        void doubleCapacity(User*& table, int& capacity);
    public:
        Post(string content);
        ~Post();
        int getNumberOfViews() const;
        int getNumberOfLikes() const;
        void addView(User user);
        bool addLike(User user);
        void removeLike(User user);
};
------------------------------------------------------------------------------------
#include "Post.h"
// Initialize m_next_id
int Post::m_next_id = 1;  // DO NOT CHANGE THIS LINE
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
Post::Post(string content) :
    m_content{content}, 
    m_post_id{m_next_id},
    m_viewed{new User[50]}, 
    m_likes{new User[25]}
{
    m_next_id++;
}
Post::~Post()
{
    delete[] m_viewed;
    m_viewed = nullptr;
    delete[] m_likes;
    m_likes = nullptr;
}
int Post::getNumberOfViews() const
{
    return m_viewed_size;
}
int Post::getNumberOfLikes() const
{
    return m_likes_size;
}
void Post::addView(User user)
{
    for(int i = 0; i<m_viewed_size;i++)
    {
        if(m_viewed[i].id == user.id)
        {
            return;
        }
    }
    if(m_viewed_size == m_viewed_capacity)
    {
        doubleCapacity(m_viewed,m_viewed_capacity);
    }
    m_viewed[m_viewed_size] = user;
    m_viewed_size++;
}
bool Post::addLike(User user)
{
    for(int i = 0; i<m_likes_size;i++)
    {
        if(m_likes[i].id == user.id)
        {
            return false;
        }
    }
    if(m_likes_size == m_likes_capacity)
    {
        doubleCapacity(m_likes,m_likes_capacity);
    }
    m_likes[m_likes_size] = user;
    m_likes_size++;
    addView(user);
    return true;
}
void Post::removeLike(User user)
{
    for(int i = 0; i<m_likes_size; i++)
    {
        if(m_likes[i].id == user.id)
        {
            for(int j=i; j<m_likes_size-1;j++)
            {
                m_likes[j] = m_likes[j+1];
            }
            m_likes_size--;
            m_likes[m_likes_size] = User();
            return;
        }
    }
}