#include <iostream>
#include <cstdlib> 
#include <stdio.h>
#include <ctime> 
#include <cmath>
#include <string>

#define N 1000 //500 1000
using namespace std;


int selectEventResult(string result[], int b2, int (*x)[3], int k, int indLast) {

    int red = 0;
    int blue = 0;
    int black = 0;

    for (int i = 0; i < b2; i++) {
        if (result[i] == "красный") red+=1;
        if (result[i] == "синий") blue+=1;
        if (result[i] == "черный") black+=1;
    }

    int index;
    for (index = 0; index < k; index++) 
    {
        if (( x[index][0] == red) && (x[index][1] == black) && (x[index][2] == blue) ) {
            return index;
        }
    }

    x[indLast][0] = red;
    x[indLast][1] = black;
    x[indLast][2] = blue;

    return -1;
    
}

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
        if (n[i] != 0) D += pow(((i+1) - M), 2) * ((float)n[i]/N);
    }

    return D;
}

void getBallsFromBox(string box[], string result[], int b, int q) {

    int ball1 = 0;
    int ball2 = 0;

    while(true) {
        ball1 = rand() % b;
        ball2 = rand() % b;
        // нельзя вытащить 2 раза один и тот же шар
        if (ball1 != ball2) break;
    }

    result[q] = box[ball1];
    result[q + 1] = box[ball2];
}

int successEvent(string result[], int b2) {

    int red = 0;
    int blue = 0;
    int black = 0;

    for (int i = 0; i < b2; i++) {
        if (result[i] == "красный") red+=1;
        if (result[i] == "синий") blue+=1;
        if (result[i] == "черный") black+=1;
    }

    if ((red == b2)||(black == b2)||(blue == b2)) return 1;
    return 0;

}

void printResult(string result[], int b2) {
    cout << "Вынутые шары: ";
    for(int i = 0; i < b2; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    /*
      * B первом ящике 4 красных, 7 черных и 3 синих шара, во втором 3 красных, 3 черных и 8 синих шара. 
      * Из каждого ящика вынули по 2 шара (всего 4 шара). Найти вероятность того, что шары одинакового цвета.
    */
    const int b = 14; //в ящике
    const int b2 = 4; //вытащили из ящика

    string box1[b] = {
        "красный", "красный", "красный", "красный", 
        "черный", "черный", "черный", "черный", "черный", "черный", "черный",
        "синий","синий","синий"
    };

    string box2[b] = {
        "красный", "красный", "красный",
        "черный", "черный", "черный",
        "синий","синий","синий","синий","синий","синий","синий","синий"
    };

    string result[b2]; 

    int k = 15; // число событий: вынимаем красный, черный или синий шар из 2 ящиков 2 раза (без учета порядка)
    int n[k]; // число успешных событий (каждого события)
    int x[k][3]; // k-событий и число шаров каждого цвета 

    float M; // мат ожидаение
    float D; // дисперсия

    int nP = 0; //число успешных событий: если все вынутые шары одного цвета
    int indLast = 0; // последний указатель на событие
    for (int i = 0; i < k; i++) n[i] = 0;

    for (int i = 0; i < N; i++) {

        int ind = 0;
        getBallsFromBox(box1, result, b, 0);
        getBallsFromBox(box2, result, b, 2);
        //printResult(result, b2);
        ind = selectEventResult(result, b2, x, k, indLast);
        
        if (ind == -1) {
            ind = indLast;
            indLast++;
        }
        //cout << ind << endl;
        n[ind] +=1; 

        // вероятность, чтовсе шары одного цвета
        nP += successEvent(result, b2);
    }

    //for (int i = 0; i < indLast; i++) cout << n[i]/N << " ";
  
    cout << endl << "\tк ч с " << endl;
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
    printf("\nP(4) = %.3f", (float)nP/N);
    printf("\nM = %.3f", M);
    printf("\nD = %.3f", D);
    cout << endl << endl;

    //for (int i = 0; i < indLast; i++) cout << i << "\t\t" << (float)n[i]/N << endl;
 
}