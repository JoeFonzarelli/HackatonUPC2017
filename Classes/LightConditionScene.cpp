#include "SimpleAudioEngine.h"
#include "LightConditionScene.h"
#include "FeedbackScene.h"
#include "SecondScene.h"

#include <iostream>

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* LightConditionScene::createScene()
{
    return LightConditionScene::create();
}

// on "init" you need to initialize your instance
bool LightConditionScene::init()
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
    
    auto label = Label::createWithTTF("what's wrong with the lights?", "fonts/Marker Felt.ttf", 20);

	label->setColor(cocos2d::Color3B(255, 100, 0));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

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


	auto label1 = Label::createWithTTF("Turn them off!", "fonts/Marker Felt.ttf", FONTSIZE);
	label1->setColor(cocos2d::Color3B(50, 100, 255));
	auto label2 = Label::createWithTTF("Turn them on!", "fonts/Marker Felt.ttf", FONTSIZE);
	label2->setColor(cocos2d::Color3B(15, 190, 30));
	auto label3 = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", FONTSIZE);
	label3->setColor(cocos2d::Color3B(255, 30, 30));

	auto menu_item_1 = MenuItemLabel::create(label1, CC_CALLBACK_1(LightConditionScene::Feedback, this));
	auto menu_item_2 = MenuItemLabel::create(label2, CC_CALLBACK_1(LightConditionScene::Feedback, this));
	auto menu_item_3 = MenuItemLabel::create(label3, CC_CALLBACK_1(LightConditionScene::GoBack, this));
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LightConditionScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 5));
	menu_item_2->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 5));
	menu_item_3->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1 / 5));
	
	Menu* menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, closeItem, NULL);
	menu->setPosition(0, 0);

	this->addChild(menu);

    return true;
}


void LightConditionScene::menuCloseCallback(Ref* pSender)
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

void LightConditionScene::Feedback(Ref* pSender) {
	auto scene = FeedbackScene::create();
	Director::getInstance()->replaceScene(scene);
};

void LightConditionScene::GoBack(Ref* pSender) {
	auto scene = SecondScene::create();
	Director::getInstance()->replaceScene(scene);
};