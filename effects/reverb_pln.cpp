//
// Created by juan_ on 4/30/2019.
//

#include "reverb_pln.h"

//
// Created by juan_ on 4/28/2019.
//

reverb_pln::reverb_pln(int w_len, float fs, float g, float delay)
{
    init(w_len,fs,g,delay);
}

reverb_pln::~reverb_pln()
{

};

void reverb_pln::init(int w_len, float fs,data d) {

//inicializo variables usadas por la clase
    this->len = w_len;
    delay=d.delay;
    this->fs=fs;
    this->g=d.g;
    this->max_delay=delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(max_delay);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
}

void reverb_pln::init(int w_len, float fs,float g,float delay)
{
    this->len = w_len;
    delay=delay;
    this->fs=fs;
    this->g=g;
    this->max_delay=delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(max_delay);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
};

void reverb_pln::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        float delay_l;
        float delay_r;
        delay_l=memory_left[max_delay];//actualizo la señal de salida retrasada que se va a agregar
        if(n_channels==2)
        {
            delay_r=memory_right[max_delay];

        }
        curr_left[i]=curr_left[i]+this->g*delay_l;//agrego la señal retrasada con el respectivo factor de atenuación
        memory_left.pop_back();//pierdo el valor de la salida mas viejo
        memory_left.push_front(curr_left[i].real());// y el valor calculado recien pasa a ser el mas nuevo
        if(n_channels==2)
        {
            curr_right[i]=curr_right[i]+this->g*delay_r;
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());
        }
    }
};

void reverb_pln::do_t_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        float delay_l;
        float delay_r;
        delay_l=memory_left[max_delay];//actualizo la señal de salida retrasada que se va a agregar
        if(n_channels==2)
        {
            delay_r=memory_right[max_delay];

        }
        curr_left[i]=curr_left[i]+this->g*delay_l;//agrego la señal retrasada con el respectivo factor de atenuación
        memory_left.pop_back();//pierdo el valor de la salida mas viejo
        memory_left.push_front(curr_left[i].real());// y el valor calculado recien pasa a ser el mas nuevo
        if(n_channels==2)
        {
            curr_right[i]=curr_right[i]+this->g*delay_r;
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());
        }
    }
};


void reverb_pln::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//actualizo vector de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}
void reverb_pln::temp_upd(std::vector<std::complex<float>>& left, std::vector<std::complex<float>>& right,std::vector<std::complex<float>>& left_o,std::vector<std::complex<float>>& right_o,int n_channels)
{
    for(int i=0;i<len;i++)
    {
        left_o[i]+=left[i];
        right_o[i]+=left_o[i];
    }
}