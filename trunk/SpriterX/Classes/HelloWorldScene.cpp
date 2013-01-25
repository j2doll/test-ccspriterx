#include "HelloWorldScene.h"

using namespace cocos2d;

#include "CCSpriterX.h"


CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Spriter Demo", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

		// 3. create sprite from spriter resource 

		// create 'Example.SCML'
		{
			CCSpriterX* animator = CCSpriterX::create( "Example.SCML" );
			CC_BREAK_IF(! animator);
			animator->setPosition(ccp(110, 350));
			animator->setScale(0.5f); // half size 
			int tag = 100;
			this->addChild(animator, 0, tag);
		}
		

		// create 'Example.SCML' 
		{
			CCSpriterX* animator = CCSpriterX::create( "Example.SCML" );
			CC_BREAK_IF(! animator);
			animator->setPosition(ccp(380, 160));
			animator->setScale(1.0f);
			// animator->PlayNext(); // play next 
			int tag = 110;
			this->addChild(animator, 0, tag);
		}

		// create 'Hero.SCML'
		{
			CCSpriterX* animator = CCSpriterX::create( "Hero.SCML" );
			CC_BREAK_IF(! animator);
			animator->setPosition(ccp(50, 200));
			animator->setScale(0.5f); // half size  
			int tag = 200;
			this->addChild(animator, 0, tag);
		}

		// create 'Hero.SCML'
		{
			CCSpriterX* animator = CCSpriterX::create( "Hero.SCML" );
			CC_BREAK_IF(! animator);
			animator->setPosition(ccp(130, 200));
			animator->setScale(1.0f);
			// animator->PlayNext(); // play next 
			int tag = 210;
			this->addChild(animator, 0, tag); 
		}

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

		// test code 		
		schedule( schedule_selector(HelloWorld::TestChangeAnimation), 1.0 );

        bRet = true;

    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	// TestChangeAnimation(0);
	return true; 
}

unsigned int test100 = 0;
unsigned int test110 = 0;
unsigned int test200 = 0;
unsigned int test210 = 0; 

void HelloWorld::TestChangeAnimation(float dt)
{


	CCSpriterX *animator = (CCSpriterX*) this->getChildByTag( 100 ); 
	{
		if ( test100 == 0 )
		{
			animator->setCurrentAnimation( 1 );
			test100 = 1;
		}
		else
		{
			animator->setCurrentAnimation( 0 );
			test100 = 0;
		}
	}

	animator = (CCSpriterX *)this->getChildByTag( 110 );
	{
		if ( test110 == 0 )
		{
			animator->setCurrentAnimation( 1 );
			test110 = 1;
		}
		else
		{
			animator->setCurrentAnimation( 0 );
			test110 = 0;
		}
	}
	

	animator = (CCSpriterX *)this->getChildByTag( 200 );
	{
		if ( test200 == 0 )
		{
			animator->setCurrentAnimation( "walk" );
			test200 = 1;
		}
		else
		{
			animator->setCurrentAnimation( "idle_healthy" );
			test200 = 0;
		}
	}
	
	animator = (CCSpriterX *)this->getChildByTag( 210 );
	{
		if ( test210 == 0 )
		{
			animator->setCurrentAnimation( 1 );
			test210 = 1;
		}
		else
		{
			animator->setCurrentAnimation( 0 );
			test210 = 0; 
		}
	}



}
