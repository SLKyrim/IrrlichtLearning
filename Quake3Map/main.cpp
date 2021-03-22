/** Example 002 Quake3Map
这份指南将为你演示如何向引擎中载入一张Quake3地图文件,并且告诉你如何最
便捷优化的创建一个场景节点渲染，以及创建一个用户控制的摄像机。
让我们像上一个HelloWorld例子一样做吧，首先包含irr引擎头文件。
另外包含一个iostram头为方便用户的控制台输入
*/
#include <irrlicht.h>
#include <iostream>

/*
类似于写HelloWorld例子之前需要做的准备一样，在irrlicht引擎中，一切函数，
类命名都是在irr命名空间内的。我们依旧要告诉编辑器我们现在使用的函数当在irr命名空间
内寻找，它们五个子命名空间，Core，Scene，video，io，Gui，与HelloWorld不同
的是，我们这里没有为五个子空间分别指定命名空间的通知，因为这样做的话，在下面的代码中，
你将更容易获知每个函数到底属于哪个命名空间内的。当然，你也可以加上using
*/
using namespace irr;

/*
同样，为了可以使用irrlicht.DLL文件，我们需要链接一个irrlicht.lib文件。我们需要进行项目设置
，或者在代码中进行一次连接声明
*/
#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
OK，我们开始。main()入口
*/
int main()
{
	/*
	类似HelloWorld例子，我们通过CreateDevice创建一个Irr设备，不过在这里我们允许
	用户进行硬件加速设备的选择，其中软件模拟进行了一次巨大的Q3场景加载将会相当慢，
	不过为了进行演示有这样一个功能，我们也把它列做选项了。

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

	//创建irr设备

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/*
	获取一个视屏驱动和场景管理的指针
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	为了显示QUAKE3的地图，我们首先需要读取它。
	Quake3地图被打包在.pk3文件中，所以我们的文件系统需要加载.pk3包文件,
	在我们加载它之后，我们还需要从包文件中对其进行读取。
	*/
	device->getFileSystem()->addFileArchive("map-20kdm2.pk3");

	/*
	现在我们可以通过调用getMesh()函数来进行Mesh的读取。我们获得了一个动画Mesh
	IAnimateMesh的指针。然而我们可能有疑问，Quake3地图并非一个动画，我们为什么要
	使用IanimateMesh动画Mesh呢？我们先研究下Quake3的地图，它是由一个巨大的模型
	以及一些贴图文件组成的。我们可以理解为，它是由一个动画组成，而这个动画仅有一帧
	所以我们获得动画的第一帧getMesh(0)(其中0就是指定帧数)，然后使用它创建一个八叉树
	场景节点。
	八叉树的作用是对场景渲染进行优化，就是仅仅渲染摄像机所见的场景，这个请自行
	查看３Ｄ渲染相关书籍。
	相对于八叉树场景节点的另一种加载方式就是直接创建一个AnimateMeshSceneNode，
	动画Mesh场景节点，但是这样做的话就不会进行优化拣选，它会一次性加载绘制所有的
	场景。
	在下面的代码里，我两种类型都写了，你可以切换着进行尝试一下。
	值得注意的是八叉树场景的适用范围一般是大型的室外场景加载
	*/
	scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//	node = smgr->addMeshSceneNode(mesh->getMesh(0));

	/*
	我们将世界矩阵的原点进行了一些平移以适应这个模型
	*/
	if (node)
		node->setPosition(core::vector3df(-1300, -144, -1249));

	/*
	现在我们仅仅需要一个摄像机去观察这张地图。这次我们设计一个可用户控制的
	灵活摄像机。在irr引擎中有许多不同类型的摄像机；例如，Maya摄像机就类似于
	Maya软件中的摄像机控制，左键按下可进行旋转，两键按下就可以进行缩放，右键按下
	就可以进行移动。假如我们想创建这样操作方式的摄像机，那么只要addCameraSceneNodeMaya()
	就可以了。而我们现在需要设计的摄像机则类似于标准FPS的控制设定，所以我们调用
	addCameraSceneNodeFPS()函数来创建。

	*/
	smgr->addCameraSceneNodeFPS();

	/*
	鼠标的图标没必要显示出来，所以我们设置其属性为隐藏。
	*/
	device->getCursorControl()->setVisible(false);

	/*
	我们做完了所有的事情，现在我们开始绘制它把。我们还需要在窗口的标题上
	显示当前的FPS。
	if(device->isWindowsActive())这一行代码是可选的，但是为了预防由于
	切换活动窗口而导致引擎渲染帧速率显示不正确，还是加上吧。
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
	最后，记得销毁irr设备
	*/
	device->drop();
	return 0;
}