#include <iostream>
#include "effects/generic_effect.h"
#include "effects/effect_factory.h"
#include "AudioFile.h"
#include <string>
#define SAMPLES_PER_WINDOW 128

EFFECT_TYPE hashit (int const& in,data& d);

int main()
{
    AudioFile<double> audioFile;
    audioFile.load ("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\test3.wav");//abro el wav que quiero leer
    int sampleRate = audioFile.getSampleRate();//guardo parámetros del archivo (frecuencia de sampleo)
    int bitDepth = audioFile.getBitDepth();//(bitdepth)
    int numSamples = audioFile.getNumSamplesPerChannel();//cantidad de muestras
    int numChannels = audioFile.getNumChannels();//cantidad de canales
    data in_data;
    generic_effect * effect =effect_factory::newEffect(hashit(7,in_data));//Creo el efecto deseado
    effect->init(SAMPLES_PER_WINDOW,sampleRate,in_data);//lo inicializo

    std::vector<std::complex<float>> left;//arreglos temporarios donde se guardaran las muestras para pasar al efecto deseado
    std::vector<std::complex<float>> right;//uno para el auricular derecho y otro para el izquierdo (stereo)
    int n_windows=numSamples/SAMPLES_PER_WINDOW;//calculo la cantidad de ventanas requeridas
    if(numSamples%SAMPLES_PER_WINDOW!=0)//en caso de no tener una cantidad entera, agrego una ventana que va a ser rellenada con 0s
        n_windows++;
    float * out;
    if(numChannels==1)
    {out=new float[n_windows*SAMPLES_PER_WINDOW];}
    else
        {out=new float[2*n_windows*SAMPLES_PER_WINDOW];}//sabiendo la cantidad de muestras que voy a tener genero el vector donde se guardaran las muestras
    for (int i = 0; i < n_windows; i++)//recorriendo ventana por ventana
    {
        for(int j=0;j<SAMPLES_PER_WINDOW;j++)//guardo las muestras en cada ventana
        {
            if(j+SAMPLES_PER_WINDOW*i<numSamples)//si es parte de las muestras originales solo las guardo
            {

                left.emplace_back(audioFile.samples[0][j+SAMPLES_PER_WINDOW*i]);
                if(numChannels==2) right.emplace_back(audioFile.samples[1][j+SAMPLES_PER_WINDOW*i]);
            }
            else//los espacios libres que quedaron se llenan con ceros
            {
                left.emplace_back(0);
                if(numChannels==2) right.emplace_back(0);
            }

        }
        effect->do_effect(left,right,numChannels);//realizo el efecto por ventana
        effect->update(left,right,&out[i*(2*SAMPLES_PER_WINDOW)],numChannels);//actualizo el vector de salida
        left.clear();//vacío el arreglo donde temporalmente estuvieron las muestras de la ventana para repetir el proceso
        if(numChannels==2) right.clear();
    }
    AudioFile<double>::AudioBuffer buffer;//creo un buffer para el nuevo archivo de audio
    if(numChannels==1){buffer.resize (1); buffer[0].resize (SAMPLES_PER_WINDOW*n_windows);}//le doy al tamaño deseado dependiendo el numero de canales y cantidad de muestras por canal
    else {buffer.resize (2); buffer[0].resize (SAMPLES_PER_WINDOW*n_windows);buffer[1].resize (SAMPLES_PER_WINDOW*n_windows);}
    for(int i=0;i<n_windows*SAMPLES_PER_WINDOW;i++)
    {
        buffer[0][i]=out[2*i];//guardo los valores con el efecto aplicado en el buffer
        if(numChannels==2)
        {
            buffer[1][i]=out[2*i+1];
        }
    }
    delete[] out;//libero memoria de objetos instanciados
    delete effect;
    AudioFile<double> outFile;//genero el archivo de audio de salida
    outFile.setBitDepth (bitDepth);//mantengo el bitdepth del archivo de entrada
    outFile.setSampleRate (sampleRate);//mantengo el samplerate
    bool ok = outFile.setAudioBuffer (buffer);//se le agrega el buffer previo
    outFile.save (std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\")+std::string("out") +std::string(".wav"));//se crea y guarda el archivo deseado
    return 0;
}

EFFECT_TYPE hashit (int const& in,data& d) {
    if (in == 1)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca el número de ecos deseados"<<std::endl;
            std::cin>> d.n_echoes;
            std::cout<<"Introduzca la atenuación deseada por eco"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo entre ecos deseado"<<std::endl;
            std::cin>> d.delay;
        }
        else
        {
            d.n_echoes=3;
            d.g=0.5;
            d.delay=0.3;
        }

        return ECO_SIMPLE;
    }
    else if (in == 2)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca la atenuación deseada por eco"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo entre ecos deseado"<<std::endl;
            std::cin>> d.delay;
        }
        else
        {
            d.g=0.5;
            d.delay=0.2;
        }

        return REVERB_PLN;
    }
    else if (in == 3)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca la atenuación deseada por eco"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo entre ecos deseado"<<std::endl;
            std::cin>> d.delay;
        }
        else
        {
            d.g=0.5;
            d.delay=0.2;
        }
        return REVERB_PB;
    }
    else if (in == 4)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca la el indice de profundiad del efecto"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo maximo deseado"<<std::endl;
            std::cin>> d.delay;
            std::cout<<"Introduzca la frecuencia de modulación deseada"<<std::endl;
            std::cin>> d.fmod;
        }
        else
        {
            d.g=0.4;
            d.delay=0.02;
            d.fmod=0.050;
        }
        return REVERB_CMP;
    }
    else if (in == 5)
    {
        return REVERB_CONV;
    }
    else if (in == 6)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca la el indice de profundiad del efecto"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo maximo deseado"<<std::endl;
            std::cin>> d.delay;
            std::cout<<"Introduzca la frecuencia de modulación deseada"<<std::endl;
            std::cin>> d.fmod;
        }
        else
        {
            d.g=0.7;
            d.delay=0.010;
            d.fmod=0.7;
        }
        return FLANGER;
    }
    else if (in == 7)
    {
        return ROBOT;
    }
    else if (in == 8)
    {
        int inp;
        std::cout<<"Desea configurar el efecto o utilizar el default?Presione 1 como afirmativo,otro numero de lo contrario"<<std::endl;
        std::cin>>inp;
        if(inp==1)
        {
            std::cout<<"Introduzca la el indice de profundiad del efecto"<<std::endl;
            std::cin>> d.g;
            std::cout<<"Introduzca el retardo maximo deseado"<<std::endl;
            std::cin>> d.delay;
            std::cout<<"Introduzca la frecuencia de modulación deseada"<<std::endl;
            std::cin>> d.fmod;
        }
        else
        {
            d.g=0.6;
            d.delay=0.005;
            d.fmod=3;
        }

        return VIBRATO;
    }
    else
    {
        return NO_EFFECT;
    }
}