
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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ALLDELETE, &CWinOGLView::OnAlldelete)
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYUP()
	ON_COMMAND(ID_SHOW_VCL, &CWinOGLView::OnShowVcl)
	ON_COMMAND(ID_FILE_SAVE_AS, &CWinOGLView::OnFileSaveAs)
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
	AC.LButtonDownVeretex->SetXY(x_Ldown, y_Ldown);

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

	if (AC.LButtonDownFlag && AC.EditFlag && AC.selectShapeFlag && AC.ShiftFlag)AC.resizeShape();
	else if (AC.LButtonDownFlag && AC.EditFlag && AC.selectShapeFlag && AC.keyRFlag)AC.rotateShape();
	else if (AC.LButtonDownFlag && AC.EditFlag)AC.moveByMouse();

	RedrawWindow();
	CView::OnMouseMove(nFlags, point);
}

void CWinOGLView::OnEdit() {
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.EditFlag = !AC.EditFlag;
	AC.resetEdit();
	RedrawWindow();
}

void CWinOGLView::OnUpdateEdit(CCmdUI* pCmdUI) {
	pCmdUI->SetCheck(AC.EditFlag);
}

void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point) {
	AC.LButtonDownFlag = false;
	if(AC.EditFlag) AC.LButtonUp();
	CView::OnLButtonUp(nFlags, point);
}

void CWinOGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case VK_DELETE:
		if (AC.EditFlag) {
			AC.deleteVertex();
		}
		RedrawWindow();
		break;
	case VK_TAB:
		OnEdit();
		break;
	case VK_SHIFT:
		AC.ShiftFlag = true;
		break;
	case 'R':
		AC.keyRFlag = true;
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CWinOGLView::OnAlldelete() {
	AC.freeALLShape();
	RedrawWindow();
}

BOOL CWinOGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CWinOGLView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case VK_SHIFT:
		AC.ShiftFlag = false;
		break;
	case 'R':
		AC.keyRFlag = false;
		break;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

CString CWinOGLView::addExtension(CString filepath) {
	// ファイルパスから拡張子を抽出
	int dotIndex = filepath.ReverseFind('.');

	// 拡張子がない場合
	if (dotIndex == -1 || dotIndex == filepath.GetLength() - 1) {
		// ".txt" を追加
		return filepath + _T(".vclcad");
	}
	else {
		// 拡張子がある場合はそのまま返す
		return filepath;
	}
}

void CWinOGLView::OnShowVcl() {
	ShellExecute(NULL, _T("open"), _T("chrome.exe"), _T("https://vclabo.com/index.html"), NULL, SW_SHOWNORMAL);
}

#include <vector>
#include <map>
#include <utility>

void CWinOGLView::OnFileSaveAs() {
	CFileDialog dlg(FALSE, _T("ply"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("PLY File (*.ply)|*.ply|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK) {
		// --- ステップ1: ユニークな頂点と面の情報を収集 ---

		std::vector<std::pair<float, float>> unique_vertices;
		std::map<std::pair<float, float>, int> vertex_map;
		std::vector<std::vector<int>> faces;

		for (CShape* nowShape = AC.GetShapeHead(); nowShape != NULL; nowShape = nowShape->GetNext()) {

			// 【修正箇所】このシェイプが有効な面（頂点3つ以上）かチェックする
			int vertices_in_this_shape = 0;
			for (CVertex* v_check = nowShape->GetVertexHead(); v_check != NULL; v_check = v_check->GetNext()) {
				vertices_in_this_shape++;
			}

			// 頂点が3つ未満の場合は「縮退した面」なのでスキップする
			if (vertices_in_this_shape < 3) {
				continue; // このforループの次のCShapeへ
			}
			// 【修正ここまで】

			std::vector<int> current_face_indices;
			for (CVertex* nowVertex = nowShape->GetVertexHead(); nowVertex != NULL; nowVertex = nowVertex->GetNext()) {
				std::pair<float, float> current_pos(nowVertex->GetX(), nowVertex->GetY());

				auto it = vertex_map.find(current_pos);

				if (it == vertex_map.end()) {
					int new_index = unique_vertices.size();
					unique_vertices.push_back(current_pos);
					vertex_map[current_pos] = new_index;
					current_face_indices.push_back(new_index);
				}
				else {
					current_face_indices.push_back(it->second);
				}
			}
			faces.push_back(current_face_indices);
		}

		// --- ステップ2: 収集した情報をもとにファイルに書き込む ---
		// (変更なし)

		FILE* fp = NULL;
		CStringA filePathA(dlg.GetPathName());
		const char* save_file = filePathA;

		if (fopen_s(&fp, save_file, "w") != 0 || fp == NULL) {
			AfxMessageBox(_T("ファイルの書き込みオープンに失敗しました。"));
			return;
		}

		// PLYヘッダーを書き込む
		fprintf_s(fp, "ply\n");
		fprintf_s(fp, "format ascii 1.0\n");

		fprintf_s(fp, "comment Generated by VCL-ATDIGITAL-CAD\n");
		fprintf_s(fp, "comment For OHUZAKE 2025/08\n");
		fprintf_s(fp, "comment Info: Visual Computing Lab. \n");

		fprintf_s(fp, "element vertex %zu\n", unique_vertices.size());
		fprintf_s(fp, "property float x\n");
		fprintf_s(fp, "property float y\n");
		fprintf_s(fp, "property float z\n");
		fprintf_s(fp, "element face %zu\n", faces.size());
		fprintf_s(fp, "property list uchar int vertex_indices\n");
		fprintf_s(fp, "end_header\n");

		// 頂点データを書き込む
		for (const auto& vertex : unique_vertices) {
			fprintf_s(fp, "%f %f %f\n", vertex.first, vertex.second, 0.0f);
		}

		// 面データを書き込む
		for (const auto& face : faces) {
			fprintf_s(fp, "%zu", face.size());
			for (const auto& index : face) {
				fprintf_s(fp, " %d", index);
			}
			fprintf_s(fp, "\n");
		}

		fclose(fp);
	}
}