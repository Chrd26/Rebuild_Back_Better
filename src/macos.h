#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

@interface MacBuild : NSObject

	@property (assign) NSBundle *standardBundle;
	@property (assign) NSString *findFontMenuTitle;
	void InitialiseProperties();
@end
