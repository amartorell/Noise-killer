//
// Created by juan_ on 5/2/2019.
//

#include "reverb_cmp.h"

void reverb_cmp::init(int w_len, float fs,data d) {

//inicializo variables usadas por la clase
    this->len = w_len;
    float delay1=d.fmod;
    float delay2=d.delay;
    this->fs=fs;
    this->g=d.g;
    rev_plan=reverb_pln(w_len,fs,g,delay1);
    rev_plan2=reverb_pln(w_len,fs,g,delay1);
    rev_allp=reverb_allp(w_len,fs,g,delay1);
    rev_allp2=reverb_allp(w_len,fs,g,delay2);
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(len);i++)
    {
        temp_pln_out_l.emplace_back(0);
        temp_pln_out_r.emplace_back(0);
        temp_pln_in_l.emplace_back(0);
        temp_pln_in_r.emplace_back(0);
        temp_allp_out_r.emplace_back(0);
        temp_allp_out_l.emplace_back(0);
    }
}

reverb_cmp::~reverb_cmp()
{
    for(int i=0;i<len;i++)
    {
    }
}

void reverb_cmp::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    std::fill(temp_pln_out_l.begin(), temp_pln_out_l.end(), 0);
    std::fill(temp_pln_out_r.begin(), temp_pln_out_r.end(), 0);

    std::vector<std::complex<float>> t_left_in(curr_left);
    std::vector<std::complex<float>> t_right_in(curr_right);
    rev_plan.do_effect(t_left_in,t_right_in,2);
    rev_plan.temp_upd(t_left_in,t_right_in,temp_pln_out_l,temp_pln_out_r,2);

    rev_plan2.do_effect(t_left_in,t_right_in,2);
    rev_plan2.temp_upd(t_left_in,t_right_in,temp_pln_out_l,temp_pln_out_r,2);

    rev_allp.do_effect(temp_pln_out_l,temp_pln_out_r,2);
    rev_allp.temp_upd(temp_pln_out_l,temp_pln_out_r,temp_allp_out_l,temp_allp_out_r,2);

    rev_allp2.do_effect(temp_allp_out_l,temp_allp_out_r,2);
    rev_allp2.temp_upd(temp_allp_out_l,temp_allp_out_r,curr_left,curr_right,2);
};

void reverb_cmp::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//actualizo vector de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}