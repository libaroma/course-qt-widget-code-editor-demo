#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycodeeditor.h"

#include <QMainWindow>

#include "QSettings"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveSuccessAction( MyCodeEditor * codeEditor);

protected:

    void closeEvent(QCloseEvent *event);


private slots:
    void on_new_file_triggered();

    void on_open_file_triggered();

    void on_save_file_triggered();

    void on_save_as_triggered();

    void on_paste_triggered();

    void on_cut_triggered();

    void on_copy_triggered();

    void on_font_triggered();

    void on_about_triggered();

    void on_undo_triggered();

    void on_redo_triggered();

    void on_exit_triggered();

    void on_print_triggered();

    void on_clear_history_triggered();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;

    QSettings * mSettings;
    QString mFontFamily;
    int mFontSize;

    void initMenu();
    void initFont();
    void initAction();


    void on_open_rencent_file();
    void saveHistory(QString path);
    QList<QString> getHistory();

    void createTab(QString fileName);



};
#endif // MAINWINDOW_H
