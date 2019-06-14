//
// Created by juan_ on 4/28/2019.
//

#include "flanger.h"

void flanger::init(int w_len, float fs,data d)
{
    this->len=w_len;
    this->g=d.g;
    this->fmod=d.fmod;
    this->fs=fs;
    float delay=d.delay;
    //Sabiendo fs y el delay deseado se calcula la cantidad de muestras que esto implica
    this->Mo=delay*fs;
    this->modcount=0;
    for(int i=0;i<(Mo);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
}

void flanger::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        int M= floor(Mo/2*(1-cos(2*M_PI*fmod*this->modcount/this->fs)));//se calcula en el punto el valor de la senoidal modulante
        float delay_l;
        float delay_r;
        this->modcount++;
        if((1/fmod-this->modcount/this->fs)<0.01)
        {
            this->modcount=0;
        }
        memory_left.pop_back();//se pierde el valor más antiguo de la cola
        memory_left.push_front(curr_left[i].real());//y se agrega el actual
        delay_l=memory_left[M];//se obtiene la muestra retrasada
        if(n_channels==2)
        {
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());
            delay_r=memory_right[M];

        }

        curr_left[i]=curr_left[i]+this->g*delay_l;//se aplica el efecto
        if(n_channels==2)
        {
            curr_right[i]=curr_right[i]+this->g*delay_r;
        }
    }
};

void flanger::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{

    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//se actualiza el vector de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}