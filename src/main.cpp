// To create an empty database in command line type: sqlite3 testSqlite.db "create table aTable(field1 int); drop table aTable;"

#include "mainwindow.h"
#include "CinDBReader.h"
#include <QCoreApplication>
#include <QCommandLineParser>

#define DEBUG false

int main(int argc, char *argv[])
{
    QApplication cinemaViewer(argc, argv);
    cinemaViewer.setStyleSheet("QSlider {height:20px; width:150}");

    // handle command line args 
    QCoreApplication::setApplicationName("CinemaScope");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("CinemaScope v0.1");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("database", 
            QCoreApplication::translate("main", "Cinema Database to open"));

    parser.process(cinemaViewer);
    const QStringList args = parser.positionalArguments();

    // currently, there is one positional argument
    QString dataPath;
    if (args.size() > 0) 
    {
        dataPath = args.at(0);
    }


    // run the application 
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.open();
    cin::DBReader reader;
    reader.readCinemaDatabase(db, dataPath, QString("cinema"));

    MainWindow mainWindow(db, dataPath);
    mainWindow.setWindowTitle("CinemaScope");
    mainWindow.show();

    return cinemaViewer.exec();
}
