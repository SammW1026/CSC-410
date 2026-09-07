#include <stdio.h>
#include <time.h>

#ifndef N
#define N 100000
#endif

double f(double x) {
    return 4.0 / (1.0 + x * x); // Function to integrate
}

double trapezoidalRule() 
{
    const double lowerBound = 0.0;
    const double upperBound = 1.0;
    const double width = (upperBound - lowerBound) / N;
    double sum = (f(lowerBound) + f(upperBound)) / 2.0;

    for (int i = 1; i < N; i++) {
        sum += f(lowerBound + i * width);
    }
    return sum * width;
}

int main() {
    clock_t start = clock();
    double pi = trapezoidalRule();
    clock_t end = clock();
    printf("Estimated value of π: %f\n", pi);
    printf("Numerical integration time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
