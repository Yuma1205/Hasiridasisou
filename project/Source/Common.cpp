#include "Common.h"
#include "../ImGui/imgui.h"

Common::Common()
{
	DontDestroyOnSceneChange(); // Scene‚ª•Ï‚í‚Á‚Ä‚àÁ‚¦‚È‚¢
	stageNumber = 1;
}

void Common::Draw()
{
	ImGui::Begin("Common");
	ImGui::InputInt("Stage", &stageNumber);
	ImGui::End();
}

