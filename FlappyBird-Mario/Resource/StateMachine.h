#pragma once
#include <memory>
#include <stack>
#include "State.h"
typedef std::unique_ptr<State> StateRef;
class StateMachine
{
private:
	std::stack<StateRef> m_States;
	StateRef m_NewState;

	bool m_bIsRemoving;
	bool m_bIsAdding;
	bool m_bIsReplacing;
public:
	StateMachine();
	~StateMachine();
public:
	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();

	StateRef &GetActiveState();

};

