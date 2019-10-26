#include "stdafx.h"
#include "CollisionManager.h"
#include "ICollider.h"
#include "RectangleCollider.h"

std::vector<std::pair<ENTITYTYPE, ENTITYTYPE>> CollisionManager::m_aeCollisionPairs;

bool CollisionManager::CheckCollision(IEntity * p_xLeft, IEntity * p_xRight)
{
	if (p_xLeft->GetCollider() == nullptr || p_xRight->GetCollider() == nullptr)
		return false;
	
	for (unsigned int i = 0; i < m_aeCollisionPairs.size(); i++)
	{
		if (((p_xLeft->getPosition().x - p_xRight->getPosition().x) > 50) || ((p_xLeft->getPosition().x - p_xRight->getPosition().x) < -50)) {
			if (((p_xLeft->getPosition().y - p_xRight->getPosition().y) > 50) || ((p_xLeft->getPosition().y - p_xRight->getPosition().y) < -50)) {
				return false;
			}
		}
		if ((m_aeCollisionPairs[i].first == p_xLeft->GetType() && m_aeCollisionPairs[i].second == p_xRight->GetType()) ||
			(m_aeCollisionPairs[i].first == p_xRight->GetType() && m_aeCollisionPairs[i].second == p_xLeft->GetType()))
		{
			return CheckCollision(p_xLeft->GetCollider(), p_xRight->GetCollider());
		}
	}
	return false;
}

bool CollisionManager::CheckCollision(ICollider * p_xLeft, ICollider * p_xRight)
{
	if (p_xLeft->GetType() == COLLIDERTYPE::RECTANGLE && p_xRight->GetType() == COLLIDERTYPE::RECTANGLE)
	{
		RectangleCollider* xLeftRect = dynamic_cast<RectangleCollider*>(p_xLeft);
		RectangleCollider* xRightRect = dynamic_cast<RectangleCollider*>(p_xRight);
		return CheckCollision(xLeftRect->GetRectangle(), xRightRect->GetRectangle());
	}
	return false;
}

bool CollisionManager::CheckCollision(SDL_Rect p_a, SDL_Rect p_b)
{
	int aLeft, aRight, aTop, aBottom;
	int bLeft, bRight, bTop, bBottom;

	aLeft = p_a.x;
	aRight = p_a.x + p_a.w;
	aTop = p_a.y;
	aBottom = p_a.y + p_a.h;

	bLeft = p_b.x;
	bRight = p_b.x + p_b.w;
	bTop = p_b.y;
	bBottom = p_b.y + p_b.h;

	if (aLeft > bRight || aRight < bLeft || aTop > bBottom || aBottom < bTop)
	{
		return false;
	}
	return true;
}

void CollisionManager::AddCollisionPair(ENTITYTYPE p_eA, ENTITYTYPE p_eB)
{
	for (unsigned int i = 0; i < m_aeCollisionPairs.size(); i++)
	{
		if ((m_aeCollisionPairs[i].first == p_eA && m_aeCollisionPairs[i].second == p_eB) ||
			(m_aeCollisionPairs[i].first == p_eB && m_aeCollisionPairs[i].second == p_eA))
		{
			return;
		}
	}
	m_aeCollisionPairs.push_back(std::make_pair(p_eA, p_eB));
}

void CollisionManager::RemoveCollisionPair(ENTITYTYPE p_eA, ENTITYTYPE p_eB)
{
	for (unsigned int i = 0; i < m_aeCollisionPairs.size(); i++)
	{
		if ((m_aeCollisionPairs[i].first == p_eA && m_aeCollisionPairs[i].second == p_eB) ||
			(m_aeCollisionPairs[i].first == p_eB && m_aeCollisionPairs[i].second == p_eA))
		{
			m_aeCollisionPairs.erase(m_aeCollisionPairs.begin() + i);
			return;
		}
	}
}

CollisionManager::CollisionManager() {
}


CollisionManager::~CollisionManager() {
}
