#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fractals", sf::Style::Fullscreen);
    sf::Shader shader;
    if(!shader.loadFromFile("fractal.frag", sf::Shader::Fragment))
        std::cout << "Failed to load shader\n";

    float posX = 0, posY = 0, zoom = 1;

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
                    {
                        clock.restart();
                        zoom = 1;
                        posX = posY = 0;
                    }
                }
                if(event.key.code == sf::Keyboard::Left) posX += 1 / pow(4, zoom);
                if(event.key.code == sf::Keyboard::Right) posX -= 1 / pow(4, zoom);
                if(event.key.code == sf::Keyboard::Down) posY += 1 / pow(4, zoom);
                if(event.key.code == sf::Keyboard::Up) posY -= 1 / pow(4, zoom);
                if(event.key.code == sf::Keyboard::Z) zoom += 0.5;
                if(event.key.code == sf::Keyboard::X) zoom -= 0.5;
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

        shader.setUniform("zoom", zoom);
        shader.setUniform("posX", posX);
        shader.setUniform("posY", posY);
        shader.setUniform("aspectRatio", sf::Vector2f(16, 9));

        window.draw(sprite, &shader);

        window.display();
    }
}