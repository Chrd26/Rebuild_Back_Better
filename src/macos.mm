#import "macos.h"

@implementation MacBuild
-	(void) InitialiseProperties{
		self.standardBundle = [NSBundle mainBundle];
		self.findFontMenuTitle = [_standardBundle pathForResource:@"/fonts/ArianVioleta-dz2K" ofType:@"ttf"];
	}

@end
