#include "Raw.h"

#include "ProcessorKeys.h"

#if USE_RAW_FRONTEND

#define raw_parameter(x, name) raw::PluginParameter<raw::Data<float>::Attribute<x>>(getMainController(), name);

DrumsData::DrumsData(MainController* mc) :
    DataHolderBase(mc)
{
    createModules( mc );
      
    // synth group
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynthGroup::SpecialParameters::UnisonoVoiceAmount>>("UnisonoVoiceAmount", synth_group_id );
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynthGroup::SpecialParameters::UnisonoDetune>>("UnisonoDetune", synth_group_id );
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynthGroup::SpecialParameters::UnisonoSpread>>("UnisonoSpread", synth_group_id );
    addToUserPreset<raw::GenericStorage::Bypassed<false>>("PolyFilterBypass", poly_filter_id);
    
    // arp
    addToUserPreset<raw::GenericStorage::Bypassed<false>>("ArpBypass", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::NumSteps>>("ArpNumSteps", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::NumSteps>>("ArpNumSteps", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::Stride>>("ArpStride", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::Tempo>>("ArpSpeed", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::Direction>>("ArpDirection", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::OctaveRange>>("ArpOctaveRange", arp_id );
    addToUserPreset<raw::GenericStorage::Attribute<Arpeggiator::Parameters::Shuffle>>("ArpShuffle", arp_id );
    addToUserPreset<raw::GenericStorage::SliderPack<0>>("ArpSemitone", arp_id );
    addToUserPreset<raw::GenericStorage::SliderPack<1>>("ArpVelocity", arp_id );
    addToUserPreset<raw::GenericStorage::SliderPack<2>>("ArpLength", arp_id );

    // waveform generator
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::WaveForm1>>("WaveForm1", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::WaveForm2>>("WaveForm2", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::PulseWidth1>>("PulseWidth1", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::PulseWidth2>>("PulseWidth2", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::OctaveTranspose1>>("OctaveTranspose1", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::OctaveTranspose2>>("OctaveTranspose2", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::Detune1>>("Detune1", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::Detune2>>("Detune2", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::Pan1>>("WaveGeneratorPan1", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::Pan2>>("WaveGeneratorPan2", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::Mix>>("WaveGeneratorMix", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Attribute<WaveSynth::SpecialParameters::EnableSecondOscillator>>("EnableSecondOscillator", waveform_generator_id );
    addToUserPreset<raw::GenericStorage::Bypassed<false>>("WaveGeneratorBypass", waveform_generator_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("WaveGeneratorGain", waveform_generator_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("WaveGeneratorPan", waveform_generator_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::VoiceLimit>>("WaveGeneratorVoiceLimit", waveform_generator_id);


    addToUserPreset<raw::GenericStorage::SampleMap>("LoadedMap1",  sampler1_id );
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("Sampler1Gain", sampler1_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("Sampler1Pan", sampler1_id);
    addToUserPreset<raw::GenericStorage::Bypassed<false>>("Sampler1Bypass", sampler1_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("LoadedMap2",  sampler2_id );
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("Sampler2Gain", sampler2_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("Sampler2Pan", sampler2_id);
    addToUserPreset<raw::GenericStorage::Bypassed<false>>("Sampler2Bypass", sampler2_id);

    addToUserPreset<raw::GenericStorage::Table<0>>("VeloTable1",  synth_group_velomod_id );
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Release>>("Release1", synth_group_ahdsr_id);
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Attack>>("Attack1", synth_group_ahdsr_id);
    
    // drums
    addToUserPreset<raw::GenericStorage::SampleMap>("KicksMap", drum_kicks_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("KicksGain", drum_kicks_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("KicksPan", drum_kicks_id);

    
    addToUserPreset<raw::GenericStorage::SampleMap>("SnaresMap", drum_snares_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("SnaresGain", drum_snares_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("SnaresPan", drum_snares_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("HatsMap", drum_hats_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("HatsGain", drum_hats_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("HatsPan", drum_hats_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("ClapsMap", drum_claps_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("ClapsGain", drum_claps_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("ClapsPan", drum_claps_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("CymbalsMap", drum_cymbals_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("CymbalsGain", drum_cymbals_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("CymbalsPan", drum_cymbals_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("PercMap", drum_perc_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("PercGain", drum_perc_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("PercPan", drum_perc_id);

    addToUserPreset<raw::GenericStorage::SampleMap>("TomsMap", drum_toms_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("TomsGain", drum_toms_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("TomsPan", drum_toms_id);

    
    // muters
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("SynthMuter", midi_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("KicksMuter", kicks_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("SnaresMuter", snare_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("HatsMuter", hats_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("ClapsMuter", claps_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("CymbalsMuter", cymbals_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("PercMuter", perc_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("TomsMuter", toms_muter_id);

    // fx
//    addToUserPreset<raw::GenericStorage::Attribute<ConvolutionEffect::WetGain>>("ReverbWet", convolution_reverb_id);
    addToUserPreset<raw::GenericStorage::Attribute<GainEffect::Width>>("Width", simple_gain_id);
    addToUserPreset<raw::GenericStorage::Attribute<ShapeFX::SpecialParameters::Mix>>("SaturationMix", shape_fx_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::Mix>>("DelayMix", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::FeedbackLeft>>("DelayFdbkL", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::FeedbackRight>>("DelayFdbkR", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::DelayTimeLeft>>("DelayTimeL", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::DelayTimeRight>>("DelayTimeR", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::LowPassFreq>>("DelayLowpass", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::HiPassFreq>>("DelayHipass", delay_id);

    // output
    addToUserPreset<raw::GenericStorage::Attribute<GainEffect::Gain>>("OutputGain", simple_gain_id);
    
    // source key
    addToUserPreset<raw::GenericStorage::SourceKey>("SourceKey", simple_gain_id);
    
    createPluginParameters(mc);
    createMacros(mc);
}

void DrumsData::createModules(MainController* mc)
{
    raw::Builder builder( mc );
    
    auto root = mc->getMainSynthChain();
    
    // global fx
    auto shape = builder.create<hise::ShapeFX>( root, raw::IDs::Chains::FX );
    shape->setId( shape_fx_id );
    ProcessorHelpers::restoreFromBase64String( shape, "329.3ocUQ1qSCCCEE1lPFPLwFirWopFwOBXgzlRgJRahZpPkQSiSyUxMNx1IkxDi79wKBuAfcZpRycxmuy85i+ITvWRkRt.gOa91bJBehcTJImNZAZ7PD9zcpKFsvAMXaNQJowHL1xqPTpa9Z6Kuoa6pLXp27tcFJB5eq2m9PYfFlzwXcGvdi8R.Z.Pj9zDkNriQ0kgMCVk1B9rFDpyrgckqOeSKz2+3NgGSaZ4b2fRpPRVmyfrUM7ee3IBjUq+JI4d2Yz3hkzCCreghupoqpo7g0fZbVdg5P5PAT1ZzIvGstOUOVi.lReVNz.a8XLn3hHEQQ0NVC3waiR4azgZY6fdEjv6L5NQDmwMq5gPdo.KNb+2kTuSy3EJ8MbBQILYaOsXcDuPrj5kRxxnL8laiOBYFsR2ynMGgHZVbk3OcUa5Xz3ZSm8ln+Ipg90D");
    
    auto delay = builder.create<hise::DelayEffect>( root, raw::IDs::Chains::FX );
    delay->setId( delay_id );
    ProcessorHelpers::restoreFromBase64String( delay, "253.3ocYPFjSCCCDEcLgH.wVVvwnQ8.zn1PEH0hhpiXua7PiEIdB1Npja.2udQ3F.woMsQhY0+8+5OikSMTNZsjAX2m0Vi.6lvDrTzBuj.raOpif4s0BqEk.iEzakopvU36Nfc20P+7X74fMpcEiRdHdIhxsh7OF0Hd5zCyF7GWnOXEsOs6fKM3mm2y2GheV8OWHIds5qKH.YXUMwa04WL+YFK3IoxQFtS3PKvBlSxVdAsW2oCif2TV01R7HvoRxql.vhBUoLc3Sx1sqMTiSo2sV3L96F9ZSEmZL43hBgVikcKOjcE3q1yS7r+QvQsrG9saNEF4Y1ovngP3Oxa5YZB");
    delay->setAttribute(hise::DelayEffect::Parameters::LowPassFreq, 2000.f, dontSendNotification);

    auto conv = builder.create<hise::ConvolutionEffect>( root, raw::IDs::Chains::FX );
    conv->setId( convolution_reverb_id );
//    ProcessorHelpers::restoreFromBase64String( conv, "341.3ocUQsjSCCCD0l1tfErohC.hC.p8D.p4CTTosJI.B1fbiGkXgimHamVhPrmiE2AtHbCf31FQpWMu2a97FOK0XJXLnlPGlTWBD5IC7P0ZTVYEnhL0mPOsKyYQvZPuhLotjYL.mPo8700WyDJB839j8uGA6gTO80LlETo0cyZZQYkz.y.UlM+egetb4NaMUUVY6xeuAlvReMSiUJdRtFX7CKC3fjcvLtQ30oGe98U9rhRgJqaNggI6V9NTBILmUzvc9f2WFs31.ujWBWLyOH5i81dQInYWrgslT31zATWcEr2bgCelRjHVFaYZaqliHPwa0o8B3BKpaxwBFBs+DjWGmiaZZVuAiIOHLhURXGHFknKZDIDkb2+tKl3kKj7ksGQSyPhvl6jJ6NlUKbVYdUQLVoSAublRARia7GQbktEOp0cwfhuE7ayau3XGltWbbqH4OnqNLVL");

    ProcessorHelpers::restoreFromBase64String( conv, "336.3ocUQEjSCCCDzl1bfCbAwC.wC.0xG.TSRoEUZiRBf3DxMdUhEN1Q1NsMBwENwyh+.eD9APbShHcOsyL6N6tZCTxDPqkJD9z3pB.gOwwUJ1H4kFlTfl6gvm0m47PXCnVilTUPzZfhv3AdppaILABe7PTa7DXNj54uVPLfHopeUyyKJ4ZXAHRMY+K7y0AMq0bQQooO+CZXBI40TkrTPiyT.gdXa.E3jClwLlaOO976a7H4ELQZ+ZlNMt436Qw3vRRdM2ENuEDt5Ne23WltZgme36sq8LBme0kaIaP41K0Aa6Kmryl9wtgHtTVDYHJSmlkvWP6f3A9TlQppqw.5Z3DIsJJSts1rANiQOxzr0bnADI4Ra1HDxMiwoAcONcsSgx5eiH8dhQwrieYYdjrTk.tYDg.3Z6HOBYacOdT2JDAB5dvu0Qq3XKF2JNtSD8Gk+oXG");
    
    auto gain = builder.create<hise::GainEffect>( root, raw::IDs::Chains::FX );
    gain->setId( simple_gain_id );
    gain->setAttribute(hise::GainEffect::Parameters::Width, 100, dontSendNotification);
        
    auto limiter = builder.create<hise::MdaLimiterEffect>( root, raw::IDs::Chains::FX );
    limiter->setId( limiter_id );
    ProcessorHelpers::restoreFromBase64String( limiter, "242.3ocMOtjSCCCDFdLsQhxZN.bDZNAQzBHg3UotpqXAtwivV3ZGYOQPXE2fdm3HfD66dj3J.1AmY078+OOW3c0XH37.6vUcMHvlTbsdqlPOb4Y.6nApDl00HBATBL1nUJOFTwhGC.r+si+o5tVpokxJu+886qVhFTDvrzi693qpSIRT+bV4jG18Y0UVbnh9fM5bolbdNIHL.rwybxNtx8hMZUTBq0A8FC9OvcFWJaJbgyHSWVJGlqzF4hgGKDm5RWKosOcif75WAVwssa4tVeMNWIrVzDWTA6.H0ZOOMwoygiVYO7aLxlkIlkMKGLg+.vf8YoC");
    
    // synth group
    auto synthGroup = builder.create<ModulatorSynthGroup>( root );
    synthGroup->setId( synth_group_id );
    
    // velocity modulator
    auto velo = builder.create<hise::VelocityModulator>( synthGroup, raw::IDs::Chains::Gain );
    velo->setAttribute(VelocityModulator::UseTable, 1.0f, dontSendNotification );
    velo->setId( synth_group_velomod_id );
    ProcessorHelpers::restoreFromBase64String( velo, "202.3ocSPErhBCDCMwZAWuu28hmDDU7hmVPGOzCKakpderSV5.CMRynR+q2OgclJULGBu2ijWdj7FtjDga.bzw1qDfiSOSNtz5agLEfe9hN4a1byo8byRXa6UsHjAPLIq1S0Rbd7igPW82WmD5n9hidWKq9N03iK0qAfhJsWHWvZ5c49a14gR60.NMc054cUt5fZ8t.39Og1uyhZadxAbvdiMDwBu1SBfIaYSaQE+nNfSWBmshsKVQRA63HZA.6prNSd+yPBQ3e.J55Q6A");

    // remove default Simple Envelope
    auto envelope = builder.find<hise::SimpleEnvelope>("DefaultEnvelope").getProcessor();
    builder.remove<SimpleEnvelope>(envelope);
        
    // add ahdsr
    auto ahdsr = builder.create<hise::AhdsrEnvelope>( synthGroup, raw::IDs::Chains::Gain );
    ahdsr->setId( synth_group_ahdsr_id );
    ahdsr->setAttribute( AhdsrEnvelope::Attack, 0, dontSendNotification );
    ahdsr->setAttribute( AhdsrEnvelope::Release, 1234, dontSendNotification );
    
    // add midi muter
    auto midimuter = builder.create<hise::MuteAllScriptProcessor>( synthGroup, raw::IDs::Chains::Midi );
    midimuter->setId( midi_muter_id );
    midimuter->setAttribute( MuteAllScriptProcessor::Parameters::IgnoreNotes, 1, dontSendNotification);
    
    // add arpeggiator
    auto arpeggiator = builder.create<hise::Arpeggiator>( synthGroup, raw::IDs::Chains::Midi);
    arpeggiator->setId( arp_id );
    ProcessorHelpers::restoreFromBase64String(arpeggiator, "468.3ocqT98SaCCDG2FvZBgJTplzdcuOoJXU6g81HsUZP2FQ3Jzd0M9ZiEt1gjK.4+9Ym1t0eLU4fvuD+8r8m6qubxw41DnnvlSnGNtJCHzVrqxyfYyTBzE85AD5oqG4RRTUlnn.jDJ8.5gCkJWTNJPnvwHxJq3o1mMt4rKI2qJTSzvBA2ps9YWPH8SUZY7pbWPbQrFDLHgP63mla0tsh0N5TFOIWkgQkHZMDkzGZgKVF5IgtzswiOhrZD.iVr6fB.2DAit2iy0JIjWe7yX+pbNGgrkw1xCe7ag.4DlmPsOZvkXM.sqAvePskMXTZfkAGAaNNBpZdwbyKRF.xQF6j.pDsWBnuc9Daj8kZDcXb3wRvj.+MbXWl0rQK1sIn3I3NgYFz7+oGy3okSmpgWWG0IrgFgqcerZu.NZAfNaj+XQxC0PduqLLWM1Zf0VXGZRAJHzKX89b2FLZfItGz1DEVsqIXz2ssAl9onqbetYP2t8Jic54d8WG4z+NKd05icOlDpA5v9AXlgoAk9t4d7u3S+2ezmtZcOudZsF85uby.RXchmy5mJLFPyAMj3eFb+Mh+WHefcaIlUhuAnNm8y3gtmXyWA6ePNHXHm4gLzH2AQaOh+vqMl48");
    arpeggiator->setBypassed( true );
    
    // add filter
    auto filter = builder.create<hise::PolyFilterEffect>( synthGroup, raw::IDs::Chains::FX);
    filter->setId( poly_filter_id );
    ProcessorHelpers::restoreFromBase64String(filter, "368.3oc0SFzRCCCEGOw0.pGDUPQusKdRP1FBhm1baNYfhcr4tm09jFHzTSx1n5kczOD9sxuH6ifIsasNYhCTA8cnj26k9xu+8epqT3AJkPhvazKNBP3cItBdbTfHj40hw0fD0tooKIMoLpdbDUo.eDFW3JJKzzyAMKZIgGFBgdwYEe90Zcx2wzp2H7g77Cp0YHkyzy2+jWdZxE0YQBNU1NTCgp7dIAdsK8YZgrqlpAEBWntvOtafXrAiBjxn9LEa.GRS5J3B6pRHTi.F22ctXUlA43lKcmTouMwP2PN0L+FAVkYE99jLQUbValHbguBKgzoU+HoNqFosDbe6T+Dpwui50SodSRefK7rGuk28xRKlolJeMt2ofdzDdxq0NbDH01WJ2.ZBdrA.eQabZ04mYxLZR0TD9HRkSOIId75X4YMLKFcq4w8GaqcdZ9OmghVQ+bGh8R6ukUVZoVY4uAuGRl8+PQ68v+ObuEoye.XeCXSUIEI");
    
    // add velocity mod for filter
    auto veloFilter = builder.create<hise::VelocityModulator>( filter, hise::PolyFilterEffect::FrequencyChain);
    veloFilter->setId( poly_filter_velo_mod_id);
    ProcessorHelpers::restoreFromBase64String(veloFilter, "203.3ocUPErhBCDCMQsf6d26dwSKHprvhmDp0C8vxJTq30wNQ5.CMRynR+q8SvY5REMGBu2ijWdjs0bAIBWC3vcMmI.+LZOY4BiqARS.bzS53eY8Eqxw0Kf3lyJQHMfX+zJGUIg4wOF.s08U4BsSczRupkVckpcgk5z.HgJLGIq252Fs6lsdjnbJ.mDs36os0g77Y+r1Ct9muc5qf1x+4.1ai13iXlS4HAv9wrtIqjuU4wQyg8FwzFq.Iisb.MCf0kFqda2yP7g3AzRqHcK");
    veloFilter->setAttribute(hise::VelocityModulator::SpecialParameters::DecibelMode, 1, dontSendNotification);

    // Sampler1 module
    auto sampler1 = builder.create<ModulatorSampler>( synthGroup );
    sampler1->setId( sampler1_id );
    sampler1->setBypassed( true );
    
    // Sampler2 module
    auto sampler2 = builder.create<ModulatorSampler>( synthGroup );
    sampler2->setId( sampler2_id );
    sampler2->setBypassed( true );

    // Waveform Generator
    auto waveformGenerator = builder.create<WaveSynth>( synthGroup );
    waveformGenerator->setId( waveform_generator_id );
    waveformGenerator->setBypassed( true );
    
    // Drums
    addDrumSampler( drum_kicks_id, kicks_muter_id, builder, root, mc, "Pancake_Kicks" );
    addDrumSampler( drum_snares_id, snare_muter_id, builder, root, mc, "Pancake_Snares" );
    auto hats = addDrumSampler( drum_hats_id, hats_muter_id, builder, root, mc, "Pancake_Hats" );
    auto pitch = builder.create<hise::VelocityModulator>( hats, raw::IDs::Chains::Pitch );
    pitch->setId( hats_pitch_id );
    ProcessorHelpers::restoreFromBase64String(pitch, "193.3ocSOsjBBCDCMo0JT26dOB5BWKTqK5BAgpteZm.cfgIklQkda7b30vKhGAmJVw.Adu748RNzw0jHbGfoG6aI.mkblrbsw2CE4.N+GcwdVewp7b2ZHquUIBoADiKbdxICyioS..t+b5iMYlV1pBphQmD5npxReaGhWaJbWoN+v9i0.HmpMUjM3B8e4Q6+nQtxq.LJIj6zlvoT5UdR.LNi08kM7MW.mrBNaDyGOGHkrkGPKAXaiwpOL9zRP+2.kY4PlA");
    pitch->setIntensity(0.75/12.0);

    addDrumSampler( drum_toms_id, toms_muter_id, builder, root, mc, "Pancake_Toms" );
    addDrumSampler( drum_perc_id, perc_muter_id, builder, root, mc, "Pancake_Perc" );
    addDrumSampler( drum_claps_id, claps_muter_id, builder, root, mc, "Pancake_Claps" );
    
    // make cymbals use a release instead of one-shot
    auto cymbals = addDrumSampler( drum_cymbals_id, cymbals_muter_id, builder, root, mc, "Pancake_Cymbals" );
    cymbals->setAttribute( hise::ModulatorSampler::Parameters::OneShot, 0, dontSendNotification);
    auto simpleEnvelope = ProcessorHelpers::getFirstProcessorWithNameSubstring(cymbals, "DefaultEnvelope");
    simpleEnvelope->setAttribute( hise::SimpleEnvelope::SpecialParameters::Attack, 0, dontSendNotification);
    simpleEnvelope->setAttribute( hise::SimpleEnvelope::SpecialParameters::Release, 500, dontSendNotification);
    simpleEnvelope->setAttribute( hise::SimpleEnvelope::SpecialParameters::LinearMode, true, dontSendNotification);
}

void DrumsData::createPluginParameters(MainController *mc)
{
    auto handler = mc->getMacroManager().getMidiControlAutomationHandler();

    auto p1 = new raw::PluginParameter<raw::Data<float>::Macro<MacroIndexes::Reverb>>(getMainController(), "reverb");
    p1->setup(raw::IDs::UIWidgets::Slider, convolution_reverb_id, { 0.f, 1.f, 1.0/127.0 }, 0.5f);
    addParameter(p1);
    
    // MIDI CC handled by Macro for Reverb
    
    auto p2 = new raw_parameter(DelayEffect::Parameters::Mix, "delay");
    p2->setup(raw::IDs::UIWidgets::Slider, delay_id, { 0.f, 0.5f, 0.01f }, 0.1f);
    addParameter(p2);
    
    // add MIDI CC for delay
    auto proc = ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), delay_id);
    handler->addMidiControlledParameter(proc, DelayEffect::Parameters::Mix, { 0.f, 0.5f, 0.01f }, -1);
    handler->setUnlearndedMidiControlNumber(15, sendNotification);
    
    auto p3 = new raw_parameter(hise::ShapeFX::SpecialParameters::Mix, "drive");
    p3->setup(raw::IDs::UIWidgets::Slider, shape_fx_id, { 0.f, 0.75f, 0.01f }, 0.5f);
    addParameter(p3);
    
    // add MIDI CC for drive
    proc = ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), shape_fx_id);
    handler->addMidiControlledParameter(proc, hise::ShapeFX::SpecialParameters::Mix, { 0.f, 0.75f, 0.01f }, -1);
    handler->setUnlearndedMidiControlNumber(14, sendNotification);

        auto p4 = new raw_parameter( hise::GainEffect::Parameters::Width, "width");
    p4->setup(raw::IDs::UIWidgets::Slider, simple_gain_id, { 0.f, 200.f, 0.1f }, 100.f);
    addParameter(p4);
    
    // add MIDI CC for width
    proc = ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), simple_gain_id);
    handler->addMidiControlledParameter(proc, hise::GainEffect::Parameters::Width, { 0.f, 200.f, 0.1f }, -1);
    handler->setUnlearndedMidiControlNumber(17, sendNotification);

    auto p5 = new raw_parameter( hise::AhdsrEnvelope::SpecialParameters::Attack, "attack");
    p5->setup(raw::IDs::UIWidgets::Slider, synth_group_ahdsr_id, { 0.f, 20000.f, 1.f }, 10000.0f);
    addParameter(p5);
    
    // add MIDI CC for attack
    proc = ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), synth_group_ahdsr_id);
    handler->addMidiControlledParameter(proc, hise::AhdsrEnvelope::SpecialParameters::Attack, { 0.f, 20000.f, 1.f }, -1);
    handler->setUnlearndedMidiControlNumber(18, sendNotification);

    auto p6 = new raw_parameter( hise::AhdsrEnvelope::SpecialParameters::Release, "release");
    p6->setup(raw::IDs::UIWidgets::Slider, synth_group_ahdsr_id, { 80.f, 20000.f, 1.f }, 10000.0f);
    addParameter(p6);
    
    // add MIDI CC for release
    proc = ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), synth_group_ahdsr_id);
    handler->addMidiControlledParameter(proc, hise::AhdsrEnvelope::SpecialParameters::Release, { 80.f, 20000.f, 1.f }, -1);
    handler->setUnlearndedMidiControlNumber(19, sendNotification);
}

void DrumsData::createMacros(MainController* mc)
{
    // reverb
    mc->getMacroManager().setEnableMacroOnFrontend(true);
    mc->getMacroManager().setMidiControllerForMacro(MacroIndexes::Reverb, 16);
    
    auto wetRange = NormalisableRange<double>( -100.f, -10.f, 0.1f );
    wetRange.setSkewForCentre(-20.f);
    mc->getMacroManager().getMacroChain()->addControlledParameter(MacroIndexes::Reverb, convolution_reverb_id, ConvolutionEffect::WetGain, "reverb wet", wetRange);
    
    auto dryRange = NormalisableRange<double>( -10.f, 0.f, 0.1f );
    dryRange.setSkewForCentre(-2.f);
    mc->getMacroManager().getMacroChain()->addControlledParameter(MacroIndexes::Reverb, convolution_reverb_id, ConvolutionEffect::DryGain, "reverb dry", dryRange, true, true);
    
    auto handler = mc->getMacroManager().getMidiControlAutomationHandler();
    handler->addMidiControlledParameter(mc->getMainSynthChain(), 0, {0, 1}, MacroIndexes::Reverb);
    handler->setUnlearndedMidiControlNumber(16, sendNotification);
}

hise::ModulatorSampler* DrumsData::addDrumSampler( const std::string& id, const std::string& muterId, raw::Builder& builder,  hise::ModulatorSynthChain* root, MainController* mc, String mapName )
{
    auto drum = builder.create<hise::ModulatorSampler>( root );
    drum->setId( id );
    drum->setAttribute( hise::ModulatorSampler::Parameters::OneShot, 1, dontSendNotification);
    
    auto simpleEnvelope = ProcessorHelpers::getFirstProcessorWithNameSubstring(drum, "DefaultEnvelope");
    simpleEnvelope->setAttribute( hise::SimpleEnvelope::SpecialParameters::Attack, 0, dontSendNotification);

    
    auto muter = builder.create<hise::MuteAllScriptProcessor>( drum, raw::IDs::Chains::Midi );
    muter->setId( id + "Muter" );
    muter->setAttribute( MuteAllScriptProcessor::Parameters::IgnoreNotes, 0, dontSendNotification);
    
    auto velo = builder.create<hise::VelocityModulator>( drum, raw::IDs::Chains::Gain );
    velo->setAttribute(VelocityModulator::UseTable, 1.0f, dontSendNotification );
    velo->setId( id + "Velo" );
    ProcessorHelpers::restoreFromBase64String( velo, "202.3ocSPErhBCDCMwZAWuu28hmDDU7hmVPGOzCKakpderSV5.CMRynR+q2OgclJULGBu2ijWdj7FtjDga.bzw1qDfiSOSNtz5agLEfe9hN4a1byo8byRXa6UsHjAPLIq1S0Rbd7igPW82WmD5n9hidWKq9N03iK0qAfhJsWHWvZ5c49a14gR60.NMc054cUt5fZ8t.39Og1uyhZadxAbvdiMDwBu1SBfIaYSaQE+nNfSWBmshsKVQRA63HZA.6prNSd+yPBQ3e.J55Q6A");

    if ( mapName.isEmpty() || !FrontendHandler::checkSamplesCorrectlyInstalled())
    {
        return drum;
    }
    
    auto pool = mc->getCurrentSampleMapPool();
    auto references = pool->getListOfAllReferences(true);
    
    bool foundIt = false;
    for ( const auto& ref : references )
    {
        auto str = ref.getReferenceString();
        if (str.contains(mapName))
        {
            drum->loadSampleMap(ref);
            foundIt = true;
            break;
        }
    }
    
    jassert( foundIt );
    
    return drum;
}


/** This method needs to be implemented and your initial preset structure must be defined here. */
raw::DataHolderBase* FrontendProcessor::createPresetRaw()
{
	return new DrumsData(this);
}


#endif
