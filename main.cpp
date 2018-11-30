/**
 * @author Athanasios Theocharis, AEM: 2961
 * A program that produces the result of a convolution between a 1D Vector with B[1/5 1/5 1/5 1/5 1/5]
 * and a 2D convolution between a 2D MxN Matrix with 3x3 Vector that only has 1/9 in each cell.
 */

#include <iostream>
#include "time.h"
using namespace std;

/**
 * The two myConvolve functions, one for each mode.
 */
void myConvolve(float[],float[],float*,int);
void myConvolve(float**,float**,float**,int,int);
int main() {
    srand(time(NULL)); // Initializing the random number generator

    /**
     * 1D Convolution
     */
    int size; // Stores the size of the random array;

    cout<<"Please enter size of vector for the 1D convolution (N>10)\n";
    cin>>size;
    // The 3 Arrays A is the random one, B is the given one, and C stores the result
    float A[size];
    float B[5];
    float C[size+4]; // Convolution gives an array the size of (Size + 5 - 1)

    // Initializes the B (the given array at 1/5)
    for (int i=0; i<5; i++){
        B[i]=0.2;
    }

    // Initializes the A (the random one)
    for (int i=0; i<size; i++){
        A[i]=rand()%100+1;
    }

    // Prints the A
    cout<<"A: ";
    for (int i=0; i<size; i++){
        cout<<A[i]<<" ";
    }

    // Prints the B
    cout<<"\nB: ";
    for (int i=0; i<5; i++) {
        cout << B[i] << " ";
    }

    cout<<"\nC: ";

    // myConvolve is called for the first mode
    myConvolve(A,B,C,size);

    // Prints the result of the convolution
    for (int i=0; i<(size+4); i++){
        cout<<C[i]<<" ";
    }
    cout<<"\n";


    /**
     * 2D Convolution
    */
    int row, col; // Variables to store the number of rows and columns
    float** D; // The random 2D matrix
    cout<<"Please enter number of rows and columns for the 2D Vector\n";
    cin>>row>>col; // The user enters desired sizes for rows and columns
    float** E; // The 1/9 2D matrix

    // D matrix is being initialized with random numbers
    D = new float*[row];
    for (int i=0; i<row; i++){
        D[i] = new float[col];
        for (int j=0; j<col; j++){
            D[i][j]=rand()%100+1;
        }
    }

    // E matrix is being initialized with 1/9 in every cell
    E = new float*[3];
    for (int i=0; i<3; i++){
        E[i] = new float[3];
        for (int j=0; j<3; j++){
            E[i][j]=(float)1/(float)9;
        }
    }


    float** F = new float*[row+2];

    // myConvolve for the result is called
    myConvolve(D,E,F,row,col);

    // Prints the random 2D Array
    cout<<"\nA: \n";
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            cout<<D[i][j]<<" ";
        }
        cout<<"\n";
    }

    // Prints the given 2D Array
    cout<<"\nB: \n";
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout<<"1/9 ";
        }
        cout<<"\n";
    }

    // Prints the results of the 2D convolution
    cout<<"\nC: \n";
    for (int i=0; i<row+2; i++){
        for (int j=0; j<col+2; j++){
            cout<<F[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

/**
 * function to compute the 1D convolution
 * @param A the random array
 * @param B the given array
 * @param C the array that keeps the results
 * @param size the size of the random array
 */
void myConvolve(float A[],float B[],float* C,int size){
    // Variables to store the places of where the convolution is at a given moment
    int counterA=0;
    int counterB=0;

    for (int i=0; i<size+4; i++){
        C[i]=0;
        if(i>4){
            counterA++;
        } else {
            counterB++;
        }
        if (i+1>size){
            counterB--;
        }
        for (int j= 0; j< counterB; j++){
            C[i]=C[i]+A[counterA+j]*B[j]; // Computes each element of the convolution
        }
    }
}

/**
 * function to compute the 1D convolution
 * @param A the random 2D array
 * @param B the given 2D array
 * @param C the array that stores the results
 * @param row the number of rows in A matrix
 * @param col the number of columns in A matrix
 */
void myConvolve(float **A, float **B,float** C, int row, int col){
    // Variables to store the places of where the convolution is at a given moment in 2D
    int counterAi=0;
    int counterAj;
    int counterBi=0;
    int counterBj;
    for (int i=0; i<row+2; i++){
        counterAj=0;
        counterBj=0;
        C[i] = new float[col+2];
        if (i>2){
            counterAi++;
        } else {
            counterBi++;
        }
        if (i+1>row){
            counterBi--;
        }
        for (int j=0; j<col+2; j++){
            if (j>2){
                counterAj++;
            } else {
                counterBj++;
            }
            if (j+1>col){
                counterBj--;
            }
            for (int k=0; k<counterBi; k++){
                for (int m=0; m<counterBj; m++){
                    C[i][j] = C[i][j] + A[counterAi+k][counterAj+m]*B[k][m]; // Computes each element of the 2D Convolution
                }
            }
        }
    }
}