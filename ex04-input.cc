class Car
{
    enum GAS_TYPE {GASOLINE = 0, DIESEL};

    char gas_type;
    bool has_turbo;
};

class Person
{
    char m_gender;
    Car m_car;

    static const char MALE;
    static const char FEMALE;
    static const char UNKNOWN;

    int m_age;
};

