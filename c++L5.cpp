
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <sstream>

//====================================================
//                  Task 1
//====================================================

/*1. Создать шаблонную функцию, которая принимает итераторы на начало и конец
последовательности слов, и выводящую в консоль список уникальных слов (если слово
повторяется больше 1 раза, то вывести его надо один раз). Продемонстрировать работу
функции, передав итераторы различных типов.*/

template <typename T >
void print_uniq_list(T it, T end)
{
    std::set<std::string> list;
    for (; it != end; ++it) 
    {    
        list.insert(*it);
    }
    
    for (std::set<std::string>::iterator itr = list.begin(); itr != list.end(); ++itr)
    {
        std::cout << *itr << std::endl;
    }
    std::cout << std::endl;
}

//====================================================
//                  Task 2
//====================================================

/*
2. Используя ассоциативный контейнер, напишите программу, которая будет считывать данные
введенные пользователем из стандартного потока ввода и разбивать их на предложения.
Далее программа должна вывести пользователю все предложения, отсортировав их по длине.*/

std::string get_text(std::istream& str)
{
    std::string temp="";
    std::getline(str, temp, '.');
    return temp+".";
}


void print_queue(std::priority_queue<std::pair <int, std::string>>& list)
{
    while (!list.empty())
    {
        std::cout << list.top().second << std::endl;
        list.pop();
    }
}

void lenght_sentence_sorter(std::istream& str)
{
    std::priority_queue <std::pair<int, std::string>> filter;
    while (!str.eof()) {
        std::string temp = get_text(str);
        filter.push(make_pair(temp.size(), temp));
    }
    print_queue(filter);
}



int main()
{
    //====================================================
    //                  Task 1
    //====================================================
    std::vector<std::string> str_vector = { "one", "two", "three", "four", "three","two", "one" };
    std::vector<std::string>::iterator s_it_first = str_vector.begin();
    std::vector<std::string>::iterator s_it_last = str_vector.end();


    std::list<std::string> str_list = { "one", "two", "three", "four", "three","two", "one" };
    std::list<std::string>::iterator s_it_list_first = str_list.begin();
    std::list<std::string>::iterator s_it_list_last = str_list.end();


    print_uniq_list(s_it_first, s_it_last);
    print_uniq_list(s_it_list_first, s_it_list_last);

    //====================================================
    //                  Task 2
    //====================================================

    std::istringstream s1 ("one. one two. one two three.");
    std::istream str(s1.rdbuf()); 
    lenght_sentence_sorter (str);


}

