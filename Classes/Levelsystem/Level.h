#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include "Layers\Layers.h"

using namespace std;
USING_NS_CC;

class Level
{
public:
	static Level* createFromFile(const char* filename);

	Level();
	~Level();

	void setName(char* name);
	char* getName();

	void setFirstVegetationLayer(FirstVegetationLayer* fVL);
	void setMainLayer(MainLayer* mL);
	void setSecondVegetationLayer(SecondVegetationLayer* svL);
	void setGroundLayer(GroundLayer* gL);
	void setFirstParallaxLayer(FirstParallaxLayer* fPL);
	void setSecondParallaxLayer(SecondParallaxLayer* sPL);
	void setThirdParallaxLayer(ThirdParallaxLayer* tPL);
	void setHorizontParallaxLayer(HorizontParallaxLayer* hPL);
	void setSkyLayer(SkyLayer* skyLayer);

	FirstVegetationLayer* getFirstVegetationLayer();
	MainLayer* getMainLayer();
	SecondVegetationLayer* getSecondVegetationLayer();
	GroundLayer* getGroundLayer();
	FirstParallaxLayer* getFirstParallaxLayer();
	SecondParallaxLayer* getSecondParallaxLayer();
	ThirdParallaxLayer* getThirdParallaxLayer();
	HorizontParallaxLayer* getHorizontParallaxLayer();
	SkyLayer* getSkyLayer();

private:
	string name;
	FirstVegetationLayer* m_fVLayer;
	MainLayer* m_mainLayer;
	SecondVegetationLayer* m_sVLayer;
	GroundLayer* m_gLayer;
	FirstParallaxLayer* m_fPLayer;
	SecondParallaxLayer* m_sPLayer;
	ThirdParallaxLayer* m_tPLayer;
	HorizontParallaxLayer* m_hPLayer;
	SkyLayer* m_skyLayer;
};

#endif