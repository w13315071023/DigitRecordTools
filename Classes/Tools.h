#pragma once

#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "tchar.h"
#include "cocos2d.h"
#include <Windows.h>
#include"cocos-ext.h"
#include "CocoStudio\Json\rapidjson\stringbuffer.h"
#include "CocoStudio\Json\rapidjson\writer.h"
#include "GL\glew.h"
#include "GL\wglew.h"
#include <windows.h>
#include "CameraApi.h"
#include "CameraGrabber.h"
#include <ocidl.h>
#include "CameraImage.h"
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <libavutil/parseutils.h>
#include <libavutil/opt.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
}


using namespace std;
using namespace rapidjson;

USING_NS_CC;
USING_NS_CC_EXT;

#define FRONT 15
#define SIDE 16

#define PI 3.1415926535
#define LINEWIDTH 3
#define GRAVITY 9.8
#define VISIBLEW CCDirector::sharedDirector()->getVisibleSize().width
#define VISIBLEH CCDirector::sharedDirector()->getVisibleSize().height
#define BIANKUANG 20

extern INT Ext_cameraNum;
extern int Ext_VideoSize;
extern int Ext_VideoSleep;
extern int Ext_SerialThreshold;
extern int Ext_VideoGain;
extern int Ext_StepNum;
extern int Ext_FFmpegStep;

extern int Ext_VideoExposureTime;

extern bool Ext_IsThreadOn;
extern bool Ext_IsRecordBegin;
extern bool Ext_TiaoShi;
extern bool Ext_IsFrontCamera;
extern bool Ext_IsTurnCamera;
extern bool Ext_IsTurnEnd;

enum MENUTAG
{
    MENUTAG_FrontView = 1000,		//������ͼ
    MENUTAG_FourView,				//4��ͼ
    MENUTAG_SideView,				//������ͼ
    MENUTAG_FrontAndSide,			//��/������ͼ
	MENUTAG_FrontDemoView,
    MENUTAG_Back,					//����
    MENUTAG_DataAnalysis,			//���ݷ���
    MENUTAG_PostureAnalysis,		//���Ʒ���
};
enum GENDER
{
    GENDER_MAN = 50,
    GENDER_WOMAN,
};
enum CUETYPE
{
    CUETYPE_YIHAOMU = 220,
    CUETYPE_MUGAN = 190,
    CUETYPE_TIEGAN = 140,
    CUETYPE_WAQIGAN = 110,
};
typedef struct _OutputStream
{
	AVStream* st;
	AVFrame* videoFrame;
	AVFrame* audioFrame;

	int64_t next_pts;
	float t, tincr,tinct2;
	struct SwsContext* sws_ctx;
	struct SwrContext* swr_ctx;
}OutputStream;
struct VideoRAW
{
	unsigned char* FrameData;
	tSdkFrameHead  FrameHead;
};
class Sender
{
public:
	virtual void Record(bool isRecord) = 0;
	virtual void RecordOk() = 0;
	virtual void PackagingCallBack(CCObject* pSender) = 0;
};
class Reseaver
{
public:
	
	Sender* m_Delegate1;
	Sender* m_Delegate2;
	Sender* m_MsgDelegate;
	Reseaver(void)
	{
		m_Delegate1 = NULL;
		m_Delegate2 = NULL;
		m_MsgDelegate = NULL;
	}
	void setDelegate1(Sender* del)
	{
		m_Delegate1 = del;
	}
	void setDelegate2(Sender* del)
	{
		m_Delegate2 = del;
	}
	void setMsgDelegate(Sender* del)
	{
		m_MsgDelegate = del;
	}
};
inline float GetTime(void)
{
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float)((counter - start) / double(frequency));

}
string GBKToUTF8(const string& strGBK);
bool readValue(const char* pszFileName, Document& value);
void saveValue(rapidjson::Value& root, const char* pszFileName);