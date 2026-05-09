//.h file
#pragma once
#include <string>
#include <vector>
using namespace std;
enum class ItemRarity
{
    COMMON,
    RARE,
    LEGENDARY,
};
struct Item
{
    string name = "Unknown";
    double value = 0.0;
    ItemRarity rarity = ItemRarity::COMMON;
};
class Character
{
    private:
        string m_name = "Unknown";
        Item* m_backpack = nullptr;
        int m_num_items = 0;
        double m_money = 0.0;
    public:
        Character();
        Character(const string name, double money, const vector<Item>& items);
        ~Character();
        string getName() const;
        double getTotalBackpackValue() const;
        int countRarity(ItemRarity rarity) const;
        bool dropItem(const string& item_name);
        double sellItem(const string& item_name);
        bool pickUpItem(Item item);
        bool tradeItem(const string& item_name, Character& partner);
};
------------------------------------------------------------------------------------
//.cpp file
#include "Character.h"
Character::Character()
{
}
Character::Character(const string name, double money, const vector<Item>& items)
{
    m_name = name;
    m_num_items = items.size();
    m_money = money;
    m_backpack = new Item[m_num_items];
    for(int i = 0; i< m_num_items; i++)
    {
        m_backpack[i] = items[i];
    }
}
Character::~Character()
{
    delete[] m_backpack;
    m_backpack = nullptr;
}
string Character::getName() const
{
    return m_name;
}
double Character::getTotalBackpackValue() const
{
    double total = 0;
    for(int i = 0; i<m_num_items; i++)
    {
        if(m_backpack[i].rarity == ItemRarity::COMMON)
        {
            total += m_backpack[i].value;
        }
        if(m_backpack[i].rarity == ItemRarity::RARE)
        {
            total += m_backpack[i].value * 1.5;
        }
        if(m_backpack[i].rarity == ItemRarity::LEGENDARY)
        {
            total += m_backpack[i].value * 2.0;
        }
    }
    return total;
}
int Character::countRarity(ItemRarity rarity) const
{
    int count = 0; 
    for(int i = 0; i<m_num_items;i++)
    {
        if(m_backpack[i].rarity == rarity)
        {
            count ++;
        }
    }
    return count;
}
bool Character::dropItem(const string& item_name)
{
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
    return false;
}
double Character::sellItem(const string& item_name)
{
    for(int i = 0; i<m_num_items; i++)
    {
        if(m_backpack[i].name == item_name)
        {
            double value = 0;
            if(m_backpack[i].rarity == ItemRarity::COMMON)
            {
                value += m_backpack[i].value;
            }
            if(m_backpack[i].rarity == ItemRarity::RARE)
            {
                value += m_backpack[i].value * 1.5;
            }
            if(m_backpack[i].rarity == ItemRarity::LEGENDARY)
            {
                value += m_backpack[i].value * 2.0;
            }
            m_money += value;
            dropItem(item_name);
            return value;
        }
    }
    return 0;
}
bool Character::pickUpItem(Item item)
{
    for(int i = 0; i<m_num_items; i++)
    {
        if(m_backpack[i].name == item.name)
        {
            if(m_backpack[i].rarity >= item.rarity)
            {
                return false;
            }
            else if(m_backpack[i].rarity < item.rarity)
            {
                m_backpack[i] = item;
                return true;
            }
        }
    }
    Item* temp = new Item[m_num_items+1];
    for(int i = 0; i<m_num_items;i++)
    {
        temp[i] = m_backpack[i];
    }
    temp[m_num_items] = item;
    delete[] m_backpack;
    m_backpack = temp;
    m_num_items++;
    return true;
}
bool Character::tradeItem(const string& item_name, Character& partner)
{
    for(int i = 0; i<m_num_items;i++)
    {
        if(m_backpack[i].name == item_name)
        {
            Item item = m_backpack[i];
            if(partner.pickUpItem(item))
            {
                dropItem(item_name);
                return true;
            }
            return false;
        }
    }
    return false;
}