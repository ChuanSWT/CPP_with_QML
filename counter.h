#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QThread>
#include "worker.h"
class Counter : public QObject
{
    Q_OBJECT
    private:
        int m_value;
        int m_multi_thread_value;
    //相当于qml的property
    //！！意思是
    // cpp 提供一个名为 value 的属性
    // QML 通过属性访问 backend.value 获取其值
    // Qt 内部使用 READ MyGetValue() 作为 getter
    // 当 emit valueChanged() 时，QML 会重新计算所有依赖 value 的绑定
    Q_PROPERTY(int value READ MyGetValue NOTIFY valueChanged)
    Q_PROPERTY(int multi_thread_value READ MyGetMultiThreadValue NOTIFY multiThreadValueChanged)
    public:
        explicit Counter(QObject *parent = nullptr)
        : QObject(parent) {
            m_value=0;
            m_multi_thread_value=0;
        }
    //getter 方法
    int MyGetValue() const { return m_value; }
    int MyGetMultiThreadValue() const { return m_multi_thread_value; };
    //Q_INVOKABLE：使得qml可以访问这个方法
    Q_INVOKABLE void increment() {
        ++m_value;
        emit valueChanged();
    }
    //多线程部分
    Q_INVOKABLE void multiThreadValueIncrement() {
        //声明一个线程和类对象
        QThread* th = new QThread(this);
        Worker* worker = new Worker;

        //将这个对象放入线程
        worker->moveToThread(th);

        //将线程启动的信号 链接到 worker开始执行任务
        connect(th, &QThread::started, worker, &Worker::doWork);
        //接收线程传回的信号
        connect(worker, &Worker::progress, this, [=](int p){
            // update UI / setProperty / emit signal to QML
            m_multi_thread_value=p;
            emit multiThreadValueChanged();
        });

        // 收尾
        //将worker的finished信号绑定在线程退出,销毁对象
        connect(worker, &Worker::finished, th, &QThread::quit);
        connect(worker, &Worker::finished, worker, &QObject::deleteLater);
        //在worker发送finished信号后
        //使得QThread触发quit()函数
        //使得事件循环结束
        //使得QThread.run()返回
        //最终触发了Qthread::finished信号
        connect(th, &QThread::finished, th, &QObject::deleteLater);

        th->start();
    }

signals:
    void valueChanged();
    void multiThreadValueChanged();

};

#endif
