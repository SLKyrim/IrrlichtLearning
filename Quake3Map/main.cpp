/** Example 002 Quake3Map
���ָ�Ͻ�Ϊ����ʾ���������������һ��Quake3��ͼ�ļ�,���Ҹ����������
����Ż��Ĵ���һ�������ڵ���Ⱦ���Լ�����һ���û����Ƶ��������
����������һ��HelloWorld����һ�����ɣ����Ȱ���irr����ͷ�ļ���
�������һ��iostramͷΪ�����û��Ŀ���̨����
*/
#include <irrlicht.h>
#include <iostream>

/*
������дHelloWorld����֮ǰ��Ҫ����׼��һ������irrlicht�����У�һ�к�����
������������irr�����ռ��ڵġ���������Ҫ���߱༭����������ʹ�õĺ�������irr�����ռ�
��Ѱ�ң���������������ռ䣬Core��Scene��video��io��Gui����HelloWorld��ͬ
���ǣ���������û��Ϊ����ӿռ�ֱ�ָ�������ռ��֪ͨ����Ϊ�������Ļ���������Ĵ����У�
�㽫�����׻�֪ÿ���������������ĸ������ռ��ڵġ���Ȼ����Ҳ���Լ���using
*/
using namespace irr;

/*
ͬ����Ϊ�˿���ʹ��irrlicht.DLL�ļ���������Ҫ����һ��irrlicht.lib�ļ���������Ҫ������Ŀ����
�������ڴ����н���һ����������
*/
#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
OK�����ǿ�ʼ��main()���
*/
int main()
{
	/*
	����HelloWorld���ӣ�����ͨ��CreateDevice����һ��Irr�豸��������������������
	�û�����Ӳ�������豸��ѡ���������ģ�������һ�ξ޴��Q3�������ؽ����൱����
	����Ϊ�˽�����ʾ������һ�����ܣ�����Ҳ��������ѡ���ˡ�

	*/

	// ask user for driver

	video::E_DRIVER_TYPE driverType;

	printf("Please select the driver you want for this example:\n"\
		" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
		" (d) Burning's Software Renderer\n (e) Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	char i;
	std::cin >> i;

	switch (i)
	{
	case 'a': driverType = video::EDT_OPENGL;   break;
	case 'b': driverType = video::EDT_DIRECT3D9; break;
	case 'c': driverType = video::EDT_DIRECT3D8; break;
	case 'd': driverType = video::EDT_BURNINGSVIDEO; break;
	case 'e': driverType = video::EDT_SOFTWARE; break;
	case 'f': driverType = video::EDT_NULL;     break;
	default: return 1;
	}

	//����irr�豸

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/*
	��ȡһ�����������ͳ��������ָ��
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	Ϊ����ʾQUAKE3�ĵ�ͼ������������Ҫ��ȡ����
	Quake3��ͼ�������.pk3�ļ��У��������ǵ��ļ�ϵͳ��Ҫ����.pk3���ļ�,
	�����Ǽ�����֮�����ǻ���Ҫ�Ӱ��ļ��ж�����ж�ȡ��
	*/
	device->getFileSystem()->addFileArchive("map-20kdm2.pk3");

	/*
	�������ǿ���ͨ������getMesh()����������Mesh�Ķ�ȡ�����ǻ����һ������Mesh
	IAnimateMesh��ָ�롣Ȼ�����ǿ��������ʣ�Quake3��ͼ����һ������������ΪʲôҪ
	ʹ��IanimateMesh����Mesh�أ��������о���Quake3�ĵ�ͼ��������һ���޴��ģ��
	�Լ�һЩ��ͼ�ļ���ɵġ����ǿ������Ϊ��������һ��������ɣ��������������һ֡
	�������ǻ�ö����ĵ�һ֡getMesh(0)(����0����ָ��֡��)��Ȼ��ʹ��������һ���˲���
	�����ڵ㡣
	�˲����������ǶԳ�����Ⱦ�����Ż������ǽ�����Ⱦ����������ĳ��������������
	�鿴������Ⱦ����鼮��
	����ڰ˲��������ڵ����һ�ּ��ط�ʽ����ֱ�Ӵ���һ��AnimateMeshSceneNode��
	����Mesh�����ڵ㣬�����������Ļ��Ͳ�������Ż���ѡ������һ���Լ��ػ������е�
	������
	������Ĵ�������������Ͷ�д�ˣ�������л��Ž��г���һ�¡�
	ֵ��ע����ǰ˲������������÷�Χһ���Ǵ��͵����ⳡ������
	*/
	scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//	node = smgr->addMeshSceneNode(mesh->getMesh(0));

	/*
	���ǽ���������ԭ�������һЩƽ������Ӧ���ģ��
	*/
	if (node)
		node->setPosition(core::vector3df(-1300, -144, -1249));

	/*
	�������ǽ�����Ҫһ�������ȥ�۲����ŵ�ͼ������������һ�����û����Ƶ�
	������������irr����������಻ͬ���͵�����������磬Maya�������������
	Maya����е���������ƣ�������¿ɽ�����ת���������¾Ϳ��Խ������ţ��Ҽ�����
	�Ϳ��Խ����ƶ������������봴������������ʽ�����������ôֻҪaddCameraSceneNodeMaya()
	�Ϳ����ˡ�������������Ҫ��Ƶ�������������ڱ�׼FPS�Ŀ����趨���������ǵ���
	addCameraSceneNodeFPS()������������

	*/
	smgr->addCameraSceneNodeFPS();

	/*
	����ͼ��û��Ҫ��ʾ������������������������Ϊ���ء�
	*/
	device->getCursorControl()->setVisible(false);

	/*
	�������������е����飬�������ǿ�ʼ�������ѡ����ǻ���Ҫ�ڴ��ڵı�����
	��ʾ��ǰ��FPS��
	if(device->isWindowsActive())��һ�д����ǿ�ѡ�ģ�����Ϊ��Ԥ������
	�л�����ڶ�����������Ⱦ֡������ʾ����ȷ�����Ǽ��ϰɡ�
	*/
	int lastFPS = -1;

	while (device->run())
	{
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
			smgr->drawAll();
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
		else
			device->yield();
	}

	/*
	��󣬼ǵ�����irr�豸
	*/
	device->drop();
	return 0;
}