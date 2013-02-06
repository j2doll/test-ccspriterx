#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend to return the exactly class pointer
    static cocos2d::CCScene* scene();

	// implement the "static node()" method manually (cocos2d-x ver.2) 
	CREATE_FUNC(HelloWorld);

protected:

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	// test code (schedule-timer) 
	void TestChangeAnimation(float dt); 

	// CCSpriterX* getChildByTag();

};

#endif  // __HELLOWORLD_SCENE_H__