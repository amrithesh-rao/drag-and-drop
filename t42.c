#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QMimeData>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setAcceptDrops(true);
    window.setCentralWidget(textEdit);

    QObject::connect(textEdit, &QTextEdit::dragEnterEvent, [](QDragEnterEvent *event) {
        if (event->mimeData()->hasUrls())
            event->acceptProposedAction();
    });

    QObject::connect(textEdit, &QTextEdit::dropEvent, [](QDropEvent *event) {
        for (const QUrl &url : event->mimeData()->urls())
            qDebug() << url.toLocalFile();
    });

    window.show();
    return app.exec();
}
