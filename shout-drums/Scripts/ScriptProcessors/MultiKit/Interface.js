/** Define the size of the interface. */
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
 