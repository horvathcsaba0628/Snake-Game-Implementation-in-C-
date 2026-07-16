#include <SFML/Graphics.hpp>
#include <optional>

// compile:g++ main.cpp -IC:\SFML\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\include -LC:\SFML\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\lib -lsfml-graphics -lsfml-window -lsfml-system -o snake.exe

int main() {
    //  how big is a "tile" on the playing field
    const int SIZE = 40;

    // creating the window
    sf::RenderWindow window(sf::VideoMode({680, 600}), "Snake");


    sf::RectangleShape player(sf::Vector2f(SIZE, SIZE));
    player.setFillColor(sf::Color::Green);

    //sf::Vector2i position(10, 10);
    std::vector<sf::Vector2i> snakeBody;

    snakeBody.push_back((10,10));
    
    sf::Vector2i direction(1, 0);

    // internal timer
    sf::Clock clock;
    float timer = 0;
    float delay = 0.2f; // refresh rate

    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();
        timer += dt;

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // input (irány váltás)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction = {0, -1};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction = {0, 1};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction = {-1, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction = {1, 0};

        // update (lépésenként)
        if (timer > delay) {
            position += direction;
            timer = 0;
        }

        player.setPosition({
            static_cast<float>(position.x * SIZE),
            static_cast<float>(position.y * SIZE)
        });

        window.clear();
        window.draw(player);
        window.display();
    }

    window.close();
 
    return 0;
}