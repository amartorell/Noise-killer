//
// Created by juan_ on 4/30/2019.
//

#ifndef EJERCICIO8_ECO_SIMPLE_H
#define EJERCICIO8_ECO_SIMPLE_H
#include "generic_effect.h"
#include <deque>


class eco_simple: public generic_effect
{
public:

    int len;
    float g;
    int echoes;
    float delay;
    int max_delay;
    float fs;
    std::deque <float> memory_left;
    std::deque <float> memory_right;

    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
};
#endif //EJERCICIO8_ECO_SIMPLE_H
