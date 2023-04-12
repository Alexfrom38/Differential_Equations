#include<iostream>
#include <fstream>
#include<cmath>
void Insert_In_File(double* new_array, size_t count, std::fstream& stream)
{
	if (stream.is_open())
	{
		for (size_t i = 0; i < count; i++)    
			stream << new_array[i] << " ";
		stream << "\n";
		//stream << "\n";
	}
	else
		throw "The file isn't exist";
}


double Get_New_Point_In_Time(double prev_point, double curr_point, double next_point, double deltaT, double deltaX, double sigma )
{
	double tmp = 0.0;
  tmp = prev_point - 2*curr_point + next_point;
	
	return((sigma * deltaT) / (deltaX * deltaX) * tmp + curr_point);
}
int main()
{
	double X_max = 0.0;
	double deltaX = 0.0;
	double T_max = 0.0;
	double deltaT = 0.0;
	double sigma = 0.0;
	size_t count = 0;
	double time = 0.0;
	const double PI = 3.141592653589793;
	int i = 1;

	std::fstream f;
	f.open("initial.txt", std::fstream::in | std::fstream::out);

	std::ifstream f_in;       
	f_in.open("const_initial.txt");
	if (f_in.is_open())
	{
		f_in >> X_max;
		f_in >> deltaX;
		f_in >> T_max;
		f_in >> deltaT;
		f_in >> sigma;
	}
	else
		throw "file wasn't opened";
	f_in.close();

	if (X_max == 0.0 || deltaX == 0.0)
		throw "count = 0 or count is infinity";

	double* initial = nullptr;
	count = static_cast<size_t>((int)(X_max / deltaX)) + 1;
	initial = new double[count];
	
	double* main_array = nullptr;
	main_array = new double[count];
	
	for (size_t q = 0; q < count; q++)
		initial[q] = sin(PI*deltaX*q);
	
	initial[count - 1] = 0.0;
	

	Insert_In_File(initial, count,f);

	while (time < T_max)
	{
		time = deltaT * i;
		for (size_t q = 1; q < count; q++)
		{
			if (q == 0)
				main_array[q] = Get_New_Point_In_Time(0, initial[q], initial[q + 1], deltaT, deltaX, sigma);
			if (q > 0 && q < 100)
				main_array[q] = Get_New_Point_In_Time(initial[q - 1], initial[q], initial[q + 1], deltaT, deltaX, sigma);
			if(q == 100)
				main_array[q] = Get_New_Point_In_Time(initial[q - 1], initial[q], 0, deltaT, deltaX, sigma);
		}
		main_array[0] = 0.0;
		main_array[100] = 0.0;
		for (size_t q = 0; q < count; q++)
			initial[q] = main_array[q];
	
		
		if (i % 10000 == 0)
			Insert_In_File(main_array, count, f);
		i++;
	}

	Insert_In_File(main_array, count, f);
	f.close();
	delete[] initial;
	return 0;
}
