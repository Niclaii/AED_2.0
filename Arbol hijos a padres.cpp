#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>      

struct TreeNode
{
    int valor;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v) : valor(v), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* n, int v)
{
    if (!n) return new TreeNode(v);
    if (v < n->valor)  n->left = insert(n->left, v);
    else               n->right = insert(n->right, v);
    return n;
}

int subtreeSumParallel(TreeNode* node)
{
    if (!node) return 0;
    if (!node->left && !node->right) return node->valor;   

    int leftSum = 0;
    int rightSum = 0;
    std::thread tL, tR;  

    if (node->left)
    {
        tL = std::thread([&leftSum, node]
            {
            leftSum = subtreeSumParallel(node->left);
            });
    }
    if (node->right) 
    {
        tR = std::thread([&rightSum, node] 
            {
            rightSum = subtreeSumParallel(node->right);
            });
    }

    if (tL.joinable()) tL.join();
    if (tR.joinable()) tR.join();

    node->valor = leftSum + rightSum;
    return node->valor;
}

class BinaryTreeVisualizer {
public:
    explicit BinaryTreeVisualizer(TreeNode* r) : raiz(r)
    {
        fontLoaded = font.loadFromFile("arial.ttf");
    }

    void draw(sf::RenderWindow& w) { drawRec(w, raiz, 400, 50, 150, 100); }

private:
    void drawRec(sf::RenderWindow& w, TreeNode* n,
        float x, float y, float dx, float dy)
    {
        if (!n) return;

        sf::CircleShape c(20);
        c.setFillColor(sf::Color::Green);
        c.setOutlineColor(sf::Color::White);
        c.setOutlineThickness(2);
        c.setPosition(x, y);
        w.draw(c);

        if (fontLoaded)
        {
            sf::Text t(std::to_string(n->valor), font, 16);
            auto b = t.getLocalBounds();
            t.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
            t.setFillColor(sf::Color::Black);
            t.setPosition(x + 20, y + 20);
            w.draw(t);
        }

        if (n->left) 
        {
            sf::Vertex line[] = { {{x + 20, y + 20}}, {{x - dx + 20, y + dy + 20}} };
            w.draw(line, 2, sf::Lines);
            drawRec(w, n->left, x - dx, y + dy, dx / 2.f, dy);
        }
        if (n->right) 
        {
            sf::Vertex line[] = { {{x + 20, y + 20}}, {{x + dx + 20, y + dy + 20}} };
            w.draw(line, 2, sf::Lines);
            drawRec(w, n->right, x + dx, y + dy, dx / 2.f, dy);
        }
    }

    TreeNode* raiz;
    sf::Font font;
    bool fontLoaded{ false };
};

int main()
{

    int vals[] = { 10, 5, 15, 3, 7, 13, 18, 1, 4, 6, 8 };
    TreeNode* root = nullptr;
    for (int v : vals) root = insert(root, v);

    std::cout << "Suma total en la raiz: " << subtreeSumParallel(root) << '\n';

    sf::RenderWindow win({ 800, 600 }, "Árbol con sumas paralelas");
    BinaryTreeVisualizer vis(root);

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e))
            if (e.type == sf::Event::Closed) win.close();

        win.clear(sf::Color::Black);
        vis.draw(win);
        win.display();
    }
    return 0;
}
