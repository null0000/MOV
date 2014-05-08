#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>


class gcRenderable;
class MainWindow;
class scObject;

class gameLogic
{
public:
    void AddSimulatable(scObject &Simulatable);
    void AddRenderable(gcRenderable &Renderable);

    gameLogic(MainWindow &window) : sourceWindow(window){}

private:
    std::vector<scObject *> simulatables;
    MainWindow &sourceWindow;
};

#endif // GAMELOGIC_H
