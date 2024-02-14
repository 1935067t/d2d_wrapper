#pragma once

#include<Windows.h>
#include<stdlib.h>
#include<wchar.h>

#include<vector>
#include<d2d1.h>
#include<d2d1helper.h>
#include<dwrite.h>
#include<wincodec.h>
#include<wrl.h>
#include<valarray>

//#include"DrawingContentsManager.h"
#include"DrawingContents.h"

//�ʂ̏������H
//#define DrawingMgr DrawingContentsManager::Instance()
using Microsoft::WRL::ComPtr;

class Direct2DBase
{

private:

	HWND m_hwnd;
	ComPtr<ID2D1Factory> m_Direct2DFactory;

	UINT m_FrameIndex;

	//Direct2D��DirectWrite�̏�����
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();


	//��肪�������Ƃ��Ƀf�o�C�X���������
	void DiscardDeviceResource();

	//�`��
	HRESULT OnRender();

	//�`��Ώۂ̃��T�C�Y
	void OnResize(UINT width, UINT height);

	//�E�B���h�E����
	static LRESULT CALLBACK WndProc(
		HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam
	);

protected:

	ComPtr<ID2D1HwndRenderTarget> m_RenderTarget;
	ComPtr<ID2D1SolidColorBrush> m_SolidColorBlush; //�}�`�╶���`��Ŏg���܂킷
	ComPtr<IDWriteFactory> m_WriteFactory;
	ComPtr<IDWriteTextFormat> m_WriteTextFormat;

	TEXTFORMAT m_TextFormat;
	D2D1_COLOR_F m_BackgroundColor;

	bool m_KeyDown[256];//�����ꂽ�u��true
	bool m_KeyUp[256];//�b�����u��true
	bool m_Key[256];//�����Ă����true

public:
	Direct2DBase();
	~Direct2DBase();

	HRESULT Initialize(HINSTANCE hInstance);

	//���C�����[�v
	void RunMessageRoop();

	//Application.cpp�ŏ���
	virtual void Update() = 0;
	virtual void Start() = 0;

};

