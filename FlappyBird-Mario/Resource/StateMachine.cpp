#include "StateMachine.h"
StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	m_bIsAdding = true;
	m_bIsReplacing = isReplacing;
	m_NewState = std::move(newState);

}

void StateMachine::RemoveState()
{
	m_bIsRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (m_bIsRemoving && !m_States.empty())
	{
		m_States.pop();

		if (!m_States.empty())
			m_States.top()->Resume();
		m_bIsRemoving = false;
	}
	if (m_bIsAdding)
	{
		if (!m_States.empty())
		{
			if (m_bIsReplacing)
				m_States.pop();
			else
				m_States.top()->Pause();
		}

		m_States.push(std::move(m_NewState));
		m_States.top()->Init();
		m_bIsAdding = false;
	}
}

StateRef &StateMachine::GetActiveState()
{
	return m_States.top();
}

