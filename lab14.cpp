#include <iostream>
#include <cstdlib> 
#include <stdio.h>
#include <ctime> 
#include <cmath>
#include <string>

#define N 1000 //500 1000
using namespace std;

float getMath(int n[], int k){

    float M = 0;
    for (int i = 0; i < k; i++) {
        if (n[i] != 0) M += (i+1) * ((float)n[i]/N);
    }

    return M;
}

float getDispersion(int n[], int k, float M){

    float D = 0;
    for (int i = 0; i < k; i++) {
        if (n[i] != 0)  D += pow(((i+1) - M), 2) * ((float)n[i]/N);
    }

    return D;
}

int getBallsFromBox(int result[], int sum, int ballPred, int q) {

    int ball = 0;
    while (true)
    {
        // нельзя вытащить 2 раза один и тот же шар
        ball = rand() % sum;
        if (ball != ballPred) break;
    }

    result[q] = ball;
    return ball; 
}

int selectEventResult(int result[], int b2, int (*x)[3], int k, int r, int b, int w, int indLast) {

    int red = 0;
    int blue = 0;
    int white = 0;

    for (int i = 0; i < b2; i++) {
        if (result[i] < r) red += 1;
        if ( (result[i] >= r) && (result[i] < r+b) )  blue += 1;
        if ( (result[i] >= r+b) && (result[i] < r+b+w) )  white += 1;
    }

    int index;
    for (index = 0; index < k; index++) 
    {
        if (( x[index][0] == red) && (x[index][1] == blue) && (x[index][2] == white) ) {
            return index;
        }
    }

    x[indLast][0] = red;
    x[indLast][1] = blue;
    x[indLast][2] = white;

    return -1;
}

int successEvent(int result[], int b2, int r, int b, int w) {

    int red = 0;
    int blue = 0;
    int white = 0;

    for (int i = 0; i < b2; i++) {
        if (result[i] < r) red += 1;
        if ( (result[i] >= r) && (result[i] < r+b) )  blue += 1;
        if ( (result[i] >= r+b) && (result[i] < r+b+w) )  white += 1;
    }

    if ((red == b2)||(blue == b2)||(white == b2)) return 1;
    return 0;

}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    /*
      * B урне 25 шаров: 9 красных, 12 синих и 4 белых. 
      * Найти вероятность того, что наугад вынутые 2 шара разного цвета.
    */
    int b2 = 2; //вынимаемые шары 

    int k = 6; // число событий: винимаем красный, синий или белый шар 2 раза
    int red = 9;
    int blue = 12;
    int white = 4;
   
    int n[k]; // число успешных событий (каждого события)
    int x[k][3]; // k-событий и число шаров каждого цвета 
    int result[b2]; // вынутые шары

    float M; // мат ожидаение
    float D; // дисперсия

    int nP = 0; //число успешных событий: все шары одного цвета
    int indLast = 0; // последний указатель на событие
    for (int i = 0; i < k; i++) n[i] = 0;

    for (int i = 0; i < N; i++) {

        // вынимаем шары из ящика
        int ball = -1; 
        for (int q = 0; q < b2; q++) {
            int s = red + blue + white;
            ball = getBallsFromBox(result, s, ball, q); 
        }
       
        int ind = 0;
        ind = selectEventResult(result, b2, x, k, red, blue, white, indLast);
       // cout << ind << " " <<endl;
        
        if (ind == -1) {
            ind = indLast;
            indLast++;
        }
        n[ind] +=1; 

        // вероятность, чтовсе шары одного цвета
        nP += successEvent(result, b2, red, blue, white);
    }
  

    cout << endl << "\tr b w " << endl;
    for (int i = 0; i < indLast; i++) 
        cout << "x[" <<i+1 << "]:\t"<< x[i][0] << " " << x[i][1] << " "  << x[i][2] << "\t\tn = " << n[i] << "\tp = " << (float)n[i]/N << endl;
    
    float sum = 0;
    for (int i = 0; i < indLast; i++) 
    {
        sum += (float)n[i]/N;
    }
    cout << "\t\t\t\tp(sum) = "<< sum << endl;

    M = getMath(n, indLast);
    D = getDispersion(n, indLast, M);

    printf("\nP(raz) = %.3f", 1 - (float)nP/N);
    printf("\nM = %.3f", M);
    printf("\nD = %.3f", D);
    cout << endl << endl;

    //for (int i = 0; i < indLast; i++) cout << i << "\t\t" << (float)n[i]/N << endl;
 
}