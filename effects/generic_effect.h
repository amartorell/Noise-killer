//
// Created by juan_ on 4/29/2019.
//

#ifndef EJERCICIO8_GENERIC_EFFECT_H
#define EJERCICIO8_GENERIC_EFFECT_H
#include "../fft.h"
#include <string>

struct data
{
    float g;
    float delay;
    float fmod;
    int n_echoes;
    std::string conv_name;
};

class generic_effect
{
public:
    virtual void init(int w_len, float fs,data d) =0;
    virtual void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) =0;
    virtual void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) =0;

};


#endif //EJERCICIO8_GENERIC_EFFECT_H
