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

/*The state manager can be used to setup different states of objects, for example for the states the game can be
in or different states of the game. For any object various states can be created and you can switch between states
by using the according functions. Each state contains different behaviour the specific object can have.
The State Manager can be used to create and destroy states as well as change between states. It also helps to make
sure, states are eventualy deleted and RAII is applied.*/

#pragma once

#include <map>
#include <string>



class IState;

class StateManager
{
public:
	StateManager();
	~StateManager();
	void AddState(std::string p_sIdentifier, IState* p_xState);
	/*AddState takes a string that identifies the state and a pointer to a state and adds them as to
	m_axStates as a pair*/

	void RemoveState(std::string p_sIdentifier);
	/*AddState takes a string that identifies the state and looks for the state in m_axStates using
	that identifier. If the pair gets found, it gets deleted.*/

	void SetState(std::string p_sIdentifier);
	/* SetState takes the identifier of a state and checks if it is in m_axStates and if it is not a nullptr.
	If both of these are true, m_xCurrentState gets set to the state passed into this function.*/

	bool Update(float p_fDelta); 
	
private:
	void ChangeState();
	/* ChangeState changes to the nextState pointer of the currentState, making that the new currentState.
	It also calls the exit function of the old currentState and the Enter function of the new currentState.*/

	IState* m_xCurrentState = nullptr;
	std::map<std::string, IState*> m_axStates;
};

