#include "mainScene.h"
#include "SettingScene.h"
#include "MessageLayer.h"

MovieVideoLayer* mainScene::m_pFrontMovieVideoLayer = NULL;
MovieVideoLayer* mainScene::m_pSideMovieVideoLayer = NULL;
char* mainScene::m_FilePath1 = new char[64];
char* mainScene::m_FilePath2 = new char[64];
bool mainScene::m_bIsPlayVideo = false;
bool mainScene::m_bIsTurnCamera = true;
mainScene::mainScene(void)
{
}
mainScene::~mainScene(void)
{
	SerialMager::getInstence()->unLoadInstence();
	m_bIsPlayVideo = false;
	m_pFrontMovieVideoLayer->ReSetVideo();
	if (Ext_cameraNum == 2)
	{
		m_pFrontMovieVideoLayer->ReSetVideo();
		m_pSideMovieVideoLayer->ReSetVideo();
	}
}
//场景的创建函数
CCScene* mainScene::CreateScene()
{
    //创建一个场景
    CCScene* scene = CCScene::create();
    //创建层
    mainScene* pLayer = mainScene::create();
    //将层加载到场景中  并返回
    scene->addChild(pLayer,1,98);

    return scene;
}
//初始化函数
bool mainScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
	printf("初始化mainScene\n");
	m_curMsg = 0;
	m_bIsPlayVideo = false;
	m_bSetMode = true;
	m_curGender = GENDER_MAN;
	m_curCueType = CUETYPE_YIHAOMU;
	
	sprintf(m_FilePath1,
		DEMOVIDEO,
		Ext_FrameRate,
		m_curGender,
		m_curCueType,
		FRONT);
	sprintf(m_FilePath2,
		DEMOVIDEO,
		Ext_FrameRate,
		m_curGender,
		m_curCueType,
		SIDE);
	{//UI显示
		CCSprite* beijing1 = CCSprite::create("VideoUI/beijing1.png");
		beijing1->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
		this->addChild(beijing1);

        m_pCueTtpeArr[0] = CCMenuItemImage::create(
										"VideoUI/yihaomu1.png",
										"VideoUI/yihaomu2.png",
										"VideoUI/yihaomu2.png",
                                        this,
										menu_selector(mainScene::menuCueTtpeCallback));
        m_pCueTtpeArr[1] = CCMenuItemImage::create(
										"VideoUI/mugan1.png",
										"VideoUI/mugan2.png",
										"VideoUI/mugan2.png",
                                        this,
										menu_selector(mainScene::menuCueTtpeCallback));
        m_pCueTtpeArr[2] = CCMenuItemImage::create(
										"VideoUI/tiegan1.png",
										"VideoUI/tiegan2.png",
										"VideoUI/tiegan2.png",
                                        this,
										menu_selector(mainScene::menuCueTtpeCallback));
        m_pCueTtpeArr[3] = CCMenuItemImage::create(
										"VideoUI/waqigan1.png",
										"VideoUI/waqigan2.png",
										"VideoUI/waqigan2.png",
                                        this,
										menu_selector(mainScene::menuCueTtpeCallback));

        m_pGenderArr[0] = CCMenuItemImage::create(
										"VideoUI/nan1.png",
										"VideoUI/nan2.png",
										"VideoUI/nan2.png",
                                        this,
										menu_selector(mainScene::menuGenderCallback));
        m_pGenderArr[1] = CCMenuItemImage::create(
										"VideoUI/nv1.png",
										"VideoUI/nv2.png",
										"VideoUI/nv2.png",
                                        this,
										menu_selector(mainScene::menuGenderCallback));
		
		m_pCueTtpeArr[0]->setPosition(ccp(120, VISIBLEH/2+180));
		m_pCueTtpeArr[1]->setPosition(ccp(120, VISIBLEH/2+60));
		m_pCueTtpeArr[2]->setPosition(ccp(120, VISIBLEH/2-60));
		m_pCueTtpeArr[3]->setPosition(ccp(120, VISIBLEH/2-180));
		m_pGenderArr[0]->setPosition(ccp(1800, VISIBLEH/2+80));
		m_pGenderArr[1]->setPosition(ccp(1800, VISIBLEH/2-80));
		
		m_pCueTtpeArr[0]->setTag(CUETYPE_YIHAOMU);
		m_pCueTtpeArr[1]->setTag(CUETYPE_MUGAN);
		m_pCueTtpeArr[2]->setTag(CUETYPE_TIEGAN);
		m_pCueTtpeArr[3]->setTag(CUETYPE_WAQIGAN);
		m_pGenderArr[0]->setTag(GENDER_MAN);
		m_pGenderArr[1]->setTag(GENDER_WOMAN);

		m_pCueTtpeArr[0]->setEnabled(false);
		m_pGenderArr[0]->setEnabled(false);
	}
	CCMenuItemImage* pPackagingMenuItem = CCMenuItemImage::create(
		"VideoUI/queding1.png",
		"VideoUI/queding2.png",
		this,
		menu_selector(mainScene::menuCallback));
	pPackagingMenuItem->setPosition(ccp(VISIBLEW / 2, VISIBLEH*0.15));

	if (!m_pFrontMovieVideoLayer)
	{
		m_pFrontMovieVideoLayer = MovieVideoLayer::create(FRONT);
	}
	m_pFrontMovieVideoLayer->ResetVideoSize();
	
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		"VideoUI/fanhuizhuye1.png",
		"VideoUI/fanhuizhuye2.png",
		this,
		menu_selector(mainScene::menuBackCallback));
	pBackItem->setPosition(ccp(116, 1000));

	m_pReadyLabel = CCSprite::create("VideoUI/ready.png");
	m_pReadyLabel->setPosition(ccp(1800, 800));
	m_pReadyLabel->setVisible(false);
	this->addChild(m_pReadyLabel);

	m_pReadyImage = CCSprite::create("VideoUI/xinhao.png");
	m_pReadyImage->setPosition(ccp(1800, 900));
	m_pReadyImage->setVisible(false);
	this->addChild(m_pReadyImage);

	if (Ext_cameraNum == 2)
	{
		if (!m_pSideMovieVideoLayer)
		{
			m_pSideMovieVideoLayer = MovieVideoLayer::create(SIDE);
		}
		m_pSideMovieVideoLayer->ResetVideoSize();
		
		if (Ext_IsFrontCamera != m_bIsTurnCamera)
		{
			swap(m_pSideMovieVideoLayer,m_pFrontMovieVideoLayer);
			m_bIsTurnCamera = Ext_IsFrontCamera;
		}
		SerialMager::getInstence()->setDelegate2(m_pSideMovieVideoLayer);
		m_pSideMovieVideoLayer->setScale(1.125);
		m_pSideMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 + 360-5, VISIBLEH / 2));
		this->addChild(m_pSideMovieVideoLayer);
	}

	SerialMager::getInstence()->setDelegate1(m_pFrontMovieVideoLayer);
	m_pFrontMovieVideoLayer->setScale(1.125);
	m_pFrontMovieVideoLayer->setPosition(ccp(VISIBLEW / 2 - 360, VISIBLEH / 2));
	this->addChild(m_pFrontMovieVideoLayer);

	MyMenu* m_pMenu = MyMenu::create(
		pBackItem,
		m_pCueTtpeArr[0],
		m_pCueTtpeArr[1],
		m_pCueTtpeArr[2],
		m_pCueTtpeArr[3],
		m_pGenderArr[0],
		m_pGenderArr[1],
		pPackagingMenuItem,
		NULL);
	m_pMenu->setPosition(CCPointZero);

	this->addChild(m_pMenu);
	this->scheduleUpdate();
	Ext_IsThreadOn = true;

    return true;
}
void mainScene::menuBackCallback(CCObject* pSender)
{
	Ext_IsThreadOn = false;
	this->unscheduleUpdate();
	
	CCDirector::sharedDirector()->replaceScene(SettingScene::getScene());
}
void mainScene::update(float dt)
{
	if (!SerialMager::getInstence()->getComPort())
	{
		CCMessageBox("请链接小盒子", "警告！");
		CCDirector::sharedDirector()->end();
	}
	SerialMager::getInstence()->SeriaUpdate();
	if (m_bIsPlayVideo == true)
	{
		if (Ext_cameraNum &&!m_pFrontMovieVideoLayer->m_IsPlayOver)
		{
			m_pFrontMovieVideoLayer->ShowVideo();
			m_pFrontMovieVideoLayer->TransData();
		}
		if (Ext_cameraNum == 2 && !m_pSideMovieVideoLayer->m_IsPlayOver)
		{
			m_pSideMovieVideoLayer->ShowVideo();
			m_pSideMovieVideoLayer->TransData();
		}
		if (!Ext_cameraNum || m_pFrontMovieVideoLayer->m_IsPlayOver)
		{
			if (m_bSetMode)
			{
				this->CallbackRePlay(NULL);
			}
			else
			{
				this->CallbackPreview(NULL);
			}
		}
	}
	else
	{
		if (Ext_cameraNum)
		{
			m_pFrontMovieVideoLayer->update(dt);
		}
		if (Ext_cameraNum == 2)
		{
			m_pSideMovieVideoLayer->update(dt);
		}
	}
	if (this->m_curMsg != SerialMager::getInstence()->m_curMsg)
	{
		m_curMsg = SerialMager::getInstence()->m_curMsg;
		if (m_curMsg == 2)
		{
			this->CallbackPreview(NULL);
			m_pReadyLabel->setVisible(true);
			m_pReadyImage->setVisible(true);
		}
		else
		{
			m_pReadyLabel->setVisible(false);
			m_pReadyImage->setVisible(false);
		}
	}
}
void mainScene::CallbackRePlay(CCObject* pSender)
{
	m_bIsPlayVideo = true;
	m_pFrontMovieVideoLayer->ReSetVideo();
	m_pFrontMovieVideoLayer->m_IsPlayOver = false;
	if (Ext_cameraNum == 2)
	{
		m_pSideMovieVideoLayer->ReSetVideo();
		m_pSideMovieVideoLayer->m_IsPlayOver = false;
	}
}
void mainScene::CallbackPreview(CCObject* pSender)
{
	m_pFrontMovieVideoLayer->ReSetVideo();
	if (Ext_cameraNum == 2)
	{
		m_pSideMovieVideoLayer->ReSetVideo();
	}
	m_bIsPlayVideo = false;
	Ext_IsThreadOn = true;
	Ext_IsRecordBegin = false;
}
//界面的触摸事件
void mainScene::menuCueTtpeCallback(CCObject* pSender)
{
	for (int i = 0; i < 4; i++)
	{
		m_pCueTtpeArr[i]->setEnabled(true);
		//判断有没有点击到球杆
		if (m_pCueTtpeArr[i] == pSender)
		{
			//记录选择的球杆
			m_curCueType = (CUETYPE)m_pCueTtpeArr[i]->getTag();
			//将标识控件移动到选择标签前
			m_pCueTtpeArr[i]->setEnabled(false);
			sprintf(m_FilePath1,
				DEMOVIDEO,
				Ext_FrameRate,
				m_curGender,
				m_curCueType,
				FRONT);
			sprintf(m_FilePath2,
				DEMOVIDEO,
				Ext_FrameRate,
				m_curGender,
				m_curCueType,
				SIDE);
		}
	}
}
void mainScene::menuGenderCallback(CCObject* pSender)
{
    for(int i = 0;i < 2;i++)
    {
		m_pGenderArr[i]->setEnabled(true);
        //判断有没有点击到性别
        if(m_pGenderArr[i] == pSender)
        {
            //记录选择的性别
            m_curGender = (GENDER)m_pGenderArr[i]->getTag();
            //将标识控件移动到选择标签前
			m_pGenderArr[i]->setEnabled(false);
			sprintf(m_FilePath1,
				DEMOVIDEO,
				Ext_FrameRate,
				m_curGender,
				m_curCueType,
				FRONT);
			sprintf(m_FilePath2,
				DEMOVIDEO,
				Ext_FrameRate,
				m_curGender,
				m_curCueType,
				SIDE);
        }
    }
}
void mainScene::menuCallback(CCObject* pSender)
{
	CCScene* pScene = MessageLayer::getScene();

	CCDirector::sharedDirector()->pushScene(pScene);
}