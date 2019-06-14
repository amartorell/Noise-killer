//
// Created by juan_ on 5/2/2019.
//

#ifndef EJERCICIO8_REVERB_CMP_H
#define EJERCICIO8_REVERB_CMP_H
#include "generic_effect.h"
#include "reverb_pln.h"
#include "reverb_allp.h"
#include <deque>
class reverb_cmp: public generic_effect {
public:

    int len;
    float g;
    float fs;
    int cant;
    int max_delay;
    ~reverb_cmp();
    std::vector<std::complex<float>> temp_pln_out_l;
    std::vector<std::complex<float>> temp_pln_out_r;
    std::vector<std::complex<float>> temp_allp_out_l;
    std::vector<std::complex<float>> temp_allp_out_r;
    std::vector<std::complex<float>> temp_pln_in_l;
    std::vector<std::complex<float>> temp_pln_in_r;

    reverb_pln rev_plan;
    reverb_pln rev_plan2;
    reverb_allp rev_allp;
    reverb_allp rev_allp2;

    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,int n_channels) override;
    void update(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,float * out,int n_channels) override;
};


#endif //EJERCICIO8_REVERB_CMP_H
