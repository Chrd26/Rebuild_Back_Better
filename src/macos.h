#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

@interface MacBuild : NSObject

	@property (readonly) NSBundle *standardBundle;
	@property (readonly) NSString *findFontMenuTitle;
	void InitialiseProperties();

@end
