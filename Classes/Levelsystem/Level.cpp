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

Level* Level::createNew(char* levelname)
{
	Level* l = new Level();
	l->setName(levelname);
	return l;
}

Level::Level() {}
Level::~Level() {}

void Level::SaveLevel()
{
	MainLayer* mainLayer = getMainLayer();
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* baseElement = doc.NewElement("Level");
	baseElement->SetAttribute("name", "level1");
	tinyxml2::XMLElement* mainLayerElement = doc.NewElement("MainLayer");
	mainLayerElement->SetAttribute("name", mainLayer->getName());
	tinyxml2::XMLElement* texturesElement = doc.NewElement("Textures");
	for (Texture* tex : *mainLayer->getTextures())
	{
		texturesElement->InsertEndChild(createTextureNode(&doc, tex));
	}
	tinyxml2::XMLElement* phyObjectsElement = doc.NewElement("PhysicsObjects");

	for (Ground* ground : *mainLayer->getPhysicsObjects())
	{
		phyObjectsElement->InsertEndChild(createGroundNode(&doc, ground));
	}
	mainLayerElement->InsertFirstChild(texturesElement);
	mainLayerElement->InsertEndChild(phyObjectsElement);
	baseElement->InsertEndChild(mainLayerElement);
	doc.InsertFirstChild(baseElement);
	doc.SaveFile(getName());
}

void Level::setName(char* name)
{
	m_name = name;
}

char* Level::getName()
{
	return m_name;
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
	if (texturesElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = texturesElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			char* filename = const_cast<char*>(child->Attribute("filename"));
			Texture* tex = Texture::create(filename);
			tinyxml2::XMLElement* pointElement = child->FirstChildElement("Point");
			Point p = Point(pointElement->FloatAttribute("x"), pointElement->FloatAttribute("y"));
			tex->setPosition(p);
			tex->getSprite()->setVisible(child->BoolAttribute("visibility"));
			mainlayer->getTextures()->push_back(tex);
		}
	}
	if (phyObjectsElement != nullptr)
	{
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
	}
	mainlayer->init();
	return l;
}

tinyxml2::XMLElement* Level::createGroundNode(tinyxml2::XMLDocument* doc, Ground* ground)
{
	tinyxml2::XMLElement* element = doc->NewElement("Ground");
	element->SetAttribute("visibility", ground->getSprite()->isVisible());
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
	element->SetAttribute("visibility", texture->getSprite()->isVisible());
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