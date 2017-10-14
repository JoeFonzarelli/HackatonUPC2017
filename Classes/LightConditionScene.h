#ifndef __LIGHTCONDITIONSCENE_SCENE_H__
#define __LIGHTCONDITIONSCENE_SCENE_H__

#include "cocos2d.h"

#define FONTSIZE 22

class LightConditionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LightConditionScene);

	void Feedback(Ref* pSender);
	void GoBack(Ref* pSender);
};

#endif // __LIGHTCONDITIONSCENE_SCENE_H__
