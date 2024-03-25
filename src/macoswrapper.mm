extern "C"
{
	#import "macos.h"
}

extern "C" MacBuild *MacBuilder()
{
	MacBuild *macbuild = [[MacBuild alloc] init];
	return macbuild;
}

extern "C" void DestroyMacBuilder(MacBuild *macbuild)
{
	[macbuild dealloc];
}

