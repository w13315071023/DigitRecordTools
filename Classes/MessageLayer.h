#pragma once
#include "Tools.h"

class MessageLayer:public CCLayer,public Reseaver
{
public:
	static CCScene* getScene();
	CREATE_FUNC(MessageLayer);
	virtual bool init();
	virtual void update(float dt);
public:
	MessageLayer(void);
	~MessageLayer(void);
	void Packaging();
public:
	CCLabelTTF* m_MsgLabel;
	int m_TimeNum;
	bool m_Acting;
};

