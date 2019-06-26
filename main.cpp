#include <iostream>
#include "effects/generic_effect.h"
#include "effects/effect_factory.h"
#include "AudioFile.h"
#include <string>
#define SAMPLES_PER_WINDOW 512

EFFECT_TYPE hashit (int const& in,data& d);

int main()
{
    AudioFile<double> audioFile;
    audioFile.load ("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\el_gato.wav");//abro el wav que quiero leer
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
    outFile.save (std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\")+std::string("sin_ruido") +std::string(".wav"));//se crea y guarda el archivo deseado


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //SEGUNDA ITERACIÓN
    AudioFile<double> audioFile2;
    audioFile2.load(std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\")+std::string("sin_ruido") +std::string(".wav"));
    int sampleRate_2 = audioFile2.getSampleRate();//guardo parámetros del archivo (frecuencia de sampleo)
    int bitDepth_2 = audioFile2.getBitDepth();//(bitdepth)
    int numSamples_2 = audioFile2.getNumSamplesPerChannel();//cantidad de muestras
    int numChannels_2 = audioFile2.getNumChannels();//cantidad de canales
    data in_data2;
    generic_effect * effect2 =effect_factory::newEffect(hashit(7,in_data2));//Creo el efecto deseado
    effect2->init(SAMPLES_PER_WINDOW,sampleRate_2,in_data2);//lo inicializo


    std::vector<std::complex<float>> left2;//arreglos temporarios donde se guardaran las muestras para pasar al efecto deseado
    std::vector<std::complex<float>> right2;//uno para el auricular derecho y otro para el izquierdo (stereo)
    int n_windows_2=numSamples_2/SAMPLES_PER_WINDOW;//calculo la cantidad de ventanas requeridas
    if(numSamples%SAMPLES_PER_WINDOW!=0)//en caso de no tener una cantidad entera, agrego una ventana que va a ser rellenada con 0s
        n_windows_2++;
    float * out_2;

    if(numChannels_2==1)
    {out_2=new float[n_windows_2*SAMPLES_PER_WINDOW];}
    else
    {out_2=new float[2*n_windows_2*SAMPLES_PER_WINDOW];}//sabiendo la cantidad de muestras que voy a tener genero el vector donde se guardaran las muestras
    for (int i = 0; i < n_windows_2; i++)//recorriendo ventana por ventana
    {
        for(int j=0;j<SAMPLES_PER_WINDOW;j++)//guardo las muestras en cada ventana
        {
            if(j+SAMPLES_PER_WINDOW*i<numSamples_2)//si es parte de las muestras originales solo las guardo
            {

                left2.emplace_back(audioFile2.samples[0][j+SAMPLES_PER_WINDOW*i]);
                if(numChannels==2) right2.emplace_back(audioFile2.samples[1][j+SAMPLES_PER_WINDOW*i]);
            }
            else//los espacios libres que quedaron se llenan con ceros
            {
                left2.emplace_back(0);
                if(numChannels_2==2) right2.emplace_back(0);
            }

        }
        effect2->do_effect(left2,right2,numChannels_2);//realizo el efecto por ventana
        effect2->update(left2,right2,&out_2[i*(2*SAMPLES_PER_WINDOW)],numChannels_2);//actualizo el vector de salida
        left2.clear();//vacío el arreglo donde temporalmente estuvieron las muestras de la ventana para repetir el proceso
        if(numChannels_2==2) right2.clear();
    }

    AudioFile<double>::AudioBuffer buffer2;//creo un buffer para el nuevo archivo de audio
    if(numChannels_2==1){buffer2.resize (1); buffer2[0].resize (SAMPLES_PER_WINDOW*n_windows_2);}//le doy al tamaño deseado dependiendo el numero de canales y cantidad de muestras por canal
    else {buffer2.resize (2); buffer2[0].resize (SAMPLES_PER_WINDOW*n_windows_2);buffer2[1].resize (SAMPLES_PER_WINDOW*n_windows_2);}
    for(int i=0;i<n_windows_2*SAMPLES_PER_WINDOW;i++)
    {
        buffer2[0][i]=out_2[2*i];//guardo los valores con el efecto aplicado en el buffer
        if(numChannels_2==2)
        {
            buffer2[1][i]=out_2[2*i+1];
        }
    }
    std::cout << "Fuera de rango" << std::endl;
    delete[] out_2;//libero memoria de objetos instanciados
    delete effect2;
    AudioFile<double> outFile2;//genero el archivo de audio de salida
    outFile2.setBitDepth (bitDepth_2);//mantengo el bitdepth del archivo de entrada
    outFile2.setSampleRate (sampleRate_2);//mantengo el samplerate
    bool ok2 = outFile2.setAudioBuffer (buffer2);//se le agrega el buffer previo
    outFile2.save (std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\")+std::string("sin_ruido") +std::string(".wav"));//se crea y guarda el archivo deseado


    //tercera iteracion

    AudioFile<double> audioFile3;
    audioFile3.load(std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\")+std::string("sin_ruido") +std::string(".wav"));
    int sampleRate_3 = audioFile3.getSampleRate();//guardo parámetros del archivo (frecuencia de sampleo)
    int bitDepth_3 = audioFile3.getBitDepth();//(bitdepth)
    int numSamples_3 = audioFile3.getNumSamplesPerChannel();//cantidad de muestras
    int numChannels_3 = audioFile3.getNumChannels();//cantidad de canales
    data in_data3;
    generic_effect * effect3 =effect_factory::newEffect(hashit(7,in_data3));//Creo el efecto deseado
    effect3->init(SAMPLES_PER_WINDOW,sampleRate_3,in_data3);//lo inicializo


    std::vector<std::complex<float>> left3;//arreglos temporarios donde se guardaran las muestras para pasar al efecto deseado
    std::vector<std::complex<float>> right3;//uno para el auricular derecho y otro para el izquierdo (stereo)
    int n_windows_3=numSamples_3/SAMPLES_PER_WINDOW;//calculo la cantidad de ventanas requeridas
    if(numSamples%SAMPLES_PER_WINDOW!=0)//en caso de no tener una cantidad entera, agrego una ventana que va a ser rellenada con 0s
        n_windows_3++;
    float * out_3;

    if(numChannels_3==1)
    {out_3=new float[n_windows_3*SAMPLES_PER_WINDOW];}
    else
    {out_3=new float[2*n_windows_3*SAMPLES_PER_WINDOW];}//sabiendo la cantidad de muestras que voy a tener genero el vector donde se guardaran las muestras
    for (int i = 0; i < n_windows_3; i++)//recorriendo ventana por ventana
    {
        for(int j=0;j<SAMPLES_PER_WINDOW;j++)//guardo las muestras en cada ventana
        {
            if(j+SAMPLES_PER_WINDOW*i<numSamples_3)//si es parte de las muestras originales solo las guardo
            {

                left3.emplace_back(audioFile3.samples[0][j+SAMPLES_PER_WINDOW*i]);
                if(numChannels_3==2) right3.emplace_back(audioFile3.samples[1][j+SAMPLES_PER_WINDOW*i]);
            }
            else//los espacios libres que quedaron se llenan con ceros
            {
                left3.emplace_back(0);
                if(numChannels_3==2) right3.emplace_back(0);
            }

        }
        effect3->do_effect(left3,right3,numChannels_3);//realizo el efecto por ventana
        effect3->update(left3,right3,&out_3[i*(2*SAMPLES_PER_WINDOW)],numChannels_3);//actualizo el vector de salida
        left3.clear();//vacío el arreglo donde temporalmente estuvieron las muestras de la ventana para repetir el proceso
        if(numChannels_3==2) right3.clear();
    }

    AudioFile<double>::AudioBuffer buffer3;//creo un buffer para el nuevo archivo de audio
    if(numChannels_3==1){buffer3.resize (1); buffer3[0].resize (SAMPLES_PER_WINDOW*n_windows_3);}//le doy al tamaño deseado dependiendo el numero de canales y cantidad de muestras por canal
    else {buffer3.resize (2); buffer3[0].resize (SAMPLES_PER_WINDOW*n_windows_3);buffer3[1].resize (SAMPLES_PER_WINDOW*n_windows_3);}
    for(int i=0;i<n_windows_3*SAMPLES_PER_WINDOW;i++)
    {
        buffer3[0][i]=out_3[2*i];//guardo los valores con el efecto aplicado en el buffer
        if(numChannels_3==2)
        {
            buffer3[1][i]=out_3[2*i+1];
        }
    }
    std::cout << "Fuera de rango" << std::endl;
    delete[] out_3;//libero memoria de objetos instanciados
    delete effect3;
    AudioFile<double> outFile3;//genero el archivo de audio de salida
    outFile3.setBitDepth (bitDepth_3);//mantengo el bitdepth del archivo de entrada
    outFile3.setSampleRate (sampleRate_3);//mantengo el samplerate
    bool ok3 = outFile3.setAudioBuffer (buffer3);//se le agrega el buffer previo
    outFile3.save (std::string("C:\\Users\\marth\\Documents\\ITBA\\ASSD\\TP4\\noise_killer\\Noise-killer\\")+std::string("el_gato_no_noise") +std::string(".wav"));//se crea y guarda el archivo deseado




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
        return NOISE_KILL;
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