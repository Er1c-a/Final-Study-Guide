//.h file
#include <string>
#include <cmath>
// YOU ARE NOT ALLOWED TO ADD OTHER LIBRARIES
using namespace std;

enum class Species
{
    DOG,
    CAT,
    BIRD,
    FISH
};

class Pet
{
    private:
        string m_name;
        Species m_species;
        int m_hunger;
        int m_energy;
        int m_happiness;
    public:
        Pet();
        Pet(const string& pet_name,const Species& pet_species,const int& hunger, const int& energy, const int& happiness);
        string getName() const;
        int getWellBeingScore();
        void feed();
        void play();
        void rest();
};
class Owner
{
    private:
        string m_name = "Unknown";
        Pet* m_pet_list = nullptr;
        int m_num_of_pets = 0;
    public:
        Owner();
        Owner(const string& owner_name);
        Owner(const Owner& owner);
        ~Owner();
        int getPetCount() const;
        bool removePet(const string& pet_name);
        bool adoptPet(const Pet& pet);
        bool transferPetTo(const string& pet_name, Owner& owner);
        Pet* getPetList() const;
};
bool isPetBelongsToOwner(const Pet& pet, const Owner& owner);
------------------------------------------------------------------------------------
//.cpp file
#include "code.h"
Pet::Pet()
{
    m_name = "Unknown";
    m_species = Species::DOG;
    m_hunger = 50;
    m_energy =50;
    m_happiness = 50;

}
Pet::Pet(const string& pet_name,const Species& pet_species,const int& hunger, const int& energy, const int& happiness)
{
    m_name = pet_name;
    m_species = pet_species;
    m_hunger = hunger;
    m_energy =energy;
    m_happiness = happiness;
}
string Pet::getName() const
{
    return m_name;
}
int Pet::getWellBeingScore()
{
    return round(m_energy * 0.3 + m_happiness * 0.3 + (100 - m_hunger) * 0.4);
}
void Pet::feed()
{
    m_hunger -=20;
}
void Pet::play()
{
    m_energy -=10;
    m_happiness +=15;
    m_hunger +=5;
}
void Pet::rest()
{
    m_energy +=20;
}

Owner::Owner()
{
}
Owner::Owner(const string& owner_name)
{
    Owner::m_name = owner_name;
}
Owner::Owner(const Owner& owner)
{
    m_name = owner.m_name;
    m_num_of_pets = owner.m_num_of_pets;
    m_pet_list = owner.m_pet_list;
}
Owner::~Owner()
{
    delete[] m_pet_list;
    m_pet_list = nullptr;
}
int Owner::getPetCount() const
{
    return m_num_of_pets;
}
bool Owner::removePet(const string& pet_name)
{
    for(int i = 0; i<m_num_of_pets; i++)
    {
        if(m_pet_list[i].getName() == pet_name)
        {
            for(int j=i; j<m_num_of_pets-1;j++)
            {
                m_pet_list[j] = m_pet_list[j+1];
            }
            m_num_of_pets--;
            return true;
        }
    }
    return false;
}
bool Owner::adoptPet(const Pet& pet)
{
    for(int i = 0; i<m_num_of_pets;i++)
    {
        if(m_pet_list[i].getName() == pet.getName())
        {
            return false;
        }
    }
    Pet* temp = new Pet[m_num_of_pets+1];
    for(int i = 0; i<m_num_of_pets;i++)
    {
        temp[i] = m_pet_list[i];
    }
    temp[m_num_of_pets] = pet;
    delete[] m_pet_list;
    m_pet_list = temp;
    m_num_of_pets++;
    return true;
}
bool Owner::transferPetTo(const string& pet_name, Owner& owner)
{
    for(int i = 0; i<m_num_of_pets;i++)
    {
        if(m_pet_list[i].getName() == pet_name)
        {
            Pet pet = m_pet_list[i];
            if(owner.adoptPet(pet))
            {
                removePet(pet_name);
                return true;
            }
            return false;
        }
    }
    return false;
}
Pet* Owner::getPetList() const
{
    return m_pet_list;
}
bool isPetBelongsToOwner(const Pet& pet, const Owner& owner)
{
    for(int i=0; i<owner.getPetCount();i++)
    {
        if(owner.getPetList()[i].getName() == pet.getName())
        {
            return true;
        }
    }
    return false;
}