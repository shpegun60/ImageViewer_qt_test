#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSlider,
            SIGNAL(valueChanged(int)),
            ui->progressBar,
            SLOT(setValue(int)));


    userInitWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userInitWidget()
{

    userInitTab();
    userInitMenu();
}

void MainWindow::userInitTab()
{
    //    QImage image("data.png");
    //    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    horizontalLayout_tab_2 = new QHBoxLayout(ui->tab_2);
    horizontalLayout_tab_2->setObjectName(QString::fromUtf8("horizontalLayout_tab_2"));

    imageLabel = new QLabel(ui->tab_2);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea(ui->tab_2);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    horizontalLayout_tab_2->addWidget(scrollArea);


    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
}

void MainWindow::userInitMenu()
{
    //
    openAct = new QAction(tr("&Open...;"), this);
    openAct->setShortcut(tr("Ctrl+O"));

    printAct = new QAction(tr("&Print...;"), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);

    exitAct = new QAction(tr("E&xit;"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));

    zoomInAct = new QAction(tr("Zoom &In; (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl+="));   //(Ctrl)(+)
    zoomInAct->setEnabled(false);

    zoomOutAct = new QAction(tr("Zoom &Out; (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));  //(Ctrl)(-)
    zoomOutAct->setEnabled(false);

    normalSizeAct = new QAction(tr("&Normal; Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    fitToWindowAct = new QAction(tr("&Fit; to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));

    aboutAct = new QAction(tr("&About;"), this);

    aboutQtAct = new QAction(tr("About &Qt;"), this);


    fileMenu = new QMenu(tr("&File;"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View;"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help;"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);

    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::open()
{
    qDebug() << "open()";
    QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
         QImage image(fileName);
         if (image.isNull()) {
             QMessageBox::information(this, tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(fileName));
             return;
         }
         imageLabel->setPixmap(QPixmap::fromImage(image));
         //scaleFactor = 1.0;

         printAct->setEnabled(true);
         fitToWindowAct->setEnabled(true);
         updateActions();

         if (!fitToWindowAct->isChecked())
             imageLabel->adjustSize();
    }
}

void MainWindow::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void MainWindow::on_actionNew_Window_triggered()
{
    mDialog = new MyDialog(this);
    mDialog->show();
}

