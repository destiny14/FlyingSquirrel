#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include "Objects\Texture.h"
#include "Layers\Layers.h"
#include "tinyxml2\tinyxml2.h"

using namespace std;
USING_NS_CC;

class Level
{
public:
	static Level* createFromFile(const char* filename);

	static Level* createNew(char* levelname);

	Level();
	~Level();

	void setName(char* name);
	char* getName();

	void SaveLevel();

	void setFirstVegetationLayer(FirstVegetationLayer* fVL);
	void setMainLayer(MainLayer* mL);
	void setSecondVegetationLayer(SecondVegetationLayer* svL);
	void setGroundLayer(GroundLayer* gL);

	FirstVegetationLayer* getFirstVegetationLayer();
	MainLayer* getMainLayer();
	SecondVegetationLayer* getSecondVegetationLayer();
	GroundLayer* getGroundLayer();
	static Level* loadLevel(char* filename);
private:
	char* m_name;
	FirstVegetationLayer* m_fVLayer;
	MainLayer* m_mainLayer;
	SecondVegetationLayer* m_sVLayer;
	GroundLayer* m_gLayer;

	// createGroundNode (XMLDocument*, Ground*)
	//
	// erstellt ein neues XMLElement mit dem Namen "Ground" aus einem Objetkt vom Typ "Ground"
	tinyxml2::XMLElement* createGroundNode(tinyxml2::XMLDocument* doc, Ground* ground);
	// createTextureNode (XMLDocument*, Texture*)
	//
	// erstellt ein neues XMLElement mit dem Namen "Texture" aus einem Objekt vom Typ "Texture"
	tinyxml2::XMLElement* createTextureNode(tinyxml2::XMLDocument* doc, Texture* texture);
	// createPointNode (XMLDocument*, Point)
	//
	// erstellt ein neues XMLElement mit dem Namen "Point" aus einem Objetkt vom Typ "Point"
	tinyxml2::XMLElement* createPointNode(tinyxml2::XMLDocument* doc, Point p);
	
	Texture* loadTextureNode(tinyxml2::XMLElement* parentElement, int count);

	const char* ftocc(float f);
	
};

#endif