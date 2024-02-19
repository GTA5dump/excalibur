#pragma once

//disable warnings and define no min max
#define WIN32_LEAN_AND_MEAN  
#define NOMINMAX  
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define CURL_STATICLIB
#pragma warning(disable : 4996 4091 4838 4311 4302 4191 4018 4305 4800 4804 4305 4551 4390 4715)

//include headers
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <xstring>
#include <tlhelp32.h>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <chrono>
#include <memory>
#include <Psapi.h>
#include <timeapi.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <shlobj.h>
#include <future>
#include <cstdint>
#include <cstdint>
#include <type_traits>
#include <sstream>
#include <cassert>
#include <utility>
#include <xutility>
#include <conio.h>
#include <wrl/client.h>
#include <winternl.h>
#include <d3d11.h>
#include <random>
#include <span>
#include <algorithm>
#include "util/curl/curl.h"
#pragma comment(lib, "libcurl_a.lib")
#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "normaliz.lib")
//include libs
#pragma comment(lib, "winmm.lib")

