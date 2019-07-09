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

	auto camCtrl = GameObject::Create();
	camCtrl->AddComponent<DebugCameraWrapper>();
	camCtrl->AddComponent<GridFloorWrapper>();
	context << camCtrl;

	auto bitObj = GameObject::Create();
	auto bit = bitObj->AddComponent<GeometricObject>(
		[](GameContext& context) { return GeometricPrimitive::CreateTeapot(context.GetDR().GetD3DDeviceContext()); },
		Color(Colors::Blue)
		);
	bitObj->transform->LocalPosition += Vector3::Up * 2;
	context << bitObj;
}
