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
	void SetCameraCallBack(CCObject* obj);
	void SetQingjingCallBack(CCObject* obj);
public:
	bool m_isBeginButtonOn;
	bool m_isEndButtonOn;
};