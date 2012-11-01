//#include <boost/asio.hpp>

/*
C++11 cheatsheet

- extern template
- initializer lists with {}
- type inference: auto, decltype()
- foreach: for(int& x : my_array)
- [object construction]
- explicit override + final
- nullptr
- enum class bla : int {};
- UTF strings: u8"öä"
- [regex]
- smart pointers
*/

#include "LuaConfiguration.h"
#include "MessageException.h"
#include "WingsOfConcept.h"

int main()
{
	WingsOfConcept c;

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
