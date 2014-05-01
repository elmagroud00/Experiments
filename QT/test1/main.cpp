#include <QCoreApplication>
//#include <QtOpenGL/QGLContext>
/*
class GLContext : public QGLContext
{
public:
    GLContext();
};

GLContext::GLContext() : QGLContext(QGLFormat::defaultFormat())
{
    create();
}
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
   // GLContext g;
    return a.exec();
}
