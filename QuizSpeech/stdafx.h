// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright © Microsoft Corporation. All rights reserved

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Disable the false warnings caused by the wrong definitions of SetWindowLongPtr
// and GetWindowLongPtr macros.
#pragma warning ( disable : 4244 )

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif // WIN32_LEAN_AND_MEAN



// Windows Header Files:
#include <windows.h>
//speech recognition include helper functions
#include "sphelper.h"

// C RunTime Header Files
#include <cstdlib>
#include <malloc.h>
#include <memory>
#include <tchar.h>

// ATL Header Files
#include <atlbase.h>

// Multi-Language Header File
#include <mlang.h>

// RichEdit 2.0
//#include <richedit.h>


//STD LIB
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <memory> 
#include <stdexcept>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>

//BOOST
#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include <boost/thread.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/string.hpp>
//#include <boost/serialization/version.hpp>
//#include <boost/serialization/list.hpp>
//#include <boost/serialization/nvp.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string.hpp>
//#include <boost/signal.hpp>
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/unordered_set.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/utility.hpp>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/core/noncopyable.hpp>

////DIRECTX
//#include <d2d1.h>
//#include <d2d1helper.h>
//#include <dwrite.h>
//#include <wincodec.h>
//#include <dsound.h>

#define _WIN32_DCOM
#define _CRT_SECURE_NO_DEPRECATE
#include <xaudio2.h>
#include <strsafe.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <conio.h>


//audio includes
#include <Mfidl.h>
#include <mfapi.h>
#include <mfplay.h>
#include <mferror.h>





#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2


#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif  
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
