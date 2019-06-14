//
// Created by juan_ on 4/30/2019.
//

#include "vibrato.h"


void vibrato::init(int w_len, float fs,data d)
{
    this->len=w_len;
    this->fmod=d.fmod;
    this->fs=fs;
    delay=d.delay;
    //conociendo fs y el delay deseado se calcula cuantas muestras implica ese retardo
    this->Mo=delay*fs;
    this->modcount=0;
    for(int i=0;i<(Mo);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
}

void vibrato::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        int M= floor(Mo/2*(1-cos(2*M_PI*fmod*this->modcount/this->fs)));//se calcula el valor de la senoidal modulante para el punto
        float delay_l;
        float delay_r;
        this->modcount++;
        if((1/fmod-this->modcount/this->fs)<0.01)
        {
            this->modcount=0;
        }
        memory_left.pop_back();//se quita la muestra mas antigua
        memory_left.push_front(curr_left[i].real());//y se agrega la actual
        delay_l=memory_left[M];//se obtiene la mmuestra retrasada
        if(n_channels==2)
        {
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());
            delay_r=memory_right[M];

        }

        curr_left[i]=delay_l;//el valor actual de la salida es el de la muestra retrasada
        if(n_channels==2)
        {
            curr_right[i]=delay_r;
        }
    }
};

void vibrato::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{

    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//se actualiza el vector out
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}