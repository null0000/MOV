#include "gamelogic.h"
#include "mainwindow.h"

void gameLogic::AddSimulatable(scObject &Simulatable)
{
    simulatables.push_back(&Simulatable);
}

void gameLogic::AddRenderable(gcRenderable &Renderable)
{
    sourceWindow.attachRenderable(&Renderable);
}
