/** Define the size of the interface. */
Content.makeFrontInterface(600, 400);

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
ConvolutionReverb.setFile("{PROJECT_FOLDER}ImpulseOpera.wav");function onNoteOn()
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
 