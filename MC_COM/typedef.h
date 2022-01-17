#ifndef __H_TYPEDEF_H__
#define __H_TYPEDEF_H__

#include <stdint.h>
#include <stdbool.h>

typedef unsigned char byte;
typedef unsigned short ushort;
typedef signed int	int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

#if defined(_MSC_VER)
# if defined(DLLBUILD)
/* define DLLBUILD when building the DLL */
#  define MELSEC_MC_API __declspec(dllexport)
# else
#  define MELSEC_MC_API __declspec(dllimport)
# endif
#else
# define MELSEC_MC_API
#endif

#endif // !__H_TYPEDEF_H__
