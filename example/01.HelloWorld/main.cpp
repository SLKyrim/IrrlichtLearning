/** Example 001 HelloWorld

本教程说明如何设置IDE以使用Irrlicht引擎，以及如何使用它编写一个简单的HelloWorld程序。
该程序将显示如何使用VideoDriver，GUIEnvironment和SceneManager的基础知识。
Microsoft Visual Studio用作IDE，但是如果您使用的操作系统不同于Windows，甚至还可以使用其他操作系统，那么您也将能够理解所有内容。

您必须包括头文件<irrlicht.h>才能使用引擎。
头文件可以在Irrlicht Engine SDK目录include中找到。
为了让编译器找到该头文件，必须指定该文件所在的目录。
对于您使用的每个IDE和编译器，这都是不同的。
让我们简短地解释一下如何在Microsoft Visual Studio 2019中执行此操作：
1、新建一个C++空项目，然后选择 项目->“项目”属性
2、首先配置好编译配置和平台；然后在VC++目录中 包含目录选择下载好的SDK的include目录；库目录选择SDK的lib目录中对应操作系统的目录
3、将SDK中bin目录中对应操作系统的目录中的Irrlicht.dll文件复制到项目根目录
4、将SDK中media目录中的模型（sydney.md2）和贴图文件（sydney.bmp）复制到项目根目录中

设置IDE之后，编译器将知道在哪里可以找到Irrlicht Engine头文件，因此我们现在可以将其包含在我们的代码中。
*/
#include <irrlicht.h>

/*
在Irrlicht引擎中，所有内容都可以在名称空间“irr”中找到。
因此，如果要使用引擎的类，则必须在该类的名称之前编写irr::
例如，使用IrrlichtDevice编写：irr::IrrlichtDevice
为了摆脱irr::在每个类的名称前面，我们告诉编译器我们从现在开始使用该名称空间，并且我们将不再需要编写irr::
*/
using namespace irr;

/*
Irrlicht引擎中有5个子名称空间。 看看它们，您可以使用此链接来阅读它们的详细说明：http://irrlicht.sourceforge.net/docu/namespaces.html
如irr名称空间一样，我们现在不希望一直声明这5个子名称空间，以使此示例保持简单。因此，我们再次告诉编译器我们不希望总是写它们的名称。
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
为了能够使用Irrlicht.DLL文件，我们需要与Irrlicht.lib链接。
我们可以在项目设置中设置此选项，但是为了简单起见，我们为VisualStudio使用了杂注注释库。
在Windows平台上，我们必须摆脱控制台窗口，该控制台窗口在使用main()启动程序时会弹出。
这是由第二个实用程序完成的。我们也可以使用WinMain方法，尽管那样会失去平台独立性。
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


/*
This is the main method. We can now use main() on every platform.
*/
int main()
{
	/*
	引擎最重要的功能是createDevice（）函数。  
	IrrlichtDevice由它创建，它是使用引擎执行任何操作的根对象。createDevice（）具有7个参数：
	- deviceType: 设备的类型。 当前可以是Null设备，可以是软件渲染器D3D8，D3D9或OpenGL三者之一。 
	在此示例中，我们使用EDT_SOFTWARE，但要进行尝试，您可能需要将其更改为EDT_BURNINGSVIDEO，EDT_NULL，EDT_DIRECT3D8，EDT_DIRECT3D9或EDT_OPENGL.
	- windowSize: 要在FullScreenMode中创建的窗口或屏幕的大小。在此示例中，我们使用640x480.
	- bits: 每个像素的颜色位数。它应该是16或32。在窗口模式下运行时，通常会忽略该参数。
	- fullscreen: 指定我们是否希望设备以全屏模式运行。
	- stencilbuffer: 指定是否要使用模板缓冲区（用于绘制阴影）。
	- vsync: 指定是否要启用vsync，这仅在全屏模式下有用。
	- eventReceiver: 接收事件的对象。我们不想在这里使用此参数，并将其设置为0。

	始终检查返回值以应对不支持的驱动器，尺寸等。
	*/
	IrrlichtDevice* device =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if (!device)
		return 1;

	/*
	将窗口的标题设置为一些漂亮的文本。 
	请注意，字符串前面有一个“L”。Irrlicht引擎在显示文本时使用宽字符串
	*/
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	/*
	获取指向VideoDriver，SceneManager和图形用户界面环境的指针，
	以便我们不必总是编写device->getVideoDriver()，device->getSceneManager()或device->getGUIEnvironment()
	*/
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	/*
	我们使用GUI环境在窗口中添加一个hello world标签。
    文本放在左上角（10,10）和右下角（260,22）处。
	*/
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	/*
	为了显示一些有趣的东西，我们加载Quake 2模型并显示它。
	我们只需要使用getMesh（）从“场景管理器”中获取网格物体，并添加一个SceneNode即可使用addAnimatedMeshSceneNode（）显示网格物体。 
	我们检查getMesh（）的返回值以了解加载问题和其他错误。

	除了编写文件名sydney.md2，还可以加载Maya目标文件（.obj），完整的Quake3映射（.bsp）或任何其他受支持的文件格式。 
	顺便说一句，酷炫的Quake 2模型叫做Sydney是由Brian Collins建模的。
	*/
	IAnimatedMesh* mesh = smgr->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	/*
	为了让网格看起来更好一点，我们更改其材质。 
	我们禁用照明，因为此处没有动态照明，否则网格将完全变为黑色。 
	然后，我们设置帧循环，以便使用预定义的STAND动画。 
	最后，我们将纹理应用于网格。 如果没有它，将仅使用一种颜色来绘制网格。
	*/
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"));
	}

	/*
	为了查看网格，我们将相机放置在3d空间中的位置（0、30，-40）。 
	相机从那里看向（0,5,0），大约是我们的md2模型所在的地方。
	*/
	smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	/*
	好的，现在我们已经设置好场景，让我们绘制所有内容：
	我们在while（）循环中运行设备，直到该设备不再需要运行为止。 
	这将是用户关闭窗口或按ALT + F4（或任何键码关闭窗口）的时间。
	*/
	while (device->run())
	{
		/*
		在beginScene（）和endScene（）调用之间可以绘制任何内容。 
		如果需要，beginScene（）调用将使用颜色和深度缓冲区清除屏幕。 
		然后，让场景管理器和GUI环境绘制它们的内容。
		通过endScene（）调用，所有内容都会显示在屏幕上。
		*/
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	/*
	完成渲染循环后，我们必须删除使用createDevice（）之前创建的Irrlicht设备。 
	在Irrlicht引擎中，您必须删除使用以'create'开头的方法或函数创建的所有对象。只需调用-> drop（）即可删除该对象。
	有关更多信息，请参见irr::IReferenceCounted::drop（）上的文档。
	*/
	device->drop();

	return 0;
}

/*
That's it. Compile and run.
**/
