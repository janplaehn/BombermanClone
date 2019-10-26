/*
Copyright 2016 Jerry Jonsson

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "stdafx.h"
#include "StateManager.h"
#include "IState.h"


StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}

void StateManager::AddState(std::string p_sIdentifier, IState* p_xState)
{
	if (p_xState == nullptr)
		return;

	auto it = m_axStates.find(p_sIdentifier);
	if (it == m_axStates.end())
	{
		m_axStates.insert(std::pair<std::string, IState*>(p_sIdentifier, p_xState));
	}
}

void StateManager::RemoveState(std::string p_sIdentifier)
{
	m_axStates.erase(p_sIdentifier);
}

void StateManager::SetState(std::string p_sIdentifier)
{
	auto it = m_axStates.find(p_sIdentifier);
	if (it == m_axStates.end())
	{
		return;
	}
	if (m_xCurrentState != nullptr)
	{
		m_xCurrentState->Exit();
	}
	m_xCurrentState = it->second;
	m_xCurrentState->Enter();
}

bool StateManager::Update(float p_fDelta)
{
	if (m_xCurrentState == nullptr)
		return false;

	if (m_xCurrentState->Update(p_fDelta) == false)
	{
		ChangeState();
	}
	return true;
}

void StateManager::ChangeState()
{
	std::string sNextState = m_xCurrentState->NextState();
	auto it = m_axStates.find(sNextState);
	if (it == m_axStates.end())
	{
		return;
	}
	m_xCurrentState->Exit();
	m_xCurrentState = it->second;
	m_xCurrentState->Enter();
}
