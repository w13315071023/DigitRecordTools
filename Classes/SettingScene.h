#pragma once
#include "Tools.h"

class SettingScene:public CCLayer
{
public:
	CCControlSlider* m_VideoSleepSlider;
	CCControlSlider* m_SerialThresholdSlider;
	CCControlSlider* m_VideoGainSlider;

	CCLabelTTF* m_VideoSleepLabel;
	CCLabelTTF* m_SerialThresholdLabel;
	CCLabelTTF* m_VideoGainLabel;

	CCMenuItemImage* m_pFrames60;
	CCMenuItemImage* m_pFrames300;
public:
	static CCScene* getScene();
	CREATE_FUNC(SettingScene);
	SettingScene(void);
	~SettingScene(void);
	virtual bool init();
	virtual void update(float dt);
	virtual void onExit();
	void valueChanged(CCObject* sender, CCControlEvent controlEvent);
	void menuStartCallback(CCObject* pSender);
	void menuExitCallback(CCObject* pSender);
	void menuFramesCallBack(CCObject* obj);
	void SetCameraCallBack(CCObject* obj);
	void SetQingjingCallBack(CCObject* obj);
public:
	bool m_isBeginButtonOn;
	bool m_isEndButtonOn;
};