#include "DFALib.h"

namespace DFALib
{
	template <typename T>
	double XDFA::Arithmetic_Mean(const std::vector<T>& data)
	{
		//std::cout << "Arithmetic_Mean" << std::endl;

		if (data.empty())
		{
			try
			{
				throw  std::invalid_argument("Vector is empty");
			}
			catch (const std::invalid_argument e)
			{
				std::cerr << e.what() << std::endl;
				return 0.0;
			}
		}

		double acc = 0.0;

		for (const T& n : data)
		{
			acc += static_cast<double>(n);
		}


		return acc / static_cast<double>(data.size());
	}

	template double XDFA::Arithmetic_Mean(const std::vector<int>&);
	template double XDFA::Arithmetic_Mean(const std::vector<double>&);
	template double XDFA::Arithmetic_Mean(const std::vector<float>&);

	template<typename T>
	std::vector<double> XDFA::Convert_to_Random_Walk(const std::vector<T>& data)
	{
		//std::cout << "Arithmetic_Mean" << std::endl;

		if (data.empty())
		{
			try
			{
				throw  std::invalid_argument("Vector is empty");
			}
			catch (const std::invalid_argument e)
			{
				std::cerr << e.what() << std::endl;
				std::vector<double> w = {};
				return w;
			}
		}

		double mean = XDFA::Arithmetic_Mean(data);

		std::vector<double> Random_Walk;
		Random_Walk.push_back(static_cast<double>(data.front()) - mean);
		double back;
		std::for_each(++data.begin(), data.end(), [&Random_Walk, &mean, &back](double n) {
			back = Random_Walk.back();
			Random_Walk.push_back(back + n - mean);
			});

		return Random_Walk;
	}

	template std::vector<double> XDFA::Convert_to_Random_Walk(const std::vector<double>&);
	template std::vector<double> XDFA::Convert_to_Random_Walk(const std::vector<int>&);
	template std::vector<double> XDFA::Convert_to_Random_Walk(const std::vector<float>&);

	template <typename T>
	std::vector<double> XDFA::linspace(const T start_in, const T end_in, const int num_in)
	{
		std::vector<double> linspaced;

		double start = static_cast<double>(start_in);
		double end = static_cast<double>(end_in);
		double num = static_cast<double>(num_in);

		if (num == 0.0) { return linspaced; }
		if (num == 1.0)
		{
			linspaced.push_back(start);
			return linspaced;
		}

		double delta = (end - start) / (num - 1);

		for (int i = 0; i < num - 1; ++i)
		{
			linspaced.push_back(start + delta * i);
		}
		linspaced.push_back(end);

		return linspaced;

	}

	std::vector<int> XDFA::logspace(const int start_in, const int end_in, const int num_in)
	{
		//const double exp_scale = (end_in - start_in) / (num_in - 1);
		//std::vector<int> logspaced;
		//logspaced.reserve(num_in);
		//for (int i = 0; i < num_in; i++)
		//{
		//	logspaced.push_back(static_cast<int>(i * exp_scale)); // this used to be floor(), but floor return double ¿?¿?¿?¿
		//}

		//std::for_each(logspaced.begin(), logspaced.end(), [](int& x) {x = static_cast<int>(pow(10, x)); }); // pow returns always double

		//return logspaced;

		double diff = static_cast<double>(end_in) - static_cast<double>(start_in);
		//std::cout << "Diff: " << diff << std::endl;
		double ratio = pow(static_cast<double>(end_in), (1.0 / (static_cast<double>(num_in) - 1.0)));
		//std::cout << "Ratio: " << ratio << std::endl;
		std::vector<double> _logspaced;
		std::vector<int> logspaced;
		for (int i = 0; i < num_in; ++i) { _logspaced.push_back(pow(ratio, i)); }
		//std::cout << "_logspaced" << std::endl;
		//std::for_each(_logspaced.begin(), _logspaced.end(), [](double x) {std::cout<< x <<" "; });
		//std::cout << std::endl<< "_logspaced end" << std::endl;

		for (int i = 0; i < num_in; ++i) { logspaced.push_back(floor(start_in+_logspaced[i]*diff/end_in)); }

		return logspaced;

	}


	template std::vector<double> XDFA::linspace(const int, const int, const int);
	template std::vector<double> XDFA::linspace(const double, const double, const int);
	template std::vector<double> XDFA::linspace(const float, const float, const int);


	std::vector<double> XDFA::gaussEliminationLS(const int n, double** M)
	{
		std::vector<double> a;// Vector of coeficients

		for (int i = 0; i <= n; i++)
		{
			double ratio = M[i][i];

			for (int j = 0; j <= n + 1; j++)
			{
				M[i][j] = M[i][j] / ratio;
			}

			for (int j = 0; j <= n; j++)
			{
				if (j != i)
				{
					ratio = M[j][i];

					for (int k = 0; k <= n + 1; k++)
					{
						M[j][k] -= ratio * M[i][k];
					}
				}
			}

		}

		for (int i = 0; i <= n; i++)
		{
			a.insert(a.begin(), M[i][n + 1]);

		}
		return a;
	}

	std::vector<double>  XDFA::polynomial_fit(const std::vector<double> x, const std::vector<double> y, const int n = 1)
	{

		if (x.size() != y.size())
		{
			try
			{
				throw  std::invalid_argument("Vector X and Y must have the same size for the polynomial fit.");
			}
			catch (const std::invalid_argument e)
			{
				std::cerr << e.what() << std::endl;
				std::vector<double> w = {};
				return w;
			}
		}

		if (n < 1)
		{
			try
			{
				throw std::invalid_argument("Degree value must be higher than 0.");
			}
			catch (const std::invalid_argument e)
			{
				std::cerr << e.what() << std::endl;
				std::vector<double> w = {};
				return w;
			}
		}

		int N = x.size();

		double** M = new double* [n + 1];

		// First row
		M[0] = new double[n + 2];
		M[0][0] = N;
		for (int j = 1; j < n + 1; j++)
		{
			double sum = 0;

			for (int k = 0; k < N; k++)
			{
				sum = sum + pow(x[k], j);
			}

			M[0][j] = sum;
		}

		// The rest rows

		for (int i = 1; i < n + 1; i++)
		{
			M[i] = new double[n + 2];
			for (int j = 0; j < n + 1; j++)
			{
				double sum = 0;
				for (int k = 0; k < N; k++)
				{
					sum = sum + pow(x[k], j + i);
				}
				M[i][j] = sum;
			}
		}

		for (int i = 0; i < n + 1; i++)
		{
			double sum = 0;
			for (int k = 0; k < N; k++)
			{
				sum = sum + (pow(x[k], i) * y[k]);
			}

			M[i][n + 1] = sum;
		}

		std::vector<double> A = gaussEliminationLS(n, M);

		return A;
	}

	std::vector<double> XDFA::polynomial_val(const std::vector<double> coeficients, const std::vector<double> X)
	{
		int n = coeficients.size();

		std::vector<double> values;

		double polynomial;

		for (int i = 0; i < X.size(); i++)
		{

			polynomial = 0;

			for (int j = coeficients.size() - 1; j >= 0; j--)
			{
				polynomial += coeficients[j] * pow(X[i], (coeficients.size() - 1) - j);
			}

			values.push_back(polynomial);
		}

		return values;
	}

	template<typename T>
	struct DFA_values XDFA::DFA(const std::vector<T>& data, const int degree, const std::vector<int>& scale_values, const int n_scales)
	{
		struct DFA_values values;
		std::vector<int> scales;
		if (scale_values.empty())
		{
			if (n_scales < 7)
			{
				try
				{
					throw  std::invalid_argument("Number of scales are two low. Must be at least 7");
				}
				catch (const std::invalid_argument e)
				{
					std::cerr << e.what() << std::endl;
					//std::vector<double> w = {};
					return  values;
				}
			}
			else
			{

				//scale=np.floor(np.logspace(int(scale_min),(np.log(int(scale_max))/np.log(10)),int(scale_res)))       

				scales = XDFA::logspace(16, log(8000)/log(10), n_scales);



			}
		}
		else
		{
			scales = scale_values;
		}

		if (degree <= 0)
		{
			try
			{
				throw  std::invalid_argument("Degree value must higher than 0.");
			}
			catch (const std::invalid_argument e)
			{
				std::cerr << e.what() << std::endl;
				//std::vector<double> w = {};
				return  values;
			}
		}

		std::vector<double> data_random_walk = XDFA::Convert_to_Random_Walk(data);
		std::vector<double> flip_data_random_walk = data_random_walk;
		std::reverse(flip_data_random_walk.begin(), flip_data_random_walk.end());
		std::cout << std::endl;

		int segments; // Number of segments of scale i
		double** F = new double* [scales.size()];
		double** F_Flip = new double* [scales.size()];

		//int** Index = new int* [scales.size()];// He traspuesto la matriz de indices respecto a paper Index{v, ns} -> Index{ns, v}
		std::vector<double> Index;
		std::vector<double> Index_Flip;
		std::vector<double> Index_X;
		int Idx_start;
		int Idx_stop;

		std::vector<double> F_;
		std::vector<double> F_aux;

		//matrix array is better

		for (int ns = 0; ns < scales.size(); ++ns)
		{
			segments = static_cast<int>(floor((data_random_walk.size()) / scales[ns])); // No se si floor es necesario

			F[ns] = new double[segments];
			F_Flip[ns] = new double[segments];

			std::vector<double> C;
			std::vector<double> Fit;
			std::vector<double> C_Flip;
			std::vector<double> Fit_Flip;

			//Index[ns] = new int[v];

			// Async ¿?¿?¿
			// Things I need:
			//		¿Store the Index?, it may be necessary in the future, but I don't think so.
			//		Store the polyval of each index 
			//		Store the RMS of each index 
			//		And at the end the F, overall RMS
			// Look the python code
			for (int v = 0; v < segments; v++)
			{
				Idx_start = v * scales[ns];
				Idx_stop = v * scales[ns] + scales[ns];

				for (double i = Idx_start; i < Idx_stop; ++i) { Index_X.push_back(i); }

				std::copy_n(&data_random_walk[Idx_start], scales[ns], std::back_inserter(Index));

				std::copy_n(&flip_data_random_walk[Idx_start], scales[ns], std::back_inserter(Index_Flip));

				C = XDFA::polynomial_fit(Index_X, Index, degree);
				Fit = XDFA::polynomial_val(C, Index_X);

				C_Flip = XDFA::polynomial_fit(Index_X, Index_Flip, degree);
				Fit_Flip = XDFA::polynomial_val(C_Flip, Index_X);

				for (int i = 0; i < scales[ns]; ++i) { F_aux.push_back(pow(Index[i] - Fit[i], 2)); }
				F[ns][v] = XDFA::Arithmetic_Mean(F_aux);
				F_aux.clear();

				for (int i = 0; i < scales[ns]; ++i) { F_aux.push_back(pow(Index_Flip[i] - Fit_Flip[i], 2)); }
				F_Flip[ns][v] = XDFA::Arithmetic_Mean(F_aux);
				F_aux.clear();

				Index.clear();
				Index_Flip.clear();
				Index_X.clear();
				C.clear();
				Fit.clear();
				C_Flip.clear();
				Fit_Flip.clear();
			}

			for (int v = 0; v < segments; v++)
			{

				F_aux.push_back(F[ns][v] + F_Flip[ns][v]);
			}
			F_.push_back(sqrt(XDFA::Arithmetic_Mean(F_aux)));
			F_aux.clear();
		}


		//std::vector<double> s_log;
		for (double n : scales) { values.S_log.push_back(log(n)); }
		//std::vector<double> F_log;
		for (double n : F_) { values.F_log.push_back(log(n)); }

		std::cout << std::endl;
		std::cout << " F_log result" << std::endl;
		std::for_each(values.F_log.begin(), values.F_log.end(), [](double& x) {std::cout << x << " " << std::endl; });
		std::cout << std::endl;
		system("pause");

		std::vector<double> Ch = XDFA::polynomial_fit(values.S_log, values.F_log, degree);
		values.H = Ch[0];
		values.Reg_Line = XDFA::polynomial_val(Ch, values.S_log);

		return values;
	}

	template struct DFA_values XDFA::DFA(const std::vector<int>&, const int, const std::vector<int>&, const int);
	template struct DFA_values XDFA::DFA(const std::vector<double>&, const int, const std::vector<int>&, const int);
	template struct DFA_values XDFA::DFA(const std::vector<float>&, const int, const std::vector<int>&, const int);


}