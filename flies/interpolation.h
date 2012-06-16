#ifndef INTERPOLATION
#define INTERPOLATION

#include <cmath>

using namespace std;

namespace Interpolation
{
    const int SMOOTH = 100;

    float cos_interpolate(float y0, float y1, float mu)
    {
        float mu2 = (1 - cos(mu * M_PI)) / 2;
        return y0 * (1 - mu2) + y1 * mu2;
    }

    float mu(float i)
    {
        return i / SMOOTH;
    }

    float x_dw(float x0, float x1, float SMOOTH)
    {
        return (x1 - x0) / SMOOTH;
    }

    // returns interpolated dots between x[dot_i] and x[dot_i + 1]
    // of float[SMOOTH - 1]
    float * interpolateX(const float xs[], int dot_i, int SMOOTH)
    {
        float *xi = (float *)malloc(sizeof(float) * (SMOOTH - 1));
        memset(xi, 0, sizeof(float) * (SMOOTH-1));

        int i;
        for (i = 1; i < SMOOTH; ++i)
            xi[i - 1] = x_dw(xs[dot_i], xs[dot_i + 1], SMOOTH) * i + xs[dot_i];

        return xi;
    }

    float * interpolateY(const float ys[], int dot_i, int SMOOTH)
    {
        float *yi = (float *)malloc(sizeof(float) * (SMOOTH - 1));
        memset(yi, 0, sizeof(float) * (SMOOTH-1));

        int i;
        for (i = 1; i < SMOOTH; ++i)
            yi[i - 1] = cos_interpolate(ys[dot_i], ys[dot_i + 1], mu(i - 1));

        return yi;
    }
}

#endif
