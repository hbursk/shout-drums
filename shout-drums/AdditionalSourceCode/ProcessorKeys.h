//
//  ProcessorKeys.h
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

const char sampler_id[] = "Sampler";
const char sampler_velomod_id[] = "Velocity Modulator1";
const char sampler_ahdsr_id[] = "AHDSR Envelope1";

const char convolution_reverb_id[] = "Convolution Reverb";
const char shape_fx_id[] = "Shape FX1";
const char delay_id[] = "Delay1";
const char limiter_id[] = "Limiter1";
const char simple_gain_id[] = "Simple Gain1";

const char midi_muter_id[] = "MidiMuter1";
const char kicks_muter_id[] = "KicksMuter";
const char snare_muter_id[] = "SnaresMuter";
const char perc_muter_id[] = "PercMuter";
const char claps_muter_id[] = "ClapsMuter";
const char hats_muter_id[] = "HatsMuter";
const char cymbals_muter_id[] = "CymbalsMuter";
const char toms_muter_id[] = "TomsMuter";

const char kicks_velo_id[] = "KicksVelo";
const char snare_velo_id[] = "SnaresVelo";
const char perc_velo_id[] = "PercVelo";
const char claps_velo_id[] = "ClapsVelo";
const char hats_velo_id[] = "HatsVelo";
const char cymbals_velo_id[] = "CymbalsVelo";
const char toms_velo_id[] = "TomsVelo";

const char drum_kicks_id[] = "Kicks";
const char drum_snares_id[] = "Snares";
const char drum_hats_id[] = "Hats";
const char drum_cymbals_id[] = "Cymbals";
const char drum_claps_id[] = "Claps";
const char drum_perc_id[] = "Perc";
const char drum_toms_id[] = "Toms";

const char hats_pitch_id[] = "HatsPitch";

enum MacroIndexes
{
    Drive,
    Delay,
    Reverb,
    Width,
    Attack,
    Release
};

