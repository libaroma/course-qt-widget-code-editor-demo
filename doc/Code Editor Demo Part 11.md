## 十一 代码块折叠

```c++
int start = -1;
int end =-1;
void MyCodeEditor::collapseWidgetPaintEvent(QPaintEvent *event)
{
    QPainter painter(collapseWidget);
    painter.fillRect(event->rect(),QColor(100,100,100,5));
    //    qDebug()<<"start"<<start<<"end"<<end;
    int top1 =start>-1? blockBoundingGeometry(document()->findBlockByNumber(start)).translated(contentOffset()).top():0;

    //    for(int i = start;i<(end==-1?blockCount():end);i++){

    //    }

    int bottom1 = end>-1?blockBoundingGeometry(document()->findBlockByNumber(end)).translated(contentOffset()).bottom():
                         start>-1&&end<0?blockBoundingGeometry(document()->lastBlock()).translated(contentOffset()).bottom():0;

    painter.fillRect(QRect(0,top1,25,bottom1-top1==0?blockBoundingRect(document()->findBlockByNumber(start)).height():(bottom1-top1)),QColor(120,180,227));

    QTextBlock  block = firstVisibleBlock();
    int top = blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + blockBoundingRect(block).height();
    while(block.isValid()&&top<=rect().bottom()){
        MyData * blockUserData = (MyData*)block.userData();
        if(!blockUserData) blockUserData = new MyData();

        QString text = block.text();

        text.replace(QRegExp("\\/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*\\/"),"aaa");
        text.replace(QRegExp("\\/\\/.*$"),"");
        text.replace(QRegExp("\\/\\*.*$"),"");
        while(text.indexOf(QRegExp("\\{[^{}]*\\}"))>-1){
            text.replace(QRegExp("\\{[^{}]*\\}"),"");
        }
        //        qDebug()<<"text"<<text;
        blockUserData->setStart(text.indexOf("{")>-1);
        blockUserData->setEnd(blockUserData->isEnd()||text.indexOf("}")>-1);
        block.setUserData(blockUserData);

        if(blockUserData&&block.isValid()&&block.isVisible()) {
            if(blockUserData->isStart()){
                painter.setPen(QColor(45,67,85));    //画笔
                painter.setBrush(QColor(45,67,85));   // 画刷
                QPolygon triangle;
                if(block.next().isValid()&&!block.next().isVisible()){
                    triangle.setPoints(3,10,top+4,10,top+12,14,top+8);//三点坐标
                }else{
                    triangle.setPoints(3,8,top+4,16,top+4,12,top+8);//三点坐标
                }
                painter.drawPolygon(triangle);    //画三角形

            }
        }
        if(block.isValid()&&block.userState()==1){


            blockUserData->setStart(true);

            block.setUserData(blockUserData);
            if(blockUserData&&block.isValid()&&block.isVisible()) {
                if(blockUserData->isStart()){
                    painter.setPen(QColor(45,67,85));    //画笔
                    painter.setBrush(QColor(45,67,85));   // 画刷
                    QPolygon triangle;
                    if(block.next().isValid()&&!block.next().isVisible()){
                        triangle.setPoints(3,10,top+4,10,top+12,14,top+8);//三点坐标
                    }else{
                        triangle.setPoints(3,8,top+4,16,top+4,12,top+8);//三点坐标
                    }
                    painter.drawPolygon(triangle);    //画三角形

                }
            }

            while(block.isValid()&&top<=rect().bottom()&&block.userState()==1){
                block = block.next();
                top = bottom;
                bottom = blockBoundingRect(block).height()+top;
            }
            if(block.isValid()){
                qDebug()<<"block isValid"<<block.userData();
                blockUserData = (MyData*)block.userData();
                if(!blockUserData) blockUserData = new MyData();
                blockUserData->setEnd(true);
                block.setUserData(blockUserData);
            }
        }else{
            block = block.next();
            top = bottom;
            bottom = blockBoundingRect(block).height()+top;
        }
    }

}

void MyCodeEditor::collapseMouseMoveEvent(QMouseEvent *event){
    QTextBlock block =  document()->findBlockByLineNumber(event->y()/fontMetrics().height()+verticalScrollBar()->value());
    qDebug()<<"block number "<<event->y()/fontMetrics().height()+verticalScrollBar()->value();
    QTextBlock blockUp = block;
    QTextBlock blockDown = block.next();
    start =-1;
    end =-1;
    int count =0;
    while (blockUp.isValid()&&start==-1) {
        MyData * blockUserData = (MyData*)blockUp.userData();
        if(blockUserData) {

            if(blockUserData->isEnd()){
                if(!blockUserData->isStart())
                    count++;
            }
            if(blockUserData->isStart()){
                count--;
                if(count==-1)
                    start = blockUp.blockNumber();
            }
        }
        blockUp = blockUp.previous();
    }
    count =0;
    while (blockDown.isValid()&&end==-1) {
        MyData * blockUserData = (MyData*)blockDown.userData();
        if(blockUserData) {
            if(blockUserData->isStart()){
                if(!blockUserData->isEnd())
                    count++;
            }
            if(blockUserData->isEnd()){
                count--;
                if(count==-1)
                    end = blockDown.blockNumber();
            }
        }
        blockDown = blockDown.next();
    }
    collapseWidget->update();
}

void MyCodeEditor::collapseMousePressEvent(QMouseEvent *event)
{
    if(start>-1){
        for(int i = start+1;i<=((end==-1)?(blockCount()-1):end);i++){
            document()->findBlockByNumber(i).setVisible(!document()->findBlockByNumber(i).isVisible());
        }
    }
    viewport()->update();
    lineNumberWidget->update();
    collapseWidget->update();
    document()->adjustSize();
}

void MyCodeEditor::collapseMouseLeaveEvent(QEvent *event)
{
    start = -1;
    end = -1;
    collapseWidget->update();
}

```