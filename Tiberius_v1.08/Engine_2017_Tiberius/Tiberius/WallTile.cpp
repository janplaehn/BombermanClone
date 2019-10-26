#include "stdafx.h"
#include "WallTile.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "Sprite.h"


WallTile::WallTile(ENTITYTYPE p_type, int p_iX, int p_iY) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/tiles/wall.png", 0, 0, 40, 40);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
}


WallTile::~WallTile() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
}

int WallTile::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int WallTile::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

void WallTile::Update(float p_fDeltaTime) {
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void WallTile::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

Sprite * WallTile::GetSprite() {
	return m_xSprite;
}

ICollider* WallTile::GetCollider() {
	return m_xCollider;
}

void WallTile::OnCollision(IEntity* p_xOther) {
	if (p_xOther->GetType() == ENTITYTYPE::ENTITY_PLAYER)
	{
	
	}
}

ENTITYTYPE WallTile::GetType() {
	return m_eType;
}

SDL_Point WallTile::getPosition() {
	return m_position;
}
