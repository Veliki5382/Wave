#include "wavepch.h"

#include "WindowsInput.h"
#include "WaveEngine/Application.h"

#include <GLFW/include/GLFW/glfw3.h>

namespace wave {

    Input* Input::s_Instance = new WindowsInput;

	bool WindowsInput::GetKeyStateImpl(int keycode) {

		GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

		int status = glfwGetKey(window, keycode);
        return (status == GLFW_PRESS || status == GLFW_REPEAT);
    		
	}
    
    bool WindowsInput::GetMouseButtonStateImpl(int button) {
        
        GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

        int status = glfwGetMouseButton(window, button);
        return status == GLFW_PRESS;
        
    }

    std::pair<double, double> WindowsInput::GetMousePositionImpl() {
        
        GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { xpos, ypos };
    }

    double WindowsInput::GetMouseXPosImpl() {

        std::pair<double, double> pos = WindowsInput::GetMousePositionImpl();
        
        return pos.first;
    }
    
    double WindowsInput::GetMouseYPosImpl() {
        
        std::pair<double, double> pos = WindowsInput::GetMousePositionImpl();
        
        return pos.first;
    }
    
    double WindowsInput::GetScrollXOffsetImpl() {
        
        GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

        return 0.0f;
    }
    
    double WindowsInput::GetScrollYOffsetImpl()
    {
        return 0.0f;
    }
    
    int WindowsInput::GetWindowWidthImpl() {

        GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        return width;
    }
    
    int WindowsInput::GetWindowHeightImpl() {

        GLFWwindow* window = (GLFWwindow*)(Application::Get()->GetWindow()->GetNativeWindow());

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        return height;
    }


} // namespace wave