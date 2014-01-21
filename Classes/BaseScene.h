#ifndef __BASESCENE_H__
#define __BASESCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CBaseScene : public Layer {
public:
	virtual bool init();

protected:
	void setShowDebugInfo(bool);
private:
}

#endif