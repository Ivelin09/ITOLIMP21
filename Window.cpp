Window::Window(const int width, const int height, std::vector<Image>& buttons, const std::string& bg)
    : window(sf::VideoMode(width, height), "Play with me!"), buttons(buttons)
{
    this->bg.loadFromFile(ImagePath + bg);
    this->background.setTexture(this->bg);
}

Image* Window::isClicked(const sf::RenderWindow& window) {
    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (int i = 0; i < buttons.size(); i++) {
        sf::Vector2f size = buttons[i].getShape().getSize();
        sf::Vector2f position = buttons[i].getShape().getPosition();

        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
            this->saveIndex = i;
            return &buttons[i];
        }
    }
    return nullptr;
}
