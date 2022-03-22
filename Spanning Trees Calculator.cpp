#include <iostream>
#include <vector>
using namespace std;

void printMatrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printLaplacianMatrix(vector<vector<double>> matrix) {
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double determinant(vector<vector<int>>& matrix) {
    vector<double> modifiedRow;
    vector<vector<double>> laplacianMatrix;

    //Copy the int matrix into the double matrix
    for (int i = 0; i < matrix.size(); i++) {
        vector<double> row;
        for (int j = 0; j < matrix.size(); j++) {
            row.push_back(matrix[i][j]);
        }
        laplacianMatrix.push_back(row);
        row.clear();
    }

    for (int i = 0; i < laplacianMatrix.size() - 1; i++) {

        //create modified row
        double factor = 1 / laplacianMatrix[i][i];
        for (int j = 0; j < laplacianMatrix.size(); j++) {
            modifiedRow.push_back(laplacianMatrix[i][j] * factor);
        }

        //computes row operation
        for (int k = i + 1; k < laplacianMatrix.size(); k++) { //Iterate through the starting positions
            double modifier = laplacianMatrix[k][i] * -1; // needs to diferent for every row
            for (int l = 0; l < laplacianMatrix.size(); l++) { //iterates through all the elements of the vectors
                laplacianMatrix[k][l] += modifiedRow[l] * modifier; //Actual Row operation
            }
        }

        modifiedRow.clear();
    }

    cout << "\nLaplacian Matrix in Triangular Form: \n";
    printLaplacianMatrix(laplacianMatrix);

    double product = 1;
    for (int i = 0; i < laplacianMatrix.size(); i++) { //Calculates the product of the diagonal
        product *= laplacianMatrix[i][i];
    }

    return product;
}

int getData() {
    int verticies;
    cout << "How many verticies make up your graph: ";
    cin >> verticies;

    return verticies;
}

void createAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix, int verticies) {
    int temp;
    vector<int> row;
    for (int k = 1; k < verticies + 1; k++) {
        cout << "Enter all elements from row " << k << ", seperated by a space: ";
        for (int i = 0; i < verticies; i++) {
            cin >> temp;
            row.push_back(temp);
        }
        adjacencyMatrix.push_back(row);
        row.clear();
    }
}

void createDegreeMatrix(vector<vector<int>>& degreeMatrix, vector<vector<int>> adjacencyMatrix) {
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        int sum = 0;
        vector<int> row(adjacencyMatrix.size(), 0);

        for (int j = 0; j < adjacencyMatrix[i].size(); j++)
        {
            sum += adjacencyMatrix[i][j];
        }

        row[i] = sum;
        degreeMatrix.push_back(row);
    }
}

void createLaplacianMatrix(vector<vector<int>>& laplacianMatrix, vector<vector<int>> degreeMatrix, vector<vector<int>> adjacencyMatrix) {
    int difference;
    vector<int> row;

    for (int i = 0; i < degreeMatrix.size(); i++)
    {
        for (int j = 0; j < degreeMatrix[i].size(); j++)
        {
            difference = degreeMatrix[i][j] - adjacencyMatrix[i][j];
            row.push_back(difference);
        }
        laplacianMatrix.push_back(row);
        row.clear();
    }
}

void modifyLaplacianMatix(vector<vector<int>>& laplacianMatrix) {
    for (int i = 0; i < laplacianMatrix.size() - 1; i++) {
        laplacianMatrix[i].pop_back();
    }
    laplacianMatrix.pop_back();
}

int main()
{
    int verticies = getData();
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> degreeMatrix;
    vector<vector<int>> laplacianMatrix;

    createAdjacencyMatrix(adjacencyMatrix, verticies);
    createDegreeMatrix(degreeMatrix, adjacencyMatrix);
    createLaplacianMatrix(laplacianMatrix, degreeMatrix, adjacencyMatrix);

    cout << "\nAdjacency Matrix:\n";
    printMatrix(adjacencyMatrix);
    cout << "Degree Matrix:\n";
    printMatrix(degreeMatrix);
    cout << "Laplacian Matrix:\n";
    printMatrix(laplacianMatrix);

    modifyLaplacianMatix(laplacianMatrix);

    cout << "Modified Laplacian Matrix:\n";
    printMatrix(laplacianMatrix);

    cout << "The number of spanning trees for this matrix is: " << determinant(laplacianMatrix) << endl;

    return 0;
}