#pragma once
#include "Tools.h"
#include "MovieVideoLayer.h"
#include "SerialMager.h"
#include "MyMenu.h"

USING_NS_CC;
class mainScene:public CCLayer
{
public:
    static MovieVideoLayer* m_pFrontMovieVideoLayer;
	static MovieVideoLayer* m_pSideMovieVideoLayer;
	CUETYPE m_curCueType;
    GENDER m_curGender;
	CCSprite* m_pReadyLabel;
	CCSprite* m_pReadyImage;
	CCMenuItemImage* m_pCueTtpeArr[4];
    CCMenuItemImage* m_pGenderArr[2];

	float m_curSingle;
	unsigned int m_curMsg;
	static char* m_FilePath1;
	static char* m_FilePath2;
	static bool m_bIsPlayVideo;
	static bool m_bIsTurnCamera;
	bool m_bSetMode;
public:
    
    mainScene(void);
    ~mainScene(void);

    //场景的创建函数
    static CCScene* CreateScene();
    //本类的创建函数
    CREATE_FUNC(mainScene);
    //初始化函数
    virtual bool init();
	virtual void update(float dt);
	//按钮的回调函数
    void menuBackCallback(CCObject* pSender);
	void menuCueTtpeCallback(CCObject* pSender);
	void menuGenderCallback(CCObject* pSender);
	void menuCallback(CCObject* pSender);
	void CallbackRePlay(CCObject* pSender);
	void CallbackPreview(CCObject* pSender);

};

