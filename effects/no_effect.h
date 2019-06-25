//
// Created by juan_ on 5/2/2019.
//

#ifndef EJERCICIO8_NO_EFFECT_H
#define EJERCICIO8_NO_EFFECT_H
#include "generic_effect.h"

class no_effect: public generic_effect
{
public:
    int len;
    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
    void reset_stats(void) override{} ;
};


#endif //EJERCICIO8_NO_EFFECT_H
