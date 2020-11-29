#ifndef _DLL_EXPORTS_H_
#define _DLL_EXPORTS_H_

#if defined _WIN32 || defined __CYGWIN__
#ifdef BITGRABBER_EXPORT
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT 
#endif

#endif
