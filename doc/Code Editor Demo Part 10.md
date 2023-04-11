## 十 代码补全提示

### 78 代码补全提示——补全括号

```c++

void MyCodeEditor::keyPressEvent(QKeyEvent *e){
    QPlainTextEdit::keyPressEvent(e);

    switch (e->key())
    {
    case Qt::Key_ParenLeft:{
        textCursor().insertText(")");
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Left);
        setTextCursor(cursor);
        break;
    }
    case Qt::Key_BracketLeft:{
        textCursor().insertText("]");
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Left);
        setTextCursor(cursor);
        break;
    }
    case Qt::Key_BraceLeft:{
        textCursor().insertText("}");
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Left);
        setTextCursor(cursor);
        break;
    }
    }

}
```

### 79 代码补全提示——设置Completer

```c++

void MyCodeEditor::initCompleter()
{
    mCompleter = new QCompleter();
    QStringList list;
    list<<"completer"<<"english"<<"list"<<"last"<<"lab"<<"highlightCurrentLine"<<"interesting"<<"initHighlighter";

    list.sort(Qt::CaseInsensitive);

    QStringListModel * model = new QStringListModel(list,mCompleter);


    mCompleter->setModel(model);
    mCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    mCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    mCompleter->setWrapAround(false);


    mCompleter->popup()->setFont(QFont("Consolas",14));
    mCompleter->popup()->setStyleSheet("QAbstractItemView{selection-background-color: #00AAAA; }");

    //    QCursor cursor = mCompleter->popup()->cursor();
    //    mCompleter->popup()->setCursor(cursor);

    mCompleter->setWidget(this);
    mCompleter->setCompletionMode(QCompleter::PopupCompletion);

    connect(mCompleter,SIGNAL(activated(const QString &)),this,SLOT(insertCompletion(const QString &)));
}

void MyCodeEditor::insertCompletion(const QString &completion)
{
    if(mCompleter->widget()!=this) return ;
    QTextCursor cursor = textCursor();

    int length = completion.length()-mCompleter->completionPrefix().length();

    cursor.movePosition(QTextCursor::Left);
    cursor.movePosition(QTextCursor::EndOfWord);

    cursor.insertText(completion.right(length));

    setTextCursor(cursor);

}

```



### 80 代码补全提示——显示补全提示代码Ⅰ

```c++

void MyCodeEditor::keyPressEvent(QKeyEvent *event)
{
    QPlainTextEdit::keyPressEvent(event);
    switch(event->key()){
    case Qt::Key_ParenLeft:
        textCursor().insertText(")");
        break;
    case Qt::Key_BracketLeft:
        textCursor().insertText("]");
        break;
    case Qt::Key_BraceLeft:
        textCursor().insertText("}");
        break;
    case Qt::Key_QuoteDbl:
        textCursor().insertText("\"");
        break;
    case Qt::Key_Apostrophe:
        textCursor().insertText("'");
        break;
    }
    if(event->key()==Qt::Key_ParenLeft||
            event->key()==Qt::Key_BracketLeft||
            event->key()==Qt::Key_BraceLeft||
            event->key()==Qt::Key_QuoteDbl||
            event->key()==Qt::Key_Apostrophe){
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Left);
        setTextCursor(cursor);
    }

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString prefix = cursor.selectedText();
    QString endSign = "~!@#$%^&*()_-+=\\/,.。；？?‘'\"{}[]<>";
    if(endSign.contains(event->text().right(1))||prefix.length()<2){
        mCompleter->popup()->hide();
        return;
    }

    if(mCompleter->completionPrefix()!=prefix){
      mCompleter->setCompletionPrefix(prefix);
      mCompleter->popup()->setCurrentIndex(mCompleter->completionModel()->index(0,0));
    }
    QRect rect = cursorRect();
    rect.setWidth(mCompleter->popup()->sizeHintForColumn(0)+mCompleter->popup()->verticalScrollBar()->sizeHint().width());

    mCompleter->complete(rect);
}
```

### 81 代码补全提示——显示补全提示代码Ⅱ

```c++
void MyCodeEditor::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_ParenLeft:
        textCursor().insertText(")");
        break;
    case Qt::Key_BracketLeft:
        textCursor().insertText("]");
        break;
    case Qt::Key_BraceLeft:
        textCursor().insertText("}");
        break;
    case Qt::Key_QuoteDbl:
        textCursor().insertText("\"");
        break;
    case Qt::Key_Apostrophe:
        textCursor().insertText("'");
        break;
    case Qt::Key_Enter:
    case Qt::Key_Backtab:
    case Qt::Key_Return:
    case Qt::Key_Escape:
    case Qt::Key_Tab:
        if(mCompleter->popup()->isVisible()){
            event->ignore();
            return;
        }
    }
    //Alt + C
    bool isShortCut = (event->modifiers()&Qt::AltModifier)&&event->key()==Qt::Key_C;

    if(!isShortCut)
        QPlainTextEdit::keyPressEvent(event);

    if(event->key()==Qt::Key_ParenLeft||
            event->key()==Qt::Key_BracketLeft||
            event->key()==Qt::Key_BraceLeft||
            event->key()==Qt::Key_QuoteDbl||
            event->key()==Qt::Key_Apostrophe){
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::Left);
        setTextCursor(cursor);
    }

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString prefix = cursor.selectedText();
    QString endSign = "~!@#$%^&*()_-+=\\/,.。；？?‘'\"{}[]<>";
    if(!isShortCut&&(endSign.contains(event->text().right(1))||prefix.length()<2)){
        mCompleter->popup()->hide();
        return;
    }

    if(mCompleter->completionPrefix()!=prefix){
      mCompleter->setCompletionPrefix(prefix);
      mCompleter->popup()->setCurrentIndex(mCompleter->completionModel()->index(0,0));
    }
    QRect rect = cursorRect();
    rect.setWidth(mCompleter->popup()->sizeHintForColumn(0)+mCompleter->popup()->verticalScrollBar()->sizeHint().width());

    mCompleter->complete(rect);
}
```

### 82 代码补全提示——读取文件



### 83 代码补全提示——动态添加提示

