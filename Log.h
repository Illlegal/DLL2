#pragma once
#include "pch.h"
//#include <iostream>

// Funkcja do logowania
std::ofstream g_LogFile;
#define LOG(x) if(g_LogFile.is_open()) { g_LogFile << x << endl; g_LogFile.flush(); }

