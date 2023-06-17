#include "QLabelDragDrop.h"

#include <QMimeData>

#include <QFileInfo>

#include <QDebug>

QLabelDragDrop::QLabelDragDrop(QWidget* parent)
    : QLabel(parent)
{
    setAcceptDrops(true);
    setMouseTracking(true);

    acceptedTypes << "jpeg" << "jpg" << "png" << "bmp";
}


QLabelDragDrop::~QLabelDragDrop()
{

}

void QLabelDragDrop::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent";

    bool acceptDrag{false};

    // Accept only image files
    foreach(const QUrl & url, event->mimeData()->urls()){
        QString fname = url.toLocalFile();
        QFileInfo info(fname);

        if (info.exists()){
            if (acceptedTypes.contains(info.suffix().trimmed(), Qt::CaseInsensitive)){
                path = QString::fromStdString(info.absoluteFilePath().toStdString());
                qDebug() << path;
                acceptDrag = true;
            }
        }
    }

    if(acceptDrag){
        event->acceptProposedAction();
    }
    else{
        path.clear();
    }
}

void QLabelDragDrop::dragLeaveEvent(QDragLeaveEvent *event)
{
    releaseMouse();
}

void QLabelDragDrop::dragMoveEvent(QDragMoveEvent *event)
{
}

void QLabelDragDrop::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event)

    if(!path.isEmpty()){
        image = QImage(path);

        setPixmap(QPixmap::fromImage(image.scaled(this->width() ,this->height() ,Qt::KeepAspectRatio, Qt::SmoothTransformation)));

        emit ImageDropped(image);
    }
}

void QLabelDragDrop::SetDefaultTextValue(const QString &newDefaultValue)
{
    defaultValue = newDefaultValue;
}

void QLabelDragDrop::RemoveImage()
{
    setPixmap(QPixmap());

    image = QImage();

    path.clear();

    setText(defaultValue);
}
