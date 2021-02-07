#include "Window.h"

Window::Window(const int width, const int height, const std::string& path) :
    window(sf::VideoMode(width, height), "Play with me !")
{
    this->backgroundFile.loadFromFile(ImagePath + path);
    this->background.setTexture(this->backgroundFile);
}

Window* Window::start()
{
    return nullptr;
}
