//
// Created by juan_ on 5/3/2019.
//

#include "reverb_allp.h"


void reverb_allp::init(int w_len, float fs,data d) {

//inicializo variables usadas por la clase
    this->len = w_len;
    delay=d.delay;
    this->fs=fs;
    this->g=d.g;
    this->max_delay=delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(max_delay);i++)
    {
        in_memory_left.push_back(0);
        in_memory_right.push_back(0);
        out_memory_left.push_back(0);
        out_memory_right.push_back(0);
    }
}

void reverb_allp::init(int w_len, float fs,float g,float delay)
{
    this->len = w_len;
    delay=delay;
    this->fs=fs;
    this->g=g;
    this->max_delay=delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(max_delay);i++)
    {
        in_memory_left.push_back(0);
        in_memory_right.push_back(0);
        out_memory_left.push_back(0);
        out_memory_right.push_back(0);
    }
};

void reverb_allp::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        float delay_in_l;
        float delay_in_r;
        float delay_out_l;
        float delay_out_r;


        in_memory_left.pop_back();
        in_memory_left.push_front(curr_left[i].real());
        delay_out_l=out_memory_left[max_delay];
        delay_in_l=in_memory_left[max_delay];//actualizo la señal de salida retrasada que se va a agregar
        if(n_channels==2)
        {
            in_memory_right.pop_back();
            in_memory_right.push_front(curr_right[i].real());
            delay_out_r=out_memory_right[max_delay];
            delay_in_r=in_memory_right[max_delay];

        }
        curr_left[i]=this->g*delay_out_l-curr_left[i]+this->g*delay_in_l;//agrego la señal retrasada con el respectivo factor de atenuación
        out_memory_left.pop_back();//pierdo el valor de la salida mas viejo
        out_memory_left.push_front(curr_left[i].real());// y el valor calculado recien pasa a ser el mas nuevo
        if(n_channels==2)
        {
            curr_right[i]=this->g*delay_out_r-curr_right[i]+this->g*delay_in_r;
            out_memory_right.pop_back();
            out_memory_right.push_front(curr_right[i].real());
        }
    }
};

void reverb_allp::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//actualizo vector de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}
void reverb_allp::temp_upd(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,std::vector<std::complex<float>>& left_o,std::vector<std::complex<float>>& right_o,int n_channels)
{
    std::copy ( left.begin(), left.end(), left_o.begin() );
    std::copy ( right.begin(), right.end(), right_o.begin() );
}