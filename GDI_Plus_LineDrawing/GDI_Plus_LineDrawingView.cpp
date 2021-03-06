
// GDI_Plus_LineDrawingView.cpp: CGDIPlusLineDrawingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GDI_Plus_LineDrawing.h"
#endif

#include "GDI_Plus_LineDrawingDoc.h"
#include "GDI_Plus_LineDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIPlusLineDrawingView

IMPLEMENT_DYNCREATE(CGDIPlusLineDrawingView, CView)

BEGIN_MESSAGE_MAP(CGDIPlusLineDrawingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGDIPlusLineDrawingView 생성/소멸

CGDIPlusLineDrawingView::CGDIPlusLineDrawingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	L_MouseDown = false;
}

CGDIPlusLineDrawingView::~CGDIPlusLineDrawingView()
{
}

BOOL CGDIPlusLineDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGDIPlusLineDrawingView 그리기

void CGDIPlusLineDrawingView::OnDraw(CDC* /*pDC*/)
{
	CGDIPlusLineDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGDIPlusLineDrawingView 인쇄

BOOL CGDIPlusLineDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGDIPlusLineDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGDIPlusLineDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGDIPlusLineDrawingView 진단

#ifdef _DEBUG
void CGDIPlusLineDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIPlusLineDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIPlusLineDrawingDoc* CGDIPlusLineDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIPlusLineDrawingDoc)));
	return (CGDIPlusLineDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIPlusLineDrawingView 메시지 처리기

// 화면을 그려야 할 때 지금 화면을 지우는 과정에서 발생하는 메시지합수
BOOL CGDIPlusLineDrawingView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;//강제로 리턴을 해서 화면이 지워지고 다시 그려지는 과정을 제거.
}

//선 그리기 시작
void CGDIPlusLineDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	L_MouseDown = true;//왼쪽 버튼 클릭

	list_Shape.AddTail(CShape(point));//시작점 추가

	CView::OnLButtonDown(nFlags, point);
}

//선 그리기
void CGDIPlusLineDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (L_MouseDown)//왼쪽 버튼을 누르면
	{
		list_Shape.GetTail().End = point;//끝 지점 저장

		Invalidate();//화면 갱신
	}

	CView::OnMouseMove(nFlags, point);
}

//선 그리기 종료
void CGDIPlusLineDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	list_Shape.GetTail().End = point;//끝 지점 저장

	L_MouseDown = false;

	Invalidate();//화면 갱신

	CView::OnLButtonUp(nFlags, point);
}

//화면
void CGDIPlusLineDrawingView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	//화면의 크기를 구한다.
	CRect rect;
	GetClientRect(&rect);

	//더블 버퍼링
	/*
	Bitmap bitmap(rect.Width(), rect.Height());
	Graphics graphics(dc);
	Graphics MemGraphics(&bitmap);

	Pen Black(Color(0, 0, 0), 1);

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 255, 255, 255));
	MemGraphics.FillRectangle(&WhiteBrush, 0, 0, rect.Width(), rect.Height());

	POSITION position = list_Shape.GetHeadPosition();
	while (position)
	{
		CShape shape = list_Shape.GetNext(position);//리스트 호출

		MemGraphics.DrawLine(&Black, shape.Start.x, shape.Start.y, shape.End.x, shape.End.y);
	}

	graphics.DrawImage(&bitmap, 0, 0);
	*/

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *pOldBitmap = MemDC.SelectObject(&memBitmap);
	Graphics mem(MemDC.m_hDC);
	mem.SetSmoothingMode(SmoothingModeHighQuality);
	//mem.FillRectangle(&bgBrush, rclClient); // 배경을 흰색으로 지운다
	Gdiplus::SolidBrush Black(Gdiplus::Color(0, 0, 0, 0));
	Gdiplus::Pen P(Color(0, 0, 0));
	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 255, 255, 255));
	mem.FillRectangle(&WhiteBrush, 0, 0, rect.Width(), rect.Height());

	POSITION position = list_Shape.GetHeadPosition();
	while (position)
	{
		CShape shape = list_Shape.GetNext(position);//리스트 호출
		mem.DrawLine(&P, shape.Start.x, shape.Start.y, shape.End.x, shape.End.y);
	}
	dc.BitBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);

}

//화면 초기화
void CGDIPlusLineDrawingView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	list_Shape.RemoveAll();//모든 선 지우기

	Invalidate();//화면 갱신

	CView::OnRButtonUp(nFlags, point);
}
