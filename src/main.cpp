#include "LuaConfiguration.h"
#include "MessageException.h"
#include "Escape.h"

int main()
{
	TheEscape c;

	c.play();

/*************************** audaspace Setup **********************************/

/*	AUD_DeviceSpecs specs;
	specs.channels = AUD_CHANNELS_STEREO;
	specs.format = AUD_FORMAT_FLOAT32;
	specs.rate = AUD_RATE_48000;
	AUD_OpenALDevice device(specs);
	AUD_SndFileFactory factory("pink_panther.ogg");
	device.play(&factory);*/

	return 0;
}
