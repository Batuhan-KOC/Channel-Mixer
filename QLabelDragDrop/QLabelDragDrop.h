#ifndef QLABELDRAGDROP_H
#define QLABELDRAGDROP_H

#include <QWidget>

#include <QLabel>

#include <QStringList>

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

class QLabelDragDrop : public QLabel
{
    Q_OBJECT
public:
    explicit QLabelDragDrop(QWidget* parent = nullptr);
    virtual ~QLabelDragDrop() override;

    void RemoveImage();

    void SetDefaultTextValue(const QString &newDefaultValue);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    // Accepted mime types
    QStringList acceptedTypes;

    // Absolute file path to the image
    QString path;

    // Dropped image
    QImage image;

    // Default text value
    QString defaultValue{""};

signals:
    void ImageDropped(QImage image);
};

#endif // QLABELDRAGDROP_H
