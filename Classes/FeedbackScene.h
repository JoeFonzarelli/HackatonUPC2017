#ifndef __FEEDBACKSCENE_SCENE_H__
#define __FEEDBACKSCENE_SCENE_H__

#include "cocos2d.h"

#define FONTSIZE 22

class FeedbackScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(FeedbackScene);

	void Feedback(Ref* pSender);
	void GoBack(Ref* pSender);
};

#endif // __FEEDBACKSCENE_SCENE_H__
