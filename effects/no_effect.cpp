//
// Created by juan_ on 5/2/2019.
//

#include "no_effect.h"

void no_effect::init(int w_len, float ,data d)
{
    this->len=w_len;
}

void no_effect::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{

};

void no_effect::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{

    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//se actualiza el vector out
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}