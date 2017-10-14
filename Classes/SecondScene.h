#ifndef __SECONDSCENE_SCENE_H__
#define __SECONDSCENE_SCENE_H__

#include "cocos2d.h"

#define FONTSIZE 22

class SecondScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SecondScene);

	void LightNotification(Ref* pSender);
	void BinNotification(Ref* pSender);
	void TrashNotification(Ref* pSender);
	void GoBack(Ref* pSender);
};

#endif // __SECONDSCENE_SCENE_H__
