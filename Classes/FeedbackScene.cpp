#include "SimpleAudioEngine.h"
#include "FeedbackScene.h"
#include "HelloWorldScene.h"

#include <iostream>

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* FeedbackScene::createScene()
{
    return FeedbackScene::create();
}

// on "init" you need to initialize your instance
bool FeedbackScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
	
    // create menu, it's an autorelease object
    /*auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Thanks for your help!", "fonts/Marker Felt.ttf", 25);

	label->setColor(cocos2d::Color3B(50, 100, 200));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height*2/3));

    // add the label as a child to this layer
    this->addChild(label, 1);

	/*
	auto button1 = ui::Button::create("button_city-lights.png", "button_city-lights_ALT.png");
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			
			break;
		default:
			break;
		}
	});

	button1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
	this->addChild(button1);
	*/


	auto label1 = Label::createWithTTF("ok!", "fonts/Marker Felt.ttf", FONTSIZE);
	label1->setColor(cocos2d::Color3B(100, 100, 255));

	auto menu_item_1 = MenuItemLabel::create(label1, CC_CALLBACK_1(FeedbackScene::GoBack, this));
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(FeedbackScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 5));
	
	Menu* menu = Menu::create(menu_item_1, closeItem, NULL);
	menu->setPosition(0, 0);

	this->addChild(menu);

    return true;
}


void FeedbackScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
}

void FeedbackScene::GoBack(Ref* pSender) {
	auto scene = HelloWorld::create();
	Director::getInstance()->replaceScene(scene);
};