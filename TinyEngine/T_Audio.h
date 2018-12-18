//*******************************************************************
// TinyEngine引擎  
// 作者: 万立中(WanLizhong)
// 博客: www.wanlizhong.com 
// 日期: 2013-08-02
// 更新: 2018-12-13
// 版权所有 2007-2018 万立中
// (C) 2007-2018 WanLizhong All Rights Reserved
//*******************************************************************

#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <dsound.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
 
class AudioDX; //由于要先引用，所以需先声明后定义

//………………………………………………………………………………………………
// wave格式的读取类
//………………………………………………………………………………………………
class AudioWave {
public:
	AudioWave();
	virtual ~AudioWave();
	//打开并读取WAVE文件
	bool Open(const wchar_t *path);
	//读取并查询是否存在data区块
	bool StartRead();
	//读取指定数据
	bool Read(unsigned long size, void *data, unsigned long *nread);
	//释放占用的资源
	bool Close();
	//获取wave格式属性
	WAVEFORMATEX *GetFormat() { return wfex; }
	//获取区块大小
	DWORD CkSize() const { return ckIn.cksize; }

protected:
	WAVEFORMATEX *wfex; //wave格式结构体指针
	HMMIO hmmio;		//文件句柄	
	MMCKINFO ckIn;		//MMCKINFO对象（查询用子块）
	MMCKINFO ckInRIFF;	//MMCKINFO对象（父块，从文件获取）
} ;


//………………………………………………………………………………………………
// AudioDXBuffer类
//………………………………………………………………………………………………
class AudioDXBuffer 
{
protected:
	LPDIRECTSOUNDBUFFER SndBuf;		// 缓冲区接口指针
	LONG Volume;					// 音量
	LONG Pan;						// 左右声道相对音量
	DWORD Freq;						// 频率

public:
	AudioDXBuffer();
	~AudioDXBuffer();
	// 创建辅助缓冲区并设计基本属性
	bool CreateBuffer(AudioDX &ds, WAVEFORMATEX *format, int size);
	// 创建主缓冲区并将主缓冲区设定为WAVE格式
	bool CreateMainBuffer(AudioDX &ds, int freq=22050);
	// 读入WAVE文件,并将文件数据写入缓冲区
	bool LoadWave(AudioDX &ds, const wchar_t *path);
	// 释放所有资源
	HRESULT Release();
	// 恢复缓冲区
	HRESULT Restore();
	// 终止处理(恢复缓冲区并停止声音播放)
	void Terminate();
	// 播放声音(参数决定是否循环)
	bool Play(bool loop=false)
	{
		if(SndBuf == NULL) return false;
		if (FAILED(SndBuf->Play(0, 0, loop? DSBPLAY_LOOPING: 0)))
			return false;
		return true;
	}
	// 停止声音播放
	bool Stop(){ return SndBuf->Stop() == DS_OK; }
	// 判断缓冲区是否处于活跃状态
	bool IsAlive() const { return SndBuf != 0; }
	// 重载"->"操作符, 表示SndBuf对象
	LPDIRECTSOUNDBUFFER operator ->() { return SndBuf; }
	
} ;


//………………………………………………………………………………………………
// AudioDX类
//………………………………………………………………………………………………
class AudioDX 
{
public:
	AudioDX();
	~AudioDX();
	// 创建DirectSound对象、设置合作级别并创建主缓冲区
	bool CreateDS(HWND hWnd, int freq=22050);
	// 释放DirectSound对象及DirectSound缓冲区对象
	void ReleaseAll();
	// 失去缓冲区内存时则复原
	HRESULT RestoreAll();
	// 重载"->"操作符, 表示ds对象
	LPDIRECTSOUND operator ->() { return ds; }

protected:
	LPDIRECTSOUND ds;		// DirectSound对象
	AudioDXBuffer dsbuf;	// DirectSound缓冲对象
} ;
