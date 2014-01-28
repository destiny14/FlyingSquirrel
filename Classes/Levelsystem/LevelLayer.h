#ifndef __LEVELLAYER_H__
#define __LEVELLAYER_H__

#include "cocos2d.h"

class LevelLayer : public cocos2d::Layer
{
public:
	virtual void SetName(char* name)
	{
		m_name = name;
	}
	virtual char* GetName()
	{
		return m_name;
	}
private:
	char* m_name;
};

#endif // !__LEVELLAYER_H__
