//
// Created by juan_ on 4/30/2019.
//

#include "reverb_pb.h"

//
// Created by juan_ on 4/28/2019.
//

void reverb_pb::init(int w_len, float fs,data d) {

//inicializo variables usadas por la clase
    this->len = w_len;
    delay=d.delay;
    this->g=d.g;
    this->fs=fs;
    this->max_delay=delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de salida del efecto
    for(int i=0;i<(max_delay);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
}

void reverb_pb::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        float delay_l;
        float delay_r;
        delay_l=(memory_left[max_delay]*0.5+memory_left[max_delay-1]*0.3+memory_left[max_delay-3]*0.2);//actualizo la señal de salida retrasada que se va a agregar
        if(n_channels==2)
        {
            delay_r=(memory_right[max_delay]*0.5+memory_right[max_delay-1]*0.5+memory_right[max_delay-3]*0.5);

        }
        curr_left[i]=curr_left[i]+g*delay_l;//agrego la señal retrasada con el respectivo factor de atenuación
        memory_left.pop_back();//pierdo el valor de la salida mas viejo
        memory_left.push_front(curr_left[i].real());// y el valor calculado recien pasa a ser el mas nuevo
        if(n_channels==2)
        {
            curr_right[i]=curr_right[i]+g*delay_r;
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());
        }
    }
};

void reverb_pb::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//actualizo vector de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}