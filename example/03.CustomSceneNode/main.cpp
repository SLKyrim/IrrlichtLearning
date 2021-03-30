/** Example 003 Custom SceneNode

���̳̱���ǰ�Ľ̸̳��߼���
�������ǰֻ����ʹ��Irrlicht���棬�������Ҫ�ȿ�������ʾ����
���̳̽�������δ����Զ��峡���ڵ��Լ������������ʹ������ 
���Ҫʵ��Irrlicht Engine��ǰ��֧�ֵ���Ⱦ����������Ҫһ���Զ��峡���ڵ㡣 
���磬������ʹ������д���������Ż�����Ⱦ����߼����γ����ڵ㡣 
ͨ�������Զ��峡���ڵ㣬������������չIrrlicht���沢ʹ֮��Ӧ���Լ�������

�ҽ�ʹ���̳̱��ּ򵥣����������ݶ����ּ�̣�
���������ݱ�����һ��.cpp�ļ��У������ڴ�ʹ�ø����棬�������������н̳���һ����

���ȣ��Ұ���ͷ�ļ���ʹ��irr�����ռ䣬��������������.lib�ļ����ӡ�
*/
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
���Ǳ��̸̳����ӵĲ��֣������Լ����Զ��峡���ڵ���ࡣ 
Ϊ����������ǵĳ����ڵ�Ȳ��������Ż���Ⱦ����Ҳ����terrain�����ڵ㣬����һ���򵥵������壬����һ����4�������Ķ�����ɵ�3d���󣬸ö���ֻ���Լ����ƣ������������顣
��ע�⣬�˷�����Irrlicht�в���Ҫ�Զ��峡���ڵ㡣
ȡ����֮���ǴӼ���ͼ�δ���һ�����񲢽��䴫�ݸ�irr::scene::IMeshSceneNode��
��ʾ����˵�����ڷǳ��򵥵������д����Զ��峡���ڵ�Ĺ��̡�

Ϊ��ʹ���ǵĳ����ڵ��ܹ����뵽Irrlicht Engine�����У����Ǵ���������Ҫ��irr::scene::ISceneNode�����������ұ�����дһЩ������
*/

class CSampleSceneNode : public scene::ISceneNode
{

	/*
	���ȣ���������һЩ��Ա�������߽��Box��4������Vertices��������Ĳ���Meterial��
	*/
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;

	/*
	���캯���Ĳ��� ָ�� �����ڵ�ĸ���parent��ָ�򳡾���������ָ��mgr�Լ������ڵ��ID��
    �ڹ��캯���У����ǵ��ø���Ĺ��캯�������ò��ʵ�ĳЩ���ԣ��������Ժ�Ҫ���Ƶ��������4�����㡣
	*/

public:

	CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id)
	{
		Material.Wireframe = false;
		Material.Lighting = false;

		Vertices[0] = video::S3DVertex(0, 0, 10, 1, 1, 0,
			video::SColor(255, 0, 255, 255), 0, 1);
		Vertices[1] = video::S3DVertex(10, 0, -10, 1, 0, 0,
			video::SColor(255, 255, 0, 255), 1, 1);
		Vertices[2] = video::S3DVertex(0, 20, 0, 0, 1, 1,
			video::SColor(255, 255, 255, 0), 1, 0);
		Vertices[3] = video::S3DVertex(-10, 0, -10, 0, 0, 1,
			video::SColor(255, 0, 255, 0), 0, 0);

		/*
		Irrlicht������Ҫ֪�������ڵ�ı߽�����������Զ��޳������������� 
		��ˣ�������Ҫ��ʹ�õ�4�����㴴��һ���߽��
		�������ϣ������ʹ�øÿ�����Զ��޳���/���봴���ÿ�
		��Ҳ������irr::scene::EAC_OFF����irr::scene::ISceneNode::setAutomaticCulling()
		*/
		Box.reset(Vertices[0].Pos);
		for (s32 i = 1; i < 4; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	/*
	�ڻ���֮ǰ�����������������ó�����ÿ�������ڵ��irr::scene::ISceneNode::OnRegisterSceneNode()������
	��������ڵ�ϣ���Լ����ƣ�����Խ���ע�ᵽҪ���Ƶĳ����������С�
	���߳�����������ʱӦ����irr::scene::ISceneNode::render()���б�Ҫ��
	���磬��ͨ�����ڵ�һ����һ������Ⱦ�����ݣ���ģ�建������Ӱϣ�����������������ڵ�֮����ơ�
	������Ҫ���������������ڵ㣨����У�֮ǰ��Ⱦ��Ӱ����ƹⳡ���ڵ㡣
	��ˣ����������ֻ��ע�᳡���ڵ㼴��������Ⱦ��
	����������������������ƹ�һ����Ⱦ�����Ǳ������SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
	�˺����ǵ��û����ʵ��irr::scene::ISceneNode::OnRegisterSceneNode()�������÷���Ҳ������ýڵ�������ӳ����ڵ�����ע�ᡣ
	*/
	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	/*
	��render()�����У������˴������Ȥ�����飺Scene�ڵ����������Ⱦ��
	������д�˷��������������塣
	*/
	virtual void render()
	{
		u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
	}

	/*
	������Ǵ���������С�ĸ��ӷ���:
	irr::scene::ISceneNode::getBoundingBox()���ش˳����ڵ�ı߽��;
	irr::scene::ISceneNode::getMaterialCount()���ش˳����ڵ��еĲ������������ǵ�������ֻ��һ�ֲ��ʣ�;
	irr::scene::ISceneNode::getMaterial()�����������Ĳ��ʡ�
	��Ϊ����ֻ��һ�ֲ��ϣ����Լ���û���˵�����������0��getMaterial()����ô���Ǿ�ֻ�ܷ���һ�ֲ��ϡ�
	*/
	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}
};

/*
�����ڵ���ɡ�
���ڣ�����ֻ��Ҫ�������棬���������ڵ����Ӱ����Ȼ��鿴������ɡ�
*/
int main()
{
	// ���û�ѯ���豸
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// �����豸

	IrrlichtDevice* device = createDevice(driverType,
		core::dimension2d<u32>(640, 480), 16, false);

	if (device == 0)
		return 1; // could not create selected driver.

	// ������������

	device->setWindowCaption(L"Custom Scene Node - Irrlicht Engine Demo");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	smgr->addCameraSceneNode(0, core::vector3df(0, -40, 0), core::vector3df(0, 0, 0));

	/*
	�������ǵĳ����ڵ㡣
	�Ҳ�������new�Ľ������Ϊ��Ӧ�������쳣����������ʧ��ʱ����0��
	��Ϊ�½ڵ㽫����һ�����ü���Ϊ1������Ȼ���ڽ�����ӵ�����ʱ���丸�����ڵ������һ�����ã���������Ҫɾ�����������á�
	���ʵ���ǽ������ʹ�������ɾ�����������ܶ��󴴽�������ü����Ƕ��١�
	*/
	CSampleSceneNode* myNode =
		new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);

	/*
	Ϊ���ڽ���һ����������ɵ����ĳ���������������
	�����������ڿ�����ʹ�������е����������ڵ�һ��ʹ�ó����ڵ㣬
	�����򳡾��ڵ������һ����������ʹ�ýڵ���΢��ת��һ�㡣
	irr::scene::ISceneManager::createRotationAnimator()���ܷ���0�����Ӧ���м�顣
	*/
	scene::ISceneNodeAnimator* anim =
		smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

	if (anim)
	{
		myNode->addAnimator(anim);

		/*
		���Ѿ�����˶Զ��������ã��������ڱ�����irr::IReferenceCounted::drop()ɾ��(?)�����ã���Ϊ������createFoo()���������ġ�
		�����Ҳ�Ӧ�����������������ȷ����������Ϊ0����ȷ���޷�����������
		*/
		anim->drop();
		anim = 0;
	}

	/*
	���Ѿ������CSampleSceneNode������˱���ɾ���ҵ����á�
	���ǣ�����Ȼ����ɾ���ö�����Ϊ���Ը����ڳ���ͼ�ϣ�
	�������Է�ֹɾ����ֱ����ͼ��ɾ�����Զ��峡���ڵ㱻ɾ��Ϊֹ��
	*/
	myNode->drop();
	myNode = 0; // As I shouldn't refer to it again, ensure that I can't

	/*
	Now draw everything and finish.
	*/
	u32 frames = 0;
	while (device->run())
	{
		driver->beginScene(true, true, video::SColor(0, 100, 100, 100));

		smgr->drawAll();

		driver->endScene();
		if (++frames == 100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames = 0;
		}
	}

	device->drop();

	return 0;
}

/*
That's it. Compile and play around with the program.
**/
