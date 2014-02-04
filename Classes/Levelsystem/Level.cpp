#include "Level.h"
#include "tinyxml2\tinyxml2.h"
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
	
	return nullptr;
}

Level::Level() {}
Level::~Level() {}

//void Level::setFirstVegetationLayer(FirstVegetationLayer* fVL)
//{
//	m_fVLayer = fVL;
//}
//void Level::setMainLayer(MainLayer* mL)
//{
//	m_mainLayer = mL;
//}
//void Level::setSecondVegetationLayer(SecondVegetationLayer* svL)
//{
//	m_sVLayer = svL;
//}
//void Level::setGroundLayer(GroundLayer* gL)
//{
//	m_gLayer = gL;
//}
//void Level::setFirstParallaxLayer(FirstParallaxLayer* fPL)
//{
//	m_fPLayer = fPL;
//}
//void Level::setSecondParallaxLayer(SecondParallaxLayer* sPL)
//{
//	m_sPLayer = sPL;
//}
//void Level::setThirdParallaxLayer(ThirdParallaxLayer* tPL)
//{
//	m_tPLayer = tPL;
//}
//void Level::setHorizontParallaxLayer(HorizontParallaxLayer* hPL)
//{
//	m_hPLayer = hPL;
//}
//void Level::setSkyLayer(SkyLayer* skyLayer)
//{
//	m_skyLayer = skyLayer;
//}
//
//FirstVegetationLayer* Level::getFirstVegetationLayer()
//{
//	return m_fVLayer;
//}
//MainLayer* Level::getMainLayer()
//{
//	return m_mainLayer;
//}
//SecondVegetationLayer* Level::getSecondVegetationLayer()
//{
//	return m_sVLayer;
//}
//GroundLayer* Level::getGroundLayer()
//{
//	return m_gLayer;
//}
//FirstParallaxLayer* Level::getFirstParallaxLayer()
//{
//	return m_fPLayer;
//}
//SecondParallaxLayer* Level::getSecondParallaxLayer()
//{
//	return m_sPLayer;
//}
//ThirdParallaxLayer* Level::getThirdParallaxLayer()
//{
//	return m_tPLayer;
//}
//HorizontParallaxLayer* Level::getHorizontParallaxLayer()
//{
//	return m_hPLayer;
//}
//SkyLayer* Level::getSkyLayer()
//{
//	return m_skyLayer;
//}