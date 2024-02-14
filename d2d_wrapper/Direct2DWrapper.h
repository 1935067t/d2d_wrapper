#pragma once
#include"Direct2DBase.h"
#include"DrawingContents.h"
#include<string>

namespace Wrapper {
	class Direct2DWrapper : public Direct2DBase
	{
	public:

		void SetBackGroundColor(D2D1_COLOR_F color);
		D2D1_SIZE_F GetWindowSize();

		void Draw(FILLED_RECT rect, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(FRAME_RECT rect, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(FILLED_ROUNDEDRECT rect, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(FRAME_ROUNDEDRECT rect, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(FILLED_ELLIPSE ellipse, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(FRAME_ELLIPSE ellipse, D2D1_COLOR_F color = { 0,0,0,1 });
		void Draw(LINE line, D2D1_COLOR_F color = { 0,0,0,1 });

		void DrawTexts(std::wstring text, FLOAT x, FLOAT y);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, D2D1_COLOR_F color);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, FLOAT fontsize);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, std::wstring fontname);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, D2D1_COLOR_F color, FLOAT fontsize);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, D2D1_COLOR_F color, std::wstring fontname);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y, FLOAT fontsize, std::wstring fontname);
		void DrawTexts(std::wstring text, FLOAT x, FLOAT y,
			D2D1_COLOR_F color,
			FLOAT fontsize,
			std::wstring fontname);

		//キーとマウスの押下判定
		bool GetKeyDown(int nVirtKey);
		bool GetKey(int nVirtKey);
		bool GetKeyUp(int nVirtKey);

	private:
		void ReCreateTextFormat();

		//Applicationクラスで使用できないようにする
		using Direct2DBase::m_RenderTarget;
		using Direct2DBase::m_SolidColorBlush;
		using Direct2DBase::m_WriteFactory;
		using Direct2DBase::m_WriteTextFormat;
		using Direct2DBase::m_TextFormat;
		using Direct2DBase::m_BackgroundColor;
		using Direct2DBase::m_KeyDown;
		using Direct2DBase::m_KeyUp;
		using Direct2DBase::m_Key;

	};
}