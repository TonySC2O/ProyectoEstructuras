#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;
using std::runtime_error;

template <typename E>
class Matrix
{
private:
	int rows;
	int columns;
	E** matrix;
public:
	Matrix(int rows, int columns) {
		if (rows <= 0 || columns <= 0) {
			throw runtime_error("Invalid matrix size");
		}
		this->rows = rows;
		this->columns = columns;
		matrix = new E * [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new E[columns];
			}
	}
	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	E getValue(int row, int column) {
		if (row < 0 || row >= rows || column < 0 || column >= columns) {
			throw runtime_error("Invalid index");
		}
		return matrix[row][column];
	}
	void setValue(int row, int column, E value) {
		if (row < 0 || row >= rows || column < 0 || column >= columns) {
			throw runtime_error("Invalid index");
		}
		matrix[row][column] = value;
	}
	int getRows() {
		return rows;
	}
	int getColumns() {
		return columns;
	}
	void setAllValues(E value) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = value;
			}
		}
	}
	void transpose() {
		E** newMatrix = new E * [columns];
		for (int i = 0; i < columns; i++) {
			newMatrix[i] = new E[rows];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				newMatrix[j][i] = matrix[i][j];
			}
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		int temp = rows;
		rows = columns;
		columns = temp;
	}
	void addRow(E value) {
				E** newMatrix = new E * [rows + 1];
				for (int i = 0; i < rows + 1; i++) {
			newMatrix[i] = new E[columns];
		}
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
				newMatrix[i][j] = matrix[i][j];
			}
		}
				for (int i = 0; i < columns; i++) {
			newMatrix[rows][i] = value;
		}
				for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		rows++;
	}
	void addColumn(E value) {
				E** newMatrix = new E * [rows];
				for (int i = 0; i < rows; i++) {
			newMatrix[i] = new E[columns + 1];
		}
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
				newMatrix[i][j] = matrix[i][j];
			}
		}
				for (int i = 0; i < rows; i++) {
			newMatrix[i][columns] = value;
		}
				for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		columns++;
	}
	void removeRow(int row) {
		if (row < 0 || row >= rows) {
			throw runtime_error("Invalid index");
		}
		E** newMatrix = new E * [rows - 1];
		for (int i = 0; i < rows - 1; i++) {
			newMatrix[i] = new E[columns];
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < columns; j++) {
				newMatrix[i][j] = matrix[i][j];
			}
		}
		for (int i = row + 1; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				newMatrix[i - 1][j] = matrix[i][j];
			}
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		rows--;
	}
	void removeColumn(int column) {
		if (column < 0 || column >= columns) {
			throw runtime_error("Invalid index");
		}
		E** newMatrix = new E * [rows];
		for (int i = 0; i < rows; i++) {
			newMatrix[i] = new E[columns - 1];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < column; j++) {
				newMatrix[i][j] = matrix[i][j];
			}
			for (int j = column + 1; j < columns; j++) {
				newMatrix[i][j - 1] = matrix[i][j];
			}
		}
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = newMatrix;
		columns--;
	}
	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

