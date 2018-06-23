#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <fstream>
#include <QErrorMessage>
#include "stagedata.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->scene = new EditorScene{QRect{0, 0, 13 * 250, 13 * 250}};
    this->ui->editorView->setScene(this->scene);

    this->ui->colorPreview->setScene(new QGraphicsScene);

    /* toolbar */
    connect(this->ui->actionAdd_Worm, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setWorm()));
    connect(this->ui->actionAdd_Long_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setLongGirder()));
    connect(this->ui->actionShort_Girder, SIGNAL(triggered(bool)), this->ui->editorView,
            SLOT(setShortGirder()));

    this->showMaximized();
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
}

void MainWindow::on_actionLejano_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo lejano"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->fartherBgFile = fileName;
        this->scene->setFartherBg(QImage(fileName));
    }
}

void MainWindow::on_actionMedio_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo medio"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->midBgFile = fileName;
        this->scene->setMedianBg(QImage(fileName));
    }
}

void MainWindow::on_actionCercano_triggered() {
    QString fileName = QFileDialog::getOpenFileName(
                                      this,
                                      tr("Seleccione una imagen para el fondo cercano"),
                                      "/home",
                                      tr("Image Files (*.png)")
                                    );
    if(!fileName.isEmpty()) {
        this->closeBgFile = fileName;
        this->scene->setCloserBg(QImage(fileName));
    }
}

void MainWindow::on_bgColorButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::yellow, this);
    if(color.isValid()) {
        this->scene->setBgColor(color);
        this->ui->colorPreview->setBackgroundBrush(QBrush(color));
    }
}

void MainWindow::on_actionOpen_triggered() {
    /* gets the output file name */
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Nombre de archivo de salida"),
                "/home",
                tr("YAML (*.yml)")
              );

    /* checks if a file was selected */
    if(fileName.isEmpty()) {
        return;
    }

    std::ofstream file;
    file.open(fileName.toStdString(), std::ios::out | std::ios::trunc);
    if(!file) {
        QErrorMessage msg;
        msg.showMessage("Error al abrir el archivo");
        return;
    }

    /* serializes the stage */
    StageData sd;
    sd.closeBgFile = this->closeBgFile;
    sd.medianBgFile = this->midBgFile;
    sd.fartherBgFile = this->fartherBgFile;

    this->ui->editorView->serialize(sd);

    sd.dump(file);
}
