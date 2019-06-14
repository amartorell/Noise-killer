//
// Created by juan_ on 4/30/2019.
//

#ifndef EJ8NOREALTIME_VIBRATO_H
#define EJ8NOREALTIME_VIBRATO_H
#include "generic_effect.h"
#include <deque>

class vibrato: public generic_effect
{
public:

    int len;
    float Mo;
    float fmod;
    float fs;
    float delay;
    float modcount;
    std::deque <float> memory_left;
    std::deque <float> memory_right;
    vibrato(){};
    void init(int w_len, float fs,data d)override;
    void do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels) override;
    void update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels) override;

};


#endif //EJ8NOREALTIME_VIBRATO_H
