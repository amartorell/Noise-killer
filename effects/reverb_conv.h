//
// Created by juan_ on 5/2/2019.
//

#ifndef EJERCICIO8_REVERB_CONV_H
#define EJERCICIO8_REVERB_CONV_H

#include "generic_effect.h"


class reverb_conv: public generic_effect
{
public:
    float fs;
    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels) override;
    void update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels) override;
    float hanning(int i);
    void do_conv(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels);
    void reset_stats(void) override{} ;
    int len;
    std::vector<std::complex<float>> prev_out_right;
    std::vector<std::complex<float>> prev_out_left;
    std::vector<std::complex<float>> prev_samples_right;
    std::vector<std::complex<float>> prev_samples_left;
    std::vector<std::complex<float>> curr_out_right;
    std::vector<std::complex<float>> curr_out_left;
    std::vector<std::complex<float>> aux_left;
    std::vector<std::complex<float>> aux_right;
    std::vector<std::complex<float>> freq_resp;
    reverb_conv(){};



};


#endif //EJERCICIO8_REVERB_CONV_H
