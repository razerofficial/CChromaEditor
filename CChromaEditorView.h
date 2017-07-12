
// CChromaEditorView.h : interface of the CCChromaEditorView class
//

#pragma once


class CCChromaEditorView : public CView
{
protected: // create from serialization only
	CCChromaEditorView();
	DECLARE_DYNCREATE(CCChromaEditorView)

// Attributes
public:
	CCChromaEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CCChromaEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CChromaEditorView.cpp
inline CCChromaEditorDoc* CCChromaEditorView::GetDocument() const
   { return reinterpret_cast<CCChromaEditorDoc*>(m_pDocument); }
#endif

