#include "Direct2DBase.h"
#include"Application.h"
using namespace Wrapper;
_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			//Direct2DBase app;
			Application app;

			if (SUCCEEDED(app.Initialize(hInstance)))
			{
				app.RunMessageRoop();
			}
		}
		CoUninitialize();
	}
	return 0;
}