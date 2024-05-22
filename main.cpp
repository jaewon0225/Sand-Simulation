#include <SFML/Graphics.hpp>
#include <iostream>

#include "sand_solver.cpp"

const int window_width = 400;
const int window_height = 600;
const int cellSize = 4;
const int rows = window_height / cellSize;
const int cols = window_width / cellSize;

int main() {
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sand Simulation");
    SandBox sandbox(cols, rows);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                // Check if the 'B' key is pressed
                if (event.key.code == sf::Keyboard::B) {
                    sandbox.SetColor('b');
                }
                if (event.key.code == sf::Keyboard::O) {
                    sandbox.SetColor('o');
                }
                if (event.key.code == sf::Keyboard::R) {
                    sandbox.SetColor('r');
                }
            }
        }

        // Place sand while the left mouse button is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            int x = mousePosition.x / cellSize;
            int y = mousePosition.y / cellSize;
            sandbox.PlaceSand(x, y);
        }

        sandbox.DFSCheck();
        sandbox.UpdateSandBox();

        window.clear();

        const auto& box = sandbox.GetBox(); // Use the getter method to access the grid
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                if (box[i][j] == 'o') 
                {
                    cell.setFillColor(sf::Color::Black);
                }
                else if (box[i][j] == 'b')
                {
                    cell.setFillColor(sf::Color::Blue);
                }
                else if (box[i][j] == 'r')
                {
                    cell.setFillColor(sf::Color::Red);
                }
                else 
                {
                    cell.setFillColor(sf::Color::White);
                }

                window.draw(cell);
            }
        }
        window.display();
    }
}
