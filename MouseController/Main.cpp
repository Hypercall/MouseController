#include "MouseController.hpp"
#include <iostream>

int main()
{
	if(MouseController::Init())
		std::cout << "MouseController is ready! Press F12 to test the Move_Mouse function" << std::endl;
	else
		std::cout << "MouseController failed to start!" << std::endl;
	while (true)
	{
		if (MouseController::GetAsyncKeyState(VK_F12))
		{
			std::cout << "Key pressed" << std::endl;
			if (MouseController::Move_Mouse(500, 500))
				std::cout << "Mouse moved to X : 500, Y : 500" << std::endl;
		}
	}
	MouseController::Uninit();
	std::cin.get();
	return 1;
}