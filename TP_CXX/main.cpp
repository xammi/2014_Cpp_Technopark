#include <QDebug>

#define SIZE 100
#define PRINT_X printf("X:\t%7d\n", &x)
#define CUBE(N) ((N) * (N) * (N))

// выбор параметров генератора псевдослучайных чисел
#ifdef ANSI_C_LIKE
#define A 1103515245
#define C 12345
#else
#define A 22695477
#define C 1
#endif

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

double a = 5;
double b = a;

int main(int argc, char *argv[]) {
    int b = 3;
    int g[0] = {};
    register int a = 5;

    int c[7] = {1, [5] = 2, 3};
    qDebug() << & a << g;

    //int x[SIZE];                       //эквивалентно: int a[100];
    //PRINT_X;                           //эквивалентно:printf("X:\t%7d\n",&x);
    //printf("%d\n", CUBE(SIZE));        //эквивалентно: printf("%d\n",((100)*(100)*(100)));

    qDebug() << argc << argv;
}
