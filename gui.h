#pragma once
#include "include.h"
#include "menu.h"

float rainbowspeed = 0.002f;
void SetupImGuiStyle()
{
	// Fork of Soft Cherry style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;

	style.WindowPadding = ImVec2(10.0f, 10.0f);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(50.0f, 50.0f);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 1.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(5.0f, 3.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(6.0f, 6.0f);
	style.ItemInnerSpacing = ImVec2(3.0f, 2.0f);

	style.IndentSpacing = 6.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 13.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 4.0f;

	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);


	style.Colors[ImGuiCol_Text] = ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5215686559677124f, 0.5490196347236633f, 0.5333333611488342f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1294117718935013f, 0.1372549086809158f, 0.168627455830574f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1490196138620377f, 0.1568627506494522f, 0.1882352977991104f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.1372549086809158f, 0.1137254908680916f, 0.1333333402872086f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.168627455830574f, 0.1843137294054031f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.3449025452136993f, 0.0563649907708168f, 0.6566523313522339f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2666666805744171f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.239215686917305f, 0.239215686917305f, 0.2196078449487686f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3882353007793427f, 0.3882353007793427f, 0.3725490272045135f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.6941176652908325f, 0.6941176652908325f, 0.686274528503418f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4605073928833008f, 0.04943911358714104f, 0.5236051082611084f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3644533753395081f, 0.1490195989608765f, 0.6509804129600525f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.4263696074485779f, 0.04343421757221222f, 0.5622317790985107f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.3773793876171112f, 0.1490195989608765f, 0.6509804129600525f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2958783209323883f, 0.04833391681313515f, 0.3519313335418701f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4867934882640839f, 0.0720587819814682f, 0.6995707750320435f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.3204914629459381f, 0.1960784494876862f, 0.4549019634723663f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.5638169050216675f, 0.05658607184886932f, 0.8240343332290649f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.585694432258606f, 0.09101291745901108f, 0.7854077219963074f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.725321888923645f, 0.07159829884767532f, 0.6944594383239746f, 0.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 0.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4549019634723663f, 0.196078434586525f, 0.2980392277240753f, 0.0f);

	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.8588235378265381f, 0.929411768913269f, 0.886274516582489f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.58902508020401f, 0.09747831523418427f, 0.8412017226219177f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.3098039329051971f, 0.7764706015586853f, 0.196078434586525f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.5510599613189697f, 0.1355707496404648f, 0.7896995544433594f, 1.0f);

	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.3450980484485626f, 0.05490196123719215f, 0.6549019813537598f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

}


void MenuAndDestroy(ImGuiWindow& window) {


	// Call rainbow here!



	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	SetupImGuiStyle();

	if (ShowMenu) {

		ImGui::SetNextWindowSize(ImVec2(350, 300));      
		ImGui::Begin(e("itsjustai | .gg/s497G2cqaz"), nullptr, ImGuiWindowFlags_NoCollapse);
		static int tab;
		if (ImGui::Button(e("Combat"), ImVec2(77, 0)))
			tab = 0;
		ImGui::SameLine();
		if (ImGui::Button(e("Visuals"), ImVec2(77, 0)))
			tab = 1;
		ImGui::SameLine();
		if (ImGui::Button(e("Exploit"), ImVec2(77, 0)))
			tab = 2;
		ImGui::SameLine();
		if (ImGui::Button(e("Misc"), ImVec2(77, 0)))
			tab = 3;
		if (tab == 0) {

			ImGui::BeginChild("##0", ImVec2(0, 0), true);
			ImGui::Checkbox(e("Memory Aim"), &Settings::MemoryAim);
			ImGui::Checkbox(e("Soft Aim"), &Settings::SoftAim);
			ImGui::SliderFloat(e("Aim Smooth"), &Settings::aimspeed, 1, 100);
			ImGui::Checkbox(e("fov circle"), &fovcircle);
			ImGui::SliderFloat(e("Fov Size"), &FovSize, 30.0f, 700.f);
			ImGui::Text("MADE BY - > itsjustai | .gg/s497G2cqaz");

			ImGui::EndChild();

		}
		else if (tab == 1)
		{

			if(ImGui::BeginChild("##1", ImVec2((350 / 2)- 10, 0), true)) {

				ImGui::Checkbox("Box Esp", &Settings::BoxESP);
				ImGui::Checkbox("Cornered box Esp", &Settings::Box);
				ImGui::Checkbox("Skeleton Esp", &Settings::SkeletonESP);
				ImGui::Checkbox("Line Esp", &Settings::LinesESP);
				ImGui::Checkbox("Name Esp", &Settings::PlayerNameESP);
				ImGui::Checkbox("Distance Esp", &Settings::DistanceESP);
				ImGui::Checkbox("Level Esp", &Settings::LevelESP);
				ImGui::Checkbox("Kills Esp", &Settings::KillsESP);
				ImGui::Text("MADE BY - > itsjustai | .gg/s497G2cqaz");


			}ImGui::EndChild();
			ImGui::SameLine();
			if (ImGui::BeginChild("##2", ImVec2(350 / 2, 0), true)) {
				ImGui::Checkbox("Platform Esp", &Settings::PlatformESP);
				ImGui::Checkbox("Weapon Esp", &Settings::EnemyWeaponESP);
				ImGui::Checkbox("Chams", &Settings::Chams);
				ImGui::Checkbox("Aim Line", &Settings::aimini);
				ImGui::Checkbox("Chest", &Settings::Chest);
				ImGui::Checkbox("Ammo", &Settings::Ammo);
				ImGui::Checkbox("Vehicle", &Settings::Vehicle);
				ImGui::Checkbox("item", &Settings::item);
				ImGui::Text("MADE BY - > itsjustai | .gg/s497G2cqaz");
			}ImGui::EndChild();

		}
		else if (tab == 2)
		{
			ImGui::BeginChild("##1", ImVec2(0, 0), true);
			ImGui::Checkbox("Fov Changer", &Settings::FovChanger);
			if (Settings::FovChanger)
				ImGui::SliderFloat("Fov Value", &Settings::FovChanger_Value, 0.0f, 180.0f);

			ImGui::Checkbox("Bullet TP", &Settings::SniperTp);
			ImGui::Checkbox("Car Fly", &Settings::CarFly);
			ImGui::Text("MADE BY - > itsjustai | .gg/s497G2cqaz");
			
			ImGui::EndChild();
		}
		else if (tab == 3)
		{
			ImGui::BeginChild("##1", ImVec2(0, 0), true);
			ImGui::Text("MADE BY - > itsjustai | .gg/s497G2cqaz");
			ImGui::EndChild();
		}








		ImGui::End();
	}

	// Rainbow renders


	ImGui::Render();
}


