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

	// ����irr�豸���������ʧ�����˳�

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/*
	��ȡָ����Ƶ���������SceneManager��ָ�룬
	�������ǾͲ������ǵ���irr::IrrlichtDevice::getVideoDriver()��irr::IrrlichtDevice::getSceneManager()��
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	Ҫ��ʾQuake 3��ͼ������������Ҫ��������
	����֮��3�ĵ�ͼ�����.pk3�ļ����൱��.zip�ļ���
    ��ˣ����ǽ�.pk3�ļ���ӵ���irr::io::IFileSystem�С�
	���֮�����ǾͿ��ԴӸô浵�ж�ȡ�ļ�����������ֱ�Ӵ洢�ڴ�����һ����
	*/
	device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

	/*
	���ڣ����ǿ���ͨ������irr::scene::ISceneManager::getMesh()���������� 
	���ǵõ�һ�����ص�irr::scene::IAnimatedMesh��ָ�롣 
	������֪��������֮��3���ĵ�ͼ�����������Ķ���������ֻ��һ��龲̬����ͼ�Σ���������һЩ���ʡ� 
	��ˣ�IAnimatedMesh����һ��֡��ɣ�������ǻ���ˡ��������������𼶱𣩵ġ���һ֡������ʹ��irr::scene::ISceneManager::addOctreeSceneNode����������һ���˶ȳ����ڵ㡣
    Octree��΢�Ż��˳��������Խ����Ƶ�ǰ�ɼ��ļ���ͼ�Ρ� 
	Octree�����������irr::scene::IMeshSceneNode������ʼ�ջ����������������ͼ�Σ�����������Ż��� 
	���ԣ�ʹ��irr::scene::ISceneManager::addMeshSceneNode()������addOctreeSceneNode()���Ƚ���Ƶ����������ƵĻ�Ԫ��  
	����irr::video::IVideoDriver������һ��irr::video::IVideoDriver::getPrimitiveCountDrawn()�������� 
	��ע�⣬ʹ��Octree���е��Ż����ڻ��ư�����������ͼ�εľ޴�����ʱ�����á�
	*/
	scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//		node = smgr->addMeshSceneNode(mesh->getMesh(0));

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
	����겻��Ҫ�ǿɼ��ģ��������ͨ��irr::IrrlichtDevice::ICursorControl�������ء�
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
	��󣬼ǵ�����Irrlicht�豸��
	*/
	device->drop();
	return 0;
}

/*
That's it. Compile and play around with the program.
**/
