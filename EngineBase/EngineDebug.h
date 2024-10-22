#pragma once
#include <Windows.h>
#include <assert.h>


#define MSGASSERT(VALUE) MessageBoxA(nullptr, VALUE, "ERROR", MB_OK); assert(false);
