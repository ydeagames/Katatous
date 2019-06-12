#include "pch.h"
#include "PlayScene.h"
#include "SceneCommons.h"
#include "Framework/SceneManager.h"
#include "Framework/DebugTools/DebugCameraWrapper.h"
#include "Framework/DebugTools/GridFloorWrapper.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void PlayScene::Build(GameContext& context)
{
	context.GetCamera().view = Matrix::CreateLookAt(Vector3(0, 5, 10), Vector3::Zero, Vector3::Up);

	context << std::make_shared<DebugCameraWrapper>();
	context << std::make_shared<GridFloorWrapper>();

	auto bit = std::make_shared<GeometricObject>(
		[](GameContext& context) { return GeometricPrimitive::CreateTeapot(context.GetDR().GetD3DDeviceContext()); },
		Color(Colors::Blue)
		);
	context << bit;
}
