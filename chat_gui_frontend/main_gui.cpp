#include <QApplication>
#include "chatGuiClient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChatGuiClient window;
    window.show();
    return app.exec();
}
