//
// Created by juan_ on 4/28/2019.
//

#ifndef EJERCICIO8_FLANGER_H
#define EJERCICIO8_FLANGER_H
#include "generic_effect.h"
#include <deque>

class flanger: public generic_effect
{
public:

    int len;
    float g;
    float Mo;
    float fmod;
    float fs;
    float modcount;
    std::deque <float> memory_left;
    std::deque <float> memory_right;
    flanger(){};
    void init(int w_len, float fs,data d)override;
    void do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels) override;
    void update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels) override;

};


#endif //EJERCICIO8_FLANGER_H
