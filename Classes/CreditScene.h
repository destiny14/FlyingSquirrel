#ifndef __CREDITSCENE_H__
#define __CREDITSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class InputManager;
class InputAction;

class CreditScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(CreditScene);

	virtual bool init() override;
	virtual void update(float _dt) override;
private:

	InputManager* input;
	InputAction* speed;
	Node* contentNode;
	Node* enemies;
	float textSpeed;
	float size;
};

#endif