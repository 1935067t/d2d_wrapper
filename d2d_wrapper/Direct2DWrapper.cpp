#include"Direct2DWrapper.h"
#include"DrawingContents.h"
#include<string>

using namespace Wrapper;
//
//public関数
//

//背景色をセット
//Update()の中で使用した場合次のフレームで反映される
void Direct2DWrapper::SetBackGroundColor(D2D1_COLOR_F color)
{
	m_BackgroundColor.a = color.a;
	m_BackgroundColor.b = color.b;
	m_BackgroundColor.g = color.g;
	m_BackgroundColor.r = color.r;
}

D2D1_SIZE_F Direct2DWrapper::GetWindowSize()
{
	return m_RenderTarget->GetSize();
}

//描画関数

void Direct2DWrapper::Draw(FILLED_RECT rect, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->FillRectangle(rect.rect, m_SolidColorBlush.Get());
}
void Direct2DWrapper::Draw(FRAME_RECT rect, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->DrawRectangle(rect.rect, m_SolidColorBlush.Get(), rect.strokeWidth);
}
void Direct2DWrapper::Draw(FILLED_ROUNDEDRECT rect, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->FillRoundedRectangle(rect.roundedRect, m_SolidColorBlush.Get());
}
void Direct2DWrapper::Draw(FRAME_ROUNDEDRECT rect, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->DrawRoundedRectangle(rect.roundedRect, m_SolidColorBlush.Get(), rect.strokeWidth);
}
void Direct2DWrapper::Draw(FILLED_ELLIPSE ellipse, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->FillEllipse(ellipse.ellipse, m_SolidColorBlush.Get());
}
void Direct2DWrapper::Draw(FRAME_ELLIPSE ellipse, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->DrawEllipse(ellipse.ellipse, m_SolidColorBlush.Get(), ellipse.strokeWidth);
}
void Direct2DWrapper::Draw(LINE line, D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);
	m_RenderTarget->DrawLine(line.start, line.end, m_SolidColorBlush.Get(), line.strokeWidth);
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y)
{
	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	FLOAT fontsize)
{
	m_TextFormat.fontsize = fontsize;
	ReCreateTextFormat();

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	std::wstring fontname)
{
	m_TextFormat.fontname = fontname;
	ReCreateTextFormat();

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	D2D1_COLOR_F color)
{
	m_SolidColorBlush->SetColor(color);

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	D2D1_COLOR_F color, std::wstring fontname)
{
	m_TextFormat.fontname = fontname;

	ReCreateTextFormat();
	m_SolidColorBlush->SetColor(color);

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	D2D1_COLOR_F color, FLOAT fontsize)
{
	m_TextFormat.fontsize = fontsize;

	ReCreateTextFormat();
	m_SolidColorBlush->SetColor(color);

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	FLOAT fontsize, std::wstring fontname)
{

	m_TextFormat.fontsize = fontsize;
	m_TextFormat.fontname = fontname;

	ReCreateTextFormat();

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

void Direct2DWrapper::DrawTexts(std::wstring text, FLOAT x, FLOAT y,
	D2D1_COLOR_F color, FLOAT fontsize, std::wstring fontname)
{
	m_TextFormat.fontsize = fontsize;
	m_TextFormat.fontname = fontname;

	ReCreateTextFormat();
	m_SolidColorBlush->SetColor(color);

	int len = text.length();
	const WCHAR* wcstring = text.c_str();
	m_RenderTarget->DrawText(wcstring, len, m_WriteTextFormat.Get(),
		D2D1::RectF(x, y, x + len * m_TextFormat.fontsize, y + m_TextFormat.fontsize), m_SolidColorBlush.Get());
}

/**
* @fn
* そのフレームでキーが押されたならtrueを返す
* @param nVirtKey 仮想キーの値（1～254）
* https://learn.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes
**/
bool Direct2DWrapper::GetKeyDown(int nVirtKey)
{
	return m_KeyDown[nVirtKey];
}

/**
* @fn
* キーが押されている状態ならばtrue
* @param nVirtKey 仮想キーの値（1～254）
* https://learn.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes
**/
bool Direct2DWrapper::GetKey(int nVirtKey)
{
	return m_Key[nVirtKey];
}

/**
* @fn
* このフレームでキーが離されたならばtrue
* @param nVirtKey 仮想キーの値（1～254）
* https://learn.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes
**/
bool Direct2DWrapper::GetKeyUp(int nVirtKey)
{
	return m_KeyUp[nVirtKey];
}

//
// private関数
// 

void Direct2DWrapper::ReCreateTextFormat()
{
	m_WriteFactory->CreateTextFormat(m_TextFormat.fontname.c_str(), NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_TextFormat.fontsize,
		L"",
		m_WriteTextFormat.ReleaseAndGetAddressOf());
}