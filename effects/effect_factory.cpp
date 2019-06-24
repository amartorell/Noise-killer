//
// Created by juan_ on 4/29/2019.
//

#include <memory>
#include "effect_factory.h"
#include "noise_kill.h"
#include "flanger.h"
#include "eco_simple.h"
#include "reverb_pln.h"
#include "vibrato.h"
#include "reverb_pb.h"
#include "reverb_cmp.h"
#include "reverb_conv.h"
#include "no_effect.h"

// ----------------------------------------------------------------------------

// createEffect

// ----------------------------------------------------------------------------

generic_effect* effect_factory::newEffect(EFFECT_TYPE shipType) {

    switch(shipType) {

        case NOISE_KILL: return new noise_kill();

        case FLANGER: return new flanger();

        case ECO_SIMPLE: return new eco_simple();

        case REVERB_PLN: return new reverb_pln();

        case REVERB_PB: return new reverb_pb();

        case REVERB_CMP: return new reverb_cmp();

        case REVERB_CONV: return new reverb_conv();

        case VIBRATO: return new vibrato();

        default:       return new no_effect();

    }

}

