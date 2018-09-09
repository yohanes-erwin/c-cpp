/**
  ******************************************************************************
  * @file	main.c
  * @author	Yohanes Erwin Setiawan
  * @date	17 Jun 2016
  ******************************************************************************
  * @brief  Implement real DFT algorithm using C++ programming language
  *         Reference: The Scientist and Engineer's Guide to DSP, 2nd Edition
  ******************************************************************************
  */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// The real DFT transforms an N point time domain signal
// into two N/2+1 point frequency domain signals
#define N_TIME  32
#define N_FREQ  (N_TIME/2+1)
#define PI      3.141

int x[N_TIME] =
{
    592, 545, 610, 590, 515, 614, 486, 348,
    534, 534, 533, 534, 548, 474, 299, 395,
    516, 652, 644, 348, 480, 526, 305, 588,
    567, 531, 630, 590, 439, 604, 479, 497
};
int REX[N_FREQ];
int IMX[N_FREQ];

void rdft(void);
void irdft(void);
void output_rdft(void);
void output_irdft(void);
void lookup_generator(void);

int main()
{
    rdft();
    output_rdft();
    irdft();
    output_irdft();
    lookup_generator();

    return EXIT_SUCCESS;
}

// Implement forward real DFT equation (Eq. 1)
void rdft()
{
    // Zero REX[] and IMX[] so they can be used as accumulators
    for (int k = 0; k < N_FREQ; k++)
    {
        REX[k] = 0;
        IMX[k] = 0;
    }

    // Loop through each sample in the frequency domain
    for (int k = 0; k < N_FREQ; k++)
    {
        // Loop through each sample in the time domain
        for (int i = 0; i < N_TIME; i++)
        {
            REX[k] += x[i] * cos(2*PI*k*i/N_TIME);
            IMX[k] += -x[i] * sin(2*PI*k*i/N_TIME);
        }
    }
}

// Implement inverse real DFT equation (Eq. 3)
void irdft()
{
    // Find the cosine and sine wave amplitudes (Eq. 2)
    for (int k = 0; k < N_FREQ; k++)
    {
        REX[k] /= (N_TIME/2);
        IMX[k] /= (N_TIME/2);
    }
    REX[0] /= 2;
    REX[N_FREQ] /= 2;

    // Zero x[] so it can be used as an accumulator
    for (int i = 0; i < N_TIME; i++)
    {
        x[i] = 0;
    }

    // Loop through each sample in the time domain
    for (int i = 0; i < N_TIME; i++)
    {
        // Loop through each sample in the frequency domain
        for (int k = 0; k < N_FREQ; k++)
        {
            x[i] += REX[k] * cos(2*PI*k*i/N_TIME);
            x[i] += -IMX[k] * sin(2*PI*k*i/N_TIME);
        }
    }
}

void output_rdft()
{
    FILE *pFile = fopen("rdft.txt", "w");

    // Print time domain signal x[]
    fprintf(pFile, "x=[");
    for (int i = 0; i < N_TIME; i++)
    {
        fprintf(pFile, (i < (N_TIME-1)) ? "%i," : "%i", x[i]);
    }
    fprintf(pFile, "];\n");

    // Print frequency domain signal REX[]
    fprintf(pFile, "REX=[");
    for (int i = 0; i < N_FREQ; i++)
    {
        fprintf(pFile, (i < (N_FREQ-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print frequency domain signal IMX[]
    fprintf(pFile, "IMX=[");
    for (int i = 0; i < N_FREQ; i++)
    {
        fprintf(pFile, (i < (N_FREQ-1)) ? "%i," : "%i", IMX[i]);
    }
    fprintf(pFile, "];\n");

    // Plot using Matlab
    fprintf(pFile, "figure(1);\n");
    fprintf(pFile, "plot(x);\n");
    fprintf(pFile, "title('Time Domain Signal');\n");
    fprintf(pFile, "axis([0, 35, 250, 700]);\n");
    fprintf(pFile, "figure(2);\n");
    fprintf(pFile, "plot(REX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Real Part)');\n");
    fprintf(pFile, "figure(3);\n");
    fprintf(pFile, "plot(IMX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Imaginary Part)');\n");
}

void output_irdft()
{
    FILE *pFile = fopen("irdft.txt", "w");

    // Print cosine amplitudes REX[]
    fprintf(pFile, "REX=[");
    for (int i = 0; i < N_FREQ; i++)
    {
        fprintf(pFile, (i < (N_FREQ-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print sine amplitudes IMX[]
    fprintf(pFile, "IMX=[");
    for (int i = 0; i < N_FREQ; i++)
    {
        fprintf(pFile, (i < (N_FREQ-1)) ? "%i," : "%i", IMX[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal x[]
    fprintf(pFile, "x=[");
    for (int i = 0; i < N_TIME; i++)
    {
        fprintf(pFile, (i < (N_TIME-1)) ? "%i," : "%i", x[i]);
    }
    fprintf(pFile, "];\n");

    // Plot using Matlab
    fprintf(pFile, "figure(4);\n");
    fprintf(pFile, "plot(REX);\n");
    fprintf(pFile, "title('Cosine Amplitudes');\n");
    fprintf(pFile, "figure(5);\n");
    fprintf(pFile, "plot(IMX);\n");
    fprintf(pFile, "title('Sine Amplitudes');\n");
    fprintf(pFile, "figure(6);\n");
    fprintf(pFile, "plot(x);\n");
    fprintf(pFile, "title('Time Domain Signal IDFT');\n");
    fprintf(pFile, "axis([0, 35, 250, 700]);\n");
}

void lookup_generator()
{
    int lookup_idx = 0;
    float cosval[N_FREQ*N_TIME], sinval[N_FREQ*N_TIME];
    FILE *pFile;

    // Generate lookup value
    for (int k = 0; k < N_FREQ; k++)
    {
        for (int i = 0; i < N_TIME; i++)
        {
            cosval[lookup_idx] = cos(2*PI*k*i/N_TIME);
            sinval[lookup_idx] = sin(2*PI*k*i/N_TIME);;
            lookup_idx++;
        }
    }

    pFile = fopen("lookup.txt", "w");

    // Print cos lookup value
    fprintf(pFile, "float cos_lookup[] =\n{\n");
    for (int i = 0; i < N_FREQ*N_TIME; i++)
    {
        fprintf(pFile, (i < (N_FREQ*N_TIME-1)) ? "%.3f, " : "%.3f", cosval[i]);
    }
    fprintf(pFile, "\n};\n");

    // Print sin lookup value
    fprintf(pFile, "float sin_lookup[] =\n{\n");
    for (int i = 0; i < N_FREQ*N_TIME; i++)
    {
        fprintf(pFile, (i < (N_FREQ*N_TIME-1)) ? "%.3f, " : "%.3f", sinval[i]);
    }
    fprintf(pFile, "\n};\n");
}
