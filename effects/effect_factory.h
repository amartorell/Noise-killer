#pragma once
#include "generic_effect.h"

enum EFFECT_TYPE { ROBOT, FLANGER, ECO_SIMPLE, REVERB_PLN, REVERB_PB, REVERB_CMP, REVERB_CONV, VIBRATO, GIRDO_3D,NO_EFFECT};

class effect_factory
{
public:
    effect_factory() {};

    static generic_effect* newEffect(EFFECT_TYPE type);
};

