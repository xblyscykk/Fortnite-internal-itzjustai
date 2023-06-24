#pragma once
#include "include.h"
#include "actorloop.h"



void DrawTransition(uintptr_t this_, uintptr_t Canvas)
{

	
	if (!Canvas)
		return DrawTransitionOriginal(this_, Canvas);

	static_canvas = (UCanvas*)Canvas;

	actorloop();
	
	/*
	* if (PlayerController->WasInputKeyJustPressed(ue::FKey(InsertKey)))
	{
		ShowMenu = !ShowMenu;
	}
	*/

	//if (ShowMenu)
	//	gui();

	return DrawTransitionOriginal(this_, Canvas);
}