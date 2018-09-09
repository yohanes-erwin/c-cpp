#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define BUFFER_LENGTH   9
#define LENGTH          100

#define PI  3.14159265

// Low pass filter coefficient
float coeff_filter[BUFFER_LENGTH] =
{
    0.0174, 0.0612, 0.1662,
    0.2552, 0.2552, 0.1662,
    0.0612, 0.0174
};
float buffer[BUFFER_LENGTH];
float x[LENGTH];
float y[LENGTH];
FILE *pFile;

float filter(float input)
{
    float result;

    // Buffering
    for (int i = BUFFER_LENGTH - 1; i > 0; i--)
    {
        buffer[i] = buffer[i -1];
    }
    buffer[0] = input;

    // Filter calculation
    result = 0;
    for (int i = 0; i < BUFFER_LENGTH; i++)
    {
        result += buffer[i] * coeff_filter[i];
    }

    return result;
}

int main()
{
    // Initialize buffer with 0
    for (int i = 0; i < BUFFER_LENGTH; i++)
    {
        buffer[i] = 0;
    }

    // Input signal
    for (int i = 0; i < LENGTH; i++)
    {
        x[i] = (sin(2*PI*200/16000*i) + sin(2*PI*1000/16000*i) +
                sin(2*PI*5000/16000*i)) / 3;
    }

    // Filter calculation
    for (int i = 0; i < LENGTH; i++)
    {
        y[i] = filter(x[i]);
    }

    // Output filter
    pFile = fopen("output.txt", "w");
    for (int i = 0; i < LENGTH; i++)
    {
        fprintf(pFile, "%4.4f\n", y[i]);
    }
    fclose(pFile);

    return EXIT_SUCCESS;
}
