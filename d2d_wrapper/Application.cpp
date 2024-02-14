#include "Application.h"
#include <string>

FILLED_RECT field;
std::wstring text;
POINT point;

using namespace Wrapper;
void Application::Start()
{

	field.rect = D2D1::RectF(80.0f, 50.0f, 280.0f, 450.0f);
	text = L"Hello World.";
}

void Application::Update()
{
	Draw(field);

	//左クリックでテキスト描画
	if(GetKey(VK_LBUTTON))
	DrawTexts(text, 0, 0);

}