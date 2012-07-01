#pragma once

#include "Singleton.h"

typedef Singleton<CL_ResourceManager> ResourceManager;

#define RC (ResourceManager::getInstance())
