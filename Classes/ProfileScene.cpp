#include "ProfileScene.h"
#include "SimpleAudioEngine.h"

#include <iostream>

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* ProfileScene::createScene()
{
    return ProfileScene::create();
}

// on "init" you need to initialize your instance
bool ProfileScene::init()
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
	
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("pet.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//sprite->setContentSize(visibleSize / 2);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ProfileScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto label1 = Label::createWithTTF("Go back", "fonts/Marker Felt.ttf", FONTSIZE);
	auto label2 = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", FONTSIZE);
	label2->setPosition(Point(origin.x + visibleSize.width / 2,origin.y + visibleSize.height *5/6));
	label1->setColor(cocos2d::Color3B(255, 30, 30));

	auto menu_item_1 = MenuItemLabel::create(label1, CC_CALLBACK_1(ProfileScene::GoBack, this));
	
	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 6));
	
	Menu* menu = Menu::create(menu_item_1, closeItem, NULL);
	menu->setPosition(0, 0);

	this->addChild(menu);
	this->addChild(label2);
	
    return true;
}


void ProfileScene::menuCloseCallback(Ref* pSender)
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

void ProfileScene::GoBack(Ref* pSender) {
	Director::getInstance()->popScene();
};