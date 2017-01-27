// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9AFFA25D_0907_11D2_9727_002048088976__INCLUDED_)
#define AFX_STDAFX_H__9AFFA25D_0907_11D2_9727_002048088976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#pragma message("Platform Stdafx.h!!")

#pragma warning(disable:4804)
#pragma warning(disable:4786)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxmt.h>
#include <afxtempl.h>
#ifdef MEDIC_ARCHIVE
#include <afxdb.h>
#endif

#define WM_SEND_PDU WM_USER + 0x300
#define WM_SEND_PDU_COMPLETE WM_USER + 0x301
#define WM_RECEIVE_PDU WM_USER + 0x302
#define WM_RECEIVE_PDU_COMPLETE WM_USER + 0x303
//#define WM_NEWCONNECTION WM_USER + 0x311
//#define WM_TCPTHREADSTART WM_USER + 0x312
//#define WM_TCPTHREADSTOP WM_USER + 0x313

// Archive Message 1
#define WM_MESSAGE1		WM_USER+0xd01

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9AFFA25D_0907_11D2_9727_002048088976__INCLUDED_)
