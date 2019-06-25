//
// Created by juan_ on 4/30/2019.
//

#ifndef EJ8NOREALTIME_REVERB_PB_H
#define EJ8NOREALTIME_REVERB_PB_H
#include "generic_effect.h"
#include <deque>


class reverb_pb: public generic_effect
{
public:

    int len;
    float g;
    float fs;
    float delay;
    int max_delay;
    std::deque <float> memory_left;
    std::deque <float> memory_right;

    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
    void reset_stats(void) override{} ;
};


#endif //EJ8NOREALTIME_REVERB_PB_H
