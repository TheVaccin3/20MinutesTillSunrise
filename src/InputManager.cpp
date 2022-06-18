#include "InputManager.hpp"
#include <string>
namespace QuickSDL {
	//Initializing to NULL
	InputManager *InputManager::sInstance = NULL;

	InputManager *InputManager::Instance() {
		//Create a new instance if no instance was created before
		if (sInstance == NULL)
			sInstance = new InputManager();

		return sInstance;
	}

	bool InputManager::KeyDown(SDL_Scancode scanCode) {
		return (mKeyboardState[scanCode] != 0);
	}

	bool InputManager::KeyPressed(SDL_Scancode scanCode) {
		//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
		return (mPrevKeyboardState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
	}

	bool InputManager::KeyReleased(SDL_Scancode scanCode) {
		//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
		return (mPrevKeyboardState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
	}

	Vector2 InputManager::MousePos() {
		//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}

	bool InputManager::MouseButtonDown(MOUSE_BUTTON button) {
		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {
			case left:

				mask = SDL_BUTTON_LMASK;
				break;

			case right:

				mask = SDL_BUTTON_RMASK;
				break;

			case middle:

				mask = SDL_BUTTON_MMASK;
				break;

			case back:

				mask = SDL_BUTTON_X1MASK;
				break;

			case forward:

				mask = SDL_BUTTON_X2MASK;
				break;
		}

		//return true if the mask exists in the current mouse state
		return ((mMouseState & mask) != 0);
	}

	bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) {
		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {
			case left:

				mask = SDL_BUTTON_LMASK;
				break;

			case right:

				mask = SDL_BUTTON_RMASK;
				break;

			case middle:

				mask = SDL_BUTTON_MMASK;
				break;

			case back:

				mask = SDL_BUTTON_X1MASK;
				break;

			case forward:

				mask = SDL_BUTTON_X2MASK;
				break;
		}

		//return true if the mask does not exist in the previous mouse state, but exists in the current one
		return ((mPrevMouseState & mask) == 0) && ((mMouseState & mask) != 0);
	}

	bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) {
		Uint32 mask = 0;

		switch (button) {
			case left:

				mask = SDL_BUTTON_LMASK;
				break;

			case right:

				mask = SDL_BUTTON_RMASK;
				break;

			case middle:

				mask = SDL_BUTTON_MMASK;
				break;

			case back:

				mask = SDL_BUTTON_X1MASK;
				break;

			case forward:

				mask = SDL_BUTTON_X2MASK;
				break;
		}

		//return true if the mask exists in the previous mouse state, but does not exist in the current one
		return ((mPrevMouseState & mask) != 0) && ((mMouseState & mask) == 0);
	}

	void InputManager::Update() {
		//Updating the mouse state to get the key states of the current frame
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
	}

	void InputManager::UpdatePrevInput() {
		//Copying the keyboard state into the previous keyboard state array at the end of the frame
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
		//Setting the previous mouse state as the current mouse state at the end of the frame
		mPrevMouseState = mMouseState;
	}
} // namespace QuickSDL