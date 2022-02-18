// c++L1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <optional>
#include <iomanip>
#include <string>
#include <algorithm>


struct Person {
private:
    std::string SURNAME;
    std::string NAME;
    std::optional<std::string> PATRONYMIC;
public:
    Person() {}
    friend bool operator < (const Person& First, const Person& Second);
    friend bool operator == (const Person& First, const Person& Second);
    Person(std::string _SURNAME, std::string _NAME, std::optional<std::string> _PATRONYMIC) : SURNAME(_SURNAME), NAME(_NAME), PATRONYMIC(_PATRONYMIC) {}
    std::string get_surname() const;
    std::string get_name() const;
    std::optional<std::string> get_patronymic() const;
    friend std::ostream& operator << (const std::ostream& outstream, const Person& Person);
    ~Person() {}
    void set_surname(std::string surname);
    void set_name(std::string surname);
    void set_patronymic(std::optional<std::string> patronymic);


};

bool operator == (const Person& First, const Person& Second) {
    return std::tie(First.SURNAME, First.NAME, First.PATRONYMIC) ==
           std::tie(Second.SURNAME, Second.NAME, Second.PATRONYMIC);
}


bool operator < (const Person& First, const Person& Second) {
    return std::tie(First.SURNAME, First.NAME, First.PATRONYMIC) <
           std::tie(Second.SURNAME, Second.NAME, Second.PATRONYMIC);
}


std::string Person::get_surname() const{
    return SURNAME;
}
std::string Person::get_name() const {
    return NAME;
}
std::optional<std::string> Person::get_patronymic() const{
    if (PATRONYMIC) {
        return PATRONYMIC.value();
    }
    return std::nullopt;
}
void Person::set_surname(std::string surname) {
    SURNAME = surname;
}
void Person::set_name(std::string name) {
    NAME = name;
}
void Person::set_patronymic(std::optional<std::string> patronymic) {
    PATRONYMIC = patronymic;
}





std::ostream& operator << (std::ostream& outstream, const Person& Person) {
    outstream.width(10);
    outstream.left;
    outstream << Person.get_surname();
    outstream.width(15);
    outstream.left;
    outstream << Person.get_name();
    outstream.width(15);
    outstream.left;
    if (Person.get_patronymic()) {
        outstream << *Person.get_patronymic();
    }
    else {
        outstream.width(15);
        outstream << '\t';
        outstream.fill(' '); }
    //outstream.fill(' ');
    return outstream;
};


struct PhoneNumber {
    int COUNTRYCODE;
    int CITYCODE;
    std::string PHONENUMBER;
    std::optional <int> ADDITIONAL_NUMBER;
    friend bool operator < (const PhoneNumber& First, const PhoneNumber& Second);
    friend bool operator == (const PhoneNumber& First, const PhoneNumber& Second);
    friend std::ostream& operator << (const std::ostream& outstream, const PhoneNumber & Number);

    PhoneNumber() {}

    PhoneNumber(int _COUNTRYCODE, int _CITYCODE, std::string _PHONENUMBER, std::optional <int> _ADDITIONAL_NUMBER) :
            COUNTRYCODE(_COUNTRYCODE), CITYCODE(_CITYCODE), PHONENUMBER(_PHONENUMBER), ADDITIONAL_NUMBER(_ADDITIONAL_NUMBER) {};

    ~PhoneNumber() {}

};



bool operator < (const PhoneNumber& First, const PhoneNumber& Second) {
    return std::tie(First.COUNTRYCODE, First.CITYCODE, First.PHONENUMBER, First.ADDITIONAL_NUMBER) <
           std::tie(Second.COUNTRYCODE, Second.CITYCODE, Second.PHONENUMBER, Second.ADDITIONAL_NUMBER);
}


bool operator == (const PhoneNumber& First, const PhoneNumber& Second) {
    return std::tie(First.COUNTRYCODE, First.CITYCODE, First.PHONENUMBER, First.ADDITIONAL_NUMBER) ==
           std::tie(Second.COUNTRYCODE, Second.CITYCODE, Second.PHONENUMBER, Second.ADDITIONAL_NUMBER);
}

std::ostream& operator << ( std::ostream& outstream, const PhoneNumber& Number) {
    outstream.width(15);
    outstream.left;
    outstream  << "+" << Number.COUNTRYCODE << "(" << Number.CITYCODE << ")" << Number.PHONENUMBER;
    if (Number.ADDITIONAL_NUMBER) {
        outstream <<" "<< Number.ADDITIONAL_NUMBER.value();
    }
    outstream.fill(' ');
    return outstream;
}




class PhoneBook {


public:

    std::vector<std::pair<Person, PhoneNumber>> Vector_Of_Pairs;
    PhoneBook(std::ifstream& FilePhoneBook);
    ~PhoneBook() {
        Vector_Of_Pairs.clear();
    }
    void SortByPhone();
    void SortByName();
    std::tuple<std::string, PhoneNumber> GetPhoneNumber(std::string Surname);
    void ChangePhoneNumber(Person person, PhoneNumber phonenumber);
    friend std::ostream& operator << (const std::ostream& outstream, const PhoneBook& Book);
};

std::ostream& operator << (std::ostream& outstream, const  PhoneBook& Book) {

    for (auto& vpair : Book.Vector_Of_Pairs) {
        outstream << vpair.first << vpair.second << std::endl;
    }
    return outstream;
}

PhoneBook::PhoneBook(std::ifstream & FilePhoneBook) {
    //std::cout << "const. PhoneBook"<<std::endl;
    Person sPersonTemp;
    std::string SURNAME;
    std::string NAME;
    std::string PATRONYMIC;
    PhoneNumber sPhoneNumberTemp;
    std::string tempName = "";
    std::string tempPhone = "";
    while (!FilePhoneBook.eof()) {
        FilePhoneBook >> SURNAME >>NAME >> PATRONYMIC
                      >> sPhoneNumberTemp.COUNTRYCODE >> sPhoneNumberTemp.CITYCODE >> sPhoneNumberTemp.PHONENUMBER >> tempPhone;
        
        sPersonTemp.set_name(NAME);
        sPersonTemp.set_surname(SURNAME);
        if (PATRONYMIC == "-") {
            sPersonTemp.set_patronymic(std::nullopt);
        } else { 
            sPersonTemp.set_patronymic(PATRONYMIC);
        }
        if (isdigit(tempPhone.c_str()[0])) {
            sPhoneNumberTemp.ADDITIONAL_NUMBER = std::stoi(tempPhone);
        }
        Vector_Of_Pairs.push_back(std::pair(sPersonTemp, sPhoneNumberTemp));
        FilePhoneBook.peek();
    }
    FilePhoneBook.close();
}

void PhoneBook::SortByPhone() {
    auto compare = [](std::pair<Person, PhoneNumber> Line1, std::pair<Person, PhoneNumber> Line2) {return Line1.second < Line2.second; };
    std::sort(Vector_Of_Pairs.begin(), Vector_Of_Pairs.end(), compare);
}

void PhoneBook::SortByName() {
    auto compare = [](std::pair<Person, PhoneNumber> Line1, std::pair<Person, PhoneNumber> Line2) {return Line1.first < Line2.first; };
    std::sort(Vector_Of_Pairs.begin(), Vector_Of_Pairs.end(), compare);
}

std::tuple<std::string, PhoneNumber> PhoneBook::GetPhoneNumber(std::string Surname) {
    std::string message_not_found = "not found";
    std::string message_found_more = "found more than 1";
    size_t count = 0;
    PhoneNumber temp;
    for ( auto& [person, phoneNumber] : Vector_Of_Pairs) {
        if (person.get_surname() == Surname) {
            ++count;
            temp = phoneNumber;
        }
    }
    if (count == 1) {
        return std::tie("", temp);
    }
    else if (count == 0) {
        return std::tie(message_not_found, temp);
    }
    else  {
        return std::tie(message_found_more, temp);
    }
}


void PhoneBook::ChangePhoneNumber(Person targetperson, PhoneNumber targetphonenumber) {

    for (auto& [person, phoneNumber] : Vector_Of_Pairs) {
        if (person == targetperson) {
            phoneNumber = targetphonenumber;
        }
    }
}



int main()
{
    std::cout << "------Start-------" << std::endl;
    std::ifstream file ("PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    std::cout << book;
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    std::cout << book;
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    std::cout << book;
    std::cout << "-----GetPhoneNumber-----" << std::endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона
    //этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const std::string& surname) {
        std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
            std::cout << std::get<1>(answer);
        else
            std::cout << std::get<0>(answer);
        std::cout << std::endl;
    };
    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    std::cout << "----ChangePhoneNumber----" << std::endl;
    book.ChangePhoneNumber(Person{"Kotov", "Vasilii", "Eliseevich"}, PhoneNumber {7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },PhoneNumber { 16, 465, "9155448", 13 });
    std::cout << book;

}