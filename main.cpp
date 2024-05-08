#include <QApplication>

#include "widget.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(150);
    graphics g(5, 5);
    g.resize(600, 600);
    g.show();

    return a.exec();
}
