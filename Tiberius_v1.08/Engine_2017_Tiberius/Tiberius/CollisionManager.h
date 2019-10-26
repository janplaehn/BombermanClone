#pragma once

#include <vector>
#include "IEntity.h"

/*The Collision Manager deals with all the collisions that happen within the game.
It checks if certain objects collide, which makes it  easy to manage collision
between objects more efficiently.*/

class ICollider;

class CollisionManager
{
public:
	static bool CheckCollision(IEntity* p_xLeft, IEntity* p_xRight); // Affected by pairs
	/*CheckCollision takes two entities and checks if they are closer than 50px to eah other.
	Furthermore, it checks if both entities are set as a Collision Pair. If both of these statements
	are true, a Collisioncheck is performed using the entities Colliders. If there is a collision,
	the function returns true, ótherwise it returns false.*/

	static bool CheckCollision(ICollider* p_xLeft, ICollider* p_xRight); // Unaffected by pairs
	 /*CheckCollision takes two colliders and checks if they are rectangles. If both of these statements
	 are true, the colliders get casted to rectangles and a Collisioncheck is performed using these 
	 rectangles. If there is a collision, the function returns true, ótherwise it returns false.*/

	static bool CheckCollision(SDL_Rect p_a, SDL_Rect p_b); // Unaffected by pairs'
	/*CheckCollision takes two SDL_Rect's and performs a collisioncheck using a basic
	algorithm for Collisionchecks, that checks if the sides of the rectangles overlap. 
	If there is a collision, the function returns true, ótherwise it returns false.*/

	static void AddCollisionPair(ENTITYTYPE p_eA, ENTITYTYPE p_eB);
	/* AddCollisionPair takes two entities. First, the function goes through every existing Collision Pair
	in the vector m_aeCollisionPairs and checks if the pair was already added. If it wasn't, the function adds
	the pair to the vector.*/

	static void RemoveCollisionPair(ENTITYTYPE p_eA, ENTITYTYPE p_eB);
	/*RemoveCollisionPair goes through m_aeCollisionPairs and checks for the two entities passed into the function.
	If the pair is found, it gets removed from the vector.*/

	~CollisionManager();
private:
	static std::vector<std::pair<ENTITYTYPE, ENTITYTYPE>> m_aeCollisionPairs;
	CollisionManager();
	CollisionManager(const CollisionManager& other) = delete; 
	CollisionManager& operator=(const CollisionManager&) = delete; 
};

