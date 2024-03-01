// Copyright 2024 Awesomium team LLC. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FTelegramMessageModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
