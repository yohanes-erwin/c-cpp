/**
  ******************************************************************************
  * @file	main.c
  * @author	Yohanes Erwin Setiawan
  * @date	17 Jun 2016
  ******************************************************************************
  * @brief  Implement complex DFT algorithm using C++ programming language
  *         Reference: The Scientist and Engineer's Guide to DSP, 2nd Edition
  ******************************************************************************
  */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// The complex DFT transforms two N point time domain signals
// into two N point frequency domain signals
#define N   32
#define PI  3.141

int xr[N] =
{
    592, 545, 610, 590, 515, 614, 486, 348,
    534, 534, 533, 534, 548, 474, 299, 395,
    516, 652, 644, 348, 480, 526, 305, 588,
    567, 531, 630, 590, 439, 604, 479, 497
};
int xi[N] = { 0 };
int REX[N];
int IMX[N];

void cdft(void);
void icdft(void);
void output_cdft(void);
void output_icdft(void);

int main()
{
    cdft();
    output_cdft();
    icdft();
    output_icdft();

    return EXIT_SUCCESS;
}

// Implement forward complex DFT equation (Eq. 1)
void cdft()
{
    float sr, si;

    // Zero REX[] and IMX[] so they can be used as accumulators
    for (int k = 0; k < N; k++)
    {
        REX[k] = 0;
        IMX[k] = 0;
    }

    // Loop for each value in frequency domain
    for (int k = 0; k < N; k++)
    {
        // Loop for each value in time domain
        for (int n = 0; n < N; n++)
        {
            // Correlate with the complex sinusoid, sr and si
            sr = cos(2*PI*k*n/N);
            si = -sin(2*PI*k*n/N);
            REX[k] += xr[n]*sr - xi[n]*si;
            IMX[k] += xr[n]*si + xi[n]*sr;
        }
    }
}

// Implement inverse complex DFT equation (Eq. 3)
void icdft()
{
    float sr, si;

    // Find the cosine and sine wave amplitudes (Eq. 2)
    for (int k = 0; k < N; k++)
    {
        REX[k] /= N;
        IMX[k] /= N;
    }

    // Zero xr[] and xi[] so it can be used as an accumulators
    for (int n = 0; n < N; n++)
    {
        xr[n] = 0;
        xi[n] = 0;
    }

    // Loop for each value in time domain
    for (int n = 0; n < N; n++)
    {
        // Loop for each value in frequency domain
        for (int k = 0; k < N; k++)
        {
            // Correlate with the complex sinusoid, sr and si
            sr = cos(2*PI*k*n/N);
            si = -sin(2*PI*k*n/N);
            xr[n] += REX[k]*sr + IMX[k]*si;
            xi[n] += -REX[k]*si + IMX[k]*sr;
        }
    }
}

void output_cdft()
{
    FILE *pFile = fopen("cdft.txt", "w");

    // Print time domain signal xr[]
    fprintf(pFile, "xr=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", xr[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal xi[]
    fprintf(pFile, "xi=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", xi[i]);
    }
    fprintf(pFile, "];\n");

    // Print frequency domain signal REX[]
    fprintf(pFile, "REX=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print frequency domain signal IMX[]
    fprintf(pFile, "IMX=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", IMX[i]);
    }
    fprintf(pFile, "];\n");

    // Plot using Matlab
    fprintf(pFile, "figure(1);\n");
    fprintf(pFile, "plot(xr);\n");
    fprintf(pFile, "title('Time Domain Signal (Real Part)');\n");
    fprintf(pFile, "axis([0, 35, 250, 700]);\n");
    fprintf(pFile, "figure(2);\n");
    fprintf(pFile, "plot(xi);\n");
    fprintf(pFile, "title('Time Domain Signal (Imaginary Part)');\n");
    fprintf(pFile, "axis([0, 35, -250, 250]);\n");
    fprintf(pFile, "figure(3);\n");
    fprintf(pFile, "plot(REX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Real Part)');\n");
    fprintf(pFile, "figure(4);\n");
    fprintf(pFile, "plot(IMX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Imaginary Part)');\n");
}

void output_icdft()
{
    FILE *pFile = fopen("icdft.txt", "w");

    // Print cosine amplitudes REX[]
    fprintf(pFile, "REX=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print sine amplitudes IMX[]
    fprintf(pFile, "IMX=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", IMX[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal xr[]
    fprintf(pFile, "xr=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", xr[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal xi[]
    fprintf(pFile, "xi=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", xi[i]);
    }
    fprintf(pFile, "];\n");

    // Plot using Matlab
    fprintf(pFile, "figure(5);\n");
    fprintf(pFile, "plot(REX);\n");
    fprintf(pFile, "title('Cosine Amplitudes');\n");
    fprintf(pFile, "figure(6);\n");
    fprintf(pFile, "plot(IMX);\n");
    fprintf(pFile, "title('Sine Amplitudes');\n");
    fprintf(pFile, "figure(7);\n");
    fprintf(pFile, "plot(xr);\n");
    fprintf(pFile, "title('Time Domain Signal IDFT (Real Part)');\n");
    fprintf(pFile, "axis([0, 35, 250, 700]);\n");
    fprintf(pFile, "figure(8);\n");
    fprintf(pFile, "plot(xi);\n");
    fprintf(pFile, "title('Time Domain Signal IDFT (Imaginary Part)');\n");
    fprintf(pFile, "axis([0, 35, -250, 250]);\n");
}
