#include "pch.h"
#include "ResultScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"

using namespace DirectX;

void ResultScene::Build(GameContext& context)
{
	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", L"リザルトシーン");
	context << text;

	class D : public GameObject
	{
		void Update(GameContext& context)
		{
			if (context.GetKeyboardStateTracker().IsKeyPressed(Keyboard::Space))
				context.GetSceneManager().LoadScene("TitleScene");
		}
	};
	context << std::make_shared<D>();
}
