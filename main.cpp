#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include "singleapplication.h"
#include "splashscreen.h"


int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv, "C64KERNALGENESIS");

    if (app.isRunning()) {
        QMessageBox::warning(nullptr,
                             "C64 KERNAL Genesis",
                             "The application is already running!");
        return 0;
    }

    QString appDir = QCoreApplication::applicationDirPath();
    QString modulesDirPath = appDir + "/modules";
    QDir modulesDir(modulesDirPath);

    if (!modulesDir.exists()) {
        modulesDir.mkpath(".");
    }

    app.setStyle("fusion");

    // Transparent PNG yükle
    QPixmap pixmap(":/res/pictures/c64kernalgenesis.png");

    SplashScreen *splash = new SplashScreen(pixmap);
    splash->show();
    app.processEvents();

    MainWindow *w = new MainWindow();

    // 3 saniye sonra splash kapat, ana pencereyi göster
    QTimer::singleShot(3000, [&splash, w]() {
        splash->close(); // Geçişi mainWindow'a bağla
        w->show();
    });

    return app.exec();
}
