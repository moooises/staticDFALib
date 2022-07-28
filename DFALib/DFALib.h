#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>
namespace DFALib
{

	struct DFA_values
	{
		std::vector<double> Reg_Line = {};
		std::vector<double> F_log = {};
		std::vector<double> S_log = {};
		double H = 0.0;
	};

	class XDFA
	{
	public:

		// Return arithmetic mean of given data
		template <typename T>
		static double Arithmetic_Mean(const std::vector<T>& data);

		// Convert the time series to random walk like time series
		template <typename T>
		static std::vector<double> Convert_to_Random_Walk(const std::vector<T>& data);

		template <typename T>
		static std::vector<double> linspace(const T start_in, const T end_in, const int num_in);

		// https://stackoverflow.com/questions/57944012/how-to-write-a-fast-code-in-c-compared-to-numpy-logspace-function
		static std::vector<int> logspace(const int start_in, const int end_in, const int num_in);

		// Used in polynomial_fit
		// https://calculator-online.net/gaussian-elimination-calculator/
		static std::vector<double> gaussEliminationLS(const int n, double** M);

		// https://www.bragitoff.com/2018/06/polynomial-fitting-c-program/
		// Return the coefs a_n,...a_0
		static std::vector<double> polynomial_fit(const std::vector<double> X, const std::vector<double> Y, const int degree);

		// Apply the Coefs to a vector of values.
		static std::vector<double> polynomial_val(const std::vector<double> coeficients, const std::vector<double> X);

		template <typename T>
		static struct DFA_values DFA(const std::vector<T>& data, const int degree = 1, const std::vector<int>& scale_values = {}, const  int n_scales = 60);




	};
}