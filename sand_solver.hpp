#include <vector>

class SandBox {
public:
    SandBox(int width, int height);
    void PlaceSand(int x, int y);
    void UpdateSandBox();
    void DFSCheck();
    const std::vector<std::vector<char>>& GetBox() const; // Getter method

private:
    std::vector<std::vector<char>> box;
    const char sand_char = 'o';
};

int randomDirection();

