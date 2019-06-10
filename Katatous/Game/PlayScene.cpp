#include "pch.h"
#include "PlayScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"

void PlayScene::Build(GameContext& context)
{
	auto text = std::make_shared<FontObject>(L"Resources/Fonts/logofont.spritefont", L"プレイシーン");
	context << text;

	class C : public GameObject
	{
		float lastTime;
		std::shared_ptr<FontObject> m_text;

	public:
		C(const std::shared_ptr<FontObject>& text)
			: m_text(text) {}

		void Initialize(GameContext& context)
		{
			lastTime = context.GetTimer().GetTotalSeconds();
		}

		void Update(GameContext& context)
		{
			float time = context.GetTimer().GetTotalSeconds() - lastTime;

			wchar_t str[256];
			std::swprintf(str, L"プレイシーン: 残り%.2f秒", 3 - time);

			m_text->SetText(str);

			if (time > 3.f)
				context.GetSceneManager().LoadScene("ResultScene");
		}
	};
	context << std::make_shared<C>(text);
}
