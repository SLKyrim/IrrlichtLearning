/** Example 001 HelloWorld

���̳�˵���������IDE��ʹ��Irrlicht���棬�Լ����ʹ������дһ���򵥵�HelloWorld���� 
�ó�����ʾ���ʹ��VideoDriver��GUIEnvironment��SceneManager�Ļ���֪ʶ��
Microsoft Visual Studio����IDE�����������ʹ�õĲ���ϵͳ��ͬ��Windows������������ʹ����������ϵͳ����ô��Ҳ���ܹ�����������ݡ�

���������ͷ�ļ�<irrlicht.h>����ʹ�����档 
ͷ�ļ�������Irrlicht Engine SDKĿ¼include���ҵ��� 
Ϊ���ñ������ҵ���ͷ�ļ�������ָ�����ļ����ڵ�Ŀ¼�� 
������ʹ�õ�ÿ��IDE�ͱ��������ⶼ�ǲ�ͬ�ġ� 
�����Ǽ�̵ؽ���һ�������Microsoft Visual Studio 2019��ִ�д˲�����

1���½�һ��C++����Ŀ��Ȼ��ѡ�� ��Ŀ->����Ŀ������

2���������úñ������ú�ƽ̨��Ȼ����VC++Ŀ¼�� ����Ŀ¼ѡ�����غõ�SDK��includeĿ¼����Ŀ¼ѡ��SDK��libĿ¼�ж�Ӧ����ϵͳ��Ŀ¼

3����SDK��binĿ¼�ж�Ӧ����ϵͳ��Ŀ¼�е�Irrlicht.dll�ļ����Ƶ���Ŀ��Ŀ¼

4����SDK��mediaĿ¼�е�ģ�ͣ�sydney.md2������ͼ�ļ���sydney.bmp�����Ƶ���Ŀ��Ŀ¼��

����IDE֮�󣬱�������֪������������ҵ�Irrlicht Engineͷ�ļ�������������ڿ��Խ�����������ǵĴ����С�
*/
#include <irrlicht.h>

/*
��Irrlicht�����У��������ݶ����������ƿռ䡰irr�����ҵ��� 
��ˣ����Ҫʹ��������࣬������ڸ��������֮ǰ��дirr:: 
���磬ʹ��IrrlichtDevice��д��irr::IrrlichtDevice
Ϊ�˰���irr::��ÿ���������ǰ�棬���Ǹ��߱��������Ǵ����ڿ�ʼʹ�ø����ƿռ䣬�������ǽ�������Ҫ��дirr::
*/
using namespace irr;

/*
Irrlicht��������5�������ƿռ䡣 �������ǣ�������ʹ�ô��������Ķ����ǵ���ϸ˵����http://irrlicht.sourceforge.net/docu/namespaces.html 
��irr���ƿռ�һ�����������ڲ�ϣ��һֱ������5�������ƿռ䣬��ʹ��ʾ�����ּ򵥡���ˣ������ٴθ��߱��������ǲ�ϣ������д���ǵ����ơ�
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
Ϊ���ܹ�ʹ��Irrlicht.DLL�ļ���������Ҫ��Irrlicht.lib���ӡ�
���ǿ�������Ŀ���������ô�ѡ�����Ϊ�˼����������ΪVisualStudioʹ������עע�Ϳ⡣
��Windowsƽ̨�ϣ����Ǳ�����ѿ���̨���ڣ��ÿ���̨������ʹ��main()��������ʱ�ᵯ���� 
�����ɵڶ���ʵ�ó�����ɵġ�����Ҳ����ʹ��WinMain����������������ʧȥƽ̨�����ԡ�
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
	��������Ҫ�Ĺ�����createDevice����������  
	IrrlichtDevice��������������ʹ������ִ���κβ����ĸ�����createDevice��������7��������

	- deviceType: �豸�����͡� ��ǰ������Null�豸�������������Ⱦ��D3D8��D3D9��OpenGL����֮һ�� 
	�ڴ�ʾ���У�����ʹ��EDT_SOFTWARE����Ҫ���г��ԣ���������Ҫ�������ΪEDT_BURNINGSVIDEO��EDT_NULL��EDT_DIRECT3D8��EDT_DIRECT3D9��EDT_OPENGL.

	- windowSize: Ҫ��FullScreenMode�д����Ĵ��ڻ���Ļ�Ĵ�С���ڴ�ʾ���У�����ʹ��640x480.

	- bits: ÿ�����ص���ɫλ������Ӧ����16��32���ڴ���ģʽ������ʱ��ͨ������Ըò�����

	- fullscreen: ָ�������Ƿ�ϣ���豸��ȫ��ģʽ���С�

	- stencilbuffer: ָ���Ƿ�Ҫʹ��ģ�建���������ڻ�����Ӱ����

	- vsync: ָ���Ƿ�Ҫ����vsync�������ȫ��ģʽ�����á�

	- eventReceiver: �����¼��Ķ������ǲ���������ʹ�ô˲���������������Ϊ0��

	ʼ�ռ�鷵��ֵ��Ӧ�Բ�֧�ֵ����������ߴ�ȡ�
	*/
	IrrlichtDevice* device =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if (!device)
		return 1;

	/*
	�����ڵı�������ΪһЩƯ�����ı��� 
	��ע�⣬�ַ���ǰ����һ����L����Irrlicht��������ʾ�ı�ʱʹ�ÿ��ַ���
	*/
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	/*
	��ȡָ��VideoDriver��SceneManager��ͼ���û����滷����ָ�룬
	�Ա����ǲ������Ǳ�дdevice->getVideoDriver()��device->getSceneManager()��device->getGUIEnvironment()
	*/
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	/*
	����ʹ��GUI�����ڴ��������һ��hello world��ǩ��
    �ı��������Ͻǣ�10,10�������½ǣ�260,22������
	*/
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	/*
	Ϊ����ʾһЩ��Ȥ�Ķ��������Ǽ���Quake 2ģ�Ͳ���ʾ����
	����ֻ��Ҫʹ��getMesh�����ӡ��������������л�ȡ�������壬�����һ��SceneNode����ʹ��addAnimatedMeshSceneNode������ʾ�������塣 
	���Ǽ��getMesh�����ķ���ֵ���˽�����������������

	���˱�д�ļ���sydney.md2�������Լ���MayaĿ���ļ���.obj����������Quake3ӳ�䣨.bsp�����κ�������֧�ֵ��ļ���ʽ�� 
	˳��˵һ�䣬���ŵ�Quake 2ģ�ͽ���Sydney����Brian Collins��ģ�ġ�
	*/
	IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	/*
	Ϊ����������������һ�㣬���Ǹ�������ʡ� 
	���ǽ�����������Ϊ�˴�û�ж�̬����������������ȫ��Ϊ��ɫ�� 
	Ȼ����������֡ѭ�����Ա�ʹ��Ԥ�����STAND������ 
	������ǽ�����Ӧ�������� ���û����������ʹ��һ����ɫ����������
	*/
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("sydney.bmp"));
	}

	/*
	Ϊ�˲鿴�������ǽ����������3d�ռ��е�λ�ã�0��30��-40���� 
	��������￴��0,5,0������Լ�����ǵ�md2ģ�����ڵĵط���
	*/
	smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	/*
	�õģ����������Ѿ����úó����������ǻ����������ݣ�
	������while����ѭ���������豸��ֱ�����豸������Ҫ����Ϊֹ�� 
	�⽫���û��رմ��ڻ�ALT + F4�����κμ���رմ��ڣ���ʱ�䡣
	*/
	while (device->run())
	{
		/*
		��beginScene������endScene��������֮����Ի����κ����ݡ� 
		�����Ҫ��beginScene�������ý�ʹ����ɫ����Ȼ����������Ļ�� 
		Ȼ���ó�����������GUI�����������ǵ����ݡ�
		ͨ��endScene�������ã��������ݶ�����ʾ����Ļ�ϡ�
		*/
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	/*
	�����Ⱦѭ�������Ǳ���ɾ��ʹ��createDevice����֮ǰ������Irrlicht�豸�� 
	��Irrlicht�����У�������ɾ��ʹ����'create'��ͷ�ķ����������������ж���ֻ�����-> drop��������ɾ���ö���
	�йظ�����Ϣ����μ�irr::IReferenceCounted::drop�����ϵ��ĵ���
	*/
	device->drop();

	return 0;
}

/*
That's it. Compile and run.
**/
