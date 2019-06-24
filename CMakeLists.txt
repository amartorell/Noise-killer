cmake_minimum_required(VERSION 3.14)
project(ej8norealtime)

set(CMAKE_CXX_STANDARD 14)

add_executable(ej8norealtime main.cpp AudioFile.cpp fft.cpp effects/noise_kill.cpp effects/generic_effect.cpp effects/effect_factory.cpp effects/flanger.cpp effects/eco_simple.cpp effects/eco_simple.h effects/reverb_pln.cpp effects/reverb_pln.h effects/reverb_pb.cpp effects/reverb_pb.h effects/vibrato.cpp effects/vibrato.h effects/reverb_cmp.cpp effects/reverb_cmp.h effects/no_effect.cpp effects/no_effect.h effects/reverb_allp.cpp effects/reverb_allp.h effects/reverb_conv.cpp effects/reverb_conv.h)