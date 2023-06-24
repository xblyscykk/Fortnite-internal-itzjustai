#pragma once
#include "include.h"
#include "itsjustai.h"

void esp(AFortPawn* player) {
	
	if (PlayerController)//player->IsA(ue::cached::objects::actor::FortPlayerPawnAthena) &&
	{
	
		auto PlayerCameraManager = PlayerController->PlayerCameraManager();
		if (!PlayerCameraManager)
			return;
		if (Settings::Chams) {
			ue::FLinearColor a{ 28, 223, 237 ,255};
			player->ApplyPawnHighlight(a, a);
		}
		Vector3 head = player->GetBone(106);
		Vector2 head_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, head);
		Vector3 head2, fuckbattleeyenigger, pelvis, fuckbattleeye, leftShoulder, rightShoulder, leftElbow, rightElbow, leftHand, rightHand, leftLeg, rightLeg, leftThigh, rightThigh, leftFoot, rightFoot, leftFeet, rightFeet, leftFeetFinger, rightFeetFinger;
		
		Vector2 head2_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, { head.x, head.y, head.z + 20 });
		Vector3 bottom = player->GetBone(0);

		
		Vector2 bottom_w2s = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, { bottom.x, bottom.y, bottom.z });
	
		float BoxHeight = (float)(bottom_w2s.y - head2_w2s.y);
		float BoxWidth = BoxHeight * 0.60f;

		float BottomLeftX = (float)head2_w2s.x - BoxWidth / 2;
		float BottomLeftY = (float)bottom_w2s.y;

		float BottomRightX = (float)head2_w2s.x + BoxWidth / 2;
		float BottomRightY = (float)bottom_w2s.y;

		float TopRightX = (float)head2_w2s.x + BoxWidth / 2;
		float TopRightY = (float)head2_w2s.y;

		float TopLeftX = (float)head2_w2s.x - BoxWidth / 2;
		float TopLeftY = (float)head2_w2s.y;

		float TextOffset_Y = head2_w2s.y;
		float TextOffset_X = TopRightX + 5;
		Vector2 calculation;
		float CornerHeight = abs(head_w2s.y - bottom.y);
		float CornerWidth = CornerHeight * 0.75;

		Vector3 viewPoint;
		bool bvis = APlayerController::IsVisible(((GWorld*)(*(uintptr_t*)(ue::cached::signatures::GWorld)))->OwningGameInstance()->LocalPlayers()->LocalPlayer()->PlayerController(), player, &viewPoint);
		if (bvis)
			color = cyan;
		else
			color = redd;
		if (Settings::BoxESP) {
			int thickness = 1.5;

			static_canvas->K2_DrawLine(Vector2(BottomLeftX, BottomLeftY), Vector2(BottomRightX, BottomRightY), thickness, color);

			//Right
			static_canvas->K2_DrawLine(Vector2(BottomRightX, BottomRightY), Vector2(TopRightX, TopRightY), thickness, color);

			//Top
			static_canvas->K2_DrawLine(Vector2(TopRightX, TopRightY), Vector2(TopLeftX, TopLeftY), thickness, color);

			//Left
			static_canvas->K2_DrawLine(Vector2(TopLeftX, TopLeftY), Vector2(BottomLeftX, BottomLeftY), thickness, color);
		}
		if (Settings::Box)
		{

			float Height = bottom_w2s.y - head2_w2s.y;
			float Width = Height * 0.50;

			Vector2 min;
			min.x = bottom_w2s.x + Width / 2;
			min.y = bottom_w2s.y;

			Vector2 max;
			max.x = head2_w2s.x - Width / 2;
			max.y = head2_w2s.y;

			Vector2 size;
			size.x = min.x - max.x;
			size.y = min.y - max.y;

			DrawCorneredBox(static_canvas, max, size, 1.f, color);
		}
		if (Settings::getboneid)
		{

			for (int i = 0; i < 107; i++)
			{
				Vector3 Bonez = player->GetBone(i);



				float CornerHeight = abs(head_w2s.y - bottom.y);
				float CornerWidth = CornerHeight * 0.75;
				Vector2 BonezOut = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, Bonez);



				static wchar_t Bonea[128];
				static char a[128];

				sprintf(a, e("%s"), std::to_string(i));
				AnsiToWide(a, Bonea);
				BonezOut.y += static_canvas->K2_TextSize(Bonea).y + 5;
				BonezOut.x += static_canvas->K2_TextSize(Bonea).x + 5;
				static_canvas->K2_DrawText(BonezOut, bluee, Bonea, false, true);
			}

		}
		Vector2 ChestAtLeft = PlayerCameraManager->WorldToScreen(player->GetBone(37));
		Vector2 ChestAtRight =PlayerCameraManager->WorldToScreen(player->GetBone(8));
		Vector2 Chest = { ChestAtLeft.x + (ChestAtRight.x - ChestAtLeft.x) / 2, ChestAtLeft.y };
		ue::FLinearColor Color = ue::FLinearColor(1.f, 1.f, 0.f, 1.f);
		if (Settings::SkeletonESP)
		{
			Vector2 Neck = PlayerCameraManager->WorldToScreen(player->GetBone(67));
			Vector2 LeftShoulder = PlayerCameraManager->WorldToScreen(player->GetBone(38));
			Vector2 RightShoulder = PlayerCameraManager->WorldToScreen(player->GetBone(9));
			Vector2 LeftElbow = PlayerCameraManager->WorldToScreen(player->GetBone(39));
			Vector2 RightElbow =PlayerCameraManager->WorldToScreen(player->GetBone(10));
			Vector2 LeftHand =PlayerCameraManager->WorldToScreen(player->GetBone(53));
			Vector2 RightHand =PlayerCameraManager->WorldToScreen(player->GetBone(24));
			Vector2 LeftLeg =PlayerCameraManager->WorldToScreen(player->GetBone(78));
			Vector2 RightLeg =PlayerCameraManager->WorldToScreen(player->GetBone(71));
			Vector2 LeftThigh =PlayerCameraManager->WorldToScreen(player->GetBone(84));
			Vector2 RightThigh =PlayerCameraManager->WorldToScreen(player->GetBone(77));
			Vector2 LeftFoot =PlayerCameraManager->WorldToScreen(player->GetBone(79));
			Vector2 RightFoot =PlayerCameraManager->WorldToScreen(player->GetBone(72));
			Vector2 LeftFeet =PlayerCameraManager->WorldToScreen(player->GetBone(82));
			Vector2 RightFeet =PlayerCameraManager->WorldToScreen(player->GetBone(75));
			Vector2 LeftFeetFinger =PlayerCameraManager->WorldToScreen(player->GetBone(83));
			Vector2 RightFeetFinger =PlayerCameraManager->WorldToScreen(player->GetBone(76));
			Vector2 Bottom =PlayerCameraManager->WorldToScreen(player->GetBone(0));
			Vector2 Pelvis =PlayerCameraManager->WorldToScreen(player->GetBone(2));


			static_canvas->K2_DrawLine(head_w2s, Neck, 1, color);
			static_canvas->K2_DrawLine(Neck, Chest, 1, color);
			static_canvas->K2_DrawLine(Chest, Pelvis, 1, color);
			static_canvas->K2_DrawLine(Chest, LeftShoulder, 1, color);
			static_canvas->K2_DrawLine(Chest, RightShoulder, 1, color);
			static_canvas->K2_DrawLine(LeftShoulder, LeftElbow, 1, color);
			static_canvas->K2_DrawLine(RightShoulder, RightElbow, 1, color);
			static_canvas->K2_DrawLine(LeftElbow, LeftHand, 1, color);
			static_canvas->K2_DrawLine(RightElbow, RightHand, 1, color);
			static_canvas->K2_DrawLine(Pelvis, LeftLeg, 1, color);
			static_canvas->K2_DrawLine(Pelvis, RightLeg, 1, color);
			static_canvas->K2_DrawLine(LeftLeg, LeftThigh, 1, color);
			static_canvas->K2_DrawLine(RightLeg, RightThigh, 1, color);
			static_canvas->K2_DrawLine(LeftThigh, LeftFoot, 1, color);
			static_canvas->K2_DrawLine(RightThigh, RightFoot, 1, color);
			static_canvas->K2_DrawLine(LeftFoot, LeftFeet, 1, color);
			static_canvas->K2_DrawLine(RightFoot, RightFeet, 1, color);
			static_canvas->K2_DrawLine(LeftFeet, LeftFeetFinger, 1, color);
			static_canvas->K2_DrawLine(RightFeet, RightFeetFinger, 1, color);

		}
		if (Settings::LinesESP) {
			static_canvas->K2_DrawLine(Vector2(width / 2, height), bottom_w2s, 0.5, color);
		}
		if (Settings::EnemyWeaponESP) {
			if (player->CurrentWeapon()->WeaponData()) {
				auto weaponname = player->CurrentWeapon()->WeaponData()->DisplayName().Get();
				if (weaponname) {
					TextOffset_Y += static_canvas->K2_TextSize(weaponname).y + 10;
					calculation = Vector2(TextOffset_X, TextOffset_Y);
					static_canvas->K2_DrawText(calculation, bluee, weaponname, false, true);
				}
			}
		}
		if (Settings::aimini) {
			if (player) {
				Vector3 bottom1 = player->GetBone(106);

				Vector2 bottom_w2s1 = PlayerCameraManager->ProjectWorldLocationToScreen(width, height, { bottom1.x, bottom1.y, bottom1.z });
				static_canvas->K2_DrawLine(Vector2(width / 2, height / 2), bottom_w2s1, 1, color);
			}

		}
		if (Settings::PlayerNameESP) {
			auto name = player->PlayerState()->GetPlayerName();
			if (name.c_str()) {

				TextOffset_Y += static_canvas->K2_TextSize(player->PlayerState()->GetPlayerName()).y + 5;
				calculation = Vector2(TextOffset_X, TextOffset_Y);
				static_canvas->K2_DrawText(calculation, white, name.c_str(), false, true);
			}
		}
		if (Settings::DistanceESP) {
			int dist = PlayerCameraManager->GetCameraLocation().Distance(player->RootComponent()->RelativeLocation()) / 100;
			static char distanceesp[128];
			static wchar_t wdistanceesp[128];
			sprintf(distanceesp, e("[%dm]"), dist);
			AnsiToWide(distanceesp, wdistanceesp);
			TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wdistanceesp)).y + 10;
			calculation = Vector2(TextOffset_X, TextOffset_Y);
			static_canvas->K2_DrawText(calculation, white, wdistanceesp, false, true);
		}
		if (Settings::LevelESP) {
			auto level = player->PlayerState()->SeasonLevelUIDisplay();
			static char levelesp[128];
			static wchar_t wlevelesp[128];
			sprintf(levelesp, e("Level: %d"), level);
			AnsiToWide(levelesp, wlevelesp);
			TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wlevelesp)).y + 10;
			calculation = Vector2(TextOffset_X, TextOffset_Y);
			static_canvas->K2_DrawText(calculation, white, wlevelesp, false, true);
		}
		if (Settings::KillsESP) {
			auto kills = player->PlayerState()->GetKillScore();
			static char killesp[128];
			static wchar_t wdkillesp[128];
			sprintf(killesp, e("Kills: %d"), kills);
			AnsiToWide(killesp, wdkillesp);
			TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wdkillesp)).y + 10;
			calculation = Vector2(TextOffset_X, TextOffset_Y);
			static_canvas->K2_DrawText(calculation, white, wdkillesp, false, true);
		}
		if (0) {
			auto Health = read<int>((uint32_t)player->PlayerState() + 0x10e8);
			static char killesp[128];
			static wchar_t wdkillesp[128];
			sprintf(killesp, e("Health: %i"), Health);
			AnsiToWide(killesp, wdkillesp);
			TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wdkillesp)).y + 10;
			calculation = Vector2(TextOffset_X, TextOffset_Y);
			static_canvas->K2_DrawText(calculation, white, wdkillesp, false, true);
		}
		if (Settings::AmmoESP) {
			auto ammo = player->CurrentWeapon()->GetMagazineAmmoCount();
			auto clipammo = player->CurrentWeapon()->GetBulletsPerClip();
			if (ammo && clipammo) {
				static char ammoesp[128];
				static wchar_t wammoesp[128];
				sprintf(ammoesp, e("Ammo: %d/%d"), ammo, clipammo);
				AnsiToWide(ammoesp, wammoesp);
				TextOffset_Y += static_canvas->K2_TextSize(ue::FString(wammoesp)).y + 10;
				calculation = Vector2(TextOffset_X, TextOffset_Y);
				static_canvas->K2_DrawText(calculation, redd, wammoesp, false, true);
			}
		}
		if (Settings::PlatformESP) {
			auto platform = player->PlayerState()->GetPlatform();
			if (!platform.IsValid()) return;
			auto platform_name = platform.c_str();
			TextOffset_Y += static_canvas->K2_TextSize(ue::FString(platform_name)).y + 10;
			calculation = Vector2(TextOffset_X, TextOffset_Y);

			if (math::custom_wcsstr(platform_name, e(L"PSN"))) {
				static_canvas->K2_DrawText(calculation, bluee, (ue::FString)e(L"PlayStation"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, (wchar_t*)e(L"XBL"))) {
				static_canvas->K2_DrawText(calculation, green, (ue::FString)e(L"Xbox"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, (wchar_t*)e(L"XSX"))) {
				static_canvas->K2_DrawText(calculation, green, (ue::FString)e(L"Xbox Series S"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"WIN"))) {
				static_canvas->K2_DrawText(calculation, white, (ue::FString)e(L"Windows"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"MAC"))) {
				static_canvas->K2_DrawText(calculation, white, (ue::FString)e(L"MacOS"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"LNX"))) {
				static_canvas->K2_DrawText(calculation, white, (ue::FString)e(L"Linux"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"IOS"))) {
				static_canvas->K2_DrawText(calculation, white, (ue::FString)e(L"Ios"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"AND"))) {
				static_canvas->K2_DrawText(calculation, Yellow, (ue::FString)e(L"Android"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"SWT"))) {
				static_canvas->K2_DrawText(calculation, redd, (ue::FString)e(L"NintendoSwitch"), false, true);
			}
			else if (math::custom_wcsstr(platform_name, e(L"PS5"))) {
				static_canvas->K2_DrawText(calculation, bluee, (ue::FString)e(L"PS5"), false, true);
			}
			else {
				static_canvas->K2_DrawText(calculation, white, platform_name, false, true);
			}
		}
	}
	
}