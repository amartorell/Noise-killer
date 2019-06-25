//
// Created by juan_ on 5/3/2019.
//

#ifndef EJERCICIO8_REVERB_ALLP_H
#define EJERCICIO8_REVERB_ALLP_H
#include "generic_effect.h"
#include <deque>


class reverb_allp: public generic_effect
{
public:

    int len;
    float g;
    float delay;
    float fs;
    int max_delay;
    std::deque <float> in_memory_left;
    std::deque <float> in_memory_right;
    std::deque <float> out_memory_left;
    std::deque <float> out_memory_right;
    reverb_allp(){};
    reverb_allp(int w_len, float fs,float g,float delay){init(w_len, fs, g, delay);};
    void init(int w_len, float fs,data d) override ;
    void init(int w_len, float fs,float g,float delay);
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
    void temp_upd(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,std::vector<std::complex<float>>& left_o,std::vector<std::complex<float>>& right_o,int n_channels);
    void reset_stats(void) override{} ;
};


#endif //EJERCICIO8_REVERB_ALLP_H
