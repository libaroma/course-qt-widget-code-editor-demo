#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "QFileDialog"
#include "QMessageBox"
#include "QFontDialog"


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#endif
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);

    mSettings = new QSettings("settings.ini",QSettings::IniFormat);

    //初始化菜单
    initMenu();

    //初始化字体
    initFont();

    //初始化动作
    initAction();

#if !QT_CONFIG(printer)
    ui->print->setEnabled(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initFont(){
    mFontFamily = mSettings->value("font_family","Consolas").toString();
    mFontSize = mSettings->value("font_size",14).toInt();
}

void MainWindow::initAction()
{
    bool valid =ui->tabWidget->count()>0;
    ui->save_file->setEnabled(valid);
    ui->save_as->setEnabled(valid);
    ui->copy->setEnabled(valid);
    ui->paste->setEnabled(valid);
    ui->cut->setEnabled(valid);
    ui->undo->setEnabled(valid);
    ui->redo->setEnabled(valid);
}

//初始化菜单
void MainWindow::initMenu()
{
    //获取Menu
    QMenu * recent = this->findChild<QMenu *>("recent");
    //获取Action
    QList<QObject *> chLists =recent->children();
    foreach(QObject * ch,chLists){
        QAction *action = (QAction *)ch;
        //清空子菜单Action
        recent->removeAction(action);
    }

    QList<QString> lists = getHistory();


    for(int i=lists.size()-1 ;i>=0;i--){
        //生成子菜单Action
        recent->addAction(lists[i],this,&MainWindow::on_open_rencent_file);
    }

    if(lists.size()>0){
        recent->addAction("清除历史记录",this,&MainWindow::on_clear_history_triggered,QKeySequence("Ctrl+Alt+Shift+C"));
    }

}


//获取历史记录
QList<QString> MainWindow::getHistory(){
    //打开开始读
    int size =mSettings->beginReadArray("history");

    //创建返回对象
    QList<QString> lists;
    for(int i = 0;i<size;i++){
        mSettings->setArrayIndex(i);
        QString path = mSettings->value("path").toString();
        lists.append(path);
    }
    //关闭读
    mSettings->endArray();

    return lists;
}



//保存打开历史记录
void MainWindow::saveHistory(QString path){

    //获取历史
    QList<QString> lists = getHistory();
    foreach(QString str,lists){
        if(str==path){
            lists.removeOne(str);
        }
    }
    lists.append(path);

    //打开开始写入
    mSettings->beginWriteArray("history");
    for(int i =0;i<lists.size();i++){
        mSettings->setArrayIndex(i);
        //保存字符串
        mSettings->setValue("path",lists[i]);
    }

    //关闭开始写入
    mSettings->endArray();
}



//新建文件
void MainWindow::on_new_file_triggered()
{
    ui->tabWidget->addTab(new MyCodeEditor(this,QFont(mFontFamily,mFontSize)),"NewFile.xjy");
    initAction();
}


//打开最近文件
void MainWindow::on_open_rencent_file()
{
    createTab(((QAction *)sender())->text());
}

//打开文件
void MainWindow::on_open_file_triggered()
{
    createTab(QFileDialog::getOpenFileName(this,"打开文件"));
}

//创建tab
void MainWindow::createTab(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"警告","无法打开此文件:"+file.errorString());
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    //创建对象
    MyCodeEditor * codeEditor = new MyCodeEditor(this,QFont(mFontFamily,mFontSize));
    codeEditor->setPlainText(text);

    //设置文件名
    codeEditor->setFileName(fileName);
    //添加tab
    ui->tabWidget->addTab(codeEditor,fileName);
    //设置当前索引
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    file.close();
    saveHistory(fileName);
    initMenu();
    initAction();
}


//保存文件
void MainWindow::on_save_file_triggered()
{    
    //把保存交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

//另存为
void MainWindow::on_save_as_triggered()
{
    //把另存为交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        if(codeEditor->saveAsFile()){
            saveSuccessAction(codeEditor);
        }
    }
}

//复制
void MainWindow::on_copy_triggered()
{
    //把复制交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->copy();
    }
}

//粘贴
void MainWindow::on_paste_triggered()
{
    //把粘贴交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->paste();
    }
}

//剪切
void MainWindow::on_cut_triggered()
{
    //把剪切交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->cut();
    }
}

//撤销
void MainWindow::on_undo_triggered()
{
    //把撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->undo();
    }
}

//取消撤销
void MainWindow::on_redo_triggered()
{
    //把取消撤销交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
        codeEditor->redo();
    }
}

//字体
void MainWindow::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected,QFont(mFontFamily,mFontSize),this);
    if(fontSelected){
        //把字体交给CodeEditor
        MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
        if(codeEditor){
            codeEditor->setAllFont(font);
        }
        mSettings->setValue("font_family",font.family());
        mSettings->setValue("font_size",font.pointSize());
    }
}

//打印
void MainWindow::on_print_triggered()
{
    //把打印交给CodeEditor
    MyCodeEditor *codeEditor = (MyCodeEditor* )ui->tabWidget->currentWidget();
    if(codeEditor){
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
        QPrinter printDev;
#if QT_CONFIG(printdialog)
        QPrintDialog dialog(&printDev,this);
        if(dialog.exec()==QDialog::Rejected)
            return;
#endif
        codeEditor->print(&printDev);
#endif
    }
}

//关于
void MainWindow::on_about_triggered()
{
    QMessageBox::about(this,"这是我的Notepad！","这是我的Notepad，欢迎学习和使用！");
}


//退出
void MainWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}


void MainWindow::on_clear_history_triggered()
{
    mSettings->remove("history");
    initMenu();
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    MyCodeEditor * codeEditor = (MyCodeEditor*)ui->tabWidget->currentWidget();

    if(!codeEditor->checkSaved()){
        QMessageBox::StandardButton btn = QMessageBox::question(this,"警告","您还没有保存文档！是否保存？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(btn ==QMessageBox::Yes){
            if(codeEditor->saveFile())
                saveSuccessAction(codeEditor);
            return;
        }else if(btn ==QMessageBox::Cancel)
            return;
    }
    ui->tabWidget->removeTab(index);
    delete codeEditor;
    initAction();
}

void MainWindow::saveSuccessAction( MyCodeEditor * codeEditor)
{
    QString fileName  = codeEditor->getFileName();
    //保存历史
    saveHistory(fileName);
    //设置tab标题
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
    //初始化菜单
    initMenu();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->tabWidget->count()>0){
        QMessageBox::question(this,
                              "警告",
                              "有未保存的文件，确定要关闭吗？",
                              QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes?event->accept():event->ignore();
    }
}
