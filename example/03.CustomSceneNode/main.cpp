/** Example 003 Custom SceneNode

本教程比以前的教程更高级。
如果您当前只是在使用Irrlicht引擎，则可能需要先看看其他示例。
本教程介绍了如何创建自定义场景节点以及如何在引擎中使用它。 
如果要实现Irrlicht Engine当前不支持的渲染技术，则需要一个自定义场景节点。 
例如，您可以使用它编写基于室内门户的渲染器或高级地形场景节点。 
通过创建自定义场景节点，您可以轻松扩展Irrlicht引擎并使之适应您自己的需求。

我将使本教程保持简单：将所有内容都保持简短，
将所有内容保存在一个.cpp文件中，并且在此使用该引擎，就像在其他所有教程中一样。

首先，我包括头文件，使用irr命名空间，并告诉链接器与.lib文件链接。
*/
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

/*
这是本教程更复杂的部分：我们自己的自定义场景节点的类。 
为简单起见，我们的场景节点既不是室内门户渲染器，也不是terrain场景节点，而是一个简单的四面体，这是一个由4个相连的顶点组成的3d对象，该对象只会自己绘制，仅做其他事情。
请注意，此方案在Irrlicht中不需要自定义场景节点。
取而代之的是从几何图形创建一个网格并将其传递给irr::scene::IMeshSceneNode。
该示例仅说明了在非常简单的设置中创建自定义场景节点的过程。

为了使我们的场景节点能够插入到Irrlicht Engine场景中，我们创建的类需要从irr::scene::ISceneNode类派生，并且必须重写一些方法。
*/

class CSampleSceneNode : public scene::ISceneNode
{

	/*
	首先，我们声明一些成员变量：边界框Box，4个顶点Vertices和四面体的材质Meterial。
	*/
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;

	/*
	构造函数的参数 指定 场景节点的父类parent，指向场景管理器的指针mgr以及场景节点的ID。
    在构造函数中，我们调用父类的构造函数，设置材质的某些属性，并创建稍后将要绘制的四面体的4个顶点。
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
		Irrlicht引擎需要知道场景节点的边界框。它将用于自动剔除和其他操作。 
		因此，我们需要从使用的4个顶点创建一个边界框。
		如果您不希望引擎使用该框进行自动剔除和/或不想创建该框，
		则也可以用irr::scene::EAC_OFF调用irr::scene::ISceneNode::setAutomaticCulling()
		*/
		Box.reset(Vertices[0].Pos);
		for (s32 i = 1; i < 4; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	/*
	在绘制之前，场景管理器将调用场景中每个场景节点的irr::scene::ISceneNode::OnRegisterSceneNode()方法。
	如果场景节点希望自己绘制，则可以将其注册到要绘制的场景管理器中。
	告诉场景管理器何时应调用irr::scene::ISceneNode::render()很有必要。
	例如，普通场景节点一个接一个地渲染其内容，而模板缓冲区阴影希望在所有其他场景节点之后绘制。
	并且需要在所有其他场景节点（如果有）之前渲染摄影机或灯光场景节点。
	因此，在这里，我们只需注册场景节点即可正常渲染。
	如果我们想让它像照相机或灯光一样渲染，我们必须调用SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
	此后，我们调用基类的实际irr::scene::ISceneNode::OnRegisterSceneNode()方法，该方法也仅允许该节点的所有子场景节点自行注册。
	*/
	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}

	/*
	在render()方法中，发生了大多数有趣的事情：Scene节点进行自身渲染。
	我们重写此方法并绘制四面体。
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
	最后，我们创建了三个小的附加方法:
	irr::scene::ISceneNode::getBoundingBox()返回此场景节点的边界框;
	irr::scene::ISceneNode::getMaterialCount()返回此场景节点中的材质数量（我们的四面体只有一种材质）;
	irr::scene::ISceneNode::getMaterial()返回索引处的材质。
	因为这里只有一种材料，所以假设没有人调用索引大于0的getMaterial()，那么我们就只能返回一种材料。
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
场景节点完成。
现在，我们只需要启动引擎，创建场景节点和摄影机，然后查看结果即可。
*/
int main()
{
	// 向用户询问设备
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// 创建设备

	IrrlichtDevice* device = createDevice(driverType,
		core::dimension2d<u32>(640, 480), 16, false);

	if (device == 0)
		return 1; // could not create selected driver.

	// 创建引擎和相机

	device->setWindowCaption(L"Custom Scene Node - Irrlicht Engine Demo");

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	smgr->addCameraSceneNode(0, core::vector3df(0, -40, 0), core::vector3df(0, 0, 0));

	/*
	创建我们的场景节点。
	我不检查调用new的结果，因为它应该引发异常，而不是在失败时返回0。
	因为新节点将创建一个引用计数为1的自身，然后在将其添加到场景时由其父场景节点添加另一个引用，所以我需要删除对它的引用。
	最佳实践是仅在完成使用它后才删除它，而不管对象创建后的引用计数是多少。
	*/
	CSampleSceneNode* myNode =
		new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);

	/*
	为了在仅由一个四面体组成的无聊场景中制作动画，
	并表明您现在可以像使用引擎中的其他场景节点一样使用场景节点，
	我们向场景节点添加了一个动画器，使该节点稍微旋转了一点。
	irr::scene::ISceneManager::createRotationAnimator()可能返回0，因此应进行检查。
	*/
	scene::ISceneNodeAnimator* anim =
		smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

	if (anim)
	{
		myNode->addAnimator(anim);

		/*
		我已经完成了对动画的引用，所以现在必须用irr::IReferenceCounted::drop()删掉(?)此引用，因为它是由createFoo()函数产生的。
		由于我不应该再引用它，因此请确保将其设置为0，以确保无法再引用它。
		*/
		anim->drop();
		anim = 0;
	}

	/*
	我已经完成了CSampleSceneNode对象，因此必须删除我的引用。
	但是，这仍然不会删除该对象，因为它仍附加在场景图上，
	这样可以防止删除，直到该图被删除或自定义场景节点被删除为止。
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
