#include "Level.h"
#include "../Nut.h"
#include "Crystal.h"
#include "Aircurrent.h"
#include "Snail.h"
#include "SlimeHeap.h"
#include "Mantis.h"

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
	Level* l = loadLevel(const_cast<char*>(filename), true);
	return l;
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
	tinyxml2::XMLElement* playerSpawnerElement = doc.NewElement("PlayerSpawner");
	playerSpawnerElement->InsertFirstChild(createPointNode(&doc, mainLayer->getPlayerSpawner()->getSpawnPosition()));
	tinyxml2::XMLElement* nutsElement = doc.NewElement("Nuts");
	tinyxml2::XMLElement* crysElement = doc.NewElement("Crystals");
	tinyxml2::XMLElement* airsElement = doc.NewElement("Airs");
	tinyxml2::XMLElement* snailsElement = doc.NewElement("Snails");
	tinyxml2::XMLElement* slimeElement = doc.NewElement("Slimes");
	tinyxml2::XMLElement* mantisElement = doc.NewElement("Mantis");

	for (Node* node : mainLayer->getChildren())
	{
		switch (node->getTag())
		{
			case TAG_NUT:
				{
					tinyxml2::XMLElement* nut = doc.NewElement("Nut");
					nut->SetAttribute("x", node->getPositionX());
					nut->SetAttribute("y", node->getPositionY());
					nutsElement->InsertEndChild(nut);
				}
				break;
			case TAG_CRYSTAL:
				{
					tinyxml2::XMLElement* crys = doc.NewElement("Crystal");
					crys->SetAttribute("x", node->getPositionX());
					crys->SetAttribute("y", node->getPositionY());
					crysElement->InsertEndChild(crys);
				}
				break;
			case TAG_AIR:
				{
					tinyxml2::XMLElement* air = doc.NewElement("Crystal");
					air->SetAttribute("x", node->getPositionX());
					air->SetAttribute("y", node->getPositionY());
					Aircurrent* cur = dynamic_cast<Aircurrent*>(node);
					air->SetAttribute("dirY", cur->getDirection().y);
					air->SetAttribute("width", cur->getSize().width);
					air->SetAttribute("height", cur->getSize().height);
					airsElement->InsertEndChild(air);
				}
				break;
			case TAG_SNAIL:
				{
					tinyxml2::XMLElement* air = doc.NewElement("Snail");
					Snail* sn = dynamic_cast<Snail*>(node);
					air->SetAttribute("timer", sn->getTimer());
					air->SetAttribute("x", node->getPositionX());
					air->SetAttribute("y", node->getPositionY());
					snailsElement->InsertEndChild(air);
				}
				break;
			case TAG_MANTIS:
				{
					  tinyxml2::XMLElement* air = doc.NewElement("Mantis");
					  air->SetAttribute("x", node->getPositionX());
					  air->SetAttribute("y", node->getPositionY());
					  mantisElement->InsertEndChild(air);
				}
				break;
			case TAG_SLIMEHEAP:
				{
					  tinyxml2::XMLElement* air = doc.NewElement("Slime");
					  SlimeHeap* sn = dynamic_cast<SlimeHeap*>(node);
					  air->SetAttribute("timer", sn->getTimer());
					  air->SetAttribute("x", node->getPositionX());
					  air->SetAttribute("y", node->getPositionY());
					  slimeElement->InsertEndChild(air);
				}
				break;
			default:
				break;
		}
	}
	mainLayerElement->InsertFirstChild(texturesElement);
	mainLayerElement->InsertEndChild(phyObjectsElement);
	mainLayerElement->InsertEndChild(playerSpawnerElement);
	mainLayerElement->InsertEndChild(nutsElement);
	mainLayerElement->InsertEndChild(crysElement);
	mainLayerElement->InsertEndChild(airsElement);
	mainLayerElement->InsertEndChild(snailsElement);
	mainLayerElement->InsertEndChild(mantisElement);
	mainLayerElement->InsertEndChild(slimeElement);
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

Level* Level::loadLevel(char* filename, bool levelEditor)
{
	Level* l = new Level();
	
	MainLayer* mainlayer = MainLayer::create();
	l->setMainLayer(mainlayer);
	tinyxml2::XMLDocument doc;
	log("%i", doc.LoadFile(filename));
	tinyxml2::XMLElement* rootElement = doc.RootElement();
	tinyxml2::XMLElement* mainLayerElement = rootElement->FirstChildElement("MainLayer");
	tinyxml2::XMLElement* texturesElement = mainLayerElement->FirstChildElement("Textures");
	tinyxml2::XMLElement* phyObjectsElement = mainLayerElement->FirstChildElement("PhysicsObjects");
	
	//################################
	//### Textures				   ###
	//################################
	if (texturesElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = texturesElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			char* filename = const_cast<char*>(child->Attribute("filename"));
			Texture* tex = Texture::create(filename);
			tex->retain();
			tinyxml2::XMLElement* pointElement = child->FirstChildElement("Point");
			Point p = Point(pointElement->FloatAttribute("x"), pointElement->FloatAttribute("y"));
			tex->setPosition(p);
			tex->getSprite()->setVisible(child->BoolAttribute("visibility"));
			mainlayer->getTextures()->push_back(tex);
		}
	}

	//################################
	//### Grounds				   ###
	//################################
	if (phyObjectsElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = phyObjectsElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			char* filename = const_cast<char*>(child->Attribute("filename"));
			Ground* ground = Ground::create(mainlayer->physic, filename);
			tinyxml2::XMLElement* pointElement = child->FirstChildElement("Point");
			Point p = Point(pointElement->FloatAttribute("x"), pointElement->FloatAttribute("y"));
			ground->setPosition(p);
			tinyxml2::XMLElement* sizeElement = child->FirstChildElement("ColliderSize");

			ground->setColliderBounds(sizeElement->FloatAttribute("width"), sizeElement->FloatAttribute("height"));
			ground->getTexture()->getSprite()->setVisible(child->BoolAttribute("visibility"));
			ground->retain();
			
			mainlayer->getPhysicsObjects()->push_front(ground);
		}
	}

	//################################
	//### PlayerSpawner			   ###
	//################################
	tinyxml2::XMLElement* playerSpawnerElement = mainLayerElement->FirstChildElement("PlayerSpawner");
	if (playerSpawnerElement != nullptr)
	{
		tinyxml2::XMLElement* playerSpawnerPosElement = playerSpawnerElement->FirstChildElement("Point");
		Point p = Point(playerSpawnerPosElement->FloatAttribute("x"), playerSpawnerPosElement->FloatAttribute("y"));
		PlayerSpawner* ps = new PlayerSpawner(p);
		mainlayer->setPlayerSpawner(ps);
	}

	//################################
	//### Nuts					   ###
	//################################
	tinyxml2::XMLElement* collectibleElement = mainLayerElement->FirstChildElement("Nuts");
	if (collectibleElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = collectibleElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			CollectibleNut* nut = CollectibleNut::create(mainlayer);
			nut->setPosition(pos);
			nut->retain();
			mainlayer->getNuts()->push_front(nut);
		}
	}

	//################################
	//### Crystals				   ###
	//################################
	tinyxml2::XMLElement* crysElement = mainLayerElement->FirstChildElement("Crystals");
	if (crysElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = crysElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			CollectibleCrystal* crys = CollectibleCrystal::create(mainlayer);
			crys->setPosition(pos);
			mainlayer->getCrystals()->push_front(crys);
		}
	}

	if (!levelEditor)
		mainlayer->init();
	else
		l->setName("tmpname.xml");

	
	//################################
	//### Aircurrent			   ###
	//################################
	tinyxml2::XMLElement* airElement = mainLayerElement->FirstChildElement("Airs");
	if (airElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = airElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			Point dir = Point(0.0f, child->FloatAttribute("dirY"));
			Size size = Size(child->FloatAttribute("width"), child->FloatAttribute("height"));
			Aircurrent* air = Aircurrent::create(mainlayer->physic, mainlayer, dir, size);
			air->setPosition(pos);
			mainlayer->addChild(air, 0);
		}
	}
	
	//################################
	//### Snails				   ###
	//################################
	tinyxml2::XMLElement* snailsElement = mainLayerElement->FirstChildElement("Snails");
	if (snailsElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = snailsElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			float timer = child->FloatAttribute("timer");
			Snail* crys = Snail::create(mainlayer->physic, mainlayer);
			crys->setTimer(timer);
			crys->setPosition(pos);
			mainlayer->addChild(crys->getSprite(), 0);
			mainlayer->addChild(crys, 0);
		}
	}
	//################################
	//### Slimes				   ###
	//################################
	tinyxml2::XMLElement* slimeElement = mainLayerElement->FirstChildElement("Slimes");
	if (slimeElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = slimeElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			float timer = child->FloatAttribute("timer");
			SlimeHeap* crys = SlimeHeap::create(mainlayer->physic, mainlayer);
			crys->setTimer(timer);
			crys->setPosition(pos);
			mainlayer->addChild(crys->getSprite(), 0);
			mainlayer->addChild(crys, 0);
		}
	}
	//################################
	//### Mantis				   ###
	//################################
	tinyxml2::XMLElement* mantisElement = mainLayerElement->FirstChildElement("Mantis");
	if (mantisElement != nullptr)
	{
		for (tinyxml2::XMLElement* child = mantisElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			Point pos = Point(child->FloatAttribute("x"), child->FloatAttribute("y"));
			float timer = child->FloatAttribute("timer");
			Mantis* crys = Mantis::create(mainlayer->physic, mainlayer);
			crys->setPosition(pos);
			mainlayer->addChild(crys->getSprite(), 0);
			mainlayer->addChild(crys, 0);
		}
	}
	return l;
}

tinyxml2::XMLElement* Level::createGroundNode(tinyxml2::XMLDocument* doc, Ground* ground)
{
	tinyxml2::XMLElement* element = doc->NewElement("Ground");
	element->SetAttribute("visibility", ground->getSprite()->isVisible());
	element->SetAttribute("filename", ground->getTexture()->getFilename());
	tinyxml2::XMLElement* pointElement = createPointNode(doc, ground->getPosition());
	element->InsertEndChild(pointElement);
	tinyxml2::XMLElement* sizeElement = doc->NewElement("ColliderSize");
	sizeElement->SetAttribute("width", dynamic_cast<AABBCollider*>(ground->getCollider())->getBoundingRect().size.width);
	sizeElement->SetAttribute("height", dynamic_cast<AABBCollider*>(ground->getCollider())->getBoundingRect().size.height);
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