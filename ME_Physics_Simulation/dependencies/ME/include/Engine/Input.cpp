#include "Input.h"

namespace ME
{
    void Input::UpdateMouse()
    {
        m_MouseDown.reset();
        m_MouseUp.reset();
    }

    void ME::Input::Update()
    {
        // Keyboard
        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        m_KeyboardUp.reset();
        m_KeyboardDown.reset();
        
        for (int i = 0; i < MAX_KEYS; i++)
        {
            if (m_Keyboard[i] == false && keystates[i] == true)  m_KeyboardDown[i] = true;         
            else if (m_Keyboard[i] == true && keystates[i] == false) m_KeyboardUp[i] = true;          
            m_Keyboard[i] = keystates[i];
        }

        // Mouse Position
        SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);
    }

    void Input::MouseDown(Uint8 index)
    {
        index--;

        if (index > 2) return;

        m_Mouse[index] = true;
        m_MouseDown[index] = true;
    }

    void Input::MouseUp(Uint8 index)
    {
        index--;

        if (index > 2) return;

        m_Mouse[index] = false;
        m_MouseUp[index] = true;
    }

    bool ME::Input::GetKey(unsigned char code)
    {
        if (code >= MAX_KEYS) return false;
        return m_Keyboard[code];
    }

    bool ME::Input::GetKeyUp(unsigned char code)
    {
        if (code >= MAX_KEYS) return false;
        return m_KeyboardUp[code];
    }

    bool ME::Input::GetKeyDown(unsigned char code)
    {
        if (code >= MAX_KEYS) return false;
        return m_KeyboardDown[code];
    }

    bool Input::GetMouse(unsigned char index)
    {
        if (index > 2) return false;
        
        return m_Mouse[index];
    }

    bool Input::GetMouseUp(unsigned char index)
    {
        if (index > 2) return false;
       
        return m_MouseUp[index];
    }

    bool Input::GetMouseDown(unsigned char index)
    {
        if (index > 2) return false;

        return m_MouseDown[index];        
    }
    Vector2i Input::GetMousePosition()
    {
        return mousePosition;
    }
}

