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

cmbSampleMap.set("items", sampleMaps.join("\n"));
const var MySampler = Synth.getSampler("Sampler");


inline function oncmbSampleMapControl(component, value)
{
	MySampler.loadSampleMap(sampleMaps[value-1]);
};

Content.getComponent("cmbSampleMap").setControlCallback(oncmbSampleMapControl);
function onNoteOn()
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
 