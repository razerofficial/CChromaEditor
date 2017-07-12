
// CChromaEditorView.cpp : implementation of the CCChromaEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CChromaEditor.h"
#endif

#include "CChromaEditorDoc.h"
#include "CChromaEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCChromaEditorView

IMPLEMENT_DYNCREATE(CCChromaEditorView, CView)

BEGIN_MESSAGE_MAP(CCChromaEditorView, CView)
END_MESSAGE_MAP()

// CCChromaEditorView construction/destruction

CCChromaEditorView::CCChromaEditorView()
{
	// TODO: add construction code here

}

CCChromaEditorView::~CCChromaEditorView()
{
}

BOOL CCChromaEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCChromaEditorView drawing

void CCChromaEditorView::OnDraw(CDC* /*pDC*/)
{
	CCChromaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCChromaEditorView diagnostics

#ifdef _DEBUG
void CCChromaEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CCChromaEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCChromaEditorDoc* CCChromaEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCChromaEditorDoc)));
	return (CCChromaEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CCChromaEditorView message handlers
