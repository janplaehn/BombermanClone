#pragma once

#include <vector>
class IEntity;
enum ENTITYTYPE;

/* The EntityManager class is a class that stores pointers to all entities
and manages adding/removing new entities as well as calling their update
and render functions. The Entitymanager makes working with entities easier as
you don't have to call each single update or render function and it makes organising entities
simpler as well.*/

class EntityManager
{
public:
	void AddEntity(IEntity* p_xEntity);
	/* AddEntity checks if the Entity passed in is a nullptr. If it isn't, it adds
	the entity to the vector m_axEntities.*/

	void RemoveEntity(IEntity* p_xEntity);
	/* RemoveEntity checks if the Entity passed in is a nullptr. If it isn't, it goes through
	the vector m_axEntities looking for the Entity that was passed in. If it gets found, it 
	gets deleted.*/

	void removeAllEntities();
	/* removeAllEntities goes through the vector m_axEntities deleting every entity in the vector.*/

	void Update(float p_fDeltaTime);
	/*Update goes through all the entities in m_axEntities calling the update function of each of them.*/

	void Render();
	/*Render goes through all the entities in m_axEntities calling the render function of each of them.*/

	std::vector<IEntity*> GetAllEntities();
	/*GetAllEntities returns a vector with all the entities in m_axEntities.*/

	template <typename T>
	std::vector<T*> GetEntities();
	std::vector<IEntity*> m_axEntities;

private:
	

};

template<typename T>
inline std::vector<T*> EntityManager::GetEntities()
{
	std::vector<T*> result;
	for (IEntity* entity : m_axEntities)
	{
		T* t = dynamic_cast<T*>(entity);
		if (t != nullptr)
		{
			result.push_back(t);
		}
	}
	return result;
}
