## 八 文件目录

### 47 文件树显示

```c++
...
    
#include <QFileSystemModel>

...

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ...

    //初始化文件目录
    initTreeView();

    ...
}

...

void MainWindow::initTreeView()
{
    //创建Model
    QFileSystemModel * mFileSystemModel = new QFileSystemModel();
    //设置根目录
    mFileSystemModel->setRootPath("E:/");
    //设置Model
    ui->treeView->setModel(mFileSystemModel);
    //设置根目录
    ui->treeView->setRootIndex(mFileSystemModel->index("E:/"));
}

...
```

### 48 隐藏多余列

```c++
...

void MainWindow::initTreeView()
{
    ...

    //隐藏列
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->setColumnHidden(3,true);
    
    //隐藏header
    ui->treeView->setHeaderHidden(true);

    ...

}

...
```

### 49 右键菜单

```c++
...

void MainWindow::initTreeView()
{
    ...

    //设置右键菜单
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    //添加connect
    //添加右键信号事件
    connect(ui->treeView,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(showCustomContextMenu()));

}

//treeview的右键事件
void MainWindow::showCustomContextMenu()
{
    QMenu menu(this);
    menu.addAction("新建文件(New File)");
    menu.addAction("新建文件夹(New Folder)");
    menu.addAction("重命名(Rename File)");
    menu.addAction("删除文件(Remove File)");
    menu.exec(QCursor::pos());
}

...
```

### 50 根据节点确定菜单

```c++
...

//treeview的右键事件
void MainWindow::showCustomContextMenu()
{
    QModelIndex index = ui->treeView->currentIndex();
    QMenu menu(this);
    if(mFileSystemModel->isDir(index)){
        menu.addAction("新建文件(New File)");
        menu.addAction("新建文件夹(New Folder)");
    }else{
        menu.addAction("重命名(Rename File)");
        menu.addAction("删除文件(Remove File)");
    }
    menu.exec(QCursor::pos());
}

...
```

### 51 文件重命名

- myfiesystemmodel.cpp

```c++
...

Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}
```

- mainwindow.cpp

```c++
...

void MainWindow::initTreeView()
{
    //创建Model
    * mFileSystemModel = new MyFileSystemModel();
    
    ...
}

...
    
//treeview的右键事件
void MainWindow::showCustomContextMenu(const QPoint &pos)
{
    ...
        
    if(mFileSystemModel->isDir(index)){
        ...
    }else{
        menu.addAction("重命名(Rename File)",[=](){
            //编辑节点
            ui->treeView->edit(index);
        });
        
        ...
    }
    ...
}

...
```

### 52 文件删除

```c++
...

//treeview的右键事件
void MainWindow::showCustomContextMenu(const QPoint &pos)
{
    ...
        
    if(mFileSystemModel->isDir(index)){
        
        ...
            
    }else{
        ...
            
        menu.addAction("删除文件(Remove File)",[=](){
            //删除文件
            //文件名称
            QString fileName = mFileSystemModel->fileName(index);
            //文件路径
            QString filePath = mFileSystemModel->filePath(index);
            if(QMessageBox::Yes==QMessageBox::question(this,"是否删除","请确认是否删除文件：\n   "+fileName+"\n此操作不可恢复!",QMessageBox::Yes|QMessageBox::No)){
                //删除
                if(!QFile::remove(filePath))
                    QMessageBox::critical(this,"失败","删除文件：\n   "+fileName+"\n失败!可能没有权限或文件不存在！");
            }
        });
    }
    
    ...
}

...
```

### 53 取消文件夹可编辑

- myfilesystemmodel.cpp

```c++
...

Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex &index) const
{
    //文件夹不可编辑
    return isDir(index)?(Qt::ItemIsSelectable|Qt::ItemIsEnabled):
                        (Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
}

int MyFileSystemModel::columnCount(const QModelIndex &parent) const
{
    //只显示一列
    return 1;
}

```

### 54 新建文件

```c++
...
    
#include <QDateTime>

...

//treeview的右键事件
void MainWindow::showCustomContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->treeView->indexAt(pos);
    QMenu menu(this);
    if(mFileSystemModel->isDir(index)){
        //文件路径
        QString filePath = mFileSystemModel->filePath(index);
        if(filePath.isEmpty()) filePath = "E:/";
        menu.addAction("新建文件(New File)",[=](){
            QString fileName = filePath+"/新建文件"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")+".xjy";
            QFile file(fileName);
            if(!file.open(QIODevice::ReadWrite)){
                QMessageBox::critical(this,"失败","创建新文件失败!可能没有权限或文件已经存在！");
            }
            file.close();
        });
        
        ...
    }
    
    ...
}

...
```

### 55 新建文件夹

```c++

//treeview的右键事件
void MyTreeView::showCustomContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);
    QMenu menu(this);
    if(mFileSystemModel->isDir(index)){
        //文件路径
        QString filePath = mFileSystemModel->filePath(index);
        ...
        menu.addAction("新建文件夹(New Folder)",this,[=](){
            QDir dir(filePath);
            QString dirName = "新建文件夹"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
            if(!dir.exists(dirName))
                dir.mkdir(dirName);

        });

        menu.addSeparator();

        menu.addAction("重命名文件夹(Rename Dir)",this,[=](){
            //编辑节点
            edit(index);
        });
    }

    ...
}
```



### 56 文件夹重命名

```c++

//treeview的右键事件
void MyTreeView::showCustomContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);
    QMenu menu(this);
    if(mFileSystemModel->isDir(index)){
        ...

        menu.addAction("重命名文件夹(Rename Dir)",this,[=](){
            //编辑节点
            edit(index);
        });
    }

    ...
}
```

### 57 双击打开文件

```c++
void MainWindow::initTreeView(){

    ...
        
    //取消双击编辑
    setEditTriggers(QTreeView::NoEditTriggers);

    //绑定双击事件
    connect(this,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(onTreeViewDoubleClicked(const QModelIndex &)));

}

void MyTreeView::onTreeViewDoubleClicked(const QModelIndex &index)
{
    //打开文件操作
    //判断是否是文件
    if(!mFileSystemModel->isDir(index)){
        QString filePath = mFileSystemModel->filePath(index);
        createTab(filePath);
    }
}
```

### 58 水平分割布局

- ui布局中打破原有布局，选中两个组件，点击水平分割布局即可

- 设置分割比例

```c++
void MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    ...
        
    //设置分割比距比例
    QList<int> sizeLists;
    sizeLists<<1000<<4000;
    setSizes(sizeLists);

    setHandleWidth(0);
}
```

### 59 去掉组件边框

- ui布局中设置frameshape为NoFrame

### 60 打开文件目录

```c++
//打开文件目录
void MainWindow::on_open_dir_triggered()
{
    QString dirFromSetttings = mSettings->value("dir",mDir).toString();
    QString dir = QFileDialog::getExistingDirectory(this,"选择文件夹",dirFromSetttings,QFileDialog::ShowDirsOnly);
    if(dir.isEmpty()) return;
    mSettings->setValue("config/dir",dir);
    mDir = dir;
    mSplitterLayout->setDir(mDir);
    //设置根目录
    setRootIndex(mFileSystemModel->index(mDir));
}
```



### 61 重写新建文件

```c++
void MainWindow::on_new_file_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();
    QString filePath =   mFileSystemModel->filePath(index);
    if(!mFileSystemModel->isDir(index)){
        filePath = filePath.left(filePath.length()-mFileSystemModel->fileName(index).length());
    }
    if(filePath.isEmpty()) return;
    QString fileName = filePath+(filePath.endsWith("/")?"":"/")+"新建文件"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss")+".xjy";
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::critical(this,"失败","创建新文件失败!可能没有权限或文件已经存在！");
    }
    file.close();

    createTab(fileName);
}

void MySplitterLayout::createTab(const QString &filePath)
{
    QFile file(filePath);
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
    codeEditor->setFileName(filePath);
    //添加tab
    ui->tabWidget->addTab(codeEditor,filePath);
    //设置当前索引
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    file.close();

    saveHistory(filePath);
    initMenu();
    initAction();

}
```

### 62 避免文件重复打开

```c++
void MySplitterLayout::createTab(const QString &filePath)
{
    ...

    int tabCount= ui->tabWidget->count();
    for(int index =0;index<tabCount;index++){
        qDebug()<<ui->tabWidget->tabText(index);
        if(ui->tabWidget->tabText(index)==filePath){
            return;
        }
    }
    ...
}
```

### 63 修复文件夹重命名漏洞

```c++
void MainWindow::onModelDataChanged(const QModelIndex &index)
{
    setTreeViewModel();
}
void MainWindow::setTreeViewModel()
{
    if(mFileSystemModel) {
        delete mFileSystemModel;
    }
    //创建Model
    mFileSystemModel = new MyFileSystemModel();
    //设置根目录
    mFileSystemModel->setRootPath(mDir);
    //设置Model
    setModel(mFileSystemModel);

    //设置根目录
    setRootIndex(mFileSystemModel->index(mDir));

    //绑定dataChanged
    connect(mFileSystemModel,SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),this,SLOT(onModelDataChanged(const QModelIndex &)));

}
```



### 64 复制路径和文件名

```c++
//treeview的右键事件
void MainWindow::showCustomContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);
    QClipboard * clipboard =QApplication::clipboard();
    QMenu menu(this);
    if(mFileSystemModel->isDir(index)){
        ...
    }else{
        ...

        menu.addSeparator();
        menu.addAction("复制文件名(Copy File Name)",this,[=](){
            //复制文件名
            clipboard->setText(mFileSystemModel->fileName(index));

        });
    }

    menu.addAction("复制全路径(Copy Full Path)",this,[=](){
        //复制全路径
        clipboard->setText(mFileSystemModel->filePath(index));
    });

    menu.exec(QCursor::pos());
}
```

### 65 修复文件重命名折叠问题

```c++
void MainWindow::onModelDataChanged(const QModelIndex &index)
{
    if(!mFileSystemModel->isDir(index))
        return;
    setTreeViewModel();
}
```

### 66 修改label背景颜色及窗口尺寸

```c++
void MainWindow::initTreeView(){
    ...
        
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(250,250,250));
    label->setPalette(palette);
    label->setAutoFillBackground(true);
    
    ...
}
```

### 67 重命名已打开的文件

```c++
void MainWindow::onModelDataChanged(const QModelIndex &index)
{
    if(!mFileSystemModel->isDir(index))
        if(!tempFilePath.isEmpty()){
            int count = tabWidget->count();
            for(int i = 0; i<count ; i++){
                if(tempFilePath==ui->tabWidget->tabText(i)){
                    QString filePath = mFileSystemModel->filePath(index);
                    ui->tabWidget->setTabText(i,filePath);
                    tempFilePath ="";
                    MyCodeEditor * codeEditor =( MyCodeEditor *) ui->tabWidget->widget(i);
                    if(codeEditor)
                        codeEditor->setFileName(filePath);
                    return;
                }
            }
            return;
        }
    setTreeViewModel();
}
```

### 68 打开CMD和文件资源管理器

```c++
//treeview的右键事件
void MainWindow::showCustomContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);
    ...

    QString filePath =mFileSystemModel->filePath(index);
    if(!mFileSystemModel->isDir(index)) filePath = filePath.left(filePath.length()-mFileSystemModel->fileName(index).length());

    menu.addAction("在文件资源管理器中显示(Show In Explorer)",this,[=](){
        //在文件资源管理器中显示
        QDesktopServices::openUrl(QUrl(filePath));
    });

    menu.addAction("打开命令提示符(Open CMD)",this,[=](){
        //打开命令提示符
        QProcess * process = new QProcess(this);
        process->startDetached("cmd",QStringList()<<"/c"<<"cd "+filePath+" && start cmd");
        delete process;
    });

    ...
}
```











