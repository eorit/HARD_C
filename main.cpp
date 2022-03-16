// c++L1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>
#include <ostream>
#include <windows.h>
#include <queue>
#include <future>
//============================================
// Task№1
//============================================

/*1. Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо,
чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль.
Продемонстрируйте работу pcout.*/


class pcout : public std::stringstream
{

    static inline  std::mutex M;

public:


    ~pcout(){
        //std::lock_guard <std::mutex> i{M};
        M.lock();
        std::cout<<rdbuf();
        std::cout.flush();
        M.unlock();
    };
} pcout;




void print_thread_id(int number)
{

    pcout << "pcout: "<<"\nthread id:" << std::this_thread::get_id()<<"\tnumber:"<<number<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    pcout << "pcout after sleep: "<<"\nthread id:" << std::this_thread::get_id()<<"\tnumber:"<<number<<std::endl;
}

//============================================
// Task№2
//============================================


/*2. Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое
число равно 15485863). Вычисления реализовать во вторичном потоке. В консоли отображать
прогресс вычисления.*/

int getNumber()
{
    int index;
    std::cin>>index;
    return index;
}

void load_bar(size_t counter, int index){

    std::mutex P;
    //std::lock_guard <std::mutex> {P};
    P.lock();
    std::system("cls");
    int proc_for_loadbar=(counter*40)/index;
    int proc=(counter*100)/index;
    //std::system("clear");
    for(int i=0; i<proc_for_loadbar; ++i)
    {
        std::cout<<"#";
    }
    std::cout<<proc<<"%"<<std::endl;
    P.unlock();
    std::this_thread::sleep_for( std::chrono::milliseconds(5));
}

int calculateSimplNumber(int index)
{
    if (index==1)
    {
        return 2;
    }
    size_t counter=1;
    std::list <int> simpl_array;
    simpl_array.push_back(2);
    //simpl_array.reserve(index);
    int i=3;
    while (counter !=index)
    {

        std::thread print (load_bar,counter,index);
        print.join();
        if ((i > 10) & (i%10==5))
         {
             i+=2;
             continue;
         }
        for (int j:simpl_array)
        {
            if ((j*j-1)>i)
            {
                simpl_array.push_back(i);
                ++counter;
                break;
            }
            if (i%j==0)
            {
                break;
            }
            else
            {
                simpl_array.push_back(i);
                ++counter;
                break;
            }
        }
        i+=2;

    }
    return *simpl_array.rbegin();
}



//============================================
// Task№3
//============================================


/*3. Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. Хозяин
приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1
раз в секунду). При этом у каждой вещи есть своя ценность. Вор забирает вещи (функция,
которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5
секунд), каждый раз забирает вещь с наибольшей ценностью.*/

//

void insertInHouse(std::vector <int>& house)
{
    std::mutex M;  // сначала сделал функции без мьютекса и блокировки, но в какой-то из запусков потоки вывода пересеклись, поэтому ввел
    std::lock_guard<std::mutex> lg {M};
    while (house.size()>1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int a = rand() % 20 + 1;
        std::cout << "thread: " << std::this_thread::get_id() << " insert: " << a << std::endl;
        house.push_back(a);
    }
}


void stealFromHouse(std::vector <int>& house)
{
    std::mutex M;
    std::lock_guard<std::mutex> lg {M};
    while (house.size())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        auto target = std::max_element(house.begin(), house.end());
        std::cout << "thread: " << std::this_thread::get_id() << " steal: " << *target << std::endl;
        house.erase(target);
    }
}




int main()
{

//============================================
// Task№1
//============================================

    std::thread th1(print_thread_id, 1);
    std::thread th2(print_thread_id, 2);
    std::thread th3(print_thread_id, 3);

    th1.join();
    th2.join();
    th3.join();

//============================================
// Task№2
//============================================

int n=100;
int simpl;
std::thread task2([&](){simpl=calculateSimplNumber(n);});
task2.join();
std::cout<<simpl;

//============================================
// Task№3
//============================================

std::vector<int> items {1,2,3};

auto insert = std::async (std::launch::async,insertInHouse,ref(items));
auto steal = std::async (std::launch::async,stealFromHouse, ref(items));

}