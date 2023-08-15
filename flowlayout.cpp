/**
 * @file flowlayout.cpp
 * @author  ()
 * @brief
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "flowlayout.h"
#include <QWidget>
#include <QDebug>

FlowLayout::FlowLayout(QWidget *parent, int _margin, int _minSpacing, int _verticalSpacing)
    : QLayout(parent), m_MinSpacing(_minSpacing), m_VerticalSpacing(_verticalSpacing)
{
    setContentsMargins(_margin, _margin, _margin, _margin);
}
FlowLayout::FlowLayout(int _margin, int _minSpacing, int _verticalSpacing)
    : m_MinSpacing(_minSpacing), m_VerticalSpacing(_verticalSpacing)
{
    setContentsMargins(_margin, _margin, _margin, _margin);
}

FlowLayout::~FlowLayout()
{
    if (!m_ItemList.isEmpty())
    {
        for (QLayoutItem *item : m_ItemList)
        {
            delete item;
        }
    }
}

void FlowLayout::addItem(QLayoutItem *_item)
{

    m_ItemList.append(_item);
}

int FlowLayout::count() const
{
    return m_ItemList.count();
}

QLayoutItem *FlowLayout::itemAt(int _index) const
{
    return m_ItemList.value(_index);
}

QLayoutItem *FlowLayout::takeAt(int _index)
{
    if (_index >= 0 && _index < m_ItemList.size())
    {
        return m_ItemList.takeAt(_index);
    }
    return nullptr;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return Qt::Orientation::Vertical;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int _width) const
{
    int height = updateLayout(QRect(0, 0, _width, 0));
    return height;
}

void FlowLayout::setGeometry(const QRect &_rect)
{
    // 计算布局项目的几何形状
    QLayout::setGeometry(_rect);
    updateLayout(_rect);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    for (const QLayoutItem *item : qAsConst(m_ItemList))
    {
        size = size.expandedTo(item->minimumSize());
    }

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

int FlowLayout::updateLayout(const QRect &_widgetSize) const
{
    if (m_ItemList.isEmpty())
    {
        return -1;
    }

    // 获取可用面积
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    // 可用大小
    QRect effectiveRect = _widgetSize.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();

    int width = m_ItemList.first()->sizeHint().width();                          // 控件宽
    int numOfLine = effectiveRect.width() / (width + this->horizontalSpacing()); // 一行最大控件数量
    if (numOfLine > m_ItemList.size())
    {
        numOfLine = m_ItemList.size();
    }
    if (numOfLine < 1)
    {
        numOfLine = 1;
    }

    int spacingOfControl = (effectiveRect.width() / numOfLine) - width; // 控件间距

    qDebug() << __func__ << "width" << effectiveRect.width() << ";num of Line" << numOfLine << ";spacing of control" << spacingOfControl;

    QVector<QPoint> HeightList;
    HeightList.resize(numOfLine);
    for (int i = 0; i < numOfLine; ++i)
    {
        HeightList[i].setX(x + i * (width + spacingOfControl)); // 获取控件行的x坐标
        HeightList[i].setY(y);                                  // 获取控件行的y坐标
    }

    int index = 0;
    for (QLayoutItem *item : qAsConst(m_ItemList))
    {
        const QWidget *widget = item->widget();

        // 调制坐标
        item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        // 保存列高
        y = HeightList[index].y() + item->sizeHint().height() + this->verticalSpacing();
        HeightList[index].setY(y);

        // 下一个item坐标
        for (int i = 0; i < numOfLine; ++i)
        {
            if (HeightList[i].y() < y)
            {
                y = HeightList[i].y();
                index = i;
            }
        }
        x = HeightList[index].x();
    }

    return 0;
}

int FlowLayout::horizontalSpacing() const
{
    if (m_MinSpacing >= 0)
    {
        return m_MinSpacing;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int FlowLayout::verticalSpacing() const
{
    if (m_VerticalSpacing >= 0)
    {
        return m_VerticalSpacing;
    }
    else
    {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

int FlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent)
    {
        return -1;
    }

    // 当父是QWidget=>顶层布局的默认间距为pm样式。
    else if (parent->isWidgetType())
    {
        QWidget *pw = qobject_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    }
    // 当父为QLayout=>子布局的默认间距由父布局的间距来确定。
    else
    {
        return static_cast<QLayout *>(parent)->spacing();
    }
}
