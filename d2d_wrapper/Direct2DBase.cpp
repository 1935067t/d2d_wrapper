#include "Direct2DBase.h"
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//#include "DrawingContents.h"
//#include"DrawingContentsManager.h"
//#define DrawingMgr DrawingContentsManager::Instance()


//�R���X�g���N�^
Direct2DBase::Direct2DBase() :
	m_hwnd(NULL),
	m_Direct2DFactory(NULL),
	m_RenderTarget(NULL),
	m_SolidColorBlush(NULL)
{}

//�f�X�g���N�^
Direct2DBase::~Direct2DBase()
{
	//�����[�X�H
}

HRESULT Direct2DBase::Initialize(HINSTANCE hInstance)
{
	HRESULT hr;

	//�e�L�X�g�t�H���g�̏����ݒ�
	m_TextFormat.fontname = L"Verdana";
	m_TextFormat.fontsize = 30;
	//�w�i�F�̏����ݒ�
	m_BackgroundColor = { 1,1,1,1 };


	//direct2D Factory�̂悤��devce-independent ���\�[�X��������
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		//�E�B���h�E�N���X�o�^
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Direct2DBase::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = hInstance;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = L"D2DDemoApp";

		RegisterClassEx(&wcex);

		//DPI�̊֌W�łЂƎ�Ԃ���
		m_hwnd = CreateWindow(
			L"D2DDemoApp",
			L"Direct2D demo",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			NULL,
			NULL,
			hInstance,
			this
		);

		if (m_hwnd)
		{
			float dpi = GetDpiForWindow(m_hwnd);
			auto g_DPIScale = dpi / USER_DEFAULT_SCREEN_DPI;

			SetWindowPos(
				m_hwnd,
				NULL,
				NULL,
				NULL,
				static_cast<int>(ceil(640.0f * dpi / 96.0f)),
				static_cast<int>(ceil(480.0f * dpi / 96.0f)),
				SWP_NOMOVE
			);

			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}
	m_FrameIndex = 0;

	for (int j = 0; j < 256; ++j)
	{
		m_KeyDown[j] = false;
		m_KeyUp[j] = false;
		m_Key[j] = false;
	}

	Start();

	return hr;
}

void Direct2DBase::RunMessageRoop()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT Direct2DBase::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;


	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_Direct2DFactory.ReleaseAndGetAddressOf());
	if (hr == S_OK)
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &m_WriteFactory);
	}
	if (hr == S_OK)
	{
		hr = m_WriteFactory->CreateTextFormat(m_TextFormat.fontname.c_str(), NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			m_TextFormat.fontsize,
			L"",
			m_WriteTextFormat.GetAddressOf());
	}
	if (hr == S_OK)
	{
		m_WriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
		m_WriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	return hr;
}

HRESULT Direct2DBase::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_RenderTarget.Get())
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		//�����_�[�^�[�Q�b�g�쐬
		hr = m_Direct2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			m_RenderTarget.ReleaseAndGetAddressOf()
		);
		
		//�J���[�u���V�쐬
		if (SUCCEEDED(hr))
		{
			hr = m_RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				m_SolidColorBlush.ReleaseAndGetAddressOf()
			);
		}

	}

	return hr;
}


void Direct2DBase::DiscardDeviceResource()
{
	m_RenderTarget.Reset();
	m_SolidColorBlush.Reset();
	m_WriteFactory.Reset();
	m_WriteTextFormat.Reset();
}

LRESULT CALLBACK Direct2DBase::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		Direct2DBase* p_direct2D = (Direct2DBase*)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(p_direct2D)
		);

		result = 1;

		SetTimer(hwnd, 1000, 15, NULL);
	}

	else
	{
		Direct2DBase* pD2DW = reinterpret_cast<Direct2DBase*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));

		bool wasHandled = false;

		if (pD2DW)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pD2DW->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			//�}�E�X�A�L�[�{�[�h����������
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_KEYDOWN:
			{
				if (pD2DW->m_Key[wParam] == true) break;

				pD2DW->m_KeyDown[wParam] = true;
				pD2DW->m_Key[wParam] = true;
			}
			result = 0;
			wasHandled = true;
			break;

			//�}�E�X���{�^���𗣂����Ƃ�
			case WM_LBUTTONUP:
			{
				pD2DW->m_KeyUp[VK_LBUTTON] = true;
				pD2DW->m_Key[VK_LBUTTON] = false;
			}
			result = 0;
			wasHandled = true;
			break;

			//�}�E�X�E�{�^���𗣂����Ƃ�
			case WM_RBUTTONUP:
			{
				pD2DW->m_KeyUp[VK_RBUTTON] = true;
				pD2DW->m_Key[VK_RBUTTON] = false;
			}
			result = 0;
			wasHandled = true;
			break;

			//�L�[�𗣂����Ƃ�
			case WM_KEYUP:
			{
				pD2DW->m_KeyUp[wParam] = true;
				pD2DW->m_Key[wParam] = false;
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_TIMER:
			{
				if (wParam != 1000)
				{
					result = DefWindowProc(hwnd, message, wParam, lParam);
					break;
				}
				InvalidateRect(hwnd, NULL, FALSE);
			}

			case WM_PAINT:
			{
				pD2DW->OnRender();
				ValidateRect(hwnd, NULL);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}

HRESULT Direct2DBase::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		//�`��̊J�n�A�w�i���N���A
		m_RenderTarget->BeginDraw();
		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_RenderTarget->Clear(m_BackgroundColor);


		//Application�N���X�ŕ`����e������
		Update();

		hr = m_RenderTarget->EndDraw();

		//���̃t���[���ŃL�[���삪����ꍇ��
		for (int j = 0; j < 256; ++j)
		{
			m_KeyDown[j] = false;
			m_KeyUp[j] = false;
		}

	}
	//�����_�[�^�[�Q�b�g���č쐬����K�v������Ƃ���discard���ĉ������
	//����wm_paint��wm_displaychange����M����ƍč쐬�����
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResource();
	}

	return hr;
}

//�E�B���h�E�T�C�Y��ύX�����Ƃ��ɌĂ΂��
void Direct2DBase::OnResize(UINT width, UINT height)
{
	if (m_RenderTarget.Get())
	{
		m_RenderTarget->Resize(D2D1::SizeU(width, height));
	}
}