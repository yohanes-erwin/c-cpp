/**
  ******************************************************************************
  * @file	main.c
  * @author	Yohanes Erwin Setiawan
  * @date	19 Jun 2016
  ******************************************************************************
  * @brief  Implement FFT algorithm using C++ programming language
  *         Reference: The Scientist and Engineer's Guide to DSP, 2nd Edition
  ******************************************************************************
  */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define N   32
#define PI  3.141

int REX[N] =
{
    592, 545, 610, 590, 515, 614, 486, 348,
    534, 534, 533, 534, 548, 474, 299, 395,
    516, 652, 644, 348, 480, 526, 305, 588,
    567, 531, 630, 590, 439, 604, 479, 497
};
int IMX[N] = { 0 };

void fft(void);
void ifft(void);
void output_original_signal(void);
void output_fft(void);
void output_ifft(void);

int main()
{
    output_original_signal();
    fft();
    output_fft();
    ifft();
    output_ifft();

    return EXIT_SUCCESS;
}

// Upon entry, REX[] and IMX[] contain the real and imaginary parts
// of the input
// Upon return, REX[] and IMX[] contain the FFT output
void fft()
{
    int nm1 = N - 1;
    int nd2 = N / 2;
    int m = log10(N) / log10(2);
    int j = nd2;
    int k;
    int le, le2;
    float ur, ui, sr, si;
    int jm1;
    int ip;
    float tr, ti;

    // Bit reversal sorting
    for (int i = 1; i <= N-2; i++)
    {
        if (i >= j) goto a;
        tr = REX[j];
        ti = IMX[j];
        REX[j] = REX[i];
        IMX[j] = IMX[i];
        REX[i] = tr;
        IMX[i] = ti;
        a:
        k = nd2;
        b:
        if (k > j) goto c;
        j -= k;
        k /= 2;
        goto b;
        c:
        j += k;
    }

    // Loop each stage
    for (int l = 1; l <= m; l++)
    {
        le = pow(2, l);
        le2 = le / 2;
        ur = 1;
        ui = 0;
        // Calculate sine and cosine values
        sr = cos(PI/le2);
        si = -sin(PI/le2);
        // Loop for each sub DFT
        for (int j = 1; j <= le2; j++)
        {
            jm1 = j - 1;
            // Loop for each butterfly
            for (int i = jm1; i <= nm1; i += le)
            {
                ip = i + le2;
                tr = REX[ip]*ur - IMX[ip]*ui;
                ti = REX[ip]*ui + IMX[ip]*ur;
                REX[ip] = REX[i] - tr;
                IMX[ip] = IMX[i] - ti;
                REX[i] = REX[i] + tr;
                IMX[i] = IMX[i] + ti;
            }
            tr = ur;
            ur = tr*sr - ui*si;
            ui = tr*si + ui*sr;
        }
    }
}

// Upon entry, REX[] and IMX[] contain the real and imaginary parts
// of the complex frequency domain
// Upon return, REX[] and IMX[] contain the complex time domain
void ifft()
{
    // Change the sign of IMX[]
    for (int k = 0; k <= N-1; k++)
    {
        IMX[k] = -IMX[k];
    }

    // Calculate forward FFT
    fft();

    // Divide the time domain by N and change the sign of IMX[]
    for (int n = 0; n <= N-1; n++)
    {
        REX[n] /= N;
        IMX[n] /= -N;
    }
}

void output_original_signal()
{
    FILE *pFile = fopen("original_signal.txt", "w");

    // Print time domain signal xr[]
    fprintf(pFile, "xr=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal xi[]
    fprintf(pFile, "xi=[");
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
}

void output_fft()
{
    FILE *pFile = fopen("fft.txt", "w");

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
    fprintf(pFile, "figure(3);\n");
    fprintf(pFile, "plot(REX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Real Part)');\n");
    fprintf(pFile, "figure(4);\n");
    fprintf(pFile, "plot(IMX);\n");
    fprintf(pFile, "title('Frequency Domain Signal(Imaginary Part)');\n");
}

void output_ifft()
{
    FILE *pFile = fopen("ifft.txt", "w");

    // Print time domain signal xr[]
    fprintf(pFile, "xr=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", REX[i]);
    }
    fprintf(pFile, "];\n");

    // Print time domain signal xi[]
    fprintf(pFile, "xi=[");
    for (int i = 0; i < N; i++)
    {
        fprintf(pFile, (i < (N-1)) ? "%i," : "%i", IMX[i]);
    }
    fprintf(pFile, "];\n");

    // Plot using Matlab
    fprintf(pFile, "figure(5);\n");
    fprintf(pFile, "plot(xr);\n");
    fprintf(pFile, "title('Time Domain Signal IFFT (Real Part)');\n");
    fprintf(pFile, "axis([0, 35, 250, 700]);\n");
    fprintf(pFile, "figure(6);\n");
    fprintf(pFile, "plot(xi);\n");
    fprintf(pFile, "title('Time Domain Signal IFFT (Imaginary Part)');\n");
    fprintf(pFile, "axis([0, 35, -250, 250]);\n");
}
