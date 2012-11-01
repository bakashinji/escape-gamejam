debug = true

if debug then
	width = 1024
	height = 768
	windowed = true
else
	width = 1680
	height = 1050
	windowed = false
end
bpp = 32

frequency = 44100
stereo = true
chunksize = 2048

plugindir = "/usr/lib/OGRE"
plugins = { "RenderSystem_GL", "Plugin_OctreeSceneManager" }

input = {
	keyboard = {
		escape = "quit",
		left = "left",
		right = "right",
		up = "rise",
		down = "fall",
		tab = "boost",
		w = "accelerate",
		a = "roll left",
		s = "drag",
		d = "roll right"
	},
	mouse = {
		relx = "steer",
		rely = "climb"
	},
	joystick0 = {
		axis1 = "roll right",
		axis2 = "fall",
		axis3 = "right",
		axis4 = "drag"
	}
}
