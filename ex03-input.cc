
class Person
{

public:
    Person()
    {
        m_age = 0;
        m_gender = UNKNOWN;
    }

    Person(int age) : m_age(age)
    {
    }

    Person(int age, char gender) : m_age(age), m_gender(gender)
    {
    }

    int get_age()
    {
        return m_age;
    }

    void set_age(int age)
    {
        m_age = age; 
    }

    char m_gender;

    static const char MALE;
    static const char FEMALE;
    static const char UNKNOWN;

private:
    int m_age;

};

const char Person::MALE = 'M';
const char Person::FEMALE = 'F';
const char Person::UNKNOWN = 'U';

int main(int argc, char* argv[])
{
    Person a;

    a.set_age(10);
    a.get_age();

    a.m_gender = Person::MALE;
}
