#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fractals", sf::Style::Fullscreen);
    sf::Shader shader;
    if(!shader.loadFromFile("fractal.frag", sf::Shader::Fragment))
        std::cout << "Failed to load shader\n";

    float posX = 1, posY = 0.8525;

    sf::Clock clock;
    while (window.isOpen())
    {
        // Poll events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
                if(event.key.code == sf::Keyboard::R)
                {
                    if(!shader.loadFromFile("fractal.frag", sf::Shader::Fragment))
                        std::cout << "Failed to load shader\n";
                    else
                        clock.restart();
                }
                if(event.key.code == sf::Keyboard::Left) posX += 0.1;
                if(event.key.code == sf::Keyboard::Right) posX -= 0.1;
                if(event.key.code == sf::Keyboard::Down) posY += 0.1;
                if(event.key.code == sf::Keyboard::Up) posY -= 0.1;
            default:
                break;
            }
        }

        // Render
        window.clear();

        sf::Sprite sprite;
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        sprite.setTexture(texture);

        shader.setUniform("iTime", clock.getElapsedTime().asSeconds());
        shader.setUniform("posX", posX);
        shader.setUniform("posY", posY);

        window.draw(sprite, &shader);

        window.display();
    }
}