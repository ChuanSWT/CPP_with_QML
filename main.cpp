#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "counter.h"
int main(int argc, char *argv[])
{
    //检测qt版本
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    //“操作系统”-必须
    QGuiApplication app(argc, argv);
    //"QML虚拟机"-必须
    QQmlApplicationEngine engine;
    //要加载的页面的资源链接-必须
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    //安全启动,一旦启动失败就退出
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    /*开始写逻辑*/
    //自定义类
    Counter counter;
    //engine.rootContext()是“注册点”
    engine.rootContext()->setContextProperty("counter", &counter);
    //加载窗口
    engine.load(url);

    return app.exec();
}
