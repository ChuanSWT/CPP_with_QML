#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{}
void Worker::doWork(){
    // 耗时任务（不要碰 UI）
    for (int i = 0; i <= 100; ++i) {
        QThread::msleep(2);
        emit progress(i);
    }
    emit finished();
}
