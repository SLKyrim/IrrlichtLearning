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

	// 创建irr设备；如果创建失败则退出

	IrrlichtDevice* device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.

	/*
	获取指向视频驱动程序和SceneManager的指针，
	这样我们就不必总是调用irr::IrrlichtDevice::getVideoDriver()和irr::IrrlichtDevice::getSceneManager()。
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	要显示Quake 3地图，我们首先需要加载它。
	雷神之锤3的地图打包成.pk3文件，相当于.zip文件。
    因此，我们将.pk3文件添加到了irr::io::IFileSystem中。
	添加之后，我们就可以从该存档中读取文件，就像它们直接存储在磁盘上一样。
	*/
	device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

	/*
	现在，我们可以通过调用irr::scene::ISceneManager::getMesh()来加载网格。 
	我们得到一个返回到irr::scene::IAnimatedMesh的指针。 
	如您所知，《雷神之锤3》的地图并不是真正的动画，它们只是一大块静态几何图形，并附加了一些材质。 
	因此，IAnimatedMesh仅由一个帧组成，因此我们获得了“动画”（即地震级别）的“第一帧”，并使用irr::scene::ISceneManager::addOctreeSceneNode（）创建了一个八度场景节点。
    Octree稍微优化了场景，尝试仅绘制当前可见的几何图形。 
	Octree的替代方法是irr::scene::IMeshSceneNode，它将始终绘制网格的完整几何图形，而无需进行优化。 
	尝试：使用irr::scene::ISceneManager::addMeshSceneNode()而不是addOctreeSceneNode()并比较视频驱动程序绘制的基元。  
	（在irr::video::IVideoDriver类中有一个irr::video::IVideoDriver::getPrimitiveCountDrawn()方法）。 
	请注意，使用Octree进行的优化仅在绘制包含大量几何图形的巨大网格时才有用。
	*/
	scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//		node = smgr->addMeshSceneNode(mesh->getMesh(0));

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
	鼠标光标不需要是可见的，因此我们通过irr::IrrlichtDevice::ICursorControl将其隐藏。
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
	最后，记得销毁Irrlicht设备。
	*/
	device->drop();
	return 0;
}

/*
That's it. Compile and play around with the program.
**/
