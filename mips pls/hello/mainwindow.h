#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "assemble.h"
#include "disassemble.h"
#include "editor.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
    QString bin_content;

private:
    void open();
    void saveFile();
    void openFile();
    void saveAsFile();
    void assemble();
    void disassemble();
    //void createFile();
    void closeEvent(QCloseEvent *event);



    /* status */
    bool isSaved;
    bool isLocated;
    bool isAssembled;
    bool bin_coe; //true : bin

    /* file path */
    QString path;
    QString outpath;
    QString disassemble_outpath;

    /* action */
    QAction *disassembleAction;
    QAction *assembleAction;
    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    /* console */

    /*
    QTextEdit * inputConsole;
    QTextEdit * AsmConsole;
    QTextEdit * infoConsole;
    */


    CodeEditor * inputConsole;
    CodeEditor * AsmConsole;
    CodeEditor * infoConsole;


    /* manager */
    assemble_manager assembler;
    disassemble_manager disassembler;

    void setActions();
    void setConnects();
    void layoutSettings();


};

class EventLabel : public QLabel
{
    Q_OBJECT
protected:
    //重载了三个函数
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

};


#endif // MAINWINDOW_H
