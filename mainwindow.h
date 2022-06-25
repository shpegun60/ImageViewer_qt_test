#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlabel.h>
#include <qmenu.h>
#include <qscrollarea.h>
#include <QtWidgets/QHBoxLayout>
#include "mydialog.h"
#include <QtWidgets/QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void userInitWidget();
    void userInitTab();
    void userInitMenu();


private slots:
    void on_actionNew_Window_triggered();
    void open();
    void updateActions();

private:
    Ui::MainWindow *ui;
    MyDialog *mDialog;

    // tab 2
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QHBoxLayout *horizontalLayout_tab_2;

    // Menu
    QMenu * fileMenu;
    QMenu * viewMenu;
    QMenu * helpMenu;

    QAction * openAct;
    QAction * printAct;
    QAction * exitAct;
    QAction * zoomInAct;
    QAction * zoomOutAct;
    QAction * normalSizeAct;
    QAction * fitToWindowAct;
    QAction * aboutAct;
    QAction * aboutQtAct;



};
#endif // MAINWINDOW_H
