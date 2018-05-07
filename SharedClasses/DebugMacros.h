#pragma once

#ifdef _DEBUG
	#define DEBUG_BEGIN(x) Serial.begin(x)
	#define DEBUG_PRINT(x) Serial.print(x)
	#define DEBUG_PRINTLN(x) Serial.println(x)
#else
	#define DEBUG_BEGIN(x)
	#define DEBUG_PRINT(x)
	#define DEBUG_PRINTLN(x)
#endif