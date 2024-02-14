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

//別の書き方？
//#define DrawingMgr DrawingContentsManager::Instance()
using Microsoft::WRL::ComPtr;

class Direct2DBase
{

private:

	HWND m_hwnd;
	ComPtr<ID2D1Factory> m_Direct2DFactory;

	UINT m_FrameIndex;

	//Direct2DやDirectWriteの初期化
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();


	//問題があったときにデバイスを解放する
	void DiscardDeviceResource();

	//描画
	HRESULT OnRender();

	//描画対象のリサイズ
	void OnResize(UINT width, UINT height);

	//ウィンドウ生成
	static LRESULT CALLBACK WndProc(
		HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam
	);

protected:

	ComPtr<ID2D1HwndRenderTarget> m_RenderTarget;
	ComPtr<ID2D1SolidColorBrush> m_SolidColorBlush; //図形や文字描画で使いまわす
	ComPtr<IDWriteFactory> m_WriteFactory;
	ComPtr<IDWriteTextFormat> m_WriteTextFormat;

	TEXTFORMAT m_TextFormat;
	D2D1_COLOR_F m_BackgroundColor;

	bool m_KeyDown[256];//押された瞬間true
	bool m_KeyUp[256];//話した瞬間true
	bool m_Key[256];//押している間true

public:
	Direct2DBase();
	~Direct2DBase();

	HRESULT Initialize(HINSTANCE hInstance);

	//メインループ
	void RunMessageRoop();

	//Application.cppで書く
	virtual void Update() = 0;
	virtual void Start() = 0;

};

