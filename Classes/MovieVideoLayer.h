#pragma once
#include "Tools.h"

USING_NS_CC;
class RecordClass;
class MovieVideoLayer :public Sender, public CCLayer 
{
public:
	static RecordClass* m_Camera1;
	static RecordClass* m_Camera2;

	bool m_IsPlayOver;
	bool m_IsRecord;

	float m_Width;
	float m_Height;

	vector<unsigned char*> m_VideoList;
	int m_ShowIndex;
	int m_TransIndex;
	int m_VideoIndex;

	RecordClass* m_Camera;
	unsigned char* m_pFrameImageRGB;
	tSdkFrameHead m_FrameImageHead;
	
	AVFrame* m_pRGBFrame;  //RGB帧数据      
	AVFrame* m_pYUVFrame;  //YUV帧数据   
	static SwsContext* pSwsCtx;

	CCTexture2D* m_pTexture;
	CCSprite* m_pSprite;
public:
	MovieVideoLayer();
	~MovieVideoLayer();
    static MovieVideoLayer* create(int Direction);
	bool init(int Direction);
	void update(float dt);

	void ShowVideo();
	void ReSetVideo();
	void Record(bool isRecord);
	void TransData();
	void RecordOk();
	void ResetVideoSize();
	void PackagingVideo(const char* pFilePath);
	void Add_audio_viode_stream(OutputStream* viode_st, OutputStream* audio_st, AVFormatContext* oc, AVCodec* video_encoder, AVCodec* audio_encoder);
	void fill_yuv_image(int imageInx);
};
