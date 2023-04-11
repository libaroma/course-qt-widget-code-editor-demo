## 一 项目创建

### 01 项目创建

[【Qt开发项目实战——代码编辑器Code Editor Demo——01 项目创建】 ](https://www.bilibili.com/video/BV1Xv4y1L7U3/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 复制上一个项目
- 重命名为code editor demo
- 打开项目

### 02 添加Tab标签页

[【Qt开发项目实战——代码编辑器Code Editor Demo——02 添加Tab标签页】 ](https://www.bilibili.com/video/BV15v4y1j7qa/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- ui界面中插入Tab Widget
- 在mainwindow.cpp中，设为中心组件：

```c++
//mainwindow.cpp

...
    
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);
    
    ...
        
}

...
    
```

### 03 新建Tab标签页

[【Qt开发项目实战——代码编辑器Code Editor Demo——03 新建Tab标签页】 ](https://www.bilibili.com/video/BV1Vm4y1k76j/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

```c++
...

//新建文件
void MainWindow::on_new_file_triggered()
{
    ui->tabWidget->addTab(new QTextEdit(),"NewTab.xjy");

//    qDebug()<<"Start Create New File ...";
//    currentFile.clear();
//    ui->textEdit->setText("");
}

...
```

### 04 修改项目名称

[【Qt开发项目实战——代码编辑器Code Editor Demo——04 修改项目名称】 ](https://www.bilibili.com/video/BV1No4y1B7qN/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 找到.pro文件，修改名称，删除.pro.user文件
- 重新打开项目

### 

