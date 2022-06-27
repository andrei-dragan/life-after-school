#include "LifeAfterSchool.h"
#include "EventService.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileEventRepo* adminRepo = new FileEventRepo{};
    HTMLEventRepo* userRepo = new HTMLEventRepo{};
    CVSEventRepo* secondaryUserRepo = new CVSEventRepo{};
    EventService es{ adminRepo, userRepo };
    EventService secondaryEs{ adminRepo, secondaryUserRepo };

    LifeAfterSchool w{es, secondaryEs};
    w.show();
    return a.exec();
}
