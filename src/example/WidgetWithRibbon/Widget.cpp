#include "Widget.h"
#include "ui_Widget.h"
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include "SARibbonPannel.h"
#include "SARibbonMainWindow.h"
Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    // 注意：ui文件中有个QVBoxLayout布局
    ui->setupUi(this);
    // 直接创建SARibbonBar
    SARibbonBar* ribbonbar = new SARibbonBar(this);
    // QWidget模式下，没有必要再显示标题
    ribbonbar->setTitleVisible(false);
    // QWidget模式下，直接使用紧凑模式效果更好
    ribbonbar->setRibbonStyle(SARibbonBar::RibbonStyleCompactThreeRow);
    // 取消applicationbutton
    ribbonbar->setApplicationButton(nullptr);
    //设置主题，这里虽然没用到SARibbonMainWindow，但Ribbon的主题是SARibbonMainWindow中定义的，因此要引入SARibbonMainWindow.h
    sa_set_ribbon_theme(ribbonbar, SARibbonMainWindow::RibbonThemeOffice2013);

    // QWidgets设置一个QVBoxLayout，把窗口放到QVBoxLayout的第二个布局中，第一个布局给SARibbonBar
    // 这样，SARibbonBar就会在最上面
    ui->verticalLayout->insertWidget(0, ribbonbar);

    buildRibbon(ribbonbar);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buildRibbon(SARibbonBar* bar)
{
    SARibbonCategory* page1 = new SARibbonCategory();
    page1->setCategoryName("page1");
    SARibbonPannel* pannel1 = new SARibbonPannel("pannel1", page1);
    page1->addPannel(pannel1);
    pannel1->addLargeAction(createAction("save", ":/icon/icon/save.svg"));
    pannel1->addLargeAction(createAction("open", ":/icon/icon/folder-star.svg"));
    pannel1->addSmallAction(createAction("action1", ":/icon/icon/action.svg"));
    pannel1->addSmallAction(createAction("action2", ":/icon/icon/action2.svg"));
    SARibbonPannel* pannel2 = new SARibbonPannel("pannel2", page1);
    page1->addPannel(pannel2);
    pannel2->addLargeAction(createAction("setting", ":/icon/icon/customize0.svg"));
    pannel2->addLargeAction(createAction("windowsflag", ":/icon/icon/windowsflag-normal.svg"));
    bar->addCategoryPage(page1);
}

QAction* Widget::createAction(const QString& text, const QString& iconurl)
{
    QAction* act = new QAction(this);
    act->setText(text);
    act->setIcon(QIcon(iconurl));
    act->setObjectName(text);
    return act;
}