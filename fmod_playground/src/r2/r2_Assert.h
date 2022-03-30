#pragma once

#ifndef R2_ASSERT_H
#define R2_ASSERT_H



#include <cassert>
#include <iostream>

#define R2_DEBUG 1

#if !defined( R2_DEBUG ) || R2_DEBUG == 0

#define R2ASSERT_2( cond, msg )     do {} while ( 0 )

#else

#define	R2ASSERT( cond, message )																											\
do {																																		\
	if( !( cond ) )																															\
	{																																		\
		printf( "+ R2ASSERT" "\nMessage : %s" "\nFile : %s" "\nLine : %d" "\nFunction : %s", message, __FILE__, __LINE__, __FUNCTION__ );	\
		__debugbreak();																														\
		throw std::runtime_error( message );																								\
	}																																		\
} while( false )

#endif




#endif