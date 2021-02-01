#include "StateGameObject.h"
#include "../Engine/StateTransition.h"
#include "../Engine/StateMachine.h"
#include "../Engine/State.h"

using namespace NCL;
using namespace CSC8508;

StateGameObject::StateGameObject() {
	counter = 0.0f;
	stateMachine = new StateMachine();

	State* stateA = new State([&](float dt)-> void
		{
			this->MoveLeft(dt);
		});

	State* stateB = new State([&](float dt)-> void
		{
			this->MoveRight(dt);
		});

	stateMachine->AddState(stateA);
	stateMachine->AddState(stateB);

	stateMachine->AddTransition(new StateTransition(stateA, stateB, [&]()->bool
		{
			return this->counter > 3.0f;
		}));

	stateMachine->AddTransition(new StateTransition(stateB, stateA, [&]()->bool
		{
			return this->counter < 0.0f;
		}));

}

StateGameObject::~StateGameObject() {
	delete stateMachine;
}

void StateGameObject::Update(float dt) {
	stateMachine->Update(dt);
}

void StateGameObject::MoveLeft(float dt) {
	GetPhysicsObject()->AddForce({ -10,0,0 });
	counter += dt;
}

void StateGameObject::MoveRight(float dt) {
	GetPhysicsObject()->AddForce({ 10,0,0 });
	counter -= dt;
}