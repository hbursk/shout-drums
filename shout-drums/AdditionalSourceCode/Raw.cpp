#include "Raw.h"

#include "ProcessorKeys.h"

#if USE_RAW_FRONTEND

#define raw_parameter(x, name) raw::PluginParameter<raw::Data<float>::Attribute<x>>(getMainController(), name);

DrumsData::DrumsData(MainController* mc) :
    DataHolderBase(mc)
{
    createModules( mc );
      
    // synth and sampler
    addToUserPreset<raw::GenericStorage::SampleMap>("LoadedMap1",  sampler_id );
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Gain>>("SamplerGain", sampler_id);
    addToUserPreset<raw::GenericStorage::Attribute<ModulatorSynth::Parameters::Balance>>("SamplerPan", sampler_id);

    addToUserPreset<raw::GenericStorage::Table<0>>("VeloTable1",  sampler_velomod_id );
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Release>>("Release1", sampler_ahdsr_id);
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Attack>>("Attack1", sampler_ahdsr_id);
    
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
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("SamplerMuter", midi_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("KicksMuter", kicks_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("SnaresMuter", snare_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("HatsMuter", hats_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("ClapsMuter", claps_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("CymbalsMuter", cymbals_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("PercMuter", perc_muter_id);
    addToUserPreset<raw::GenericStorage::Attribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>("TomsMuter", toms_muter_id);

    // fx
    addToUserPreset<raw::GenericStorage::Attribute<ConvolutionEffect::WetGain>>("ReverbWet", convolution_reverb_id);
    addToUserPreset<raw::GenericStorage::Attribute<GainEffect::Width>>("Width", simple_gain_id);
    addToUserPreset<raw::GenericStorage::Attribute<ShapeFX::SpecialParameters::Mix>>("SaturationMix", shape_fx_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::Mix>>("DelayMix", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::FeedbackLeft>>("DelayFdbkL", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::FeedbackRight>>("DelayFdbkR", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::DelayTimeLeft>>("DelayTimeL", delay_id);
    addToUserPreset<raw::GenericStorage::Attribute<DelayEffect::Parameters::DelayTimeRight>>("DelayTimeR", delay_id);
    
    // output
    addToUserPreset<raw::GenericStorage::Attribute<GainEffect::Gain>>("OutputGain", simple_gain_id);
    
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

    auto conv = builder.create<hise::ConvolutionEffect>( root, raw::IDs::Chains::FX );
    conv->setId( convolution_reverb_id );
    ProcessorHelpers::restoreFromBase64String( conv, "341.3ocUQsjSCCCD0l1tfErohC.hC.p8D.p4CTTosJI.B1fbiGkXgimHamVhPrmiE2AtHbCf31FQpWMu2a97FOK0XJXLnlPGlTWBD5IC7P0ZTVYEnhL0mPOsKyYQvZPuhLotjYL.mPo8700WyDJB839j8uGA6gTO80LlETo0cyZZQYkz.y.UlM+egetb4NaMUUVY6xeuAlvReMSiUJdRtFX7CKC3fjcvLtQ30oGe98U9rhRgJqaNggI6V9NTBILmUzvc9f2WFs31.ujWBWLyOH5i81dQInYWrgslT31zATWcEr2bgCelRjHVFaYZaqliHPwa0o8B3BKpaxwBFBs+DjWGmiaZZVuAiIOHLhURXGHFknKZDIDkb2+tKl3kKj7ksGQSyPhvl6jJ6NlUKbVYdUQLVoSAublRARia7GQbktEOp0cwfhuE7ayau3XGltWbbqH4OnqNLVL");
    
    
    auto gain = builder.create<hise::GainEffect>( root, raw::IDs::Chains::FX );
    gain->setId( simple_gain_id );
    gain->setAttribute(hise::GainEffect::Parameters::Width, 100, dontSendNotification);
        
    auto limiter = builder.create<hise::MdaLimiterEffect>( root, raw::IDs::Chains::FX );
    limiter->setId( limiter_id );
    ProcessorHelpers::restoreFromBase64String( limiter, "242.3ocMOtjSCCCDFdLsQhxZN.bDZNAQzBHg3UotpqXAtwivV3ZGYOQPXE2fdm3HfD66dj3J.1AmY078+OOW3c0XH37.6vUcMHvlTbsdqlPOb4Y.6nApDl00HBATBL1nUJOFTwhGC.r+si+o5tVpokxJu+886qVhFTDvrzi693qpSIRT+bV4jG18Y0UVbnh9fM5bolbdNIHL.rwybxNtx8hMZUTBq0A8FC9OvcFWJaJbgyHSWVJGlqzF4hgGKDm5RWKosOcif75WAVwssa4tVeMNWIrVzDWTA6.H0ZOOMwoygiVYO7aLxlkIlkMKGLg+.vf8YoC");
    
    // Sampler module
    auto sampler = builder.create<ModulatorSampler>( root );
    sampler->setId( sampler_id );
    
    // velocity modulator
    auto velo = builder.create<hise::VelocityModulator>( sampler, raw::IDs::Chains::Gain );
    velo->setAttribute(VelocityModulator::UseTable, 1.0f, dontSendNotification );
    velo->setId( sampler_velomod_id );
    ProcessorHelpers::restoreFromBase64String( velo, "202.3ocSPErhBCDCMwZAWuu28hmDDU7hmVPGOzCKakpderSV5.CMRynR+q2OgclJULGBu2ijWdj7FtjDga.bzw1qDfiSOSNtz5agLEfe9hN4a1byo8byRXa6UsHjAPLIq1S0Rbd7igPW82WmD5n9hidWKq9N03iK0qAfhJsWHWvZ5c49a14gR60.NMc054cUt5fZ8t.39Og1uyhZadxAbvdiMDwBu1SBfIaYSaQE+nNfSWBmshsKVQRA63HZA.6prNSd+yPBQ3e.J55Q6A");
    
    // Remove default Simple Envelope
    auto envelope = builder.find<hise::SimpleEnvelope>("DefaultEnvelope1").getProcessor();
    builder.remove<SimpleEnvelope>(envelope);
        
    auto ahdsr = builder.create<hise::AhdsrEnvelope>( sampler, raw::IDs::Chains::Gain );
    ahdsr->setId( sampler_ahdsr_id );
    ahdsr->setAttribute( AhdsrEnvelope::Attack, 0, dontSendNotification );
    ahdsr->setAttribute( AhdsrEnvelope::Release, 1234, dontSendNotification );
    
    auto midimuter = builder.create<hise::MuteAllScriptProcessor>( sampler, raw::IDs::Chains::Midi );
    midimuter->setId( midi_muter_id );
    midimuter->setAttribute( MuteAllScriptProcessor::Parameters::IgnoreNotes, 1, dontSendNotification);
    
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
    auto p1 = new raw_parameter(ConvolutionEffect::WetGain, "reverb");
    p1->setup(raw::IDs::UIWidgets::Slider, convolution_reverb_id, { -100.f, -20.f, 0.1f }, -30.f);
    addParameter(p1);
    
    auto p2 = new raw_parameter(DelayEffect::Parameters::Mix, "delay");
    p2->setup(raw::IDs::UIWidgets::Slider, delay_id, { 0.f, 0.5f, 0.01f }, 0.1f);
    addParameter(p2);
    
    auto p3 = new raw_parameter(hise::ShapeFX::SpecialParameters::Mix, "drive");
    p3->setup(raw::IDs::UIWidgets::Slider, shape_fx_id, { 0.f, 1.f, 0.01f }, 0.5f);
    addParameter(p3);
    
    auto p4 = new raw_parameter( hise::GainEffect::Parameters::Width, "width");
    p4->setup(raw::IDs::UIWidgets::Slider, simple_gain_id, { 0.f, 200.f, 0.1f }, 100.f);
    addParameter(p4);
    
    auto p5 = new raw_parameter( hise::AhdsrEnvelope::SpecialParameters::Attack, "attack");
    p5->setup(raw::IDs::UIWidgets::Slider, sampler_ahdsr_id, { 0.f, 20000.f, 1.f }, 10000.0f);
    addParameter(p5);

    auto p6 = new raw_parameter( hise::AhdsrEnvelope::SpecialParameters::Release, "release");
    p6->setup(raw::IDs::UIWidgets::Slider, sampler_ahdsr_id, { 80.f, 20000.f, 1.f }, 10000.0f);
    addParameter(p6);
}

void DrumsData::createMacros(MainController* mc)
{
    // reverb
    mc->getMacroManager().setEnableMacroOnFrontend(true);
    mc->getMacroManager().setMidiControllerForMacro(MacroIndexes::Reverb, 1);
    
    auto wetRange = NormalisableRange<double>( -100.f, -10.f, 0.1f );
    wetRange.setSkewForCentre(-20.f);
    mc->getMacroManager().getMacroChain()->addControlledParameter(MacroIndexes::Reverb, convolution_reverb_id, ConvolutionEffect::WetGain, "reverb wet", wetRange);
    
    auto dryRange = NormalisableRange<double>( -10.f, 0.f, 0.1f );
    dryRange.setSkewForCentre(-2.f);
    mc->getMacroManager().getMacroChain()->addControlledParameter(MacroIndexes::Reverb, convolution_reverb_id, ConvolutionEffect::DryGain, "reverb dry", dryRange, true, true);
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
