#pragma once
#include "include.h"
#include <Windows.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include "safecall.h"
#include "encrypt.h"

#include "sdk.h"
#include "FNTool.h"
#include "VMTHook.h"
#include "DrawTransition.h"
#include "shit.h"
#include "actorloop.h"
#include "gui.h"
#include "menu.h"
#include "aimbot.h"
#include "mouse.h"
#include "esp.h"
#include "sdkdefines.h"
AFortPawn* player_p;
ue::FLinearColor getColorFromTier(BYTE Tier) {
	ue::FLinearColor color = { 255.f, 255.f, 255.f, 1 };

	if (Tier == 1)
		color = { 255.f, 255.f, 255.f, 1 };
	else if (Tier == 2)
		color = { 0.0f, 255.f, 0.0f, 1 };
	else if (Tier == 3)
		color = { 0.f, 1.f, 1.f, 1 };
	else if (Tier == 4)
		color = { 0.8f, 0.f, 0.8f, 1.f };
	else if (Tier == 5)
		color = { 1.f, 1.f, 0.f, 1 };

	return color;
}

class FText {
private:
	char _padding_[0x28];
	PWCHAR Name;
	DWORD Length;
public:


	inline PWCHAR c_wstr() {
		return Name;
	}

	inline char* c_str()
	{

		char sBuff[255];
		wcstombs((char*)sBuff, (const wchar_t*)this->Name, sizeof(sBuff));
		return sBuff;
	}
};

Vector3 AimbotCorrection(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity) {
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	float bulletDrop = (gravity / 250) * time * time;
	recalculated.z += bulletDrop * 120;
	recalculated.x -= time * (targetVelocity.x);
	recalculated.y -= time * (targetVelocity.y);
	recalculated.z -= time * (targetVelocity.z);
	return recalculated;
}



auto gold = ue::FLinearColor(1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f);
auto lightgreen = ue::FLinearColor(0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f);
auto redcol = ue::FLinearColor(1.f, 1.f, 1.f, 1.f);
auto bluecol = ue::FLinearColor(1.f, 1.f, 0.f, 1.f);
float ProjectileSpeed = 1;
 float ProjectilePitchOffset = 1;
void actorloop() {
	if (fovcircle)
	{
		jeremycircle(Vector2(width / 2, height / 2), FovSize, { 0.52f, 0.52f, 2.35, 1.0 });
	}


	width = static_canvas->SizeX();
	height = static_canvas->SizeY();
	auto gworld = ((GWorld*)(*(uintptr_t*)(ue::cached::signatures::GWorld)));
	auto Uworld = (*(uintptr_t*)(ue::cached::signatures::GWorld));
	auto OwningGameInstance = gworld->OwningGameInstance();
	PlayerController = OwningGameInstance->LocalPlayers()->LocalPlayer()->PlayerController();


	auto PlayerCameraManager = PlayerController->PlayerCameraManager();
	auto LocalPawn = (AFortPawn*)PlayerController->LocalPawn();
	auto CurrentVehicle = (AFortPawn*)LocalPawn->jeremyvehicle();
	auto levels = gworld->PersistentLevel();
	

	if (Settings::CarFly)
	{

		auto CurrentVehicle = (AFortPawn*)LocalPawn->jeremyvehicle();
		if (CurrentVehicle)
		{

			if (Settings::CarTpToPing)
			{

				{
					if (Settings::SyncCameraRotation)
					{
						Vector3 camrotation = PlayerCameraManager->GetCameraRotation();

						CurrentVehicle->K2_TeleportTo(Settings::Location, camrotation);
					}
					else
					{
						CurrentVehicle->K2_TeleportTo(Settings::Location, Vector3(NULL, NULL, NULL));
					}

					if (GetAsyncKeyState(0x57)) //w
					{
						Settings::Location.x += Settings::VehicleFlySpeed;
					}

					if (GetAsyncKeyState(0x41)) //a
					{
						Settings::Location.x -= Settings::VehicleFlySpeed;
					}

					if (GetAsyncKeyState(0x53)) //s
					{
						Settings::Location.y -= Settings::VehicleFlySpeed;
					}

					if (GetAsyncKeyState(0x44)) //d
					{
						Settings::Location.y += Settings::VehicleFlySpeed;
					}

					if (GetAsyncKeyState(VK_SPACE))
					{
						Settings::Location.z += Settings::VehicleFlySpeed;
					}
				}

				if (GetAsyncKeyState(VK_LSHIFT))
				{
					Settings::Location.z -= Settings::VehicleFlySpeed;
				}
			}
			else
			{
				if (Settings::SyncCameraRotation)
				{
					Vector3 camrotation = PlayerCameraManager->GetCameraRotation();

					CurrentVehicle->K2_TeleportTo(Settings::Location, camrotation);
				}
				else
				{
					CurrentVehicle->K2_TeleportTo(Settings::Location, Vector3(NULL, NULL, NULL));
				}

				if (GetAsyncKeyState(0x57)) //w
				{
					Settings::Location.x += Settings::VehicleFlySpeed;
				}

				if (GetAsyncKeyState(0x53)) //s
				{
					Settings::Location.x -= Settings::VehicleFlySpeed;
				}

				if (GetAsyncKeyState(0x41)) //a
				{
					Settings::Location.y -= Settings::VehicleFlySpeed;
				}

				if (GetAsyncKeyState(0x44)) //d
				{
					Settings::Location.y += Settings::VehicleFlySpeed;
				}

				if (GetAsyncKeyState(VK_SPACE))
				{
					Settings::Location.z += Settings::VehicleFlySpeed;
				}

				if (GetAsyncKeyState(VK_LSHIFT))
				{
					Settings::Location.z -= Settings::VehicleFlySpeed;
				}
			}

			if (GetAsyncKeyState(VK_RSHIFT))
			{
				Settings::Location = Vector3(5100, 2800, -85);
			}
		}
	}

/*	if (itsjustaispoof(GetAsyncKeyState)(VK_XBUTTON2) && !itsjustaispoof(GetAsyncKeyState)(0x45)) {
		LocalPawn->GetVehicle()->SetOnFire(true);
		
	}*/




	if (Settings::FovChanger) { PlayerController->Fov(Settings::FovChanger_Value); }

	auto actors = levels->ActorArray();
	AFortPawn* TargetPawno = NULL;
	float closestTocenter1 = FLT_MAX;
	for (int i = 0; i < actors.Num(); i++)
	{
		//MsgBox("1");
		auto currentactor = actors[i];
		uint32_t player = (uint32_t)currentactor;
		uint32_t LocalPawno = (uint32_t)LocalPawn;
		if (LocalPawn)
		{
			
			if (currentactor == LocalPawn)
				continue;
		
			if (currentactor->IsA(ue::cached::objects::actor::FortPlayerPawnAthena) && LocalPawn)
			{
				
			/*	if((currentactor->PlayerState()->TeamIndex() == LocalPawn->PlayerState()->TeamIndex()) || !Settings::TeamCheck)
					continue;*/
				
				Vector3 head = currentactor->GetBone(106);
				Vector2 head_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, head);
				
				if (IsNotInScreen(width, height, head_w2s)) 
					continue;
				
				esp(currentactor);
				/*if (itsjustaispoof(GetAsyncKeyState)(VK_XBUTTON1) && !itsjustaispoof(GetAsyncKeyState)(0x45)) {
					currentactor->GetVehicle()->SetOnFire(true);
					LocalPawn->GetVehicle()->SetHealthPercent(100);
				}*/
				


				if (Settings::RapidFire) {
					LocalPawn->CurrentWeapon()->RapidFire();
				}


				auto dx = head_w2s.x - (width / 2);
				auto dy = head_w2s.y - (height / 2);
				auto dist = crt::sqrtf(dx * dx + dy * dy);

				if (dist < FovSize && dist < closestTocenter1) {
					closestTocenter1 = dist;
					TargetPawno = currentactor;
				}
				else
					TargetPawno = NULL;

			
		
				int distance1 = PlayerCameraManager->GetCameraLocation().Distance(TargetPawno->RootComponent()->RelativeLocation());
				
				auto vellocity = TargetPawno->RootComponent()->GetComponentVelocity();
				
				ProjectileSpeed = LocalPawn->CurrentWeapon()->GetProjectileSpeed();
				
				ProjectilePitchOffset = LocalPawn->CurrentWeapon()->GetProjectilePitchOffset();
		/*		static wchar_t Bonea[128];
				static char a[128];
				sprintf(a, e("ProjectileSpeed %f \n ProjectilePitchOffset %f\n ", ProjectileSpeed, ProjectilePitchOffset));
				AnsiToWide(a, Bonea);
				if (!IsNotInScreen(width, height, head_w2s))
					static_canvas->K2_DrawText(head_w2s, getColorFromTier(1), Bonea, true, false);*/
				
				Vector3 viewPoint;
				bool bvis = APlayerController::IsVisible(gworld->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController(), TargetPawno, &viewPoint);
				if (Settings::MemoryAim && (PlayerController->IsInputKeyDown(ue::FKey(RBKey)) || PlayerController->IsInputKeyDown(ue::FKey(ltKey)))) {

					Vector3 headtarget = TargetPawno->GetBone(106);
				
				//	Vector3 Predicted = AimbotCorrection(ProjectileSpeed, ProjectilePitchOffset, distance1, headtarget, vellocity);

					auto camloc = PlayerCameraManager->GetCameraLocation();
					auto NewRotation = galgan(camloc, headtarget);

					if (bvis)
						PlayerController->ClientSetRotation(NewRotation, false);
				}
				if (Settings::SoftAim && (PlayerController->IsInputKeyDown(ue::FKey(RBKey)) || PlayerController->IsInputKeyDown(ue::FKey(ltKey)))) {

					Vector3 headtarget = TargetPawno->GetBone(106);
			
					//Vector3 Predicted = AimbotCorrection(ProjectileSpeed, ProjectilePitchOffset, distance1, headtarget, vellocity);
					Vector2 headtarget_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, headtarget);

					if (bvis)
						aimbot(headtarget_w2s.x, headtarget_w2s.y);

				}


			}
			static AFortPawn* playero;
			if (currentactor->IsA(ue::cached::objects::actor::FortPlayerPawnAthena))
				playero = currentactor;
			if (currentactor && playero)
			{
				if (currentactor->IsA(ue::cached::objects::FortProjectileBase) && Settings::SniperTp)
				{
					currentactor->K2_SetActorLocation(playero->GetBone(106), false, true);
				}
			}
		}
	}
	if (Settings::item || Settings::Zipline || Settings::Marker || Settings::tpplayer) {
		auto levelscount = read<uint32_t>(Uworld + 0x170 + 0x8);
		for (unsigned long N = 0; N < levelscount; N++)
		{

			AFortPawn* TargetPawno1 = NULL;
			float closestTocenter = FLT_MAX;

			auto levels = read<uint64_t>(Uworld + 0x170);
			if (!levels) continue;

			auto level = read<uint64_t>(levels + (N * 0x8));
			if (!level) continue;

			auto actorscount = read<uint32_t>(level + 0xA0);
			auto actorsarray = read<uint64_t>(level + 0x98);
			if (!actorsarray) continue;
			for (uint32_t i = 0; i < actorscount; i++)
			{

				auto actor = read<uint64_t>(actorsarray + (i * 0x8));
				AFortPawn* player = *(AFortPawn**)(actorsarray + (i * 0x8));
				if (!actor)
					continue;
				if (!player)
					continue;
				if (player == LocalPawn)
					continue;
				auto id = read<int>(actor + 0x18);
				
			
				auto Rootcomp = read<uint64_t>(actor + 0x190);
				if (!Rootcomp)
					continue;
				auto Pos = read<Vector3>(Rootcomp + 0x128);
				Vector2 Pos_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, Pos);

				auto dx = Pos_w2s.x - (width / 2);
				auto dy = Pos_w2s.y - (height / 2);
				auto dist = crt::sqrtf(dx * dx + dy * dy);

				if (dist < closestTocenter) {
					closestTocenter = dist;
					TargetPawno1 = player;
				}
				else
					TargetPawno1 = NULL;


				if (player)
				{
					if (player && LocalPawn->IsA(ue::cached::objects::actor::FortPlayerPawnAthena) && PlayerController && Settings::tpplayer)
					{
						if (player->IsA(ue::cached::objects::actor::FortPlayerPawnAthena) && itsjustaispoof(GetAsyncKeyState)(VK_LSHIFT))
						{


							LocalPawn->K2_SetActorLocation(player->GetBone(8), false, true);

							PlayerController->ClientSetRotation(Vector3(-90, 180, 0), false);


						}
					}
				}
				auto Rootcomp1 = read<uint64_t>(actor + 0x190);
				if (!Rootcomp1)
					continue;
				auto Pos1 = read<Vector3>(Rootcomp + 0x128);
				float dist2 = Pos1.DistanceFrom(PlayerCameraManager->GetCameraLocation());
				Vector2 Pos_w2s1 = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, Pos1);

				if (player->IsA(ue::cached::objects::AFortAthenaZipline) && LocalPawn && Settings::Zipline)
				{


					if (itsjustaispoof(GetAsyncKeyState)(VK_XBUTTON2) && !itsjustaispoof(GetAsyncKeyState)(0x45))
						LocalPawn->K2_SetActorLocation(Pos1, false, true);

					static wchar_t Bonea[128];
					static char a[128];
					sprintf(a, e("Zipline", dist2));
					AnsiToWide(a, Bonea);
					if (!IsNotInScreen(width, height, Pos_w2s1))
						static_canvas->K2_DrawText(Pos_w2s1, getColorFromTier(1), Bonea, true, false);

				}
				if (player->IsA(ue::cached::objects::actor::PlayerMarker) && LocalPawn && Settings::Marker)
				{

				//	if (itsjustaispoof(GetAsyncKeyState)(VK_XBUTTON1) && !itsjustaispoof(GetAsyncKeyState)(0x45))
						CurrentVehicle->K2_TeleportTo(Pos1, Vector3(0, 0, 0));

				/*	static wchar_t Bonea[128];
					static char a[128];
					sprintf(a, e("Marker", dist2));
					AnsiToWide(a, Bonea);
					if (!IsNotInScreen(width, height, Pos_w2s))
						static_canvas->K2_DrawText(Pos_w2s, getColorFromTier(1), Bonea, true, false);*/

					Settings::Marker = !Settings::Marker;

				}
				int dist1 = PlayerCameraManager->GetCameraLocation().Distance(player->RootComponent()->RelativeLocation()) / 100;
				if (Settings::Chest)
				{
					bool bAlreadySearched = read<bool>(actor + 0x1032);

					if (wcsstr(player->ObjectName(), e(L"Tiered_Chest")) && !bAlreadySearched && dist1 < 50)
					{


						static char distanceesp[128];
						static wchar_t wdistanceesp[128];
						sprintf(distanceesp, e("Chest [%i]"), dist1);
						AnsiToWide(distanceesp, wdistanceesp);


						auto ItemPos = PlayerCameraManager->WorldToScreen(player->RootComponent()->RelativeLocation());
						static_canvas->K2_DrawText(ItemPos, gold, wdistanceesp, true, true);
					}

				}

				if (Settings::Vehicle)
				{
					if (wcsstr(player->ObjectName(), e(L"Vehicle")) && dist1 < 50)
					{



						static char distanceesp[128];
						static wchar_t wdistanceesp[128];
						sprintf(distanceesp, e("Vehicle [%i]"), dist1);
						AnsiToWide(distanceesp, wdistanceesp);


						auto ItemPos = PlayerCameraManager->WorldToScreen(player->RootComponent()->RelativeLocation());
						static_canvas->K2_DrawText(ItemPos, bluecol, wdistanceesp, true, true);
					}
				}

				if (Settings::Ammo)
				{
					if (wcsstr(player->ObjectName(), e(L"Tiered_Ammo_Athena")) && dist1 < 50)
					{

						static char distanceesp[128];
						static wchar_t wdistanceesp[128];
						sprintf(distanceesp, e("AmmoBox [%i]"), dist1);
						AnsiToWide(distanceesp, wdistanceesp);


						auto ItemPos = PlayerCameraManager->WorldToScreen(player->RootComponent()->RelativeLocation());
						static_canvas->K2_DrawText(ItemPos, lightgreen, wdistanceesp, true, true);
					}
				}


			}
		}
	}



}
