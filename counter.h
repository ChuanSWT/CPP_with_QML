#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
    //相当于qml的property
    //！！意思是
    // cpp 提供一个名为 value 的属性
    // QML 通过属性访问 backend.value 获取其值
    // Qt 内部使用 READ MyGetValue() 作为 getter
    // 当 emit valueChanged() 时，QML 会重新计算所有依赖 value 的绑定
    Q_PROPERTY(int value READ MyGetValue NOTIFY valueChanged)

    public:
        explicit Counter(QObject *parent = nullptr)
        : QObject(parent), m_value(0) {}

    int MyGetValue() const { return m_value; }

    //Q_INVOKABLE：使得qml可以访问这个方法
    Q_INVOKABLE void increment() {
        ++m_value;
        emit valueChanged();
    }

signals:
    void valueChanged();

private:
    int m_value;
};

#endif
