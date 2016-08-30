#include "MessageLayer.h"
#include "mainScene.h"

CCScene* MessageLayer::getScene()
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer = CCLayer::create();

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
	m_MsgLabel = CCLabelTTF::create(GBKToUTF8("ÕýÔÚ±£´æ¡£¡£¡£").c_str(), "Arial", 72);
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
		break;
	case 1:
		break;
	}
}
void MessageLayer::Packaging()
{
	m_Acting = true;
	if(m_MsgDelegate)
	{
		m_MsgDelegate->PackagingCallBack(NULL);
	}
	m_Acting = false;
}
MessageLayer::~MessageLayer(void)
{
}
