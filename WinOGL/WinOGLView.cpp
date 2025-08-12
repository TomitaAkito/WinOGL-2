
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_SIZEDOWN, &CWinOGLView::OnSizedown)
	ON_COMMAND(ID_SIZEUP, &CWinOGLView::OnSizeup)
	ON_COMMAND(ID_AXIS, &CWinOGLView::OnAxis)
	ON_UPDATE_COMMAND_UI(ID_AXIS, &CWinOGLView::OnUpdateAxis)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT, &CWinOGLView::OnEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT, &CWinOGLView::OnUpdateEdit)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT*/);


	AC.Draw();

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー

void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetLButton(nFlags, point);

	AC.LButtonDownFlag = true;

	if (AC.EditFlag) AC.Edit(x_Ldown, y_Ldown);
	else  AC.SetVertex(x_Ldown, y_Ldown);

	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}

void CWinOGLView::SetLButton(UINT nFlags, CPoint point) {
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);

	x_Ldown = point.x;
	y_Ldown = point.y;

	double rectWidth = static_cast<double>(rect.Width());
	double rectHeight = static_cast<double>(rect.Height());

	// 正規化座標系に変換
	x_Ldown = x_Ldown / (rectWidth);
	y_Ldown = y_Ldown / (rectHeight);

	// ワールド座標系に変換
	x_Ldown = (x_Ldown * 2.0) - 1.0; // 左端が-1.0、右端が1.0
	y_Ldown = 1.0 - (y_Ldown * 2.0); // 上端が1.0、下端が-1.0

	// 縦横比を考慮して座標を調整
	if (rectWidth > rectHeight) {
		x_Ldown *= rectWidth / rectHeight;
	}
	else {
		y_Ldown *= rectHeight / rectWidth;
	}
}

int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	24,
	0,0,
	PFD_MAIN_PLANE,
	0,
	0,0,0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC,
		&pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);
}

BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspect;

	if (cx > cy)
	{
		aspect = static_cast<double>(cx) / static_cast<double>(cy);
		glOrtho(-aspect, aspect, -1.0, 1.0, -100.0, 100.0);
	}
	else
	{
		aspect = static_cast<double>(cy) / static_cast<double>(cx);
		glOrtho(-1.0, 1.0, -aspect, aspect, -100.0, 100.0);
	}

	glMatrixMode(GL_MODELVIEW);
	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}
void CWinOGLView::OnSizedown() {
	AC.DrawSizeChangeDOWN();
	RedrawWindow();
}

void CWinOGLView::OnSizeup() {
	AC.DrawSizeChangeUP();
	RedrawWindow();
}

void CWinOGLView::OnAxis() {
	AC.AxisFlag = !AC.AxisFlag;
	RedrawWindow();
}

void CWinOGLView::OnUpdateAxis(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(AC.AxisFlag);
}

void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point) {
	SetLButton(nFlags, point);
	AC.SetMouseVertex(x_Ldown, y_Ldown);

	if (AC.LButtonDownFlag && AC.EditFlag)AC.moveByMouse();

	RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}

void CWinOGLView::OnEdit() {
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.EditFlag = !AC.EditFlag;
	RedrawWindow();
}

void CWinOGLView::OnUpdateEdit(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(AC.EditFlag);
}

void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point) {
	AC.LButtonDownFlag = false;
	CView::OnLButtonUp(nFlags, point);
}
