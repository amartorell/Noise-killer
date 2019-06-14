//
// Created by juan_ on 4/28/2019.
//

#include "robot.h"

void robot::init(int w_len, float fs,data d)
{
    //inicializo el robot generando los vectores auxiliares que voy a utilizar luego
	win_noise = 30;
    this->len=w_len;
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

		noise_mean.emplace_back(0);
		ventana_anteanterior_transformada.emplace_back(0);
		ventana_anterior_transformada.emplace_back(0);
		H_base.emplace_back(0);
		Signal_out.emplace_back(0);
		
    }

}

void robot::do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels)
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
    termminate_noise(aux_left,aux_left,n_channels);
    termminate_noise(aux_right,aux_right,n_channels);
    //aca deberia sumar a la salida los aux
    //aca sumo a las samples del callback anterior
    for(int i=0;i<len;i++)
    {
        curr_out_left[i]=curr_left[i]*hanning(i);
        if(n_channels==2)
        {
            curr_out_right[i]=curr_right[i]*hanning(i);
        }
    }
    //robotify(curr_out_left,curr_out_left,n_channels);
    //robotify(curr_out_right,curr_out_right,n_channels);
};

void robot::update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels)
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
            //std::cout << "Fuera de rango" << std::endl;
        }
    }

    std::swap(curr_left,prev_samples_left);
    std::swap(curr_right,prev_samples_right);
    std::swap(curr_out_left,prev_out_left);
    std::swap(curr_out_right,prev_out_right);
}

float robot::hanning(int i)
{
    return (0.5-(0.5)*cos(2*M_PI*i/((float)this->len-1)));//le aplico una ventana de hanning a las muestras
};

void robot::robotify(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out,int n_channels)
{
    fft(in,out);//calculo la fft de la ventana actual
	if (win_noise > 0)  // divido a cada 
	{
		for (int i = 0; i < out.size(); i++)  //divido cada elemento por n y se lo sumo elemento a elemento el vector
		{
			out[i] = ((out[i]) / (std::complex<float>(MAX_NOISE_WINDOW)));
			this->noise_mean[i] = ((this->noise_mean[i]) + out[i]);  //hacer que noise mean tenga todos ceros primeros

			this->win_noise--;
		}
	}
	for (int i = 0; i < this->len; i++)
	{

	}
    ifft(out,in);//calculo la ifft de lo obtenido
	
};

void robot::noise_mean_calculator(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels)
{
	fft(in, out);//calculo la fft de la ventana actual
	if (win_noise > 0)  // divido a cada 
	{
		for (int i = 0; i < out.size(); i++)  //divido cada elemento por n y se lo sumo elemento a elemento el vector
		{
			out[i] = ((out[i]) / (std::complex<float>(MAX_NOISE_WINDOW)));
			this->noise_mean[i] = ((this->noise_mean[i]) + out[i]);  //hacer que noise mean tenga todos ceros primeros
			this->win_noise--;
		}
	}
	//for (int i = 0; i < this->len; i++)
	//{

	//}

	ifft(out, in);//calculo la ifft de lo obtenido
};



void robot::x_mean_calculator(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels)
{
	fft(in, out);
	
	
	for (int i = 0; i < out.size(); i++)
	{
		out[i] = norma_compleja(out[i]);
		this->ventana_anterior_transformada[i] = (((this->ventana_anterior_transformada[i]) + (this->ventana_anteanterior_transformada[i]) + (out[i])) / std::complex<float>(MAX_AVERAGING_WINDOW));
		this->ventana_anteanterior_transformada[i]= (this->ventana_anterior_transformada[i]);
	}
	
	ifft(out, in);


};

void robot::calculate_halfwave_rectification()
{

	for (int i = 0; i < (this->noise_mean.size()); i++)
	{
		(this->H_base[i]) = ((std::complex<float>(1.0)) - (noise_mean[i]) / (ventana_anterior_transformada[i]));
		if(((norma_compleja((this->H_base[i]))).real()) < 0.0001)   //esto es porque el ruido es mas bajo que lo estimado
        {
		    this->H_base[i]=std::complex<float>(0);
            std::cout<<"entro aca"<<i<<std::endl;
        }

		this->H_base[i] = ((norma_compleja((this->H_base[i])) + (this->H_base[i])) / std::complex<float>(2));

	}

}
void robot::calculate_signal_out(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels)
{
	for (int i = 0; i < out.size(); i++)
	{
		out[i] = (this->H_base[i])*(out[i]);
	}

	ifft(out, in);
}
void robot::termminate_noise(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels)
{
	noise_mean_calculator(in, out,0);
	x_mean_calculator(in, out,0);
	calculate_halfwave_rectification();
	calculate_signal_out(in, out,0);
}




