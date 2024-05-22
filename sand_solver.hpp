#include <vector>

class SandBox {
public:
    SandBox(int width, int height);
    void PlaceSand(int x, int y);
    void UpdateSandBox();
    void DFSCheck();
    void SetColor(char color);
    const std::vector<std::vector<char>>& GetBox() const; // Getter method

private:
    std::vector<std::vector<char>> box;
    char color = 'o';
};

int randomDirection();

