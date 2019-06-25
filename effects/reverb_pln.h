//
// Created by juan_ on 4/30/2019.
//

#ifndef EJERCICIO8_REVERB_PLN_H
#define EJERCICIO8_REVERB_PLN_H
#include "generic_effect.h"
#include <deque>


class reverb_pln: public generic_effect
{
public:

    int len;
    float g;
    float delay;
    float fs;
    int max_delay;
    std::deque <float> memory_left;
    std::deque <float> memory_right;
    reverb_pln(){};
    reverb_pln(int w_len, float fs,float g,float delay);
    ~reverb_pln();
    void init(int w_len, float fs,data d) override ;
    void init(int w_len, float fs,float g,float delay);
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void do_t_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels);
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
    void temp_upd(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,std::vector<std::complex<float>>& left_o,std::vector<std::complex<float>>& right_o,int n_channels);
    void reset_stats(void) override{} ;
};
#endif //EJERCICIO8_REVERB_PLN_H
