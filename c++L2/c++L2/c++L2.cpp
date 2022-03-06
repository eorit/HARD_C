
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <list>


//============================================
// Task№1
//============================================

/*
1Написать функцию, добавляющую в конец списка вещественных чисел
элемент, значение которого равно среднему арифметическому всех его
элементов.*/

void insert_arithmetic_mean(std::list<double>& list)
{   
    double result = NULL;
    int counter= NULL;
    for(double meaning : list)
    {
        result+= meaning;
    }
    counter=list.size();
    result = result / counter;
    list.push_back(result);
}


void print_list(std::list<double>& list)
{
    for (double meaning : list)
    {
        std::cout << meaning<<" ";
    }
    std::cout << std::endl;
}



//============================================
// Task№2
//============================================


/*
2. Создать класс, представляющий матрицу. Реализовать в нем метод,
вычисляющий определитель матрицы.*/

class matrix 
{
    std::vector<std::vector<int>> Matrix;
    int determinant;
    
public:
    matrix() {};
    matrix(std::vector<std::vector<int>>& _Matrix)
    {
        Matrix = move(_Matrix);
        determinant = calculate_determinant();
    };

    void set_matrix( std::vector<std::vector<int>>& _Matrix);
    void insert_column( std::vector<int>& _Matrix, int pos);
    void insert_row( std::vector<std::vector<int>>& _Matrix, int pos);
    void delete_column( int pos);
    void delete_row( int pos);
    void delete_column(std::vector<std::vector<int>>& _Matrix, int pos);
    void delete_row(std::vector<std::vector<int>>& _Matrix, int pos);

    int calculate_determinant(std::vector<std::vector<int>> _Matrix);
    int calculate_determinant();

    int get_determinant();
    std::vector<std::vector<int>> get_matrix() ; 
    void print();
    void print_determinant();
    ~matrix() {};

};


void matrix::set_matrix( std::vector<std::vector<int>>& _Matrix)
{
    Matrix = move(_Matrix);
}

/*void matrix::insert_column(std::vector<int>& _Matrix, int pos)
{
    for (std::vector<std::vector<int>>::iterator row = Matrix.begin(); row != Matrix.end(); ++row)
    {
        std::vector<int > ::iterator column = (*row).begin();
        std::vector<int > ::iterator column_for_insert =( _Matrix.begin()+ ((Matrix.begin()-row)));
        for (int counter = 0; counter <= pos; ++column, ++counter)
        {
            if (counter == pos)
            {
                (*row).emplace(column, *column_for_insert);
            }
        }
    }
};*/

/*void matrix::insert_row(std::vector<std::vector<int>>& _Matrix, int pos)
{
    Matrix.emplace(Matrix.begin() + pos, _Matrix);
};*/

void matrix::delete_column(std::vector<std::vector<int>>& _Matrix, int pos)
{
    for (std::vector<std::vector<int>>::iterator row = _Matrix.begin(); row != _Matrix.end(); ++row)
    {   
        std::vector<int > ::iterator column = (*row).begin();
        for (int counter = 0; counter <= pos;   ++counter, ++column)
        {
            if (counter == pos) 
            {
                (*row).erase(column);
                break;
            }
            //++column;
        }
    }
    //return _Matrix;
}

void matrix::delete_column(int pos)
{
    for (std::vector<std::vector<int>>::iterator row = Matrix.begin(); row != Matrix.end(); ++row)
    {
        std::vector<int > ::iterator column = (*row).begin();
        for (int counter = NULL; counter <= pos; ++column, ++counter)
        {
            if (counter == pos)
            {
                (*row).erase(column);
            }
        }
    }
}

std::vector<std::vector<int>> matrix::get_matrix()
{
    return  Matrix;
}

void matrix::delete_row(std::vector<std::vector<int>>& _Matrix, int pos)
{
    _Matrix.erase(_Matrix.begin()+pos);
    //return _Matrix;
}

void matrix::delete_row(int pos)
{
    Matrix.erase(Matrix.begin() + pos);
}

int matrix::calculate_determinant()
{
    int quant_rows = Matrix.size();
    int quant_columns = (*(Matrix.begin())).size();
    int temp;
    int result=0;
    int k = 1;
    //std::vector<std::vector<int>> temp_matrix = matrix;
    if (quant_rows == quant_columns)
    {
        std::vector<std::vector<int>>::iterator rows = Matrix.begin();
        std::vector<int>::iterator columns = (*(rows)).begin();

        if (quant_rows == 2) {
            //for (int i = 0, int k = 1; i < quant_row; ++i, k *= -1)
            std::vector<int>::iterator meaning_first_row = (*(rows)).begin();
            std::vector<int>::iterator meaning_second_row = (*(rows + 1)).begin();
            result = ((*meaning_first_row) * *(meaning_second_row + 1)) - (*(meaning_first_row + 1) * (*meaning_second_row));
            //std::cout << "result square matrix: " << result << std::endl;
        }

        else {
            for (int i = 0; i < (quant_rows); ++i, k *= -1)
            {   
                
                temp = 0;
                int first_row = 0;
                std::vector<std::vector<int>> temp_matrix = Matrix;
                temp += k * (*(columns + i));
                //std::cout << "a"<<i<< "= " << temp << std::endl;
                delete_row(temp_matrix, first_row);
                delete_column(temp_matrix, i);
                temp *= calculate_determinant(temp_matrix);
               // std::cout <<"temp= " << temp << std::endl;
                result =result+ temp;
                //std::cout << result << std::endl;
            }

        }
        return result;
    }

    else
    {
        std::cout << "Matrix is not square matrix" << std::endl;
    }
};

int matrix::calculate_determinant(std::vector<std::vector<int>> matrix)
{
    int quant_rows = matrix.size();
    int quant_columns =(*(matrix.begin())).size();
    int temp=0;
    int result=0;
    int k = 1;
    //std::vector<std::vector<int>> temp_matrix = matrix;
    if (quant_rows == quant_columns)
    {
        std::vector<std::vector<int>>::iterator rows = matrix.begin();
        std::vector<int>::iterator columns = (*(rows)).begin();

        if (quant_rows == 2) {
            //for (int i = 0, int k = 1; i < quant_row; ++i, k *= -1)
            std::vector<int>::iterator meaning_first_row = (*(rows)).begin();
            std::vector<int>::iterator meaning_second_row = (*(rows + 1)).begin();
            result = ((*meaning_first_row) * *(meaning_second_row + 1)) - (*(meaning_first_row + 1) * (*meaning_second_row));
            //std::cout << *meaning_first_row<< "\t"<< *(meaning_first_row + 1) << " mATRIX" << std::endl;
           // std::cout << *(meaning_second_row)  << "\t" << *(meaning_second_row+1 ) << std::endl;
           // std::cout << ((*meaning_first_row) * *(meaning_second_row + 1)) << "\t" << ((*(meaning_first_row + 1)) * (*meaning_second_row)) << " R" << std::endl;
            //std::cout << "result square matrix: " << result << std::endl;
        }

        else {
            for (int i = 0;  i < (quant_rows); ++i, k *= -1)
            {
                temp = 0;
                int first_row = 0;
                std::vector<std::vector<int>> temp_matrix = matrix;
                temp += (k * (*(columns + i)));
                std::cout << "a" << i << "= " << temp << std::endl;
                delete_row(temp_matrix, first_row);
                delete_column(temp_matrix, i);
                //delete_row(temp_matrix, i);
                temp *= calculate_determinant(temp_matrix);
               // std::cout << "temp= " << temp << std::endl;
                result += temp;
               // std::cout << result << std::endl;
            }

        }
        return result;
    }

    else 
    {
        std::cout << "Matrix is not square matrix" << std::endl;
    }
};

int matrix::get_determinant() 
{
    return determinant;
}

void matrix::print() 
{
    for (std::vector<std::vector<int>>::iterator row=Matrix.begin(); row!=Matrix.end(); ++row)
    {
        std::cout << "\t";
        for (std::vector<int > ::iterator column = (*row).begin(); column != (*row).end(); ++column)
        {
            std::cout << *(column) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

void matrix::print_determinant()
{
    std::cout << "\t" << "Determinant: " << determinant << std::endl;
}
//*/

//============================================
// Task№3
//============================================
/*3. Реализовать собственный класс итератора, с помощью которого можно будет
проитерироваться по диапазону целых чисел в цикле for-range-based.*/





int main()
{

//============================================
// Task№1
//============================================

    std::list<double> list{ 5.5, 10.1, 3.14 };
    insert_arithmetic_mean(list);
    print_list(list);



//============================================
// Task№2
//============================================
    std::vector<std::vector<int>> mtrx={ {1, -2, 3}, {0, 7, 4}, {5,3,-3} };
    
    matrix matrix(mtrx);
    matrix.print();
    matrix.print_determinant();


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
 
}