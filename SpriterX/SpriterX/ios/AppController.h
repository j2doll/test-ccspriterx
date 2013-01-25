//
//  SpriterXAppController.h
//  SpriterX
//
//  Created by James Hui on 12/09/12.
//  Copyright Khors 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

