#pragma once
#include "Classes/Components/PlayerCollider.h"
#include "Input.h"


class CPlayer : public PlayerCollider
{
public:

	CPlayer();
	~CPlayer();

	static CPlayer* create(InputManager* pManager);
	virtual bool init();

	virtual void update(float dt);

private:
	bool m_isGrounded;

	Point m_direction;
	float m_speed;

	InputAction* m_pForward;
	InputAction* m_pBackward;
	InputAction* m_pJump;
};

