#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int GRIDSIZE = 50;
const int WIDTH = 17;
const int HEIGHT = 15;
const int BOARDWIDTH = GRIDSIZE * WIDTH;
const int BOARDHEIGHT = GRIDSIZE * HEIGHT;

// compile:g++ main.cpp -IC:\SFML\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\include -LC:\SFML\SFML-3.1.0-windows-gcc-14.2.0-mingw-64-bit\SFML-3.1.0\lib -lsfml-graphics -lsfml-window -lsfml-system -o snake.exe

void drawGameboard(sf::RenderWindow& newWindow){

        sf::RectangleShape tile(sf::Vector2f(GRIDSIZE,GRIDSIZE));

        int even = 0;

        for (int i = 0; i <= BOARDHEIGHT; i += GRIDSIZE) {
            
            for (int j = 0; j <= BOARDWIDTH; j += GRIDSIZE) {

                tile.setPosition({
                static_cast<float>(j),
                static_cast<float>(i)
                });

                if ( even % 2 == 0) {

                    tile.setFillColor({25,105,5});
                    /*tile.setOutlineColor(sf::Color::Black);
                    tile.setOutlineThickness(1);*/

                } else {
                    
                    tile.setFillColor({39,245,87});
                    /*tile.setOutlineColor(sf::Color::Black);
                    tile.setOutlineThickness(1);*/
                }

                newWindow.draw(tile);
                
                even++;
                
            }

            even++;

        }
    }

int main() {

    sf::RenderWindow window(sf::VideoMode({BOARDWIDTH, BOARDHEIGHT}), "Snake Game"); // creating the window

    sf::RectangleShape bodyPart(sf::Vector2f(GRIDSIZE, GRIDSIZE)); // creating a part of the body
    
    std::vector<sf::Vector2i> snakeBody = {{5,5},{5,6},{5,7}}; // temporary vector

    sf::RectangleShape apple(sf::Vector2f(GRIDSIZE,GRIDSIZE)); // apple
    apple.setFillColor(sf::Color::Red);

    // internal timer
    sf::Clock clock;
    float timer = 0;
    float delay = 0.2f;

    sf::Vector2i direction = {1,0}; // default movement to the right
    sf::Vector2i nextDirection = {1,0};

    sf::Vector2i up = {0,-1};
    sf::Vector2i left = {-1,0};
    sf::Vector2i down = {0,1};
    sf::Vector2i right = {1,0};

    srand(time(0));

    int alma_x = (rand() % 18);
    int alma_y = (rand() % 16);

    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();
        timer += dt;

        while(auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>())
                window.close();

            if(event->is<sf::Event::KeyPressed>()){
                auto key = event->getIf<sf::Event::KeyPressed>();

                if (key) {
                    if (key->code == sf::Keyboard::Key::W && direction != down)
                        nextDirection = up;

                    if (key->code == sf::Keyboard::Key::A && direction != right)
                        nextDirection = left;

                    if (key->code == sf::Keyboard::Key::S && direction != up)
                        nextDirection = down;

                    if (key->code == sf::Keyboard::Key::D && direction != left)
                        nextDirection = right;
                }
            }
        }

        // update: moving the snake
        if (timer > delay) {
            timer = 0;

            direction = nextDirection;

            sf::Vector2i newHead = snakeBody[0] + direction;

            if (newHead.x > WIDTH || newHead.x < -1 || newHead.y > HEIGHT || newHead.y < -1)
            {
                window.close();
            }
            
            for (int i = 1; i < snakeBody.size(); i++){

                if (newHead.x == snakeBody[i].x && newHead.y == snakeBody[i].y)
                {
                    window.close();
                }
            }

            snakeBody.insert(snakeBody.begin(), newHead); // we give the snake a new head




            if (snakeBody[0].x == alma_x && snakeBody[0].y == alma_y) { // is the snake eating an apple?

                alma_x = rand() % 17;
                alma_y = rand() % 15;
            } else {
                snakeBody.pop_back(); // if not we remove the last body part
            }
          
        }


        // drawing the snake from the vector
        window.clear(sf::Color::White);

        drawGameboard(window);

        for (int i = 0; i < snakeBody.size(); i++) {

            bodyPart.setPosition({
                static_cast<float>(snakeBody[i].x * GRIDSIZE),
                static_cast<float>(snakeBody[i].y * GRIDSIZE)
            });

            if (i == 0) { 
                
                bodyPart.setFillColor({37,36,189}); 
            
            } else { 
                
                bodyPart.setFillColor({56,218,224}); 
            
            };
   
            bodyPart.setOutlineColor(sf::Color::Red);
            bodyPart.setOutlineThickness(2);

            window.draw(bodyPart);

        }
        apple.setPosition({

            static_cast<float>(alma_x * GRIDSIZE),
            static_cast<float>(alma_y * GRIDSIZE)
        });

        window.draw(apple);

        window.display();
    }

    window.close();

    return 0;

}
