#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGLWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 300, 300);
    scene.setBackgroundBrush(QBrush(QColor("#120")));
    QGLWidget qgl;
    qgl.makeCurrent();

    QGraphicsView view(&scene);
    view.setViewport(&qgl);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    //view.setWindowFlags(Qt::FramelessWindowHint);
    view.showFullScreen();
    view.show();

    return app.exec();
}
