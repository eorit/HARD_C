// c++L1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include "Timer.hpp"

//============================================
// Task№1
//============================================

/*Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает
местами значения, на которые указывают эти указатели (нужно обменивать именно сами
указатели, переменные должны оставаться в тех же адресах памяти).*/
template <class T>
void  Swap(T&& T1, T&& T2)
{
    // T temp = {std::move(T2)};
    // temp = std::move(T2);
    auto temp = std::move(T2);
    T2 = std::move(T1);
    T1 = std::move(temp);
}
//============================================
// Task№2
//============================================
/*Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и
сортирует указатели по значениям, на которые они указывают.*/

template <typename T> void  SortPointers(std::vector <T>& T1)
{
    std::sort(T1.begin(), T1.end(), [](T a, T b) { return *a < *b; });
}

//============================================
// Task№3
//============================================
/*Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4
 * способа:
○ count_if и find
○ count_if и цикл for
○ цикл for и find
○ 2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.*/


void read_file(std::list<std::string > & text)
{
    std::string text_word;
    std::ifstream file_read("War and peace.txt");
    //char vowels[] = { 'а', 'е' ,'ё' ,'и' ,'о' ,'у' ,'э' ,'ю' ,'я' };
    int counter = NULL;
    if (!file_read.is_open()) { // если файл не открыт
        std::cout << "Файл \"War and peace.txt\" не может быть открыт!" << std::endl;
    }
    while (!file_read.eof()) {
        //getline(file_read, text_line);
        file_read >> text_word;
        //int first_meth = std::count_if(begin(text_word),end(text_word), std::find(begin(), end(), *vowels));
        text.push_back((text_word));
    }
    file_read.close();
}






int main()
{

    //============================================
    // Task№1
    //============================================
    int a = 5;
    int b = 10;
    int *ptrA=&a;
    int *ptrB=&b;
    std::cout << ptrA << "\t" << ptrB << std::endl;
    std::cout << *ptrA << "\t" << *ptrB << std::endl;
    //Swap(&a,&b);
    //Swap(&V[0],&V[1]);
    Swap(ptrA,ptrB);
    std::cout << ptrA << "\t" << ptrB << std::endl;
    std::cout << *ptrA << "\t" << *ptrB << std::endl;

//============================================
// Task№2
//============================================
    int a = 10;
    int b = 5;
    int* ptra = &a;
    int* ptrb = &b;

    std::cout << "ptra " << ptra << std::endl;
    std::cout << "ptrb " << ptrb << std::endl;
    std::vector <int*> T2{ ptra, ptrb };
    SortPointers(T2);
    std::cout << *T2[0] << " " << *T2[1] << std::endl;
    
//============================================
// Task№3
//============================================

    /*Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4
способа:
○ count_if и find
○ count_if и цикл for
○ цикл for и find
○ 2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.*/
    setlocale(LC_ALL, "Russian");
    
    std::list<std::string> WAR_AND_PEACE;
    read_file(WAR_AND_PEACE);

    char vowels []= { 'а', 'е' ,'ё' ,'и' ,'о' ,'у' ,'э' ,'ю' ,'я' };

    //std::string vowels = "аеёиоуэюя";

    auto compare = [=](auto sym)
                        {
                            if (((sym).find('а') != (sym).npos) || ((sym).find('е') != (sym).npos) || ((sym).find('ё') != (sym).npos) ||
                            ((sym).find('и') != (sym).npos) || ((sym).find('о') != (sym).npos) || ((sym).find('у') != (sym).npos) ||
                            ((sym).find('э') != (sym).npos) || ((sym).find('ю') != (sym).npos) || ((sym).find('я') != (sym).npos))
                            //if ((sym).find(vowels) != (sym).npos)   - в таком виде не счетает, хотя одногрупники говорят, что получалось. в чем подвох?

                            { return true;}
                          return false; 
                          };
    
    Timer Count_if_find;
    Count_if_find.start("Count_if_find");
    auto count_if_find = std::count_if(WAR_AND_PEACE.begin(), WAR_AND_PEACE.end(), compare);
    Count_if_find.print();
    std::cout << count_if_find << std::endl;




    //-------------------------------------------------

    //○ count_if и цикл for


    auto compare2 = [=](std::string& word)
    {
        for (std::string::iterator it = word.begin(); it != word.end(); ++it) {
            if ((*it)== 'а' || (*it) == 'е' || (*it) == 'ё' 
                || (*it) == 'и' || (*it) == 'о' || (*it) == 'у' 
                || (*it) == 'э' || (*it) == 'ю' || (*it) == 'я')
            {
                return true;
            }
            return false;
        }
    };
    Timer Count_if_for;
    Count_if_for.start("Count_if_for");
    int count_if_for = std::count_if(WAR_AND_PEACE.begin(), WAR_AND_PEACE.end(), compare2);
    Count_if_for.print();
    std::cout<<count_if_for<<std::endl;
    
    //-------------------------------------------------
    //○ цикл for и find
    int count_for_find = NULL;
    Timer For_find;
    For_find.start("For_find");
    for (auto it = WAR_AND_PEACE.begin(); it != WAR_AND_PEACE.end(); ++it)
    {
        if (((*it).find('а') != (*it).npos) || ((*it).find('е') != (*it).npos) || ((*it).find('ё') != (*it).npos) ||
            ((*it).find('и') != (*it).npos) || ((*it).find('о') != (*it).npos)|| ((*it).find('у') != (*it).npos)|| 
            ((*it).find('э') != (*it).npos) || ((*it).find('ю') != (*it).npos)|| ((*it).find('я') != (*it).npos) )
        
       //if( (std::find((*it).begin(), (*it).end(), 'а')!=

        {
            ++count_for_find;
        }

    }
    For_find.print();
    std::cout << count_for_find << std::endl;
    //-------------------------------------------------
    //○ 2 цикла for
    
    int count_for_for = NULL;
    Timer For_for;
    For_for.start("for_for");

    for (auto it = WAR_AND_PEACE.begin(); it != WAR_AND_PEACE.end(); ++it) 
    {
        for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            if ((*it2) == 'а' || (*it2) == 'е' || (*it2) == 'ё'
                || (*it2) == 'и' || (*it2) == 'о' || (*it2) == 'у'
                || (*it2) == 'э' || (*it2) == 'ю' || (*it2) == 'я')
            {
                ++count_for_for;
            }
        }
        
    }
    For_for.print();
    std::cout << count_for_for<< std::endl;
    

}