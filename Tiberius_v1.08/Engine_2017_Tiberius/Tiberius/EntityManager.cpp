#include "stdafx.h"
#include "EntityManager.h"
#include "IEntity.h"

void EntityManager::AddEntity(IEntity * p_xEntity)
{
	if (p_xEntity == nullptr)
		return;

	m_axEntities.push_back(p_xEntity);
}

void EntityManager::RemoveEntity(IEntity * p_xEntity)
{
	if (p_xEntity == nullptr)
		return;

	for (unsigned int i = 0; i < m_axEntities.size(); i++)
	{
		if (m_axEntities[i] == p_xEntity)
		{
			m_axEntities.erase(m_axEntities.begin() + i);
			return;
		}
	}	
}

void EntityManager::removeAllEntities() {
	/*for (IEntity* entity : m_axEntities) {
		RemoveEntity(entity);
	}*/
}

void EntityManager::Update(float p_fDeltaTime)
{
	for (IEntity* entity : m_axEntities){
		if (entity) {
			entity->Update(p_fDeltaTime);
		}
	}
}

void EntityManager::Render()
{
	for (IEntity* entity : m_axEntities)
	{
		entity->Render();
	}
}

std::vector<IEntity*> EntityManager::GetAllEntities()
{
	return m_axEntities;
}
