/** Example 004 Movement

���̳���ʾ������ƶ���ʹSceneNodes��ɶ�����
��ʾ��SceneNodeAnimators�Ļ�������Լ�ʹ�ü��̽��еĽڵ��ֶ��ƶ���
���ǽ���ʾ������֡�ʵ��ƶ�������ζ���ƶ���ȡ����Irrlichtѭ�������һ�����еĳ���ʱ�䡣

ʾ��19.MouseAndJoystick��ʾ����δ�����Щ���͵����롣

������һ�����Ұ���ͷ�ļ���ʹ��irr�����ռ䣬��������������.lib�ļ����ӡ�
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
Ҫ�����������ͼ�������֮����¼��������硰����OK��ť�ѱ�������֮���GUI�¼���������Ҫһ����irr::IEventReceiver���������Ķ���
ֻ��һ�ַ���������д��irr::IEventReceiver::OnEvent()��
�¼�����ʱ�����潫�������ô˷�����
����������֪�������Ƿ�ס��ĳ������������ǽ���סÿ�����ĵ�ǰ״̬��
*/
class MyEventReceiver : public IEventReceiver
{
public:
	// �������Ǳ���ʵ�ֵ�һ������
	virtual bool OnEvent(const SEvent& event)
	{
		// ��סÿ���������»�������
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// �����ڼ���Ƿ�ס��ĳ����
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
		//return KeyIsDown[229]; // �������뷨���ص�KeyCode����229���л���Ӣ�����뷨�Ϳ����ƶ�������
	}

	MyEventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// ����ʹ�ô�����洢ÿ�����ĵ�ǰ״̬
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


/*
���ڱ��ְ��¼����¼���������׼��������ʵ�ʵ���Ӧ���ڻ��Ƴ���֮ǰ����Ⱦѭ���ڽ��С�
��ˣ�����ֻ�贴��һ��irr::IrrlichtDevice������Ҫ�ƶ��ĳ����ڵ㼴�ɡ�
���ǻ�����������һЩ�����ڵ㣬����ʾ�ƶ������ó����ڵ㶯���ĸ��ֿ����ԡ�
*/
int main()
{
	// ���û�ѯ���豸
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// ����ʱ�������
	MyEventReceiver receiver;

	// �����豸
	IrrlichtDevice* device = createDevice(driverType,
		core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	������ʹ��WSAD�����ƶ��Ľڵ㡣
	���Ǵ���һ������ڵ㣬����һ�����õļ���ͼԪ��
	���ǽ��ڵ�����ڣ�0,0,30������Ϊ�����������ʹ�俴��������Ȥ��
	��Ϊ�����ڸó�����û�ж�̬��Դ����������Ϊÿ��ģ�Ͷ�����������������ģ�ͽ��Ǻ�ɫ�ģ���
	*/
	scene::ISceneNode* node = smgr->addSphereSceneNode();
	if (node)
	{
		node->setPosition(core::vector3df(0, 0, 30));
		node->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	/*
	���ڣ����Ǵ�����һ���ڵ㣬�ýڵ����ʹ�ó����ڵ㶯������animator���ƶ���
	�����ڵ㶯���������޸ĳ����ڵ㣬���ҿ��Խ��丽�ӵ��κγ����ڵ㣬�������񳡾��ڵ㣬����ƣ��ƹ�������������ڵ㡣
	�����ڵ㶯���������ܹ��޸ĳ����ڵ��λ�ã����һ����ԶԶ����������ж�������
	���Ǵ���һ����ά���ݼ������ڵ㣬�������ϸ���һ��������Բ�������ڵ㶯������������ʹ�ýڵ�Χ�����ǵ����峡���ڵ���С�
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
	�����������ʾ�����ڵ㶯���������Ե����һ�������ڵ���b3dģ�ͣ���ģ��ʹ�á�ֱ�ɡ��������ڵ�֮�����С�
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
		Ϊ��ʹģ�Ϳ�������ȷ�����ǽ������������ö���Ӧ�����ѭ����֡����ģ����ת180�ȣ������������ٶȺ�����
		Ҫ������ȷ�Ķ�����֡���ٶȣ������ǻ����Ե���"anms->setMD2Animation(scene::EMAT_RUN)"���ڡ����С������������ǡ�setFrameLoop���͡�setAnimationSpeed��
		�����������MD2�����������֪����ο�ʼ����������
		����һ���õĽ����ǲ�Ҫʹ��Ӳ�����֡��...
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
	Ϊ���ܹ��ڴ˳����й۲���ƶ������Ǵ����˵�һ�˳������Ϸ�����������ʹ����겻�ɼ���
	*/
	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);

	/*
	���ɫ�ʷḻ��irrlicht Logo
	*/
	device->getGUIEnvironment()->addImage(
		driver->getTexture("../../media/irrlichtlogoalpha2.tga"),
		core::position2d<s32>(10, 20));

	gui::IGUIStaticText* diagnostics = device->getGUIEnvironment()->addStaticText(
		L"", core::rect<s32>(10, 10, 400, 20));
	diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));

	/*
	�����Ѿ���������й�������������������������
	���ǻ���ÿ��ĵ�ǰ֡�����������������д�봰�ڵı��⡣
	*/
	int lastFPS = -1;

	// Ϊ�˽��ж�����֡���ʵ��˶������Ǳ���֪������һ֡�����Ѿ����˶೤ʱ��
	u32 then = device->getTimer()->getTime();

	// �����ƶ��ٶȣ���λΪÿ�롣
	const f32 MOVEMENT_SPEED = 5.f;

	while (device->run())
	{
		// ���֡����ʱ��
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		/* ����Ƿ�סW��S��A��D����Ȼ��ֱ��ƶ�����ڵ㡣*/
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

		smgr->drawAll(); // ����3D����
		device->getGUIEnvironment()->drawAll(); // ����gui������Logo��

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
