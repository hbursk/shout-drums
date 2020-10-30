#include "Raw.h"

#include "ProcessorKeys.h"

#if USE_RAW_FRONTEND

#define raw_parameter(x, name) raw::PluginParameter<raw::Data<float>::Attribute<x>>(getMainController(), name);

DrumsData::DrumsData(MainController* mc) :
    DataHolderBase(mc)
{
    createModules( mc );
      
    // sampler
    addToUserPreset<raw::GenericStorage::SampleMap>("LoadedMap1",  sampler_id );
    addToUserPreset<raw::GenericStorage::Table<0>>("VeloTable1",  sampler_velomod_id );
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Release>>("Release1", sampler_ahdsr_id);
    addToUserPreset<raw::GenericStorage::Attribute<AhdsrEnvelope::Attack>>("Attack1", sampler_ahdsr_id);
    
    // drums
    addToUserPreset<raw::GenericStorage::SampleMap>("KicksMap", drum_kicks_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("SnaresMap", drum_snares_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("HatsMap", drum_hats_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("ClapsMap", drum_claps_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("CymbalsMap", drum_cymbals_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("PercMap", drum_perc_id);
    addToUserPreset<raw::GenericStorage::SampleMap>("TomsMap", drum_toms_id);
    
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
    
    // output
    addToUserPreset<raw::GenericStorage::Attribute<GainEffect::Gain>>("OutputGain", simple_gain_id);
    
    createPluginParameters(mc);
}

void DrumsData::createModules(MainController* mc)
{
    raw::Builder builder( mc );
    
    auto root = mc->getMainSynthChain();
    
    // global fx
    auto shape = builder.create<hise::ShapeFX>( root, raw::IDs::Chains::FX );
    shape->setId( shape_fx_id );
    ProcessorHelpers::restoreFromBase64String( shape, "335.3ocUQ0ySCCCD0l1LfXhMFYuRUTwGBXgzlRfJRapZpPkQSsSyI4FGY6jRYhQ9+weD9G.1ooJM2z8du676tySkhkLkRHQ3SmuMigvG6DkPxX9KPiFhvmrCct+hdnAayHJEihv3Vd4xBSwW6b4McaFEgS7l2syPYX+a89L.JBMjwcrR2A723uDhF.DU.KVaLqMpJrbyfUIMHe1PL03YM2UtAhMMn99G2wBJqtjybCKXREYcFGRWUy+6COQfzJ7Www26NiQyWxNzv94Zwp5pJ6J.VC5QoY45CYGJghFsNF9nw9Tdr7At1LKGJfa8HEzBYjlnYFk1CDzsQIhMFSa4zC8Jnf24rcfHAWXyt.4K3T6o2li7R.Nc59uNk4UmIx0lscLQKsygyj70Qhb4RlWBIMkwMF4fOBYasDegEaGmHVJsD7mIpD6Yw3Jwd6EQ+WB9.VM");
    
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
    
    addDrumSampler( drum_kicks_id, kicks_muter_id, builder, root, mc, "Kicks1" );
    addDrumSampler( drum_snares_id, snare_muter_id, builder, root, mc, "Snares1" );
    addDrumSampler( drum_hats_id, hats_muter_id, builder, root, mc, "Hats1" );
    addDrumSampler( drum_cymbals_id, cymbals_muter_id, builder, root, mc, "Cymbals1" );
    addDrumSampler( drum_toms_id, toms_muter_id, builder, root, mc, "Toms1" );
    addDrumSampler( drum_perc_id, perc_muter_id, builder, root, mc, "Perc1" );
    addDrumSampler( drum_claps_id, claps_muter_id, builder, root, mc, "Claps1" );
}

void DrumsData::createPluginParameters(MainController *mc)
{
    auto p1 = new raw_parameter(ConvolutionEffect::WetGain, "reverb");
    p1->setup(raw::IDs::UIWidgets::Slider, convolution_reverb_id, { -100.f, -30.f, 0.1f }, -40.f);
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

void DrumsData::addDrumSampler( const std::string& id, const std::string& muterId, raw::Builder& builder,  hise::ModulatorSynthChain* root, MainController* mc, String mapName )
{
    auto drum = builder.create<hise::ModulatorSampler>( root );
    drum->setId( id );
    drum->setAttribute( hise::ModulatorSampler::Parameters::OneShot, 1, dontSendNotification);
    
    auto muter = builder.create<hise::MuteAllScriptProcessor>( drum, raw::IDs::Chains::Midi );
    muter->setId( id + "Muter" );
    muter->setAttribute( MuteAllScriptProcessor::Parameters::IgnoreNotes, 0, dontSendNotification);
    
    auto velo = builder.create<hise::VelocityModulator>( drum, raw::IDs::Chains::Gain );
    velo->setAttribute(VelocityModulator::UseTable, 1.0f, dontSendNotification );
    velo->setId( id + "Velo" );
    ProcessorHelpers::restoreFromBase64String( velo, "202.3ocSPErhBCDCMwZAWuu28hmDDU7hmVPGOzCKakpderSV5.CMRynR+q2OgclJULGBu2ijWdj7FtjDga.bzw1qDfiSOSNtz5agLEfe9hN4a1byo8byRXa6UsHjAPLIq1S0Rbd7igPW82WmD5n9hidWKq9N03iK0qAfhJsWHWvZ5c49a14gR60.NMc054cUt5fZ8t.39Og1uyhZadxAbvdiMDwBu1SBfIaYSaQE+nNfSWBmshsKVQRA63HZA.6prNSd+yPBQ3e.J55Q6A");

    if ( mapName.isEmpty() || !FrontendHandler::checkSamplesCorrectlyInstalled())
    {
        return;
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
}


/** This method needs to be implemented and your initial preset structure must be defined here. */
raw::DataHolderBase* FrontendProcessor::createPresetRaw()
{
	return new DrumsData(this);
}


#endif
