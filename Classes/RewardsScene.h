#ifndef __REWARDSSCENE_SCENE_H__
#define __REWARDSSCENE_SCENE_H__

#include "cocos2d.h"

#define FONTSIZE 22

class RewardsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(RewardsScene);

	void GoBack(Ref* pSender);
	void OpenLink(Ref* pSender);
};

#endif // __REWARDSSCENE_SCENE_H__
