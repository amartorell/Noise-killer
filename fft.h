//
// Created by juan_ on 4/28/2019.
//

#ifndef EJERCICIO8_FFT_H
#define EJERCICIO8_FFT_H

#endif //EJERCICIO8_FFT_H

#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std::complex_literals;
void fft(std::vector<std::complex<float> >& in, std::vector<std::complex<float>>& out);

void ifft(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out);

std::complex<float> norma_compleja(std::complex<float> a);