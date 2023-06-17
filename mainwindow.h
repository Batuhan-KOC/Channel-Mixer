
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Channel{
    Red,
    Green,
    Blue,
    Alpha
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool RedChannelSet;
    bool BlueChannelSet;
    bool GreenChannelSet;
    bool AlphaChannelSet;

    QImage RedChannel;
    QImage BlueChannel;
    QImage GreenChannel;
    QImage AlphaChannel;
    QImage* Output{nullptr};

    inline void RedChannelImageAdded(QImage& image);
    inline void GreenChannelImageAdded(QImage& image);
    inline void BlueChannelImageAdded(QImage& image);
    inline void AlphaChannelImageAdded(QImage& image);

    void UpdateOutputImage();

    void CheckOutputText();

private slots:
    void ImageAdded(QImage image);

    void RemoveA();
    void RemoveR();
    void RemoveG();
    void RemoveB();

    void GenerateButtonPressed();
};

#endif // MAINWINDOW_H
