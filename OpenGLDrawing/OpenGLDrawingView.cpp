
// OpenGLDrawingView.cpp : COpenGLDrawingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OpenGLDrawing.h"
#endif

// newTask9View.cpp: CnewTask9View ���ʵ��
//

#include "stdafx.h"
#include <atlstr.h>
#include"Field.h"

// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS

#endif

#include <iostream>
#include "Model.h"
#include "MyPoint.h"
#include "Facet.h"
#include <io.h> 
#include <iostream>
#include <io.h> 

#include <fcntl.h>
#include <string>

#include <fcntl.h>
#include <string>
using namespace std;
#include "OpenGLDrawingDoc.h"
#include "OpenGLDrawingView.h"
#include "Gl/gl.h"
#include "GL/glu.h"
#include "gl/glut.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
set<MyPoint>_listinsert;
set<MyPoint>_setPoint;
set<int>listPoint;
string m_txtName;
MyPoint getPoint;
int index;
int field;
// �洢�����Ϣ
map<int, MyPoint>_mapPoint;
// �洢��Ƭ����Ϣ
map<int, Facet>_mapFacet;
map<string, int>_stringPoint;
void ReadStlFile(string fileName);
void writeFile(CString path, map<int, Facet >mapFacet, map<int, MyPoint>mapPoint);
double GetArea();
double GetVolume();
double Sarea = 0.0;
double Vvolume=0.0;
// COpenGLDrawingView
Model model;
IMPLEMENT_DYNCREATE(COpenGLDrawingView, CView)

BEGIN_MESSAGE_MAP(COpenGLDrawingView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_OPEN, &COpenGLDrawingView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, &COpenGLDrawingView::OnFileSaveAs)
	ON_COMMAND(ID_32771, &COpenGLDrawingView::OnArea)
	ON_COMMAND(ID_32772, &COpenGLDrawingView::OnVolume)
	ON_COMMAND(ID_32774, &COpenGLDrawingView::OnField)
END_MESSAGE_MAP()

// COpenGLDrawingView ����/����

COpenGLDrawingView::COpenGLDrawingView()
{
	// TODO:  �ڴ˴���ӹ������
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_zPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_zAngle = 0.0f;
	m_Scale = 1.0f;

}
COpenGLDrawingView::~COpenGLDrawingView()
{
}

BOOL COpenGLDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW);
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

// COpenGLDrawingView ����

void COpenGLDrawingView::OnDraw(CDC* /*pDC*/)
{
	COpenGLDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	if (m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;
	
	//glRotatef(m_zAngle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, m_Scale);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(m_xPos, m_yPos, m_zPos);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	glScalef(m_Scale, m_Scale, m_Scale);
	glColor3f(1.0,1.0,0.0);
	for (auto it = model.modelFacet.begin();it != model.modelFacet.end();it++)
	{
		glPushMatrix();
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(it->second._vertex_1._x / 100, it->second._vertex_1._y / 100, it->second._vertex_1._z / 100);
		glVertex3f(it->second._vertex_3._x / 100, it->second._vertex_3._y / 100, it->second._vertex_3._z / 100);
		glVertex3f(it->second._vertex_2._x / 100, it->second._vertex_2._y / 100, it->second._vertex_2._z / 100);
		glEnd(); //������
		glPopMatrix();
		// ����
		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(it->second._vertex_1._x / 100, it->second._vertex_1._y / 100, it->second._vertex_1._z / 100);
		glVertex3f(it->second._vertex_3._x / 100, it->second._vertex_3._y / 100, it->second._vertex_3._z / 100);
		glEnd();


		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);

		glVertex3f(it->second._vertex_1._x / 100, it->second._vertex_1._y / 100, it->second._vertex_1._z / 100);
		glVertex3f(it->second._vertex_2._x / 100, it->second._vertex_2._y / 100, it->second._vertex_2._z / 100);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(it->second._vertex_2._x / 100, it->second._vertex_2._y / 100, it->second._vertex_2._z / 100);
		glVertex3f(it->second._vertex_3._x / 100, it->second._vertex_3._y / 100, it->second._vertex_3._z / 100);
		glEnd();
	}
	if (field != 0)
	{
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(getPoint._x / 100, getPoint._y / 100, getPoint._z / 100);
		glEnd();
		for (auto it = _setPoint.begin();it != _setPoint.end();it++)
		{
			glBegin(GL_POINTS);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(it->_x / 100, it->_y / 100, it->_z /100);
			glEnd();
		}
	}
	//glutWireTeapot(2);
	::SwapBuffers(m_pDC->GetSafeHdc());
	
}
// COpenGLDrawingView ��ӡ

BOOL COpenGLDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COpenGLDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COpenGLDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

// COpenGLDrawingView ���
#ifdef _DEBUG
void COpenGLDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDrawingDoc* COpenGLDrawingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDrawingDoc)));
	return (COpenGLDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLDrawingView ��Ϣ�������


void COpenGLDrawingView::OnDestroy()
{
	// TODO:  �ڴ˴������Ϣ����������
	
	//Delete the rendering context  
	::wglMakeCurrent(NULL, NULL);
	if (m_hglrc)
		::wglDeleteContext(m_hglrc);
	if (m_pDC)
		delete m_pDC;
	CView::OnDestroy();
}


int COpenGLDrawingView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	int n;
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	static PIXELFORMATDESCRIPTOR pfd =

	{

		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd  
		1,                              // version number  

		PFD_DRAW_TO_WINDOW |            // support window  

		PFD_SUPPORT_OPENGL |            // support OpenGL  

		PFD_DOUBLEBUFFER,                // double buffered  

		PFD_TYPE_RGBA,                  // RGBA type  
		24,                             // 24-bit color depth  
		0, 0, 0, 0, 0, 0,               // color bits ignored  
		0,                              // no alpha buffer  
		0,                              // shift bit ignored  
		0,                              // no accumulation buffer  
		0, 0, 0, 0,                     // accum bits ignored  
		16,                             // 16-bit z-buffer  
		0,                              // no stencil buffer  
		0,                              // no auxiliary buffer  
		PFD_MAIN_PLANE,                 // main layer  
		0,                              // reserved  
		0, 0, 0                         // layer masks ignored  

	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)

	{
		return FALSE;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);
	

	//Create Rendering Context  
	m_hglrc = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context  
	if (m_hglrc == 0)
	{
		MessageBox("Error Creating RC");
		return FALSE;
	}
	//Make the RC Current  
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc) == FALSE)
	{
		MessageBox("Error making RC Current");
		return FALSE;
	}
	//Specify Black as the clear color  
	::glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//Specify the back of the buffer as clear depth  
	::glClearDepth(1.0f);
	//Enable Depth Testing  
	::glEnable(GL_DEPTH_TEST);
	return 0;

}
void COpenGLDrawingView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;

	// TODO:  �ڴ˴������Ϣ����������

	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	 //select the full client area  
	::glViewport(0, 0, cx, cy);
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	if (cx < cy)
		glOrtho(-10.0, 100.0, -10.0*(GLfloat)cy / (GLfloat)cx, 10.0*(GLfloat)cy / (GLfloat)cx, -100.0, 100.0);
	else
		glOrtho(-10.0*(GLfloat)cx / (GLfloat)cy, 10.0*(GLfloat)cx / (GLfloat)cy, -10.0, 10.0, -100.0, 100.0);
	// switch back to the modelview matrix and clear it  
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


void COpenGLDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void COpenGLDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


BOOL COpenGLDrawingView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_Scale >= 0)
	{
		m_Scale += 0.05 *zDelta / 120;
	}
	else
	{
		if (zDelta > 0)
		{
			m_Scale += 0.05 *zDelta / 120;
		}
	}
	InvalidateRect(NULL, FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
	
}


void COpenGLDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (GetCapture() == this)
	{
		//Increment the object rotation angles  
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;
		//Redraw the view  
		InvalidateRect(NULL, FALSE);
		//Set the mouse point  
		m_MouseDownPoint = point;
	};
	CView::OnMouseMove(nFlags, point);
}


void COpenGLDrawingView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nChar)
	{
	case VK_UP:        m_yPos = m_yPos + 1.0f;
		break;
	case VK_DOWN:    m_yPos = m_yPos - 1.0f;
		break;
	case VK_LEFT:    m_xPos = m_xPos - 1.0f;
		break;
	case VK_RIGHT:  m_xPos = m_xPos + 1.0f;
		break;
	default:        MessageBox("Press the arrow keys only");
		break;
	}

	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void COpenGLDrawingView::OnFileOpen()
{
	// TODO: �ڴ���������������
	char ch = getchar();                // ������
	CString filename;
	CFileDialog opendlg(TRUE, _T("*"), _T("*.stl"), OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);
	int n = opendlg.DoModal();
	// �û��Ƿ�ѡ�����ļ�
	if (n == IDOK)
	{
		filename = opendlg.GetPathName();
		// �ļ���·��
		std::string str((LPCTSTR)filename);
		/*freopen("CONOUT$", "w+t", stdout);// ����д
		cout << "filename is " << str << endl;   // д���ݣ����������Ҫ�ĵ�����Ϣ�ȣ�

		freopen("CONIN$", "r+t", stdin);  // �����*/
		m_txtName = str;
		ReadStlFile(str);
	}
}
void InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE * hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}
void ReadStlFile(string fileName)
{
	cout << "file name is " << fileName << endl;

	string s;
	int nodeNumber = 0;
	int pointCount = 0;
	int facetCount = 0;
	try
	{
		fstream fin(fileName);
		Facet cFacet;
		while (getline(fin, s))
		{
			if (strstr(s.c_str(), "vertex") != NULL)
			{
				pointCount++;
				istringstream iss(s);
				string first;
				double x1, y1, z1;
				iss >> first >> x1 >> y1 >> z1;
				MyPoint point(x1, y1, z1);
				//point.index = 0;
				// �ж�map���Ƿ��Ѿ����ڸõ�
				auto it = _stringPoint.find(s);
				if (it == _stringPoint.end())
				{
					_stringPoint.insert(pair<string, int>(s, nodeNumber));
					point.addFacet(facetCount);
					point.index = nodeNumber;
					model.addPoint(point, nodeNumber);
					nodeNumber++;
				}
				else
				{
					auto itt = model.modelPoint.find(it->second);
					itt->second.addFacet(facetCount);
					point = itt->second;
				}
				if (pointCount % 3 == 1)
				{
					cFacet._vertex_1 = point;
					cFacet.index1 = point.index;
				}
				else if (pointCount % 3 == 2)
				{
					cFacet._vertex_2 = point;
					cFacet.index2 = point.index;

				}
				else if (pointCount % 3 == 0)
				{
					cFacet._vertex_3 = point;
					cFacet.index3 = point.index;

					cFacet.index = facetCount;
					// ���㷽������
					cFacet.getNormal();
					// �������
					cFacet.getS();
					// �������
					cFacet.getVolume();
					model.addFacet(facetCount, cFacet);
					facetCount++;
					Facet cFacet;
				}
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "���ļ�����" << endl;
	}
	cout << " ���ٵ㣺" << model.modelPoint.size() << endl;
	cout << " ������Ƭ��" << model.modelFacet.size() << endl;
	for (auto it = model.modelFacet.begin();it != model.modelFacet.end();it++)
	{
		Vvolume += it->second.volume;
		Sarea += it->second.s;
	}
}

void COpenGLDrawingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	CString path;
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &rootLoation);
	if (rootLoation == NULL) {
		return;
	}
	// ���öԻ���  
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));

	// �򿪶Ի���, �е���DoModal  
	LPITEMIDLIST targetLocation = SHBrowseForFolder(&bi);
	if (targetLocation != NULL) {
		TCHAR targetPath[MAX_PATH];
		SHGetPathFromIDList(targetLocation, targetPath);
		path = targetPath;
		path += "//result.ply";
		writeFile(path, model.modelFacet, model.modelPoint);
	}
}

void writeFile(CString path, map<int, Facet>mapFacet, map<int, MyPoint>mapPoint)
{
	ofstream OpenFile(path);
	if (OpenFile.fail())
	{
		cout << "���ļ�����!" << endl;
	}
	OpenFile << "ply" << endl;
	OpenFile << "format ascii 1.0" << endl;
	OpenFile << "comment generated by platoply" << endl;
	OpenFile << "element vertex  " << model.modelPoint.size() << endl;
	OpenFile << "property float32 x" << endl;
	OpenFile << "property float32 y" << endl;
	OpenFile << "property float32 z" << endl;
	OpenFile << "element face " << model.modelFacet.size() << endl;
	OpenFile << "property list uint8 int32 vertex_indices" << endl;
	OpenFile << "end_header" << endl;
	// ��ȡ���������Ϣ
	for (auto iter = model.modelPoint.begin(); iter != model.modelPoint.end(); iter++)
	{
		OpenFile << iter->second._x << " " << iter->second._y << " " << iter->second._z << endl;
	}
	for (auto iter = model.modelFacet.begin(); iter != model.modelFacet.end(); iter++)
	{
		OpenFile << " " << 3 << " " << iter->second._vertex_1.index << " " << iter->second._vertex_2.index << " " << iter->second._vertex_3.index << endl;
	

	}
}
double GetVolume()
{
	return Vvolume;
}
// ������㺯��
double GetArea()
{
	return Sarea;
}
void COpenGLDrawingView::OnArea()
{
	// TODO: �ڴ���������������
	CString stream;
	stream.Format("��� = %.2f", Sarea);
	MessageBox(stream);
}
void COpenGLDrawingView::OnVolume()
{
	// TODO: �ڴ���������������
	CString stream;
	stream.Format("��� = %.2f", Vvolume);
	MessageBox(stream);
}
void GetFieldcirculation(int index, int nField)
{
	int size = 0;
	// ����index�ҵ���,ע���ظ����⣬�Ѿ��жϵĵ㲻���ٴμ���
	list<int>_listPointTemp;
	auto ittt = model.modelPoint.find(index);
	if (ittt != model.modelPoint.end())
	{
		getPoint = ittt->second;
	}
	_listPointTemp.push_back(index);
	listPoint.insert(index);
	while (nField > 0)
	{
		int start = 0, size = _listPointTemp.size();
		while ((!_listPointTemp.empty()) && (start < size))
		{
			// ��ջ,���ص�һ������
			//cout << "Point Size is : " << _listPointTemp.size() << endl;
			index = _listPointTemp.front();
			//cout << "index :" << index << endl;
			_listPointTemp.pop_front();
			for (auto it = model.modelPoint.begin();it != model.modelPoint.end();it++)
			{
				if (index == it->second.index)
				{
					vector<int>listInt = it->second.listfacet;
					for (auto i = listInt.begin();i != listInt.end();i++)
					{
						auto it = model.modelFacet.find(*i);
						//Facet facet=it->second;
						if (listPoint.count(it->second._vertex_1.index) == 0)
						{
							listPoint.insert(it->second._vertex_1.index);
							_listPointTemp.push_back(it->second._vertex_1.index);
							_setPoint.insert(it->second._vertex_1);
						}
						if (listPoint.count(it->second._vertex_2.index) == 0)
						{
							listPoint.insert(it->second._vertex_2.index);
							_listPointTemp.push_back(it->second._vertex_2.index);
							_setPoint.insert(it->second._vertex_2);

						}
						if (listPoint.count(it->second._vertex_3.index) == 0)
						{
							listPoint.insert(it->second._vertex_3.index);
							_listPointTemp.push_back(it->second._vertex_3.index);
							_setPoint.insert(it->second._vertex_3);
						}
					}
					break;
				}
			}
			size--;
		}
		nField--;
	}
	cout << " list is :" << listPoint.size() << endl;
}
void COpenGLDrawingView::OnField()
{
	Field f;
	if (f.DoModal()==IDOK)
	{
		index = f.m_point;
		field = f.field;
		GetFieldcirculation(index, field);
		Invalidate();
	}
	// TODO: �ڴ���������������
}
