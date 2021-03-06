#include "RewardsScene.h"
#include "SimpleAudioEngine.h"

#include <iostream>

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* RewardsScene::createScene()
{
    return RewardsScene::create();
}

// on "init" you need to initialize your instance
bool RewardsScene::init()
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

    // add a "close" icon to exit the progress. it's an autorelease object
	
    // create menu, it's an autorelease object
    /*auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("See your rewards", "fonts/Marker Felt.ttf", 24);    
	label->setColor(cocos2d::Color3B(255, 100, 0));
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

	auto labelb = Label::createWithTTF("Your next reward is...", "fonts/Marker Felt.ttf", 24);
	labelb->setColor(cocos2d::Color3B(100, 100, 0));
	// position the label on the center of the screen
	labelb->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height *5/6));

	auto labelc = Label::createWithTTF("A free bus ticket!", "fonts/Marker Felt.ttf", 30);
	labelc->setColor(cocos2d::Color3B(250, 0, 0));
	// position the label on the center of the screen
	labelc->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height * 3 / 6));

    // add the label as a child to this layer
    this->addChild(label, 1);
	this->addChild(labelb, 1);
	this->addChild(labelc, 1);

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

	auto label1 = Label::createWithTTF("Visit the website for more rewards", "fonts/Marker Felt.ttf", FONTSIZE);
	auto label2 = Label::createWithTTF("Go Back", "fonts/Marker Felt.ttf", FONTSIZE);
	
	auto menu_item_1 = MenuItemLabel::create(label1, CC_CALLBACK_1(RewardsScene::OpenLink, this));
	auto menu_item_2 = MenuItemLabel::create(label2, CC_CALLBACK_1(RewardsScene::GoBack, this));
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(RewardsScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 7));
	menu_item_2->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1 / 6));
	
	Menu* menu = Menu::create(menu_item_1, menu_item_2, closeItem, NULL);
	menu->setPosition(0, 0);

	this->addChild(menu);

    return true;
}


void RewardsScene::menuCloseCallback(Ref* pSender)
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

void RewardsScene::GoBack(Ref* pSender) {
	Director::getInstance()->popScene();
};

void RewardsScene::OpenLink(Ref* pSender) {
	Application::getInstance()->openURL("http://ajuntament.barcelona.cat/es/");
};