#include "pch.h"
#include "CppUnitTest.h"
#include "../DFALib/DFALib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DFATestUnit
{
	TEST_CLASS(DFATestUnit)
	{
	public:
		
		TEST_METHOD(Arithmetic_Mean)
		{
			std::vector<double> v = {};
			double m = DFALib::XDFA::Arithmetic_Mean(v);
			Assert::AreEqual(m, (double)0);

			v = { 1,2,3,4,5,6,7,8,9,10 };
			m = DFALib::XDFA::Arithmetic_Mean(v);
			Assert::AreEqual(m, 5.5);

			std::vector<int> w = { 1,2,3,4,5,6,7,8,9,10 };
			m = DFALib::XDFA::Arithmetic_Mean(v);
			Assert::AreEqual(m, 5.5);

			std::vector<float> x = { 1,2,3,4,5,6,7,8,9,10 };
			m = DFALib::XDFA::Arithmetic_Mean(x);
			Assert::AreEqual(m, 5.5);
			/*v = { 22,24,87,89,45,213,8798,2321,564231,654217,5643213,3132,9784 };
			m = DFALib::DFA::Arithmetic_Mean(v);
			Assert::AreEqual(m, 529705.84615384613);*/


		}

		TEST_METHOD(Convert_to_Random_Walk)
		{
			std::vector<double> v = {};
			std::vector<double> r = DFALib::XDFA::Convert_to_Random_Walk(v);
			Assert::IsTrue(v == r);

			v = { 1,2,3,4,5,6,7,8,9,10};
			r = DFALib::XDFA::Convert_to_Random_Walk(v);
			std::vector<double> result_double = { -4.5, -8., -10.5, -12., -12.5, -12., -10.5, -8., -4.5, 0. };
			Assert::IsTrue(result_double==r);

			std::vector<int> w = { 1,2,3,4,5};
			r = DFALib::XDFA::Convert_to_Random_Walk(w);
			std::vector<double> result_int = {-2, -3, -3, -2, 0 };
			Assert::IsTrue(result_int == r);

			std::vector<float> x = { 1,2,3,4,5,6,7,8,9,10 };
			r = DFALib::XDFA::Convert_to_Random_Walk(x);
			Assert::IsTrue(result_double == r);


			//v = { 22,24,87,89,45,213,8798,2321,564231,654217,5643213,3132,9784 };
			//result = { -5.29683846e+05, -1.05936569e+06, -1.58898454e+06, -2.11860138e+06, 
			//	-2.64826223e+06, -3.17775508e+06, -3.69866292e+06, -4.22604777e+06,
			//	-4.19152262e+06, -4.06701146e+06,  1.04649569e+06,  5.19921846e+05,
			//	6.98491931e-10 };
			//r = DFALib::DFA::Convert_to_Random_Walk(v);
			//Assert::IsTrue(result == r);


		}

		TEST_METHOD(polynomial_fit)
		{
			std::vector<double> X = { 0.0,1.0,2.0,3.0,4.0,5.0 };
			std::vector<double> Y = { 0.0,1.0,2.0,3.0,4.0,5.0 };
			std::vector<double> result = {1.0,0.0};
			int degree = 1;
			std::vector<double> coeficients = DFALib::XDFA::polynomial_fit(X, Y, degree);

			Assert::IsTrue(coeficients == result);

		}

		TEST_METHOD(polynomial_val)
		{
			std::vector<double> X = { 0.0,1.0,2.0,3.0,4.0,5.0 };
			std::vector<double> Y = { 0.0,1.0,2.0,3.0,4.0,5.0 };
			std::vector<double> Z = { 5.0,6.0,7.0,8.0,9.0,10.0 };
			std::vector<double> result = { 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
			int degree = 1;
			std::vector<double> coeficients = DFALib::XDFA::polynomial_fit(X, Y, degree);
			std::vector<double> values = DFALib::XDFA::polynomial_val(coeficients, Z);
			Assert::IsTrue(values == result);



		}

	};
}
