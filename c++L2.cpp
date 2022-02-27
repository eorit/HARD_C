// c++L1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <deque>
#include <optional>
#include <iomanip>
#include <string>
#include <algorithm>
#include <utility>
#include <numeric>
#include <cmath>
//#include <functional>


//-------------------------------------------------------------------
//          TASK №1
//---------------------------------------------------------------------
/*Имеется отсортированный массив целых чисел. Необходимо разработать функцию
insert_sorted, которая принимает вектор и новое число и вставляет новое число в
определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым
контейнером, содержащим любой тип значения.*/


/*void insert_sorted(std::vector<int>& array, int& number)
{
    std::vector<int>::iterator it= std::lower_bound(array.begin(), array.end(), number);
    array.insert(it, number);
}
*/

template<template<class T, class Alloc = std::allocator<T>> typename Container, class T > void insert_sorted(Container <T>& array, T& number)
{
    typename Container <T>::iterator it;
    it= std::lower_bound(array.begin(), array.end(), number);
    array.insert(it, number);
}

void fill_array(std::vector<float>& array, const int& quant)
{
    srand(1000);
    for (int i = 0; i < quant; ++i)
    {
        
        float num = float(rand() )/ 100;
        array.push_back(num);
    }
}

template<template<class T, class Alloc = std::allocator<T>> typename Container, class T> void print_array (Container <T>& array)
{
    for (auto const& num : array) {
        std::cout << num << " ";
    }
    std::cout <<"\n" << std::endl;
}


int main()
{

//-------------------------------------------------------------------
//          TASK №1
//---------------------------------------------------------------------

    std::vector<int> vec{ 0, 10, 100};
    int a= 50;
    insert_sorted(vec, a);
    print_array(vec);
    std::deque <int> deq{ 0, 10, 100 };
    insert_sorted(deq, a);
    print_array(deq);


//-------------------------------------------------------------------
//          TASK №2
//---------------------------------------------------------------------


    //-------------------------------------------
    //Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой
    //значения аналогового сигнала.На основе этого массива чисел создайте другой вектор целых
    //чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
    //Выведите получившиеся массивы чисел.Посчитайте ошибку, которой обладает цифровой
    // сигнал по сравнению с аналоговым по формуле :
    //----------------------------------------------
    
    std::vector<float> fvec;
    std::vector<int> ivec;
    
    int quantity = 100;

    fvec.reserve(quantity);
    ivec.reserve(quantity);

    fill_array(fvec, quantity);
    std::transform(fvec.begin(), fvec.end(), back_inserter(ivec), [](float number) {return round(number); });

    print_array(fvec);
    print_array(ivec);

    float result = std::inner_product(begin(fvec), end(fvec), begin(ivec), 0.0, std::plus<>(), [](float &first, int &second) {return (first-second)* (first - second); });
    std::cout << result << std::endl;
}