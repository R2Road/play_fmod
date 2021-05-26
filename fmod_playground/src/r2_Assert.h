#pragma once

#ifndef R2_ASSERT_H
	#define R2_ASSERT_H

	#include <cassert>
	#include <iostream>

	#define R2_DEBUG 1

	#ifndef R2ASSERT
		#if !defined( R2_DEBUG ) || R2_DEBUG == 0
			#define R2ASSERT( cond, msg )     do {} while ( 0 )
		#else
			#define R2ASSERT( cond, msg )     do { std::cerr << msg; assert( cond ); } while ( 0 )
		#endif
	#endif

#endif