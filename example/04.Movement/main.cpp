/** Example 004 Movement

本教程显示了如何移动和使SceneNodes变成动画。
显示了SceneNodeAnimators的基本概念，以及使用键盘进行的节点手动移动。
我们将演示独立于帧率的移动，这意味着移动量取决于Irrlicht循环的最后一次运行的持续时间。

示例19.MouseAndJoystick显示了如何处理这些类型的输入。

和往常一样，我包括头文件，使用irr命名空间，并告诉链接器与.lib文件链接。
*/
#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

/*
要接收诸如鼠标和键盘输入之类的事件，或诸如“单击OK按钮已被单击”之类的GUI事件，我们需要一个从irr::IEventReceiver对象派生的对象。
只有一种方法可以重写：irr::IEventReceiver::OnEvent()。
事件发生时，引擎将立即调用此方法。
我们真正想知道的是是否按住了某个键，因此我们将记住每个键的当前状态。
*/
class MyEventReceiver : public IEventReceiver
{
public:
	// 这是我们必须实现的一个方法
	virtual bool OnEvent(const SEvent& event)
	{
		// 记住每个键是向下还是向上
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// 这用于检查是否按住了某个键
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
		//return KeyIsDown[229]; // 中文输入法返回的KeyCode总是229，切换成英文输入法就可以移动球体了
	}

	MyEventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// 我们使用此数组存储每个键的当前状态
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


/*
用于保持按下键的事件接收器已准备就绪，实际的响应将在绘制场景之前在渲染循环内进行。
因此，我们只需创建一个irr::IrrlichtDevice和我们要移动的场景节点即可。
我们还创建了其他一些场景节点，以显示移动和设置场景节点动画的各种可能性。
*/
int main()
{
	// 向用户询问设备
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// 创建时间接收器
	MyEventReceiver receiver;

	// 创建设备
	IrrlichtDevice* device = createDevice(driverType,
		core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	创建将使用WSAD按键移动的节点。
	我们创建一个球体节点，它是一个内置的几何图元。
	我们将节点放置在（0,0,30）处并为其分配纹理，以使其看起来更有趣。
	因为我们在该场景中没有动态光源，所以我们为每个模型都禁用了照明（否则模型将是黑色的）。
	*/
	scene::ISceneNode* node = smgr->addSphereSceneNode();
	if (node)
	{
		node->setPosition(core::vector3df(0, 0, 30));
		node->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	/*
	现在，我们创建另一个节点，该节点可以使用场景节点动画器（animator）移动。
	场景节点动画器可以修改场景节点，并且可以将其附加到任何场景节点，例如网格场景节点，广告牌，灯光甚至相机场景节点。
	场景节点动画器不仅能够修改场景节点的位置，而且还可以对对象的纹理进行动画处理。
	我们创建一个多维数据集场景节点，并在其上附加一个“飞行圆”场景节点动画制作器，以使该节点围绕我们的球体场景节点飞行。
	*/
	scene::ISceneNode* n = smgr->addCubeSceneNode();

	if (n)
	{
		n->setMaterialTexture(0, driver->getTexture("../../media/t351sml.jpg"));
		n->setMaterialFlag(video::EMF_LIGHTING, false);
		scene::ISceneNodeAnimator* anim =
			smgr->createFlyCircleAnimator(core::vector3df(0, 0, 30), 20.0f);
		if (anim)
		{
			n->addAnimator(anim);
			anim->drop();
		}
	}

	/*
	我们添加来显示场景节点动画器可能性的最后一个场景节点是b3d模型，该模型使用“直飞”动画器在点之间运行。
	*/
	scene::IAnimatedMeshSceneNode* anms =
		smgr->addAnimatedMeshSceneNode(smgr->getMesh("../../media/ninja.b3d"));

	if (anms)
	{
		scene::ISceneNodeAnimator* anim =
			smgr->createFlyStraightAnimator(core::vector3df(100, 0, 60),
				core::vector3df(-100, 0, 60), 3500, true);
		if (anim)
		{
			anms->addAnimator(anim);
			anim->drop();
		}

		/*
		为了使模型看起来正确，我们禁用照明，设置动画应在其间循环的帧，将模型旋转180度，并调整动画速度和纹理。
		要设置正确的动画（帧和速度），我们还可以调用"anms->setMD2Animation(scene::EMAT_RUN)"用于“运行”动画，而不是“setFrameLoop”和“setAnimationSpeed”
		但这仅适用于MD2动画，因此您知道如何开始其他动画。
		但是一个好的建议是不要使用硬编码的帧号...
		*/
		anms->setMaterialFlag(video::EMF_LIGHTING, false);

		anms->setFrameLoop(0, 13);
		anms->setAnimationSpeed(15);
		//		anms->setMD2Animation(scene::EMAT_RUN);

		anms->setScale(core::vector3df(2.f, 2.f, 2.f));
		anms->setRotation(core::vector3df(0, -90, 0));
		//		anms->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"));

	}


	/*
	为了能够在此场景中观察和移动，我们创建了第一人称射击游戏风格的相机，并使鼠标光标不可见。
	*/
	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);

	/*
	添加色彩丰富的irrlicht Logo
	*/
	device->getGUIEnvironment()->addImage(
		driver->getTexture("../../media/irrlichtlogoalpha2.tga"),
		core::position2d<s32>(10, 20));

	gui::IGUIStaticText* diagnostics = device->getGUIEnvironment()->addStaticText(
		L"", core::rect<s32>(10, 10, 400, 20));
	diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

	/*
	我们已经完成了所有工作，所以让我们来绘制它。
	我们还将每秒的当前帧数和驱动程序的名称写入窗口的标题。
	*/
	int lastFPS = -1;

	// 为了进行独立于帧速率的运动，我们必须知道自上一帧以来已经过了多长时间
	u32 then = device->getTimer()->getTime();

	// 这是移动速度，单位为每秒。
	const f32 MOVEMENT_SPEED = 5.f;

	while (device->run())
	{
		// 算出帧增量时间
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		/* 检查是否按住W，S，A或D键，然后分别移动球体节点。*/
		core::vector3df nodePosition = node->getPosition();

		if (receiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
		else if (receiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

		if (receiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
		else if (receiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;

		node->setPosition(nodePosition);

		driver->beginScene(true, true, video::SColor(255, 113, 113, 133));

		smgr->drawAll(); // 绘制3D场景
		device->getGUIEnvironment()->drawAll(); // 绘制gui环境（Logo）

		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
	}

	/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();

	return 0;
}

/*
That's it. Compile and play around with the program.
**/
