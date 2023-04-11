## 五 纯代码自定义组件Ⅱ

### 24 类创建

[【Qt开发项目实战——代码编辑器Code Editor Demo——24 纯代码自定义组件Ⅱ——类创建】](https://www.bilibili.com/video/BV1zL411X7L2/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- 新建类MyCodeEditor，选择Widget
- 修改继承——QPlainTextEdit
- 修改字体
- 添加行高亮
- 添加高亮

- mycodeeditor.h

```c++
#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QScrollBar>

class MyTextEditByCode : public QWidget
{
    Q_OBJECT
public:
    explicit MyTextEditByCode(QWidget *parent = nullptr);

private slots:
    void onTextEditHorizontalScrollBarChanged();
    void onTextEditVerticalScrollBarChanged();
    void onScrollBarChanged();
    void onTextBrowserHorizontalScrollBarChanged();

    void onTextChanged();

    void highlightCurrentLine();

private:
    QTextEdit *textEdit ;
    QTextBrowser *textBrowser;
    QScrollBar *scrollBar ;
    QFont mFont;

    void initWidget();
    void initFont();
    void initConnection();
    void initHighlighter();

signals:

};

#endif // MYTEXTEDITBYCODE_H

```

- mycodeeditor.cpp

```c++
#include "mycodeeditor.h"
#include "myhighlighter.h"

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    //绑定
    initConnection();
    //初始字体
    initFont();

    //高亮
    initHighlighter();

    //行高亮
    highlightCurrentLine();
}


void MyCodeEditor::initConnection()
{
    //cursor
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));
}

void MyCodeEditor::initFont()
{
    this->setFont(QFont("Consolas",14));
}

void MyCodeEditor::initHighlighter()
{
    new MyHighlighter(document());
}


void MyCodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(0,100,100,20));
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor =textCursor();

    extraSelections.append(selection);
    setExtraSelections(extraSelections);

}
```

### 25 绘制行号区域

[【Qt开发项目实战——代码编辑器Code Editor Demo——25 纯代码自定义组件Ⅱ——绘制行号区域】](https://www.bilibili.com/video/BV17M4y127PG/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h

```c++
...

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetPaintEvent(QPaintEvent *event);

...
    
protected:
    void resizeEvent(QResizeEvent *event);

private:
    ...
        
    LineNumberWidget *lineNumberWidget;
signals:

};


class LineNumberWidget :public QWidget
{
public:
    LineNumberWidget(MyCodeEditor * editor=nullptr):QWidget(editor){
        codeEditor = editor;
    }

protected:
    void paintEvent(QPaintEvent *event){
        codeEditor->lineNumberWidgetPaintEvent(event);
    }

private:
    MyCodeEditor * codeEditor;
};

...
```

- mycodeeditor.cpp

```c++
...

#include <QPainter>

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    //行号
    lineNumberWidget = new LineNumberWidget(this);

    ...

    //设置边距
    setViewportMargins(25,0,0,0);
}

...
    
void MyCodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect rect =    contentsRect();
    lineNumberWidget->setGeometry(QRect(rect.left(),rect.top(),25,rect.height()));
}


void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    painter.fillRect(event->rect(),QColor(100,100,100,100));
}

```

### 26 绘制行号文字

[【Qt开发项目实战——代码编辑器Code Editor Demo——26 纯代码自定义组件Ⅱ——绘制行号文字】](https://www.bilibili.com/video/BV1Sk4y1i7o9/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h

```c++
...
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
...
private slots:
    ...
    void updateLineNumberWidget(QRect rect,int dy);

...

private:
    ...
    int getLineNumberWidgetWidth();

    ...
}
...
```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::initConnection()
{
    ...

    //updateRequest
    connect(this,SIGNAL(updateRequest(QRect, int)),this,SLOT(updateLineNumberWidget(QRect, int)));
}

...

void MyCodeEditor::updateLineNumberWidget(QRect rect, int dy)
{
    if(dy)
        lineNumberWidget->scroll(0,dy);
    else
        lineNumberWidget->update(0,rect.y(),25,rect.height());
}

...

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    //绘制行号区域
    painter.fillRect(event->rect(),QColor(100,100,100,20));

    //拿到block
    QTextBlock block = firstVisibleBlock();

    //拿到行号
    int blockNumber =block.blockNumber();

    //拿到block的top
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();

    //拿到block的bottom
    int bottom = top +blockBoundingRect(block).height();

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(Qt::black);
        //绘制文字
        painter.drawText(0,top,25,bottom-top,Qt::AlignRight,QString::number(blockNumber+1));

        //拿到下一个block
        block = block.next();

        top = bottom;
        bottom =  top +blockBoundingRect(block).height();
        blockNumber++;
    }
}
```

### 27 行号宽度及高亮

[【Qt开发项目实战——代码编辑器Code Editor Demo——27 纯代码自定义组件Ⅱ——行号宽度及高亮】](https://www.bilibili.com/video/BV11L411m7Sq/?share_source=copy_web&vd_source=7b61313e652a9e58e9a373dd521bb6d9)

- mycodeeditor.h

```c++
...
class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
...
        
private slots:
    ...
    void updateLineNumberWidgetWidth();
    ...

...

private:
    ...
    int getLineNumberWidgetWidth();

    ...
}
...
```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    ...

    //设置边距
    updateLineNumberWidgetWidth();
}

void MyCodeEditor::initConnection()
{
    ...
        
    //blockCount
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberWidgetWidth()));

    ...
}

...

int MyCodeEditor::getLineNumberWidgetWidth()
{
    //获取宽度（合适）
    return 8+QString::number(blockCount()+1).length()*fontMetrics().horizontalAdvance(QChar('0'));
}

...

void MyCodeEditor::updateLineNumberWidget(QRect rect, int dy)
{
    if(dy)
        lineNumberWidget->scroll(0,dy);
    else
        lineNumberWidget->update(0,rect.y(),getLineNumberWidgetWidth(),rect.height());
}

void MyCodeEditor::updateLineNumberWidgetWidth()
{
    //设置边距
    setViewportMargins(getLineNumberWidgetWidth(),0,0,0);
}

...

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    ...

    //拿到当前的block的top
    int cursorTop = blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    ...

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(cursorTop==top?Qt::black:Qt::gray);
        
        ...
    }
}
```

### 28 行号点击事件Ⅰ

[【Qt开发项目实战——代码编辑器Code Editor Demo——28 纯代码自定义组件Ⅱ——行号点击事件Ⅰ】]()

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetMousePressEvent(QMouseEvent *event);

...

};

class LineNumberWidget :public QWidget{
    
...

protected:
    ...
        
    void mousePressEvent(QMouseEvent *event) override{
        //把鼠标点击任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetMousePressEvent(event);
    }
};
...

```

- mycodeeditor.cpp

```c++
...

void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}
```

### 29 行号点击事件Ⅱ

[【Qt开发项目实战——代码编辑器Code Editor Demo——29 纯代码自定义组件Ⅱ——行号点击事件Ⅱ】]()

- mycodeeditor.cpp

```c++
...
    
#include <QScrollBar>
    
...
    
void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}
```

### 30 行号滚动事件

[【Qt开发项目实战——代码编辑器Code Editor Demo——30 纯代码自定义组件Ⅱ——行号滚动事件】]()

- mycodeeditor.h

```c++
...

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ...

    void lineNumberWidgetWheelEvent(QWheelEvent *event);
...

};

class LineNumberWidget :public QWidget{
...

protected:
    ...

    void wheelEvent(QWheelEvent *event) override{
        //把滚轮任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetWheelEvent(event);
    }
...
    
};

...
```

- mycodeeditor.cpp

```c++
...

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    ...

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

...

void MyCodeEditor::lineNumberWidgetWheelEvent(QWheelEvent *event)
{
    if(event->orientation()==Qt::Horizontal){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    }else {
       verticalScrollBar()->setValue(verticalScrollBar()->value()-event->delta());
    }
    event->accept();
}
```

### 小结——完整代码

- mycodeeditor.h

```c++
#ifndef MYCODEEDITOR_H
#define MYCODEEDITOR_H

#include <QPlainTextEdit>

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MyCodeEditor(QWidget *parent = nullptr);

    void lineNumberWidgetPaintEvent(QPaintEvent * event);

    void lineNumberWidgetMousePressEvent(QMouseEvent *event);

    void lineNumberWidgetWheelEvent(QWheelEvent *event);

private slots:
    void highlightCurrentLine();
    void updateLineNumberWidget(QRect rect, int dy);
    void updateLineNumberWidgetWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initConnection();
    void initFont();
    void initHighlighter();
    int getLineNumberWidgetWidth();


    LineNumberWidget * lineNumberWidget;
signals:

};

class LineNumberWidget :public QWidget{
public:
    explicit LineNumberWidget(MyCodeEditor *editor=nullptr):QWidget(editor){
        codeEditor=editor;
    }

protected:
    void  paintEvent(QPaintEvent *event) override{
        //把绘制任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetPaintEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override{
        //把鼠标点击任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetMousePressEvent(event);
    }

    void wheelEvent(QWheelEvent *event) override{
        //把滚轮任务提交给MyCodeEditor
        codeEditor->lineNumberWidgetWheelEvent(event);
    }

private:
    MyCodeEditor *codeEditor;
};

#endif // MYCODEEDITOR_H
```

- mycodeeditor.cpp

```c++
#include "mycodeeditor.h"
#include "myhighlighter.h"

#include <QPainter>
#include <QDebug>
#include <QScrollBar>

MyCodeEditor::MyCodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberWidget = new LineNumberWidget(this);
    //绑定
    initConnection();

    //初始字体
    initFont();

    //高亮
    initHighlighter();

    //行高亮
    highlightCurrentLine();

    //设置边距
    updateLineNumberWidgetWidth();

    setLineWrapMode(QPlainTextEdit::NoWrap);
}

void MyCodeEditor::initConnection()
{
    //cursor
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(highlightCurrentLine()));

    //blockCount
    connect(this,SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumberWidgetWidth()));

    //updateRequest
    connect(this,SIGNAL(updateRequest(QRect, int)),this,SLOT(updateLineNumberWidget(QRect, int)));
}

void MyCodeEditor::initFont()
{
    this->setFont(QFont("Consolas",14));
}

void MyCodeEditor::initHighlighter()
{
    new MyHighlighter(document());
}

int MyCodeEditor::getLineNumberWidgetWidth()
{
    //获取宽度（合适）
    return 8+QString::number(blockCount()+1).length()*fontMetrics().horizontalAdvance(QChar('0'));
}


void MyCodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(0,100,100,20));
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor =textCursor();

    extraSelections.append(selection);
    setExtraSelections(extraSelections);

}

void MyCodeEditor::updateLineNumberWidget(QRect rect, int dy)
{
    if(dy)
        lineNumberWidget->scroll(0,dy);
    else
        lineNumberWidget->update(0,rect.y(),getLineNumberWidgetWidth(),rect.height());
}

void MyCodeEditor::updateLineNumberWidgetWidth()
{
    //设置边距
    setViewportMargins(getLineNumberWidgetWidth(),0,0,0);
}

void MyCodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    lineNumberWidget->setGeometry(0,0,getLineNumberWidgetWidth(),contentsRect().height());
}

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberWidget);
    //绘制行号区域
    painter.fillRect(event->rect(),QColor(100,100,100,20));

    //拿到block
    QTextBlock block = firstVisibleBlock();

    //拿到行号
    int blockNumber =block.blockNumber();

    //拿到当前的block的top
    int cursorTop = blockBoundingGeometry(textCursor().block()).translated(contentOffset()).top();

    //拿到block的top
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();

    //拿到block的bottom
    int bottom = top +blockBoundingRect(block).height();

    while(block.isValid()&&top<=event->rect().bottom()){
        //设置画笔颜色
        painter.setPen(cursorTop==top?Qt::black:Qt::gray);
        //绘制文字
        painter.drawText(0,top,getLineNumberWidgetWidth()-3,bottom-top,Qt::AlignRight,QString::number(blockNumber+1));

        //拿到下一个block
        block = block.next();

        top = bottom;
        bottom =  top +blockBoundingRect(block).height();
        blockNumber++;
    }
}

void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event)
{
    setTextCursor(QTextCursor(document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value())));
}

void MyCodeEditor::lineNumberWidgetWheelEvent(QWheelEvent *event)
{
    if(event->orientation()==Qt::Horizontal){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->delta());
    }else {
       verticalScrollBar()->setValue(verticalScrollBar()->value()-event->delta());
    }
    event->accept();
}
```
