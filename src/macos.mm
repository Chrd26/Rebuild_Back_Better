#import "macos.h"

@implementation MacBuild
-	(void) InitialiseProperties(){
		autoreleasepool{
			self.standardBundle = [NSBundle mainBundle];
			self.findFontMenuTitle = [main pathForResource:@"/fonts/ArianVioleta-dz2K" ofType:@"ttf"];
		}
	}

@end
