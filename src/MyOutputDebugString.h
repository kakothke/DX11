#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h>

//-------------------------------------------------------------------------------------------------
#ifdef _DEBUG

//-------------------------------------------------------------------------------------------------
#   define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf_s( c, 256, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }

#else
#    define MyOutputDebugString( str, ... ) // ??????
#endif

// EOF
