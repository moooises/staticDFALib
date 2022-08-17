// DFAClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DFALib.h"
#include <fstream>
#include <string>
#include <chrono>

//#include <cmath>
#include <matplot/matplot.h>
//#include <sqlite3.h>



int main()
{

    //// DFA test /////////////

    std::vector<double> data;
    std::fstream newfile;
    //std::string file = "C:/Users/mo_oi/source/repos/staticDFALib/DFAClient/Multifractal.txt";
    //std::string file = "C:/Users/mo_oi/source/repos/staticDFALib/DFAClient/O3_2017.dat";
    //std::string file = "C:/Users/mo_oi/source/repos/staticDFALib/DFAClient/O3_2018_reminder.dat";
    std::string file = "C:/Users/mo_oi/source/repos/staticDFALib/DFAClient/O3_2019.dat";


    //newfile.open();

    if (newfile.is_open())
    {
        std::string tp;
        while (std::getline(newfile, tp, ','))
        {
            data.push_back(std::stold(tp)); // convert string to long double https://stackoverflow.com/questions/4754011/c-string-to-double-conversion
        }
    }
    newfile.close();

    std::cout << data.size() << std::endl;
    if (data.size() == 1 || data.size() == 0)
    {
        data.clear();
        newfile.open(file);
        if (newfile.is_open())
        {
            std::string tp;
            while (std::getline(newfile, tp))
            {
                data.push_back(std::stold(tp));
            }
        }
        newfile.close();
    }

    auto start1 = std::chrono::high_resolution_clock::now();

    double result1 = DFALib::XDFA::Arithmetic_Mean(data);
    auto end1 = std::chrono::high_resolution_clock::now();

    std::cout << "Resultado sin paralelismo: " << result1 << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    double result2 = DFALib::XDFA::Arithmetic_Mean(data, 1);

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Resultado con paralelismo: " << result2 << std::endl;

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << std::endl;


    //std::cout << "Data" << std::endl;
    //std::for_each(data.begin(), data.end(), [](double n) {std::cout << n << " "; });

    ////std::vector<int> scales = { 16, 32, 64, 128, 256, 512, 1024 };
    ////std::vector<int> scales = { 10, 11, 12, 14, 15, 17, 19, 22, 24, 27, 31, 34, 38, 43, 48, 54, 61, 68, 76, 86, 96, 107, 120, 135, 151, 169, 190, 213, 238, 267, 299, 335, 375, 420, 470, 527, 590, 661, 740, 829, 929, 1040, 1165, 1305, 1462, 1637, 1834, 2054, 2300, 2576, 2885, 3231, 3619, 4053, 4540, 5084, 5694, 6377, 7143, 7999 };
    ////std::vector<int> scales = { 10, 11, 12, 13, 15, 17, 19, 21, 24, 27, 30, 33, 37, 42, 47, 52, 59, 66, 73, 82, 92, 103, 115, 128, 144, 161, 180, 201, 224, 251, 280, 313, 350, 391, 438, 489, 547, 611, 683, 763, 853, 953, 1066, 1191, 1331, 1488, 1663, 1858, 2077, 2321, 2594, 2899, 3240, 3621, 4047, 4523, 5054, 5649, 6313, 7055 };
    ////std::vector<int> scales = { 10, 11, 12, 13, 15, 17, 19, 21, 24, 27, 30, 33, 37, 42, 47, 52, 59, 66, 73, 82, 92, 103, 115, 128, 144, 161, 180, 201, 224, 251, 280, 313, 350, 391, 438, 489, 547, 611, 683, 763, 853, 953, 1066, 1191, 1331, 1488, 1663, 1858, 2077, 2321, 2594, 2899, 3240, 3621, 4047, 4523, 5054, 5649, 6313, 7055 };
    //std::vector<int> scales = { 10, 11, 12, 13, 15, 17, 19, 21, 24, 27, 30, 33, 37, 42, 47, 52, 59, 66, 73, 82, 92, 103, 115, 128, 144, 161, 180, 201, 224, 251, 280, 313, 350, 391, 438, 489, 547, 611, 683, 763, 853, 953, 1066, 1191, 1331, 1488, 1663, 1858, 2077, 2321, 2594, 2899, 3240, 3621, 4047, 4523, 5054, 5649, 6313, 7055 };

    //std::vector<double> data_test;
    //std::vector<double> data_test_flip;

    //std::vector<double> R = DFALib::XDFA::Convert_to_Random_Walk(data);
    //copy(R.begin(), R.begin() + 100, std::back_inserter(data_test));

    //std::vector<double> R_flip = R;
    //std::reverse(R_flip.begin(), R_flip.end());
    //copy(R_flip.begin(), R_flip.begin() + 100, std::back_inserter(data_test_flip));


    //// Test DFA

    //std::cout << "Normal" << std::endl;
    //std::for_each(data_test.begin(), data_test.end(), [](double n) {std::cout << n << " "; });
    //std::cout << std::endl;
    //std::cout << "Flip" << std::endl;
    //std::for_each(data_test_flip.begin(), data_test_flip.end(), [](double n) {std::cout << n << " "; });
    //std::cout << std::endl;

    //struct DFALib::DFA_values dfa = DFALib::XDFA::DFA(data, 1,scales);


    //matplot::plot(dfa.S_log, dfa.F_log, "o");
    //matplot::hold(matplot::on);
    //matplot::plot(dfa.S_log, dfa.Reg_Line, "--");
    //matplot::show();
    
    ///////////////////////////////
    //  
     //Test logspace

    //std::vector<double> logspaced = DFALib::XDFA::logspace(16, 8000, 60);

    //std::cout << "Scales" << std::endl;
    //std::for_each(logspaced.begin(), logspaced.end(), [](double x) {std::cout << " " << x << std::endl; });
    ////std::for_each(logspaced.begin(), logspaced.end(), [](int& x) {x = static_cast<int>(pow(10, x)); }); // pow returns always double
    //std::cout << "Scales end" << std::endl;


    /////////////
    // Test logspace v4
    //double start_in=1;
    //double end_in =log(8000)/log(10);
    //int num_in=60;
    //const auto exp_scale = (end_in - start_in) / (num_in - 1);
    //std::cout << exp_scale << std::endl;
    //std::vector<int> logspaced(num_in, 0.0);
    //std::generate(logspaced.begin(), logspaced.end(), [n = -1, exp_scale]() mutable {n++; return floor(10*pow(10, n * exp_scale)); });

    //for (double x : logspaced) { std::cout << x << " "; }



    
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
