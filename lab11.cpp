#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#define N 100
using namespace std;

int main(){
	
	ofstream outRand("lab.txt", ios::out);
	double x[N];
	unsigned long long step = 0;
	double delta,deltaSum,avgRand,rnumber=0;
	srand((unsigned)time(NULL));

	for (int i = 0; i < N; i++){
		step++;
		x[i]=(double)(rand())/RAND_MAX;
		avgRand = (x[i] + (step - 1) * avgRand)/step;
		
		deltaSum += pow((x[i]-avgRand),2);	
		delta = sqrt((1.0/i)*deltaSum);
		delta = delta/sqrt(i);

		cout << step << '\t' << avgRand << '\t' << x[i] << '\t' << delta << endl; 
		outRand << step << '\t' << avgRand << '\t' << x[i] << '\t' << delta << endl; 
	}
	return 0;
}