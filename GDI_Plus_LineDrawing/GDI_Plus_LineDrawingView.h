
// GDI_Plus_LineDrawingView.h: CGDIPlusLineDrawingView 클래스의 인터페이스
//

#pragma once
#include "Shape.h"

class CGDIPlusLineDrawingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGDIPlusLineDrawingView() noexcept;
	DECLARE_DYNCREATE(CGDIPlusLineDrawingView)

// 특성입니다.
public:
	CGDIPlusLineDrawingDoc* GetDocument() const;

// 작업입니다.
public:
	BOOL L_MouseDown;//마우스 왼쪽버튼
	CList<CShape> list_Shape;//선 저장

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGDIPlusLineDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GDI_Plus_LineDrawingView.cpp의 디버그 버전
inline CGDIPlusLineDrawingDoc* CGDIPlusLineDrawingView::GetDocument() const
   { return reinterpret_cast<CGDIPlusLineDrawingDoc*>(m_pDocument); }
#endif

