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
//#include <lock_guard>
//============================================
// Task№1
//============================================

/*1. Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. Необходимо,
чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль.
Продемонстрируйте работу pcout.*/
class pcout //: public  std::ostream
{
	//T BUFFER;
	
	std::mutex M;

	//std::ostream;
public:
	//pcout(T _BUFFER) :BUFFER(_BUFFER) {};
	pcout() 
	{
		std::mutex M;
		M.lock();
	};

	template < typename Type>
	void operator << (Type BUFFER)
	{
		out << BUFFER;
		//return *this;
	}
	
	/*void operator << (std::string BUFFER)
	{
		std::cout << BUFFER;
		//return *this;
	}
	*/


	template < typename Type>
	std::ostream& operator << ( Type BUFFER)
	{
		std::cout << BUFFER;
		//return *this;
	}

	~pcout(){
		M.unlock();
	};
} pcout;


void print_thread_id()
{
	pcout << std::this_thread::get_id();
	std::cout << "2" << 1;
}

//============================================
// Task№2
//============================================


/*2. Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое
число равно 15485863). Вычисления реализовать во вторичном потоке. В консоли отображать
прогресс вычисления.*/









//============================================
// Task№3
//============================================


/*3. Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. Хозяин
приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1
раз в секунду). При этом у каждой вещи есть своя ценность. Вор забирает вещи (функция,
которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5
секунд), каждый раз забирает вещь с наибольшей ценностью.*/

//





int main()
{
	std::thread th1;
	std::thread th2;
	std::thread th3;
	std::string a = "a";

	pcout << 12;
}