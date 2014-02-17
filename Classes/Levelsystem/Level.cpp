#include "Level.h"
Level* Level::createFromFile(const char* filename)
{
	tinyxml2::XMLDocument doc;
	int e = doc.LoadFile(filename);
	if (e != 0)
	{
		log("XML File Error: %i", e);
		return nullptr;
	}
	
	tinyxml2::XMLElement* levelElement = doc.FirstChildElement("level");
	Level* l = new Level();
	//loadLevel("testlevel.xml");
	l->SaveLevel();
	delete l;
	return nullptr;
}

Level::Level() {}
Level::~Level() {}

void Level::SaveLevel()
{
	MainLayer* mainLayer = new MainLayer();
	mainLayer->setName("mainlayer");
	Texture* tex = Texture::create("ground.png");
	Texture* tex2 = Texture::create("CloseNormal.png");
	list<Texture*>* texList = mainLayer->getTextures();
	texList->push_back(tex);
	texList->push_front(tex2);
	mainLayer->setTextures(texList);
	Ground* g1 = Ground::create("HelloWorld.png");
	g1->setPosition(50, 50);
	list<Ground*>* groundList = mainLayer->getPhysicsObjects();
	groundList->push_back(g1);
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* baseElement = doc.NewElement("Level");
	baseElement->SetAttribute("name", "level1");
	tinyxml2::XMLElement* mainLayerElement = doc.NewElement("MainLayer");
	mainLayerElement->SetAttribute("name", mainLayer->getName());
	tinyxml2::XMLElement* texturesElement = doc.NewElement("Textures");
	for (Texture* tex : *texList)
	{
		texturesElement->InsertEndChild(createTextureNode(&doc, tex));
	}
	tinyxml2::XMLElement* phyObjectsElement = doc.NewElement("PhysicsObjects");

	for (Ground* ground : *groundList)
	{
		phyObjectsElement->InsertEndChild(createGroundNode(&doc, ground));
	}
	mainLayerElement->InsertFirstChild(texturesElement);
	mainLayerElement->InsertEndChild(phyObjectsElement);
	baseElement->InsertEndChild(mainLayerElement);
	doc.InsertFirstChild(baseElement);

	//tinyxml2::XMLText* t = doc.NewText("LEVEL1");
	//t->SetValue("Miep?");
	//baseElement->InsertEndChild(t);
	//doc.InsertFirstChild(e);
	doc.SaveFile("testlevel.xml");
}

Level* Level::loadLevel(char* filename)
{
	Level* l = new Level();
	
	MainLayer* mainlayer = MainLayer::create();
	l->setMainLayer(mainlayer);
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	tinyxml2::XMLElement* rootElement = doc.RootElement();
	tinyxml2::XMLElement* mainLayerElement = rootElement->FirstChildElement("MainLayer");
	tinyxml2::XMLElement* texturesElement = mainLayerElement->FirstChildElement("Textures");
	tinyxml2::XMLElement* phyObjectsElement = mainLayerElement->FirstChildElement("PhysicsObjects");
	for (tinyxml2::XMLElement* child = texturesElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
	{
		char* filename = const_cast<char*>(child->Attribute("filename"));
		Texture* tex = Texture::create(filename);
		tinyxml2::XMLElement* pointElement = child->FirstChildElement("Point");
		Point p = Point(pointElement->FloatAttribute("x"), pointElement->FloatAttribute("y"));
		tex->setPosition(p);
		mainlayer->getTextures()->push_back(tex);
	}
	for (tinyxml2::XMLElement* child = phyObjectsElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
	{
		char* filename = const_cast<char*>(child->Attribute("filename"));
		Ground* ground = Ground::create(filename);
		tinyxml2::XMLElement* pointElement = child->FirstChildElement("Point");
		Point p = Point(pointElement->FloatAttribute("x"), pointElement->FloatAttribute("y"));
		ground->setPosition(p);
		tinyxml2::XMLElement* sizeElement = child->FirstChildElement("ColliderSize");
		Rect colRect = Rect(0, 0, sizeElement->FloatAttribute("width"), sizeElement->FloatAttribute("height"));
		ground->getColliderComponent()->setCollisionRectangle(colRect);
		ground->setGround(child->BoolAttribute("isGround"));
		mainlayer->getPhysicsObjects()->push_front(ground);
	}
	mainlayer->init();
	return l;
}

tinyxml2::XMLElement* Level::createGroundNode(tinyxml2::XMLDocument* doc, Ground* ground)
{
	tinyxml2::XMLElement* element = doc->NewElement("Ground");
	element->SetAttribute("filename", ground->getTexture()->getFilename());
	element->SetAttribute("isGround", ground->getGround());
	tinyxml2::XMLElement* pointElement = createPointNode(doc, ground->getPosition());
	element->InsertEndChild(pointElement);
	tinyxml2::XMLElement* sizeElement = doc->NewElement("ColliderSize");
	sizeElement->SetAttribute("width", ground->getColliderComponent()->getCollisionRectangle().size.width);
	sizeElement->SetAttribute("height", ground->getColliderComponent()->getCollisionRectangle().size.height);
	element->InsertEndChild(sizeElement);
	return element;
}

tinyxml2::XMLElement* Level::createTextureNode(tinyxml2::XMLDocument* doc, Texture* texture)
{
	tinyxml2::XMLElement* element = doc->NewElement("Texture");
	element->SetAttribute("filename", texture->getFilename());
	tinyxml2::XMLElement* pointElement = createPointNode(doc, texture->getPosition());
	element->InsertEndChild(pointElement);
	return element;
}

tinyxml2::XMLElement* Level::createPointNode(tinyxml2::XMLDocument* doc, Point p)
{
	tinyxml2::XMLElement* element = doc->NewElement("Point");
	element->SetAttribute("x", p.x);
	element->SetAttribute("y", p.y);
	return element;
}

const char* Level::ftocc(float f)
{
	char array[64];
	sprintf(array, "%f", f);
	return array;
}

void Level::setFirstVegetationLayer(FirstVegetationLayer* fVL)
{
	m_fVLayer = fVL;
}
void Level::setMainLayer(MainLayer* mL)
{
	m_mainLayer = mL;
}
void Level::setSecondVegetationLayer(SecondVegetationLayer* svL)
{
	m_sVLayer = svL;
}
void Level::setGroundLayer(GroundLayer* gL)
{
	m_gLayer = gL;
}
void Level::setFirstParallaxLayer(FirstParallaxLayer* fPL)
{
	m_fPLayer = fPL;
}
void Level::setSecondParallaxLayer(SecondParallaxLayer* sPL)
{
	m_sPLayer = sPL;
}
void Level::setThirdParallaxLayer(ThirdParallaxLayer* tPL)
{
	m_tPLayer = tPL;
}
void Level::setHorizontParallaxLayer(HorizontParallaxLayer* hPL)
{
	m_hPLayer = hPL;
}
void Level::setSkyLayer(SkyLayer* skyLayer)
{
	m_skyLayer = skyLayer;
}

FirstVegetationLayer* Level::getFirstVegetationLayer()
{
	return m_fVLayer;
}
MainLayer* Level::getMainLayer()
{
	return m_mainLayer;
}
SecondVegetationLayer* Level::getSecondVegetationLayer()
{
	return m_sVLayer;
}
GroundLayer* Level::getGroundLayer()
{
	return m_gLayer;
}
FirstParallaxLayer* Level::getFirstParallaxLayer()
{
	return m_fPLayer;
}
SecondParallaxLayer* Level::getSecondParallaxLayer()
{
	return m_sPLayer;
}
ThirdParallaxLayer* Level::getThirdParallaxLayer()
{
	return m_tPLayer;
}
HorizontParallaxLayer* Level::getHorizontParallaxLayer()
{
	return m_hPLayer;
}
SkyLayer* Level::getSkyLayer()
{
	return m_skyLayer;
}