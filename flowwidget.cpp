/**
 * @file flowwidget.cpp
 * @author  ()
 * @brief
 * @version 0.1
 * @date 2023-08-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "flowwidget.h"

#include <QLabel>
#include <QDebug>

FlowWidget::FlowWidget(QWidget *parent)
    : QWidget{parent}
{
    m_FlowLayout = std::make_shared<FlowLayout>(10, 3);
    this->setLayout(m_FlowLayout.get());
}

void FlowWidget::addItemWidget(QWidget *_item)
{
    // resize
    double scaled = (double)m_ItemWidth / (double)_item->width();
    int width = _item->width() * scaled;
    int height = _item->height() * scaled;
    _item->setFixedSize(width, height);

    // add item
    m_FlowLayout->addWidget(_item);
    m_ItemList.append(_item);
}

void FlowWidget::addItemImage(const QString &fileName)
{
    QLabel *label;
    QPixmap pix, ret;
    int itemWidth = m_ItemWidth;

    pix.load(fileName);
    ret = pix.scaledToWidth(itemWidth);

    label = new QLabel();
    label->setPixmap(ret);

    m_FlowLayout->addWidget(label);
    m_ItemList.append(label);
    m_ImgList[m_ItemList.size()] = pix;
}

void FlowWidget::resizeItemWidth(const int _width)
{
    static int lastWidth = m_ItemWidth;
    int addSize = _width - lastWidth;

    int count = 1;
    foreach (QWidget *widget, m_ItemList)
    {
        widget->setFixedSize(widget->size().width() + addSize, widget->size().height() + addSize);
        qDebug() << __func__ << "resize" << widget->size();

        if (!m_ImgList[count].isNull())
        {
            QPixmap ret = m_ImgList[count].scaledToWidth(_width);

            QLabel *label = qobject_cast<QLabel *>(widget);
            label->setPixmap(ret);
        }
        count++;
    }

    lastWidth = _width;
}
