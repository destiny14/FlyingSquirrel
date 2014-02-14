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
	loadLevel("testlevel.xml");
	//l->SaveLevel();
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
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* baseElement = doc.NewElement("level");
	baseElement->SetAttribute("name", "level1");
	tinyxml2::XMLElement* mainLayerElement = doc.NewElement("mainLayer");
	mainLayerElement->SetAttribute("name", mainLayer->getName());
	mainLayerElement->SetAttribute("texcount", static_cast<int>(texList->size()));
	for (Texture* tex : *texList)
	{
		mainLayerElement->InsertEndChild(createTextureNode(&doc, tex));
	}
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
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	tinyxml2::XMLElement* rootElement = doc.RootElement();
	tinyxml2::XMLElement* mainLayerElement = rootElement->FirstChildElement("mainLayer");
	int texCount = mainLayerElement->IntAttribute("texcount");

	log(mainLayerElement->Attribute("name"));
	log("%i", texCount);
	return nullptr;
}

tinyxml2::XMLElement* Level::createTextureNode(tinyxml2::XMLDocument* doc, Texture* texture)
{
	tinyxml2::XMLElement* element = doc->NewElement("texture");
	element->SetAttribute("filename", texture->getFilename());
	tinyxml2::XMLElement* pointElement = createPointNode(doc, texture->getPosition());
	element->InsertEndChild(pointElement);
	return element;
}

tinyxml2::XMLElement* Level::createPointNode(tinyxml2::XMLDocument* doc, Point p)
{
	tinyxml2::XMLElement* element = doc->NewElement("point");
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