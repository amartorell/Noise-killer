//
// Created by juan_ on 4/30/2019.
//

#include "eco_simple.h"

//
// Created by juan_ on 4/28/2019.
//

void eco_simple::init(int w_len, float fs,data d) {

//guardo los datos que recibo para inicializar
    this->len = w_len;
    delay=d.delay;
    this->fs=fs;
    this->g=d.g;
    this->echoes=d.n_echoes;
    //sabiendo la cantidad de ecos que voy a tener, fs y el retraso deseado se calcula la longitud de la cola
    this->max_delay=echoes*delay*fs;
    //memory_l/r son colas con instancias anteriores de la función de entrada del efecto
    for(int i=0;i<(max_delay);i++)
    {
        memory_left.push_back(0);
        memory_right.push_back(0);
    }
}

void eco_simple::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<this->len;i++)
    {
        float delay_l;
        float delay_r;
        //el valor de entrada actual entra a la memoria, pierdo el valor mas viejo
        memory_left.pop_back();
        memory_left.push_front(curr_left[i].real());
        if(n_channels==2)
        {
            memory_right.pop_back();
            memory_right.push_front(curr_right[i].real());

        }
        for(int j=0;j<echoes;j++)//for donde se agrega la cantidad deseada de ecos
        {
            delay_l=memory_left[(j+1)*max_delay/echoes];//obtengo el j-esimo eco deseado
            curr_left[i]=curr_left[i]+(float)pow(this->g,j)*delay_l;//agrego al eco deseado con un factor de atenuacion adecuado
            if(n_channels==2)
            {
                delay_r=memory_right[(j+1)*max_delay/echoes];
                curr_right[i]=curr_right[i]+(float)pow(this->g,j)*delay_r;
            }
        }

    }
};

void eco_simple::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for( int i=0; i<len; i++ )
    {
        out[2*i] = curr_left[i].real();//actualizo vector out de salida
        if(n_channels==2) out[2*i+1] = curr_right[i].real();
    }

}