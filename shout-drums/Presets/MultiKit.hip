Processor 
Type SynthChain ID 
MultiKit Bypassed Gain 	      �?Balance 	        VoiceLimit 	      P@KillFadeTime 	      4@IconColour 0 packageName  BuildVersion �  EditorStates BodyShown 0 Visible 1 Solo 0 Folded 1  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors  Processor Type ScriptProcessor ID Interface Bypassed Script ~/** Define the size of the interface. */
Content.makeFrontInterface(800, 600);

/** We grab a reference to the full screen floating tile. */
const var FloatingTile1 = Content.getComponent("FloatingTile1");

/** Just set the ID to the ID we'll use for our C++ component.
*   In HISE it will show a placeholder, but in our compiled plugin
*   we can define the actual component. 
*/
FloatingTile1.setContentData({"Type": "ExternalTestComponent"});

// Create a typed Audio Sample Script Reference with right click on the Convolution Module
const var ConvolutionReverb = Synth.getAudioSampleProcessor("Convolution Reverb");

// load all Audio Files from the AudioFiles Folder into the Pool
Engine.loadAudioFilesIntoPool();

// set a new file 
ConvolutionReverb.setFile("{PROJECT_FOLDER}ImpulseOpera.wav");

// hidden control for sample map changing
const var sampleMaps = Sampler.getSampleMapList();
const var cmbSampleMap = Content.getComponent("cmbSampleMap");
const var kickMap = Content.getComponent("kickMap");
const var snareMap = Content.getComponent("snareMap");
const var hatMap = Content.getComponent("hatMap");
const var percMap = Content.getComponent("percMap");
const var clapMap = Content.getComponent("clapMap");
const var tomMap = Content.getComponent("tomMap");
const var cymbalMap = Content.getComponent("cymbalMap");

const var items = sampleMaps.join("\n");
cmbSampleMap.set("items", items);
kickMap.set("items", items);
snareMap.set("items", items);
hatMap.set("items", items);
percMap.set("items", items);
clapMap.set("items", items);
tomMap.set("items", items);
cymbalMap.set("items", items);

const var MySampler = Synth.getSampler("Sampler");
const var Kicks = Synth.getSampler("Kicks");
const var Snares = Synth.getSampler("Snares");
const var Hats = Synth.getSampler("Hats");
const var Perc = Synth.getSampler("Perc");
const var Clap = Synth.getSampler("Claps");
const var Tom  = Synth.getSampler("Toms");
const var Cymbal = Synth.getSampler("Cymbals");

// Sampler
inline function oncmbSampleMapControl(component, value)
{
	MySampler.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("cmbSampleMap").setControlCallback(oncmbSampleMapControl);

// Kicks
inline function onKicksMapControl(component, value)
{
	Kicks.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("kickMap").setControlCallback(onKicksMapControl);

// Snares
inline function onSnaresMapControl(component, value)
{
	Snares.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("snareMap").setControlCallback(onSnaresMapControl);

// Hats
inline function onHatsMapControl(component, value)
{
	Hats.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("hatMap").setControlCallback(onHatsMapControl);

// Perc
inline function onPercMapControl(component, value)
{
	Perc.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("percMap").setControlCallback(onPercMapControl);

// Clap
inline function onClapMapControl(component, value)
{
	Clap.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("clapMap").setControlCallback(onClapMapControl);

// Tom
inline function onTomMapControl(component, value)
{
	Tom.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("tomMap").setControlCallback(onTomMapControl);

// Cymbals
inline function onCymbalMapControl(component, value)
{
	Cymbal.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("cymbalMap").setControlCallback(onCymbalMapControl);function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
  EditorStates BodyShown 1 Visible 1 Solo 0 contentShown 1 onInitOpen 1  ChildProcessors   Content  Control type ScriptSlider id MainOutput value 	      �? Control type ScriptButton id KickMuted value 	      �? Control type ScriptButton id SamplerMuted value 	         Control type ScriptSlider id ReverbWet value 	      Y� Control type ScriptComboBox id cmbSampleMap value 	      @ Control type ScriptComboBox id 
snareMap value 	       @ Control type ScriptComboBox id hatMap value 	      @ Control type ScriptComboBox id 	kickMap value 	      @ Control type ScriptButton id SnareMuted value 	      �? Control type ScriptButton id HatsMuted value 	      �? Control type ScriptButton id PercMuted value 	      �? Control type ScriptButton id ClapMuted value 	      �? Control type ScriptButton id TomsMuted value 	      �? Control type ScriptButton id CymbalsMuted value 	      �? Control type ScriptComboBox id 	percMap value 	      @ Control type ScriptComboBox id 	clapMap value 	      �? Control type ScriptComboBox id tomMap value 	      &@ Control type ScriptComboBox id cymbalMap value 	       @ Control type ScriptSlider id SaturationMix value 	         Control type ScriptSlider id Width value 	      Y@ Control type ScriptSlider id SamplerAttack value 	         Control type ScriptSlider id SamplerRelease value 	      b@ UIData  ContentProperties DeviceType 	Desktop Component type ScriptFloatingTile id FloatingTile1 x 	        y 	        width 	      �@height 	      �@ContentType ExternalTestComponent bgColour 4294951115 itemColour 4294951115 itemColour2 4294951115 textColour 4294951115 Data {
}  Component type ScriptFloatingTile id InternalControls x 	      �?y 	      �width 	      �@height 	     �@Component type ScriptSlider id MainOutput x 	     �u@y 	      9@parentComponent InternalControls processorId Simple Gain1 parameterId Gain mode 	Decibel min 	      Y�max 	        stepSize 	�������?suffix  dB middlePosition 	      2� Component type ScriptButton id KickMuted x 	      I@y 	     `e@parentComponent InternalControls processorId KicksMuter parameterId ignoreButton  Component type ScriptButton id SamplerMuted x 	     �I@y 	      \@parentComponent InternalControls processorId MidiMuter1 parameterId ignoreButton  Component type ScriptSlider id ReverbWet x 	     �h@y 	      9@parentComponent InternalControls processorId Convolution Reverb parameterId 	WetGain min 	      Y�max 	        mode 	Decibel defaultValue 	      N�middlePosition 	      >� Component type ScriptComboBox id cmbSampleMap x 	     �j@y 	     �[@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id 
snareMap x 	     �j@y 	     �j@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id hatMap x 	     �j@y 	     �p@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id 	kickMap x 	     @j@y 	      e@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptButton id SnareMuted x 	     �H@y 	     @k@parentComponent InternalControls processorId SnaresMuter parameterId ignoreButton  Component type ScriptButton id HatsMuted x 	     �I@y 	     �p@parentComponent InternalControls processorId HatsMuter parameterId ignoreButton  Component type ScriptButton id PercMuted x 	      I@y 	     `t@parentComponent InternalControls processorId PercMuter parameterId ignoreButton  Component type ScriptButton id ClapMuted x 	      I@y 	     Pw@parentComponent InternalControls processorId ClapsMuter parameterId ignoreButton  Component type ScriptButton id TomsMuted x 	      H@y 	      z@parentComponent InternalControls processorId TomsMuter parameterId ignoreButton  Component type ScriptButton id CymbalsMuted x 	     �H@y 	     �|@parentComponent InternalControls processorId CymbalsMuter parameterId ignoreButton  Component type ScriptComboBox id 	percMap x 	      k@y 	     `t@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id 	clapMap x 	     �j@y 	     0w@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id tomMap x 	     �j@y 	     z@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptComboBox id cymbalMap x 	     �j@y 	     �|@max    parentComponent InternalControls items YClaps1
Cymbals1
Hats1
Kicks1
Kicks2
MoreGiraffeFX
Perc1
Snares1
Snares2
TestDrums
Toms1  Component type ScriptSlider id SaturationMix x 	     �@y 	      ;@parentComponent InternalControls processorId Shape FX1 parameterId Mix  Component 	type ScriptSlider id Width x 	     `�@y 	      >@parentComponent InternalControls processorId Simple Gain1 parameterId Width max 	      i@defaultValue 	      Y@ Component type ScriptSlider id SamplerAttack x 	     �v@y 	      Z@parentComponent InternalControls text Attack processorId AHDSR Envelope1 parameterId Attack mode Time max 	     ��@stepSize 	      �?suffix  ms middlePosition 	�����?�@ Component type ScriptSlider id SamplerRelease x 	     X�@y 	     �Z@parentComponent InternalControls text 	Release mode Time max 	     ��@stepSize 	      �?suffix  ms middlePosition 	�����?�@processorId AHDSR Envelope1 parameterId 	Release defaultValue 	     H�@min 	      T@ Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 1 Solo 0 Folded 0  ChildProcessors  Processor Type Convolution ID Convolution Reverb Bypassed DryGain 	        WetGain 	      Y�Latency 	        ImpulseLength 	      �?ProcessInput 	      �?UseBackgroundThread 	      �?Predelay 	        HiCut 	     ��@Damping 	        FFTType 	        FileName "{PROJECT_FOLDER}ImpulseOpera.wav min     max Z loopStart     loopEnd Z EditorStates BodyShown 1 Visible 1 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� Processor Type 	Limiter ID 
Limiter1 Bypassed Thresh 	   �z�?Output 	   ��Q�?Release 	   `���?Attack 	    \��?Knee 	        EditorStates BodyShown 1 Visible 1 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� Processor Type 	ShapeFX ID Shape FX1 Bypassed Curve 536...............vONCT.+DrOA8CzLivO...f+....9ilYlKO BiasLeft 	        BiasRight 	        HighPass 	      4@LowPass 	     ��@Mode 	      @Oversampling 	      �?Gain 	   �ff:@Reduce 	        Autogain 	      �?LimitInput 	      �?Drive 	        Mix 	        BypassFilters 	        EditorStates BodyShown 1 Visible 1 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� Processor Type SimpleGain ID Simple Gain1 Bypassed Gain 	        Delay 	        Width 	      Y@Balance 	        InvertPolarity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Delay Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Width Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Pan Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� Processor Type StreamingSampler ID 	Sampler Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	        CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID MoreGiraffeFX EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 0 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID MidiMuter1 Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	         Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type AHDSR ID AHDSR Envelope1 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?AttackCurve 	   ��Q�?DecayCurve 	        Attack 	        AttackLevel 	        Hold 	      $@Decay 	     �r@Sustain 	        Release 	     |�@EcoMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Attack Level Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Decay Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sustain Level Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Release Time Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator1 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......PDQD4C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Kicks Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Kicks1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID KicksMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type 
Velocity ID Velocity Modulator1 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......vLyL5C...vO...f+....9CYlIuO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor 	Type SimpleEnvelope ID Simple Envelope1 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Snares Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID 	Snares1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID SnaresMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope1 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator2 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......nYlY5C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Perc Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Perc1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID PercMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope2 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Claps Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Claps1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID ClapsMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope3 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator3 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......3t6t5C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Hats Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Hats1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID HatsMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope4 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator4 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......HhHh5C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type 
Velocity ID Velocity Modulator5 Bypassed Intensity 	   `j��?Bipolar UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData  EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type PolyphonicFilter ID 	Filter1 Bypassed Gain 	        Frequency 	    �N�@Q 	      �?Mode 	      @Quality 	        BipolarIntensity 	        EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Frequency Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type 
Velocity ID Velocity Modulator6 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24..........7C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID Gain Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Bipolar Freq Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Q Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID 	Cymbals Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	        CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID 
Cymbals1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID CymbalsMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope5 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	     �}@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator7 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......PDQD6C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   Processor Type StreamingSampler ID Toms Bypassed Gain 	      �?Balance 	        VoiceLimit 	      p@KillFadeTime 	      4@IconColour 0 PreloadSize 	      �@BufferSize 	      �@VoiceAmount 	      p@SamplerRepeatMode 	      @RRGroupAmount 	      �?PitchTracking 	      �?OneShot 	      �?CrossfadeGroups 	        Purged 	        Reversed 	        NumChannels    UseStaticMatrix 	        Group0Table  Group1Table  Group2Table  Group3Table  Group4Table  Group5Table  Group6Table  Group7Table  SampleMapID Toms1 EditorStates BodyShown 1 Visible 1 Solo 0 MapPanelShown 1 BigSampleMap 1 Folded 1 CrossfadeTableShown 0  ChildProcessors  Processor Type MidiProcessorChain ID Midi Processor Bypassed EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor Type MidiMuter ID TomsMuter Bypassed EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Content  Control type ScriptButton id ignoreButton value 	      �? Control type ScriptButton id fixStuckNotes value 	         Processor Type ModulatorChain ID GainModulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0  ChildProcessors  Processor 	Type SimpleEnvelope ID DefaultEnvelope6 Bypassed Monophonic 	        Retrigger 	      �?Intensity 	      �?Attack 	        Release 	      $@LinearMode 	      �?EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors  Processor Type ModulatorChain ID Attack Time Modulation Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type 
Velocity ID Velocity Modulator8 Bypassed Intensity 	      �?UseTable 	      �?Inverted 	        DecibelMode 	        VelocityTableData %24......XUUU6C...vO...f+....9C...vO EditorStates BodyShown 1 Visible 1 Solo 0  ChildProcessors   Processor Type ModulatorChain ID PitchModulation Bypassed Intensity 	        EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type EffectChain ID FX Bypassed EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Sample Start Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   Processor Type ModulatorChain ID Group Fade Bypassed Intensity 	      �?EditorStates BodyShown 1 Visible 0 Solo 0 Folded 1  ChildProcessors   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� channels  channelData enabled level 	        suffix   RoutingMatrix NumSourceChannels    Channel0     Send0 ����Channel1    Send1 ���� macro_controls  macro name 	Macro 1 value 0.0 midi_cc -1  macro name 	Macro 2 value 0.0 midi_cc -1  macro name 	Macro 3 value 0.0 midi_cc -1  macro name 	Macro 4 value 0.0 midi_cc -1  macro name 	Macro 5 value 0.0 midi_cc -1  macro name 	Macro 6 value 0.0 midi_cc -1  macro name 	Macro 7 value 0.0 midi_cc -1  macro name 	Macro 8 value 0.0 midi_cc -1  MidiAutomation   MPEData Enabled  