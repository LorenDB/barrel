#include <QCoreApplication>
#include <QCommandLineParser>
#include <QRandomGenerator64>
#include <QFile>
#include <QThread>

#include <iostream>

#include "BarrelParser.h"

QString parseBarrelInstructionString(QString input);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("barrel");
    QCoreApplication::setApplicationVersion("0.0.1");

    QCommandLineParser optionsParser;
    optionsParser.addHelpOption();
    optionsParser.addVersionOption();

    QCommandLineOption file{QStringList() << "f" << "file",
                            "File to read data from. If this is not specified, barrel will start in program input mode.",
                            "file"};
    optionsParser.addOption(file);

    optionsParser.process(a);

    BarrelParser parser;

    QThread thread{&a};
    parser.moveToThread(&thread);
    thread.start();

    QObject::connect(&parser, &BarrelParser::done, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    QObject::connect(&parser, &BarrelParser::done, &a, [&thread] {
        thread.quit();
        thread.wait();
    });

    if (optionsParser.isSet(file))
    {
        QFile barrelFile(optionsParser.value(file));
        if (barrelFile.open(QIODevice::ReadOnly))
        {
            parser.run(barrelFile.readAll());
        }
        else
        {
            std::cerr << QString("Could not open file %1!").arg(optionsParser.value(file)).toStdString();
            return 0;
        }
    }
    else
        parser.run();

    return a.exec();
}
