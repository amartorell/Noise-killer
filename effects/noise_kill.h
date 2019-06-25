//
// Created by juan_ on 4/28/2019.
//

#ifndef EJERCICIO8_NOISE_KILL_H
#define EJERCICIO8_NOISE_KILL_H
#define MAX_NOISE_WINDOW	80
#define MAX_AVERAGING_WINDOW 3.0
#include "generic_effect.h"

class noise_kill: public generic_effect
{
public:
    void init(int w_len, float fs,data d) override ;
    void do_effect(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels) override;
    void update(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,float * out,int n_channels) override;
    float hanning(int i);
    void robotify(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right,int n_channels);
	void noise_mean_calculator(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right, int n_channels);
	void x_mean_calculator(std::vector<std::complex<float>>& curr_left, std::vector<std::complex<float>>& curr_right, int n_channels);

	void calculate_halfwave_rectification();

	void calculate_signal_out(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels);

	void terminate_noise(std::vector<std::complex<float>>& in, std::vector<std::complex<float>>& out, int n_channels=0);

	void reset_stats(void);


    int len;
	int win_noise;


	std::vector<std::complex<float>> noise_mean;
	std::vector<std::complex<float>> ventana_anterior_transformada;			//transfromar
	std::vector<std::complex<float>> ventana_anteanterior_transformada;
	std::vector<std::complex<float>> H_base;
	std::vector<std::complex<float>> Signal_out;
	
    std::vector<std::complex<float>> prev_out_right;
    std::vector<std::complex<float>> prev_out_left;
    std::vector<std::complex<float>> prev_samples_right;
    std::vector<std::complex<float>> prev_samples_left;
    std::vector<std::complex<float>> curr_out_right;
    std::vector<std::complex<float>> curr_out_left;
    std::vector<std::complex<float>> aux_left;
    std::vector<std::complex<float>> aux_right;
    noise_kill(){};


};


#endif //EJERCICIO8_ROBOT_H
