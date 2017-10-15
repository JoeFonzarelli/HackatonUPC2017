#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SecondScene.h"
#include "ProfileScene.h"
#include "RewardsScene.h"

#include <curl\include\win32\curl\curl.h>

#include <Python.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if (curl) {

	//append the headers
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "'IDENTITY_KEY' : 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75'");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "'Accept' : 'Application/JSON'");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "'Content-Type' : 'Application/JSON'");

	//connect ( //i added this here since curl_easy_send() says it requires it. )
	curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);

	//specify the request (PUT in our case)
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

	/* enable uploading */
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

	/* specify target URL, and note that this URL should include a file
	name, not only a directory */
	curl_easy_setopt(curl, CURLOPT_URL, "http://api.thingtia.cloud/data/provedor1.component1.Score1/9999");

	curl_easy_setopt(curl, CURLOPT_PUT, "699");

	curl_easy_cleanup(curl);

	
	
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "http://api.thingtia.cloud/data/provedor1/score1/9999");
		
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "pulse=70 & temp=35");
	}
	
	
	Py_Initialize();
	std::cout << " print" << std::endl;
	PyRun_SimpleString("print('python funziona')");
	//FILE* file_1 = std::fopen("readDB.py", "r");
	
	//if (file_1 != NULL)
	//{
		//PyRun_AnyFile(file_1, "readDB.py");
	/*PyRun_SimpleString("import requests\
import json\
\
\
def get_sensor_information() : \
	headers = { 'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75' } \
	resp = requests.get('http://api.thingtia.cloud/data/provedor1/Score1', headers = headers) \
	if not resp.ok : \
		resp.raise_for_status() \
\
	data = resp.json(); \
	out = data['observations'][0]['value'] \
	return out \
\
\
def put_sensor_information(value) : \
	headers = { 'IDENTITY_KEY': 'e3ba38839c9f601471b8f3f662a38ae23473bebf63cec53a183edec2d5c84e75' } \
	resp = requests.put('http://api.thingtia.cloud/data/provedor1/Score1/' + str(value), headers = headers) \
	if not resp.ok :\
		resp.raise_for_status()\
\
	print(res.content)\
\
\
	data = get_sensor_information('Luminosity1') \
	print(data)\
\
put_sensor_information(666);");
*/	Py_Finalize();
	//}
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    
    // create menu, it's an autorelease object
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Smart citizens", "fonts/Marker Felt.ttf", 24);
	label->setColor(cocos2d::Color3B(255, 100, 0));

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto label1 = Label::createWithTTF("Notify a problem", "fonts/Marker Felt.ttf", FONTSIZE);
	auto label2 = Label::createWithTTF("My profile", "fonts/Marker Felt.ttf", FONTSIZE);
	auto label3 = Label::createWithTTF("Rewards", "fonts/Marker Felt.ttf", FONTSIZE);

	auto menu_item_1 = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::Play, this));
	auto menu_item_2 = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::Highscores, this));
	auto menu_item_3 = MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::Settings, this));

	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));
	menu_item_2->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	menu_item_3->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));

	Menu* menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, closeItem, NULL);
	menu->setPosition(0, 0);
	
	this->addChild(menu);
	/*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
    return true;
}

void HelloWorld::Play(cocos2d::Ref* pSender) {
	CCLOG("Play");

	auto scene = SecondScene::createScene();
	Director::getInstance()->pushScene(scene); // replaceScene(scene) --> pushback new, pop up current
}

void HelloWorld::Highscores(cocos2d::Ref* pSender) {
	CCLOG("high");

	auto scene = ProfileScene::createScene();
	Director::getInstance()->pushScene(scene); // replaceScene(scene) --> pushback new, pop up current

}

void HelloWorld::Settings(cocos2d::Ref* pSender) {
	CCLOG("Quit");

	auto scene = RewardsScene::create();

	Director::getInstance()->pushScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
