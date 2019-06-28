#include "pch.h"
#include "TitleScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"

using namespace DirectX;

void TitleScene::Build(GameContext& context)
{
	auto obj = GameObject::Create();
	auto text = obj->AddComponent<FontObject>(L"Resources/Fonts/logofont.spritefont", L"�^�C�g���V�[��");
	context << obj;

	class B : public Component
	{
		void Update(GameContext& context)
		{
			if (context.GetKeyboardStateTracker().IsKeyPressed(Keyboard::Space))
				context.GetSceneManager().LoadScene("PlayScene");
		}
	};
	auto obj2 = GameObject::Create();
	obj2->AddComponent<B>();
	context << obj2;
}
