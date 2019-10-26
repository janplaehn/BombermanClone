#pragma once

/*This Manager nadles every input the player provides while playing the
game. It allows us to have control over all the actions performed by the
player during gameplay. While the isKey..-Functions handle input on the keyboard,
isMouse..-Functions handle input done via the mouse.*/


class Mouse;
class Keyboard;

class InputManager
{
public:
	InputManager();
	~InputManager();
	bool Initialize();
	void Shutdown();

	bool IsKeyDown(SDL_Scancode p_eKey);
	/* IsKeyDown takes the SDL_Scancode of a key and returns, if that key is hold down.
	This function returns true as long as the key is pressed down*/

	bool IsKeyPressed(SDL_Scancode p_eKey); 
	/* IsKeyPressed takes the SDL_Scancode of a key and returns, if that key is pressed.
	This function returns true only once, when the key is pressed, not if it is hold down longer*/

	bool IsKeyReleased(SDL_Scancode p_eKey);
	/* IsKeyReleased takes the SDL_Scancode of a key and returns, if that key is released.
	This function returns true only once, when the key is released, not if it is pressed or hold down*/

	bool IsMouseButtonDown(int p_iButton);
	/* IsMouseButtonDown takes an int (which stands for a button on the mouse), and calls the
	IsMouseButtonDown function of the Mouse, which returns if that button is down.
	This function returns true as long as the mouse button is hold down. */

	bool IsMouseButtonPressed(int p_iButton);
	/* IsMouseButtonPressed takes an int (which stands for a button on the mouse), and calls the
	IsMouseButtonPressed function of the Mouse, which returns if that button is pressed.
	This function returns true once, when the button is pressed. */

	bool IsMouseButtonReleased(int p_iButton);
	/* IsMouseButtonReleased takes an int (which stands for a button on the mouse), and calls the
	IsMouseButtonReleased function of the Mouse, which returns if that button is pressed.
	This function returns true once, when the button is released. */

	SDL_Point GetMousePosition();
	/* GetMousePosition calls the GetMousePosition function of the mouse, which returns th position of the
	mouse as an SDL_Point*/

	SDL_Point GetMouseMotion();
	/* GetMouseMotion calls the GetMouseMotion function of the mouse, which returns the variable m_motion of the
	mouse. This variable stores, which way the mouse is moving.*/

	void HandleEvents(SDL_Event &p_Event);
	/* HandleEvents calls the HandleEvents function of the Keyboard and the mouse, which handles events
	such as Keydown, Keyup or Mousemotion.*/


	void LateUpdate(float p_fDelta);
private:
	Mouse* m_xMouse = nullptr;
	Keyboard* m_xKeyboard = nullptr;
};

