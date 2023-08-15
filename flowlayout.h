/**
 * @file flowlayout.h
 * @author  ()
 * @brief
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QLayout>
#include <QStyle>

class FlowLayout : public QLayout
{
    Q_OBJECT

public:
    explicit FlowLayout(QWidget *parent, int _margin = -1, int _minSpacing = -1, int _verticalSpacing = -1);
    explicit FlowLayout(int _margin = -1, int _minSpacing = -1, int _verticalSpacing = -1);
    ~FlowLayout();

    /**
     * @brief 添加子项
     * @param item
     */
    void addItem(QLayoutItem *_item) override;
    /**
     * @brief 返回子项计数
     * @return int
     */
    int count() const override;
    /**
     * @brief 返回index所在项
     *
     * @param _index
     * @return QLayoutItem*
     */
    QLayoutItem *itemAt(int _index) const override;

    /**
     * @brief 移除index所在项
     *
     * @param _index
     * @return QLayoutItem*
     */
    QLayoutItem *takeAt(int _index) override;

    /**
     * @brief 获取扩展方向
     *
     * @return Qt::Orientations
     */
    Qt::Orientations expandingDirections() const override;

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool hasHeightForWidth() const override;
    /**
     * @brief
     *
     * @param _width
     * @return int
     */
    int heightForWidth(int _width) const override;

    /**
     * @brief 调制布局
     *
     * @param _rect
     */
    void setGeometry(const QRect &_rect) override;

    /**
     * @brief 大小提示
     *
     * @return QSize
     */
    QSize sizeHint() const override;
    /**
     * @brief 返回组件大小最小值
     *
     * @return QSize
     */
    QSize minimumSize() const override;

private:
    /**
     * @brief 更新显示
     *
     * @param rect
     * @return height
     */
    int updateLayout(const QRect &_widgetSize) const;

    /**
     * @brief
     *
     * @return int
     */
    int horizontalSpacing() const;
    /**
     * @brief
     *
     * @return int
     */
    int verticalSpacing() const;
    /**
     * @brief 
     * 
     * @return int 
     */
    int smartSpacing(QStyle::PixelMetric pm) const;

private:
    QList<QLayoutItem *> m_ItemList; // layout的子项

    int m_MinSpacing;
    int m_VerticalSpacing;
};

#endif // FLOWLAYOUT_H
