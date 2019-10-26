#include "stdafx.h"
#include "BrickTile.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "Sprite.h"
#include "StateGame.h"

BrickTile::BrickTile(ENTITYTYPE p_type, int p_iX, int p_iY, StateGame* state) {
	m_xRenderManager = Service<RenderManager>::GetService();
	m_xSprite = Service<SpriteManager>::GetService()->CreateSprite("../Assets/tiles/brick.png", 0, 0, 40, 40);
	m_xCollider = new RectangleCollider(p_iX, p_iY, m_xSprite->GetWidth(), m_xSprite->GetHeight());
	m_position.x = p_iX;
	m_position.y = p_iY;
	m_eType = p_type;
	m_xState = state;
}

BrickTile::~BrickTile() {
	Service<SpriteManager>::GetService()->DestroySprite(m_xSprite);
	delete m_xCollider;
}

SDL_Point BrickTile::getPosition() {
	return m_position;
}

void BrickTile::Update(float p_fDeltaTime) {
	m_xCollider->SetPosition(m_position.x, m_position.y);
}

void BrickTile::Render() {
	m_xRenderManager->Draw(m_xSprite, m_position.x, m_position.y);
}

int BrickTile::getXTile() {
	int xTile = (m_position.x + 20) / 40;
	return xTile;
}

int BrickTile::getYTile() {
	int yTile = (m_position.y + 20) / 40;
	return yTile;
}

Sprite * BrickTile::GetSprite() {
	return m_xSprite;
}

ICollider* BrickTile::GetCollider() {
	return m_xCollider;
}

void BrickTile::OnCollision(IEntity* p_xOther) {
}

ENTITYTYPE BrickTile::GetType() {
	return m_eType;
}
