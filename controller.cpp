#include "controller.h"
#include "worker.h"

#include <QDebug>
#include <QThread>
//#include <QCoreApplication>

Controller::Controller()
{
    // first thread
    Worker* workerFirst = new Worker();
    workerFirst->moveToThread(&workerFirstThread);
    connect(&workerFirstThread, SIGNAL(started()), workerFirst, SLOT(run()));
    connect(&workerFirstThread, SIGNAL(finished()), workerFirst, SLOT(deleteLater()));

    workerFirstThread.start();
    if (workerFirstThread.isRunning())
    {
       qDebug() << "Started 1st thread...\n";
    }

    //second thread
    Worker* workerSecond = new Worker();
    workerSecond->moveToThread(&workerSecondThread);
    connect(&workerSecondThread, SIGNAL(started()), workerSecond, SLOT(run()));
    connect(&workerSecondThread, SIGNAL(finished()), workerSecond, SLOT(deleteLater()));

    workerSecondThread.start();
    if (workerSecondThread.isRunning())
    {
       qDebug() << "Started 2st thread...\n";
    }

}

Controller::~Controller()
{
    workerFirstThread.quit();
    workerFirstThread.wait();
    qDebug() << "Finishing 1st thread...\n";

    workerSecondThread.quit();
    workerSecondThread.wait();
    qDebug() << "Finishing 2nd thread...\n";

    some_function();

    emit QCoreApplication::quit();
    qDebug() << "Quitting...";
}

void Controller::some_function() {
    qDebug() << "Executing some function...";
}
