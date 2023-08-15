/**
 * @file flowwidget.h
 * @author  ()
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef FLOWWIDGET_H
#define FLOWWIDGET_H

#include <QWidget>
#include <map>
#include "flowlayout.h"

class FlowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowWidget(QWidget *parent = nullptr);

    /**
     * @brief 添加子项到布局中
     *
     * @param item
     */
    void addItemWidget(QWidget *_item);

    void addItemImage(const QString &fileName);

    /**
     * @brief 修改控件大小
     *
     * @param _width
     */
    void resizeItemWidth(const int _width);

signals:

private:
    std::map<int, QPixmap> m_ImgList;
    QList<QWidget *> m_ItemList;

    std::shared_ptr<FlowLayout> m_FlowLayout;

    int m_ItemWidth = 120;
};

#endif // FLOWWIDGET_H
