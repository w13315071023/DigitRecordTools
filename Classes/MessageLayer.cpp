#include "MessageLayer.h"
#include "mainScene.h"

CCScene* MessageLayer::getScene()
{
	CCScene* pScene = CCScene::create();
	MessageLayer* pLayer = MessageLayer::create();

	pScene->addChild(pLayer);
	return pScene;
}
MessageLayer::MessageLayer(void)
{
}
bool MessageLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_Acting = false;
	m_TimeNum = 0;
	m_MsgLabel = CCLabelTTF::create(GBKToUTF8("正在保存。。。").c_str(), "Arial", 72);
	m_MsgLabel->setPosition(ccp(VISIBLEW / 2, VISIBLEH*0.75));
	this->addChild(m_MsgLabel);

	this->scheduleUpdate();
	return true;
}
void MessageLayer::update(float dt)
{
	switch(m_TimeNum)
	{
	case 0:
		if(m_Acting)
		{
			return;
		}
		m_TimeNum++;
		break;
	case 1:
		if(m_Acting)
		{
			return;
		}
		Packaging();
		m_TimeNum++;
		break;
	case 2:
		if(m_Acting)
		{
			return;
		}
		m_MsgLabel->setString(GBKToUTF8("保存完成").c_str());
		m_TimeNum++;
		break;
	case 3:
		if(m_Acting)
		{
			return;
		}
		Sleep(2000);
		m_TimeNum++;
		CCDirector::sharedDirector()->popScene();
		break;
	}
}
void MessageLayer::Packaging()
{
	m_Acting = true;
	if(mainScene::m_pFrontMovieVideoLayer)
	{
		mainScene::m_pFrontMovieVideoLayer->PackagingVideo(mainScene::m_FilePath1);
	}
	if(mainScene::m_pSideMovieVideoLayer)
	{
		mainScene::m_pSideMovieVideoLayer->PackagingVideo(mainScene::m_FilePath2);
	}
	m_Acting = false;
}
MessageLayer::~MessageLayer(void)
{
}
