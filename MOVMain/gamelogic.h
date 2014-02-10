#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>


class scSimulatable;
class gcRenderable;
class MainWindow;

class gameLogic
{
public:
    void AddSimulatable(scSimulatable &Simulatable);
    void AddRenderable(gcRenderable &Renderable);

    gameLogic(MainWindow &window) : sourceWindow(window){}

private:
    std::vector<scSimulatable *> simulatables;
    MainWindow &sourceWindow;
};

#endif // GAMELOGIC_H
