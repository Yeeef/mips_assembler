#include <QtGui>
#include <QtWidgets>


#include "mainwindow.h"


MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent)
{
    isSaved = true;
    isLocated = false;
    isAssembled = true;
    bin_coe = false;
    setWindowTitle(tr("MIPS PLS"));



    setActions();
    layoutSettings();
    setConnects();







}

void MainWindow::setActions()
{

    assembleAction = new QAction(QIcon(":/images/电子"), tr("&汇编"), this);
    assembleAction->setShortcuts(QKeySequence::Bold);
    assembleAction->setStatusTip(tr("汇编"));

    disassembleAction = new QAction(QIcon(":/images/阴阳"), tr("&反汇编"), this);
    disassembleAction->setShortcut(tr("ctrl+shift+B"));
    disassembleAction->setStatusTip(tr("反汇编"));

    openAction = new QAction(QIcon(":/images/书"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    saveAction = new QAction(QIcon(":/images/回形针"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save"));

    saveAsAction = new QAction(QIcon(":/images/盒子"), tr("&Save as..."), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save as"));


    createAction = new QAction(tr("&新建"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("新建"));

}

void MainWindow::setConnects()
{
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile);
    connect(assembleAction, &QAction::triggered, this, &MainWindow::assemble );
    connect(disassembleAction, &QAction::triggered, this, &MainWindow::disassemble);
    //connect(createAction, &QAction::triggered, this, &MainWindow::createFile);

    connect(inputConsole, &QPlainTextEdit::textChanged,[=]() {
        this->setWindowModified(true),this->isSaved = false;
    });

    connect(AsmConsole, &QPlainTextEdit::textChanged,[=]() {
        this->setWindowModified(true),this->isSaved = false;
    });


}

void MainWindow::layoutSettings()
{
    QMenu * menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(openAction);
    menu->addAction(saveAction);
    menu->addAction(saveAsAction);

    QMenu * Compile_menu = menuBar()->addMenu(tr("&Compile"));
    Compile_menu->addAction(assembleAction);
    Compile_menu->addAction(disassembleAction);


    QToolBar * toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(saveAsAction);
    toolBar->addAction(assembleAction);
    toolBar->addAction(disassembleAction);

    //QSplitter * splitter = new QSplitter(Qt::Vertical, this);
    QSplitter * mainsplitter = new QSplitter(this);
    QSplitter * leftsplitter = new QSplitter(Qt::Vertical, mainsplitter);
    QSplitter * rightsplitter = new QSplitter(mainsplitter);
/*
    QWidget * widget = new QWidget(this);
    QHBoxLayout * layout = new QHBoxLayout(widget);
*/

    /*
    inputConsole = new QTextEdit(this);
    AsmConsole = new QTextEdit(this);
    infoConsole = new QTextEdit(this);
    */

    inputConsole = new CodeEditor(this);
    AsmConsole = new CodeEditor(this);
    infoConsole = new CodeEditor(this);

    AsmConsole->setReadOnly(true);
    infoConsole->setReadOnly(true);
    //QFont monofont("monospace");
     QFont font("Courier");
    inputConsole->setFont(font);
    AsmConsole->setFont(font);
    infoConsole->setFont(font);
/*
    inputConsole->setFontPointSize(17);
    AsmConsole->setFontPointSize(16);
    infoConsole->setFontPointSize(16);
    */

    leftsplitter->addWidget(inputConsole);
    leftsplitter->addWidget(infoConsole);
    rightsplitter->addWidget(AsmConsole);

    mainsplitter->addWidget(leftsplitter);
    mainsplitter->addWidget(rightsplitter);

    leftsplitter->setStretchFactor(1, 1);
    leftsplitter->setStretchFactor(0, 4);
    //mainsplitter->setStretchFactor(0, 1);
    setCentralWidget(mainsplitter);



/*
    layout->addWidget(inputConsole);
    layout->addWidget(AsmConsole);
    widget->setLayout(layout);
    setCentralWidget(widget);
    */


    //估计这也是 QMainWindow提供的函数
    statusBar();

}


void MainWindow::assemble()
{

    //这一步需要保存右边的文件
        QString content, process_content;
        assembler.clearError();
        if(this->isWindowModified()) {


            content = inputConsole->toPlainText();
            assembler.convert2lines(content);
            assembler.firstProcess();
            assembler.finalProcess(process_content);

            bin_content = process_content;

            assembler.printLabel();
            if(assembler.get_status()) {
                infoConsole->setPlainText(assembler.get_error());
            }
            else {
                infoConsole->setPlainText("汇编成功");
                //infoConsole->clear();
            }

            AsmConsole->setPlainText(process_content);

            if(this->outpath.isEmpty()) {
                //没有建立保存路径
                //请求用户选取一个位置
                QString user_path = QFileDialog::getSaveFileName(this,
                                                            tr("save File"),
                                                            ".",
                                                            tr("Text Files(*.bin *.coe)"));


                this->outpath = user_path;
                if(user_path.right(3) == "coe")
                    bin_coe = false;
                else
                    bin_coe = true;

                if(!user_path.isEmpty()) {
                    QFile file(user_path);
                    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                        QMessageBox::warning(this, tr("Write File"),
                                             tr("Cannot open file:\n%1").arg(user_path));
                        return;
                    }

                    QTextStream out(&file);
                    if(bin_coe == true)
                        out << AsmConsole->toPlainText();
                    else {
                        //需要输出coe文件
                        QString coe_content;
                        coe_content += "memory_initialization_radix = 16;\n";
                        coe_content += "memory_initialization_vector = \n";

                        assembler.convert2coe(process_content, coe_content);
                        out << coe_content;

                    }

                    file.close();
                }


            }
            else
            {
                //用户已有保存位置
                QFile file(outpath);
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::warning(this, tr("Write File"),
                                         tr("Cannot open file:\n%1").arg(outpath));
                    return;
                }

                QTextStream out(&file);
                if(bin_coe == true)
                    out << AsmConsole->toPlainText();
                else {
                    //需要输出coe文件

                    QString coe_content;
                    coe_content += "memory_initialization_radix = 16;\n";
                    coe_content += "memory_initialization_vector = \n";

                    assembler.convert2coe(process_content, coe_content);
                    out << coe_content;

                }


                file.close();

            }



        }
        else {
            //窗口没有改变，拿上次的结果就好
            AsmConsole->setPlainText(process_content);
        }

        /*
        QString str("");
        assembler.processAline("addi $t0, $t1, 31;", str);
        */




}

void MainWindow::disassemble()
{
    QString content, process_content;
    disassembler.clearError();
    if(this->isWindowModified()) {
        content = inputConsole->toPlainText();
        //这里要判断打开的是coe 还是 bin
        qDebug() << path;
        if(path.right(3) == "coe") {
            //做一个预处理
            QString Bincontent;
            if( !disassembler.coe2bin(content, Bincontent)) {
                infoConsole->setPlainText(disassembler.get_error());
                return;
            }
            else
                infoConsole->setPlainText("coe文件加载成功");
            content.clear();
            content = Bincontent;


        }
        disassembler.convert2lines(content);
        disassembler.firstProcess();
        disassembler.finalProcess(process_content);

        if(disassembler.get_status()) {
            infoConsole->setPlainText(disassembler.get_error());
        }
        else {
            infoConsole->setPlainText("反汇编成功");
        }

        AsmConsole->setPlainText(process_content);

        if(this->disassemble_outpath.isEmpty()) {

            QString user_path = QFileDialog::getSaveFileName(this,
                                                             tr("save File"),
                                                             ".",
                                                             tr("Text Files(*.s *.asm *.ASM)"));

            this->disassemble_outpath = user_path;


        }
        if(!disassemble_outpath.isEmpty())
        {
            QFile file(disassemble_outpath);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Write File"),
                                     tr("Cannot open file:\n%1").arg(disassemble_outpath));
                return;
            }
            QTextStream out(&file);
            out << AsmConsole->toPlainText();
            file.close();
        }




    }
    else
    {
        AsmConsole->setPlainText(process_content);
    }
}
MainWindow::~MainWindow() {}

/*
void MainWindow::open()
{
    //QMessageBox::information(this, tr("Information"), tr("Open"));


    //建立一个对话框
    //此处对话框没有设置父指针，如果 parent 为 NULL，则该对话框会作为一个顶层窗口
    QDialog dialog;
    dialog.setWindowTitle(tr("开始编译"));

    //这句话是 executable
    //生成一个应用的 模态对话框
    dialog.exec();
    qDebug() << dialog.result();

    //生成一个窗口级别的 模态对话框
    //dialog.open();

    //通过以下方法实现一个 非模态对话框
    //在堆上分配
    //QDialog *dialog = new QDialog;
    //setAttribute()函数设置对话框关闭时，自动销毁对话框
    //dialog->setAttribute(Qt::WA_DeleteOnClose);
    //dialog->setWindowTitle(tr("Hello, dialog!"));
    //dialog->show();



}
*/

void MainWindow::open()
{
    QMessageBox msgBox;
    msgBox.setText(tr("文件已改变"));
    msgBox.setInformativeText(tr("你想保存修改吗？"));
    msgBox.setDetailedText(tr("Difference"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch(ret)
    {
        case QMessageBox::Save:
            qDebug() << "文件保存";
        break;

        case QMessageBox::Discard:
            qDebug() << "discard";
        break;

        case QMessageBox::Cancel:
            qDebug() << "取消";
        break;

    }


}

void MainWindow::openFile()
{
    //本质上是一个模态对话框
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",    //dir
                                                tr("Text Files(*.s *.asm *.ASM *.bin *.coe)")); //过滤器
    this->path = path;




    if(!path.isEmpty())
    {
        QFile file(path);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Read File"), tr("不能打开文件：\n%1").arg(path));
            return;

        }
        QTextStream in(&file);
        QString content;
        while(!in.atEnd())
        {
            content += in.readLine();
            content += '\n';
        }

        inputConsole->setPlainText(content);
        file.close();

    }

}

void MainWindow::saveFile()
{
    //如果当前未打开文件
    if(this->path.isEmpty()) {
        //请求用户选取一个位置
        QString path = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    ".",
                                                    tr("Text Files(*.s *.ASM *.asm *.coe *.bin)"));

        //对当前path 进行赋值
        this->path = path;

        if(!path.isEmpty()) {
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Write File"),
                                     tr("Cannot open file:\n%1").arg(path));
                return;
            }

            QTextStream out(&file);
            out << inputConsole->toPlainText();
            isSaved = true;
            file.close();


        } else {
            QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));

        }

    } else {//若已打开某文件
        QFile file(this->path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("打开文件错误"), tr("不能打开文件：\n%1").arg(this->path));
            return;
        }

        QTextStream out(&file);
        out << inputConsole->toPlainText();
        isSaved = true;
        file.close();
    }


}

void MainWindow::saveAsFile()
{
    //请求用户选取一个位置
    //专门针对于 右边的窗口
    QString path = QFileDialog::getSaveFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.bin *.coe *.s *.asm *.ASM)"));



    if(path.right(3) == "coe")
        bin_coe = false;
    else
        bin_coe = true;
    //this->path = path;
    if(!path.isEmpty()) {
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }

        QTextStream out(&file);
        if(path.right(3) == "coe") {
            //需要输出coe文件
            QString coe_content;
            coe_content += "memory_initialization_radix = 16;\n";
            coe_content += "memory_initialization_vector = \n";

            assembler.convert2coe(bin_content, coe_content);
            out << coe_content;
        }
        else if(path.right(3) == "bin") {
            out << AsmConsole->toPlainText();
        }
        else if(path.right(1) == "s" || path.right(3) == "ASM" || path.right(3) == "asm") {
            out << AsmConsole->toPlainText();

        }

        /*
        if(bin_coe == true)
            out << AsmConsole->toPlainText();
        else {
            //需要输出coe文件
            QString coe_content;
            coe_content += "memory_initialization_radix = 16;\n";
            coe_content += "memory_initialization_vector = \n";

            assembler.convert2coe(coe_content);
            out << coe_content;

        }
        */


        file.close();

    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //文本框改变，且没有保存
    if(isWindowModified() && !isSaved)
    {

       //QMessageBox::question()

        //question的第四个重载
        bool exit = QMessageBox::question(this,
                                              tr("Quit"),
                                              tr("有未保存的内容，您确定要退出吗？"),
                                              QMessageBox::Yes | QMessageBox::No,
                                              QMessageBox::No) == QMessageBox::Yes;


        if(exit) {
            event->accept();
        } else {
            event->ignore();
        }

    } else {
        //return QMainWindow::closeEvent(event);
        event->accept();
    }
}




void EventLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->setText(QString("<center><h1>Press: (%1, %2) </h1></center>")
                  .arg(QString::number(event->x()), QString::number(event->y()))
                  );
    qDebug() << "move";


}

void EventLabel::mousePressEvent(QMouseEvent *event)
{
    this->setText(QString("<center><h1>Press: (%1, %2) </h1></center>")
                  .arg(QString::number(event->x()), QString::number(event->y()))
                  );
    qDebug() << "press";



}

void EventLabel::mouseReleaseEvent(QMouseEvent *event)
{

    QString msg;
    msg.sprintf("<center><h1>Press: (%d, %d) </h1></center>",
                event->x(), event->y());
    this->setText(msg);
    qDebug() << "Release";


}






