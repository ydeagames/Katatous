#include "pch.h"
#include "TitleScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"

using namespace DirectX;

void TitleScene::Build(GameContext& context)
{
	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", L"タイトルシーン");
	context << text;

	class B : public GameObject
	{
		void Update(GameContext& context)
		{
			if (context.GetKeyboardStateTracker().IsKeyPressed(Keyboard::Space))
				context.GetSceneManager().LoadScene("PlayScene");
		}
	};
	context << std::make_shared<B>();
}
