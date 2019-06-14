//
// Created by juan_ on 5/2/2019.
//

#include "reverb_conv.h"
#include <fstream>
#include <iostream>
#define RIR_SAMPLE_RATE (48000) //Frecuencia de muestreo de la medicion de la rta impulsiva de la sala

void reverb_conv::init(int w_len, float fs,data d)
{
    //inicializo el robot generando los vectores auxiliares que voy a utilizar luego
    this->len=w_len;
    this->fs=fs;
    for(int i=0;i<w_len;i++)
    {
        prev_out_right.emplace_back(0);
        prev_out_left.emplace_back(0);
        prev_samples_right.emplace_back(0);
        prev_samples_left.emplace_back(0);
        curr_out_right.emplace_back(0);
        curr_out_left.emplace_back(0);
        aux_left.emplace_back(0);
        aux_right.emplace_back(0);
    }
    std::complex<float> H;
    std::ifstream fin;
    fin.open("C:\\Users\\juan_\\CLionProjects\\ejercicio8\\effects\\H_f_booth.dat", std::ios::in);
    if (!fin.good())
    {
        std::cout << "no se pudo abrir el archivo" << std::endl;
    }
    std::string line;
    freq_resp.reserve(200000);
    while (std::getline(fin, line))
    {
        std::stringstream stream(line);
        while (stream >> H)
        {
            freq_resp.push_back(H);
        }
    }
}

void reverb_conv::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
{
    for(int i=0;i<len/2;i++)
    {
        aux_left[i]=prev_samples_left[i+len/2]*hanning(i);
        aux_left[i+len/2]=curr_left[i]*hanning(i+len/2);
        if(n_channels==2)
        {
            aux_right[i]=prev_samples_right[i+len/2]*hanning(i);
            aux_right[i+len/2]=curr_right[i]*hanning(i+len/2);
        }

    }
    do_conv(aux_left,aux_left,n_channels);
    do_conv(aux_right,aux_right,n_channels);

    for(int i=0;i<len;i++)
    {
        curr_out_left[i]=curr_left[i]*hanning(i);
        if(n_channels==2)
        {
            curr_out_right[i]=curr_right[i]*hanning(i);
        }
    }
    do_conv(curr_out_left,curr_out_left,n_channels);
    do_conv(curr_out_right,curr_out_right,n_channels);
};

void reverb_conv::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
{
    for(int i=0;i<len;i++)
    {
        out[2 * i] = aux_left[i].real();
        out[2 * i + 1] = aux_right[i].real();
    }

    for (int i = 0; i < len / 2; i++)
    {
        float left_sample = prev_out_left[len / 2 + i].real();
        float right_sample = prev_out_right[len / 2 + i].real();
        out[2 * i] +=  left_sample;
        out[2 * i + 1] += right_sample;
    }

    for (int i = 0; i < len/2; ++i)
    {
        float left_sample = curr_out_left[i].real();
        float right_sample = curr_out_right[i].real();
        out[2 * (i + len / 2) ] +=  left_sample;
        out[2 * (i + len / 2) + 1] += right_sample;
        if((out[2*i] < -1) || (out[2*i] > 1)  || (out[(2*i)+1] < -1) || (out[(2*i)+1] > 1) )
        {
            out[2 * i] = out[2 * i + 1] = 0;
            //std::cout << "Out of range" << std::endl;
        }
    }

    std::swap(curr_left,prev_samples_left);
    std::swap(curr_right,prev_samples_right);
    std::swap(curr_out_left,prev_out_left);
    std::swap(curr_out_right,prev_out_right);
}

float reverb_conv::hanning(int i)
{
    return (0.5-(0.5)*cos(2*M_PI*i/((float)this->len-1)));//le aplico una ventana de hanning a las muestras
};

void reverb_conv::do_conv(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out,int n_channels)
{
    float N = len;    //float porque se usan para dividir
    float N_FFT = freq_resp.size();

    //1) calculo la fft de la ventana
    fft(in, out);

    //2) Multiplico por la respuesta en frecuencia
    for (int i = 0; i < N; i++)
    {
        out[i]= out[i]*freq_resp[(unsigned int)(i*(fs/N)*N_FFT/(RIR_SAMPLE_RATE))];
    }
    //3)obtengo la ventana en tiempo*/
    ifft(out, in);
}