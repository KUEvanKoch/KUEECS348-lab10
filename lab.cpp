//Program: EECS 348 Lab 10
//Description: C++ program that takes in an input file from the user and gets 2 matrices, and performs various operations on them with a Matrix class
//Inputs: Input file provided via terminal
//Outpts: Terminal output between the user and the program displaying matrices
//Collaborators: Me
//Name: Evan Koch
//Creation Date: 11/5/26
#include <iostream> //Include the iostream library
#include <fstream> //Include the fstream library
#include <iomanip> //Include the iomanip library
#include <string> //Include the string library

using namespace std; //Allows accessing libraries without the std:: prefix

class Matrix //Defines the Matrix class
{
	private:
		int N; //Integer N that defines the size of the matrix
		int** data; //2D integer array that contains the matrix data
	public:
		Matrix() //Default constructor
		{
			N = 0; //Sets N to 0
			data = nullptr; //Sets data to empty
		}

		Matrix(int size) //Constructor that takes in an integer size and makes a matrix of that size
		{
			N = size; //Sets N to size
			data = new int*[N]; //Sets data to an array of size N

			//Loops N times, filling the data array with arrays of size N
			for (int i = 0; i < N; i++)
			{
				data[i] = new int[N];
			}
		}

		Matrix(const Matrix& matrix) //Constructor that takes in a matrix, creating a copy of it
		{
			N = matrix.N; //Sets N to the N of the matrix
			data = new int*[N]; //Sets data to an array of size N

			//Loops through all of the data of matrix and sets the data of the new matrix equal to its data
			for (int i = 0; i < N; i++)
			{
				data[i] = new int[N];
				for (int j = 0; j < N; j++)
				{
					data[i][j] = matrix.data[i][j];
				}
			}
		}

		~Matrix() //Deconstructor
		{
			//Loops through N times and deletes all of the arrays in data from memory
			for (int i = 0; i < N; i++)
			{
				delete[] data[i];
			}

			//Deletes the main array of data from memory
			delete[] data;
		}

		Matrix& operator=(const Matrix& other) //Overloaded = operator creating a copy of a matrix when used
		{
			if (this != &other) //Checks if the matrix is being set to itself
			{
				//Clears the data of this matrix
				for (int i = 0; i < N; i++)
				{
					delete[] data[i];
				}
				delete[] data;

				N = other.N; //Sets N to the N of the other matrix
				data = new int*[N]; //Sets data to an array of size N

				//Loops through N times and fills the array of data with arrays of size N, filling them with the data of the other matrix
				for (int i = 0; i < N; i++)
				{
					data[i] = new int[N];

					for (int j = 0; j < N; j++)
					{
						data[i][j] = other.data[i][j];
					}
				}
			}

			return *this; //Return the new matrix
		}

		bool readFromFile(ifstream& fin) //Function that reads a matrix from a file, taking in a file and returning a boolean if the reading waas successful
		{
			//Loops through the size of the matrix and sets the data positions to the read data from the file, returning false if there is an error
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (!(fin >> data[i][j]))
					{
						return false;
					}
				}
			}
			return true; //Returns true with the matrix successfully read
		}

		void display() const //Function that displays the matrix
		{
			//Loops through the matrix data and outputs it with formatting to align the columns and rows
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					cout << setw(5) << data[i][j];
				}
				cout << endl;
			}
		}

		Matrix operator+(const Matrix& other) const //Overloaded + operator that adds two matrices together
		{
			Matrix result(N); //Creates a result matrix of size N

			//Loops through the data of the two matrices and adds them together
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					result.data[i][j] = data[i][j] + other.data[i][j];
				}
			}
			return result; //Returns the result matrix
		}

		Matrix operator*(const Matrix& other) const //Overloaded * operator that multiplies two matrices
		{
			Matrix result(N); //Creates a result matrix of size N

			//Loops through the data of the two matrices and multiplies them together using matrix multiplication
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					result.data[i][j] = 0;

					for (int k = 0; k < N; k++)
					{
						result.data[i][j] += data[i][k] * other.data[k][j];
					}
				}
			}
			return result; //Returns the result matrix
		}

		int mainDiagonalSum() const //Function that calculates the main diagonal sum (top left to bottom right) and returns it as an integer
		{
			int sum = 0; //Create an integer for the sum set to 0
			//Loops through the size of the matrix, adding the value along the main diagonal to the sum
			for (int i = 0; i < N; i++)
			{
				sum += data[i][i];
			}
			return sum; //Returns the sum
		}

		int secondaryDiagonalSum() const //Function that calculates the secondary diagonal sum (top right to bottom left) and returns it as an integer
		{
			int sum = 0; //Create an integer for the sum set to 0
			//Loops through the size of the matrix, adding the values of the secondary diagonal to the sum
			for (int i = 0; i < N; i++)
			{
				sum += data[i][N-1-i];
			}
			return sum; //Returns the sum
		}

		void swapRows(int row1 = 0, int row2 = 1) //Function that swaps two rows at provided indices
		{
			if (row1 >= 0 && row1 < N && row2 >= 0 && row2 < N) //Checks to make sure the indices are valid
			{
				//Loops through the data of the rows and swaps them
				for (int i = 0; i < N; i++)
				{
					swap(data[row1][i], data[row2][i]);
				}
			}
			else
			{
				cout << "Error: Invalid row indices" << endl; //Outputs that the row indices are invalid
			}
		}

		void swapColumns(int col1 = 0, int col2 = 1) //Function that swaps two columns at provided indices 
		{
			if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) //Checks to make sure the indices are valid
			{
				//Loops through the data of the columns and swaps them
				for (int i = 0; i < N; i++)
				{
					swap(data[i][col1], data[i][col2]);
				}
			}
			else
			{
				cout << "Error: Invalid column indices" << endl; //Outputs that the column indices are invalid
			}
		}

		void updateElement(int row = 0, int col = 0, int value = 100) //Function that takes in a row index, a column index, and a value, and sets the value of that row and column to the new value
		{
			if (row >= 0 && row < N && col >= 0 && col < N) //Checks to make sure the indices are valid
			{
				data[row][col] = value; //Sets the value at the given row and column to the new value
			}
			else
			{
				cout << "Error: Invalid row or column indicies" << endl; //Outputs that the indices are invalid
			}
		}
};

int main() //Defines the main function
{
	string filename;

	cout << "Enter input filename: ";
	cin >> filename;

	ifstream fin(filename);

	if (!fin)
	{
		cout << "Error: Could not open file" << endl;
		return 1;
	}

	int N;
	fin >> N;

	Matrix A(N);
	Matrix B(N);

	if (!A.readFromFile(fin) || !B.readFromFile(fin))
	{
		cout << "Error: Could not read matrix data" << endl;
		return 1;
	}

	fin.close();

	cout << "\nMatrix A:\n";
	A.display();

	cout << "\n\nMatrix B:\n";
	B.display();

	cout << "\n\nA + B\n";
	Matrix sum = A + B;
	sum.display();

	cout << "\n\nA * B:\n";
	Matrix product = A * B;
	product.display();

	cout << "\n\nDiagonal sums for Matrix A:\n";
	cout << "Main diagonal sum: " << A.mainDiagonalSum() << endl;
	cout << "Secondary diagonal sum: " << A.secondaryDiagonalSum() << endl;

	cout << "\nProblem 5 - Rows 0 and 2 swapped:\n";
	Matrix swap = A;
	swap.swapRows(0, 2);
	swap.display();

	cout << "\n\nProblem 6 - Columns 0 and 2 swapped:\n";
	Matrix swapC = A;
	swapC.swapColumns(0, 2);
	swapC.display();

	cout << "\n\nProblem 7 - Updated matrix:\n";
	A.updateElement(1, 2, 99);
	A.display();

	return 0;
}
