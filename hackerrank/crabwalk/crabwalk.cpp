#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

float ExpectedCrabWalk(int numsteps) {

	if(numsteps <= 0)
		return 0.0;

	double **fProbMatrix = (double **)malloc((2*numsteps+3)*(2*numsteps+3)*sizeof(double*));
	double **fProbPreviousMatrix = (double **)malloc((2*numsteps+3)*(2*numsteps+3)*sizeof(double*));
	int** wakeMat = (int **)malloc((2*numsteps+3)*(2*numsteps+3)*sizeof(int*));
	int** wakeMatPrev = (int **)malloc((2*numsteps+3)*(2*numsteps+3)*sizeof(int*));

	for(int i=0; i<2*numsteps+3; i++) {
		double *fRow = new double[2*numsteps+3];
		double *fRowPrev = new double[2*numsteps+3];
		int *wakeRow = new int[2*numsteps+3];
		int *wakeRowPrev = new int[2*numsteps+3];
		fProbMatrix[i] = fRow;
		fProbPreviousMatrix[i] = fRowPrev;
		wakeMat[i] = wakeRow;
		wakeMatPrev[i] = wakeRowPrev;
		for(int j=0; j<2*numsteps+3; j++) {
			fProbMatrix[i][j] = 0.0;
			wakeMat[i][j] = 1;
		}
	}
	// Init the center position
	fProbMatrix[numsteps+1][numsteps+1] = 1.0;


	// Calc probability
	for(int k=1;k<=numsteps;k++) {
		// Init Previous state Probablity Matrix
		for(int i=0; i<2*numsteps+3; i++)
			for(int j=0; j<2*numsteps+3; j++){
				fProbPreviousMatrix[i][j] = fProbMatrix[i][j];
				wakeMatPrev[i][j] = wakeMat[i][j];
			}
		for(int i=0; i<=k; i++) {
			for(int j=0; j<=k; j++) {
				// Right,Bottom
				fProbMatrix[numsteps+1+i][numsteps+1+j] = 0.2
									* (fProbPreviousMatrix[numsteps+1+i][numsteps+1+j] * wakeMatPrev[numsteps+1+i][numsteps+1+j]
								+ fProbPreviousMatrix[numsteps+1+i-1][numsteps+1+j] * wakeMatPrev[numsteps+1+i-1][numsteps+1+j]
								+ fProbPreviousMatrix[numsteps+1+i+1][numsteps+1+j] * wakeMatPrev[numsteps+1+i+1][numsteps+1+j]
								+ fProbPreviousMatrix[numsteps+1+i][numsteps+1+j-1] * wakeMatPrev[numsteps+1+i][numsteps+1+j-1]
								+ fProbPreviousMatrix[numsteps+1+i][numsteps+1+j+1] * wakeMatPrev[numsteps+1+i][numsteps+1+j+1]);
				// Other positions can be retrieved by symmetric mapping
				fProbMatrix[numsteps+1+i][numsteps+1-j] = fProbMatrix[numsteps+1+i][numsteps+1+j];
				fProbMatrix[numsteps+1-i][numsteps+1+j] = fProbMatrix[numsteps+1+i][numsteps+1+j];
				fProbMatrix[numsteps+1-i][numsteps+1-j] = fProbMatrix[numsteps+1+i][numsteps+1+j];

				// Set wake state array
				if(fabs(fProbMatrix[numsteps+1+i][numsteps+1+j]
					- 0.2 * fProbPreviousMatrix[numsteps+1+i][numsteps+1+j] * wakeMat[numsteps+1+i][numsteps+1+j])<1e-10)
					wakeMat[numsteps+1+i][numsteps+1+j] = 0;
				else
					wakeMat[numsteps+1+i][numsteps+1+j] = 1;
				wakeMat[numsteps+1+i][numsteps+1-j] = wakeMat[numsteps+1+i][numsteps+1+j];
				wakeMat[numsteps+1-i][numsteps+1+j] = wakeMat[numsteps+1+i][numsteps+1+j];
				wakeMat[numsteps+1-i][numsteps+1-j] = wakeMat[numsteps+1+i][numsteps+1+j];
			}
		}
	}

	double fDistance = 0.0;
	for(int i=0; i<2*numsteps+3; i++) {
		for(int j=0; j<2*numsteps+3; j++){
			double fdis = fProbMatrix[i][j]*sqrt((double)(i-numsteps-1)*(i-numsteps-1)+(j-numsteps-1)*(j-numsteps-1));;
			fDistance += fdis;
		}
	}

	// Free memory
	for(int i=0; i<2*numsteps+3; i++) {
		delete[] fProbPreviousMatrix[i];
		delete[] fProbMatrix[i];
		delete[] wakeMatPrev[i];
		delete[] wakeMat[i];
	}

	free(fProbPreviousMatrix);
	free(fProbMatrix);
	free(wakeMatPrev);
	free(wakeMat);
	return (float)fDistance;
}

int main()
{
    int numsteps = 0;
    cin >> numsteps;
    cout << ExpectedCrabWalk(numsteps) << endl;
    return 0;
}
