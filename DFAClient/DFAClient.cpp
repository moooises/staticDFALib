// DFAClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DFALib.h"
#include <fstream>
#include <string>

//#include <cmath>
#include <matplot/matplot.h>
//#include <sqlite3.h>



int main()
{

    std::vector<double> data;
    std::fstream newfile;
    newfile.open("C:/Users/mo_oi/source/repos/staticDFALib/DFAClient/Multifractal.txt");
    if (newfile.is_open())
    {
        std::string tp;
        while (std::getline(newfile, tp, ','))
        {
            data.push_back(std::stold(tp)); // convert string to long double https://stackoverflow.com/questions/4754011/c-string-to-double-conversion
        }
    }
    newfile.close();
    std::vector<int> scales = { 16, 32, 64, 128, 256, 512, 1024 };


    std::vector<double> data_test;
    std::vector<double> data_test_flip;

    std::vector<double> R = DFALib::XDFA::Convert_to_Random_Walk(data);
    copy(R.begin(), R.begin() + 100, std::back_inserter(data_test));

    std::vector<double> R_flip = R;
    std::reverse(R_flip.begin(), R_flip.end());
    copy(R_flip.begin(), R_flip.begin() + 100, std::back_inserter(data_test_flip));


    std::cout << "Normal" << std::endl;
    std::for_each(data_test.begin(), data_test.end(), [](double n) {std::cout << n << " "; });
    std::cout << std::endl;
    std::cout << "Flip" << std::endl;
    std::for_each(data_test_flip.begin(), data_test_flip.end(), [](double n) {std::cout << n << " "; });
    std::cout << std::endl;

    struct DFALib::DFA_values dfa = DFALib::XDFA::DFA(data, 1, scales);


    //
    // Polinomial regression
    /*
    std::vector<double> X = { 0.0,1.0,2.0,3.0,4.0,5.0 };
    std::vector<double> Y = { 0.0,0.8,0.9,0.1,-0.8,-1.0 };
    std::vector<double> Z = { 5,6,7,8,9,10 };
    int degree = 2;
    std::vector<double> coeficients = DFALib::XDFA::polynomial_fit(X, Y, degree);
    for (int i = 0; i <= degree; i++)
    {
        std::cout << coeficients[i] << " ";
    }
    std::cout << std::endl;

    std::vector<double> values = DFALib::XDFA::polynomial_val(coeficients, Z);
    for (int i = 0; i < values.size(); i++)
    {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;

    degree = 3;
    coeficients = DFALib::XDFA::polynomial_fit(X, Y, degree);
    for (int i = 0; i <= degree; i++)
    {
        std::cout << coeficients[i] << " ";
    }
    std::cout << std::endl;

    values = DFALib::XDFA::polynomial_val(coeficients, Z);
    for (int i = 0; i < values.size(); i++)
    {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;

    std::cout<<"End Test" << std::endl;
    */

    //std::cout.precision(15);

    //std::vector<double> X = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //std::vector<double> X ={ 22,24,87,89,45,213,8798,2321,564231,654217,5643213,3132,9784 };

    // Random Walk Test
    //double m = DFALib::XDFA::Arithmetic_Mean(X);
    //std::cout <<"Media: " << m << std::endl;
    //std::vector<double> R = DFALib::XDFA::Convert_to_Random_Walk(X);
    //std::for_each(R.begin(), R.end(), [](double n) {std::cout << n << " "; });
    //std::cout<<std::endl;
    //std::vector<int> Y = { 22,24,87,89,45,213,8798,2321,564231,654217,5643213,3132,9784 };
    //// Random Walk Test
    //m = DFALib::XDFA::Arithmetic_Mean(Y);
    //std::cout << "Media: " << m << std::endl;
    //R = DFALib::XDFA::Convert_to_Random_Walk(Y);
    //std::for_each(R.begin(), R.end(), [](double n) {std::cout << n << " "; });
    //std::cout << std::endl;

    //std::vector<double> L = DFALib::XDFA::linspace(0, 10, 20);
    //std::for_each(L.begin(), L.end(), [](double n) {std::cout << n << " "; });
    //std::cout << std::endl;


    matplot::plot(dfa.S_log, dfa.F_log, "o");
    matplot::hold(matplot::on);
    matplot::plot(dfa.S_log, dfa.Reg_Line, "-");
    matplot::show();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
