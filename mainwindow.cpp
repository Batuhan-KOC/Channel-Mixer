#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <QFileInfo>

#include <QColor>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), RedChannelSet(false), BlueChannelSet(false), GreenChannelSet(false), AlphaChannelSet(false)
{
    ui->setupUi(this);

    connect(ui->inputR, &QLabelDragDrop::ImageDropped, this, &MainWindow::ImageAdded);
    connect(ui->inputG, &QLabelDragDrop::ImageDropped, this, &MainWindow::ImageAdded);
    connect(ui->inputB, &QLabelDragDrop::ImageDropped, this, &MainWindow::ImageAdded);
    connect(ui->inputA, &QLabelDragDrop::ImageDropped, this, &MainWindow::ImageAdded);

    connect(ui->removeR, &QPushButton::pressed, this, &MainWindow::RemoveR);
    connect(ui->removeG, &QPushButton::pressed, this, &MainWindow::RemoveG);
    connect(ui->removeB, &QPushButton::pressed, this, &MainWindow::RemoveB);
    connect(ui->removeA, &QPushButton::pressed, this, &MainWindow::RemoveA);

    ui->inputR->SetDefaultTextValue("R");
    ui->inputG->SetDefaultTextValue("G");
    ui->inputB->SetDefaultTextValue("B");
    ui->inputA->SetDefaultTextValue("A");

    ui->removeA->setVisible(false);
    ui->removeR->setVisible(false);
    ui->removeG->setVisible(false);
    ui->removeB->setVisible(false);

    connect(ui->generate, &QPushButton::pressed, this, &MainWindow::GenerateButtonPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedChannelImageAdded(QImage& image)
{
    int referenceWidth = 0;
    int referenceHeight = 0;

    if(BlueChannelSet){
        referenceWidth = BlueChannel.width();
        referenceHeight = BlueChannel.height();
    }
    else if(GreenChannelSet){
        referenceWidth = GreenChannel.width();
        referenceHeight = GreenChannel.height();
    }
    else if(AlphaChannelSet){
        referenceWidth = AlphaChannel.width();
        referenceHeight = AlphaChannel.height();
    }

    if(referenceHeight != 0 && referenceWidth != 0){
        if(image.height() == referenceHeight && image.width() == referenceWidth){
            RedChannel = image;
            RedChannelSet = true;
            ui->removeR->setVisible(true);
        }
        else{
            ui->inputR->RemoveImage();
            RedChannelSet = false;
            ui->removeR->setVisible(false);
        }
    }
    else{
        RedChannel = image;
        RedChannelSet = true;
        ui->removeR->setVisible(true);
    }

    UpdateOutputImage();
}

void MainWindow::GreenChannelImageAdded(QImage& image)
{
    int referenceWidth = 0;
    int referenceHeight = 0;

    if(BlueChannelSet){
        referenceWidth = BlueChannel.width();
        referenceHeight = BlueChannel.height();
    }
    else if(RedChannelSet){
        referenceWidth = RedChannel.width();
        referenceHeight = RedChannel.height();
    }
    else if(AlphaChannelSet){
        referenceWidth = AlphaChannel.width();
        referenceHeight = AlphaChannel.height();
    }

    if(referenceHeight != 0 && referenceWidth != 0){
        if(image.height() == referenceHeight && image.width() == referenceWidth){
            GreenChannel = image;
            GreenChannelSet = true;
            ui->removeG->setVisible(true);
        }
        else{
            ui->inputG->RemoveImage();
            GreenChannelSet = false;
            ui->removeG->setVisible(false);
        }
    }
    else{
        GreenChannel = image;
        GreenChannelSet = true;
        ui->removeG->setVisible(true);
    }

    UpdateOutputImage();
}

void MainWindow::BlueChannelImageAdded(QImage& image)
{
    int referenceWidth = 0;
    int referenceHeight = 0;

    if(GreenChannelSet){
        referenceWidth = GreenChannel.width();
        referenceHeight = GreenChannel.height();
    }
    else if(RedChannelSet){
        referenceWidth = RedChannel.width();
        referenceHeight = RedChannel.height();
    }
    else if(AlphaChannelSet){
        referenceWidth = AlphaChannel.width();
        referenceHeight = AlphaChannel.height();
    }

    if(referenceHeight != 0 && referenceWidth != 0){
        if(image.height() == referenceHeight && image.width() == referenceWidth){
            BlueChannel = image;
            BlueChannelSet = true;
            ui->removeB->setVisible(true);
        }
        else{
            ui->inputB->RemoveImage();
            BlueChannelSet = false;
            ui->removeB->setVisible(false);
        }
    }
    else{
        BlueChannel = image;
        BlueChannelSet = true;
        ui->removeB->setVisible(true);
    }

    UpdateOutputImage();
}

void MainWindow::AlphaChannelImageAdded(QImage& image)
{
    int referenceWidth = 0;
    int referenceHeight = 0;

    if(GreenChannelSet){
        referenceWidth = GreenChannel.width();
        referenceHeight = GreenChannel.height();
    }
    else if(RedChannelSet){
        referenceWidth = RedChannel.width();
        referenceHeight = RedChannel.height();
    }
    else if(BlueChannelSet){
        referenceWidth = BlueChannel.width();
        referenceHeight = BlueChannel.height();
    }

    if(referenceHeight != 0 && referenceWidth != 0){
        if(image.height() == referenceHeight && image.width() == referenceWidth){
            AlphaChannel = image;
            AlphaChannelSet = true;
            ui->removeA->setVisible(true);
        }
        else{
            ui->inputA->RemoveImage();
            AlphaChannelSet = false;
            ui->removeA->setVisible(false);
        }
    }
    else{
        AlphaChannel = image;
        AlphaChannelSet = true;
        ui->removeA->setVisible(true);
    }

    UpdateOutputImage();
}

void MainWindow::UpdateOutputImage()
{
    if(RedChannelSet || GreenChannelSet || BlueChannelSet || AlphaChannelSet){
        int outputWidth = 0;
        int outputHeight = 0;

        // Find the size of the output image
        if(RedChannelSet){
            outputWidth = RedChannel.width();
            outputHeight = RedChannel.height();
        }
        else if(GreenChannelSet){
            outputWidth = GreenChannel.width();
            outputHeight = GreenChannel.height();
        }
        else if(BlueChannelSet){
            outputWidth = BlueChannel.width();
            outputHeight = BlueChannel.height();
        }
        else if(AlphaChannelSet){
            outputWidth = AlphaChannel.width();
            outputHeight = AlphaChannel.height();
        }

        if(outputWidth == 0 && outputHeight == 0){
            return;
        }

        if(Output != nullptr){
            delete Output;
        }

        Output = new QImage(outputWidth, outputHeight, QImage::Format_RGBA8888);

        for(int x = 0 ; x < Output->width() ; x++){
            for(int y = 0 ; y < Output->width() ; y++){
                int r = 0;
                int g = 0;
                int b = 0;
                int a = 255;

                if(RedChannelSet){
                    r = RedChannel.pixelColor(x, y).red();
                }

                if(GreenChannelSet){
                    g = GreenChannel.pixelColor(x, y).green();
                }

                if(BlueChannelSet){
                    b = BlueChannel.pixelColor(x, y).blue();
                }

                if(AlphaChannelSet){
                    a = AlphaChannel.pixelColor(x, y).blue();
                }

                Output->setPixelColor(x, y, QColor(r, g, b, a));
            }
        }

        ui->output->setPixmap(QPixmap::fromImage(Output->scaled(ui->output->width() ,ui->output->height() ,Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    else{
        ui->output->setPixmap(QPixmap());
    }
}

void MainWindow::CheckOutputText()
{
    if(!RedChannelSet && !GreenChannelSet && !BlueChannelSet && !AlphaChannelSet){
        ui->output->setText("OUTPUT");
    }
}

void MainWindow::ImageAdded(QImage image)
{
    QLabelDragDrop* button = qobject_cast<QLabelDragDrop*>(sender());

    if(button != NULL){
        if(button == ui->inputR){
            RedChannelImageAdded(image);
        }
        else if(button == ui->inputG){
            GreenChannelImageAdded(image);
        }
        else if(button == ui->inputB){
            BlueChannelImageAdded(image);
        }
        else if(button == ui->inputA){
            AlphaChannelImageAdded(image);
        }
    }
}

void MainWindow::RemoveA(){
    ui->inputA->RemoveImage();

    ui->removeA->setVisible(false);

    AlphaChannelSet = false;

    UpdateOutputImage();

    CheckOutputText();
}

void MainWindow::RemoveR(){
    ui->inputR->RemoveImage();

    ui->removeR->setVisible(false);

    RedChannelSet = false;

    UpdateOutputImage();

    CheckOutputText();
}

void MainWindow::RemoveG(){
    ui->inputG->RemoveImage();

    ui->removeG->setVisible(false);

    GreenChannelSet = false;

    UpdateOutputImage();

    CheckOutputText();
}

void MainWindow::RemoveB(){
    ui->inputB->RemoveImage();

    ui->removeB->setVisible(false);

    BlueChannelSet = false;

    UpdateOutputImage();

    CheckOutputText();
}

void MainWindow::GenerateButtonPressed()
{
    if(RedChannelSet || GreenChannelSet || BlueChannelSet || AlphaChannelSet){
        if(AlphaChannelSet){
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                            QDir::currentPath(),
                                                            tr("Images (*.png)"));

            QFileInfo info(fileName);

            if(info.suffix() != "png"){
                fileName = info.path() + "/" + info.completeBaseName() + ".png";
            }

            qDebug() << fileName;

            if(Output != nullptr){
                Output->save(fileName);
            }
        }
        else{
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                            QDir::currentPath(),
                                                            tr("Images (*.jpg *.jpeg *.png)"));

            QStringList allowedSuffixes;

            allowedSuffixes << "png" << "jpg" << "jpeg";

            QFileInfo info(fileName);

            if(!allowedSuffixes.contains(info.suffix())){
                fileName = info.path() + "/" + info.completeBaseName() + ".jpg";
            }

            qDebug() << fileName;

            if(Output != nullptr){
                Output->save(fileName);
            }
        }
    }
}



