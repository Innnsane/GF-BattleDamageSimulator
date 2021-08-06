#include "calculation.h"
#include "ui_calculation.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>
#include <QKeyEvent>
#include <QComboBox>
#include <QCheckBox>
#include <string.h>
#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QtGui>


struct doll_info doll[11];
struct doll_info doll_reserve[10];
struct condition_info condition;
struct enemy_info enemy;
static int arr_edit[35]={0};
static int arr_edit_i;
int fairy_id = 0;
int fairy_gift_id = 0;

calculation::calculation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calculation)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("白矢 少女前线阵型模拟器"));
    setWindowIcon(QIcon(":/new/prefix1/WhiteArrow.png"));

    clear_all();
    doll_select();
    buff_set();
    condition_enemy_set();
    fairy_select();

    connect( ui->Go_pushButton , &QPushButton::pressed ,this ,
             [=]()
            {
                free(damage);
                free(damage_together);
                Fw = 416;
                calculate();
                ui->label_of->setNum(of);
                ui->label_out->setNum(out);
            });

    ui->debug_button->setVisible(true);
    connect( ui->debug_button , &QPushButton::pressed ,this ,
             [=]()
            {
                free(damage);
                free(damage_together);
                Fw = 1;
                calculate();
            });

    ui->position_1->installEventFilter(this);
    ui->position_2->installEventFilter(this);
    ui->position_3->installEventFilter(this);
    ui->position_4->installEventFilter(this);
    ui->position_5->installEventFilter(this);
    ui->position_6->installEventFilter(this);
    ui->position_7->installEventFilter(this);
    ui->position_8->installEventFilter(this);
    ui->position_9->installEventFilter(this);
}

calculation::~calculation()
{
    delete ui;
}

void calculation::doll_select()
{
    static int type=0,star=0;

    QButtonGroup* stargroup; //建立星级按键组
    stargroup = new QButtonGroup( this );

    stargroup->addButton( ui->star_1 , 1 );
    stargroup->addButton( ui->star_2 , 2 );
    stargroup->addButton( ui->star_3 , 3 );
    stargroup->addButton( ui->star_4 , 4 );
    stargroup->addButton( ui->star_5 , 5 );
    stargroup->addButton( ui->star_6 , 6 );

    connect( stargroup , QOverload<int>::of(&QButtonGroup::buttonClicked) ,
             [=](int id ) mutable{{ //改变选择数值并呈现对应doll
                star=id ;
                doll_present(id,type);
              }});

    QButtonGroup* typegroup;
    typegroup = new QButtonGroup( this );

    typegroup->addButton( ui->type_HG , 1 );
    typegroup->addButton( ui->type_SMG , 2 );
    typegroup->addButton( ui->type_RF , 3 );
    typegroup->addButton( ui->type_AR , 4 );
    typegroup->addButton( ui->type_MG , 5 );
    typegroup->addButton( ui->type_SG , 6 );

    connect( typegroup , QOverload<int>::of(&QButtonGroup::buttonClicked) ,
             [=]( int id ) mutable{{
               type=id ;
               doll_present(star,id);
            }});
}

void calculation::doll_present(int star , int type)
{
    clear_all(); //清空装备栏信息

    //呈现人形名称
    ui->name_listWidget->clear();
    for (int i=0 ; i < 600 ; i++ ) {  //遍历所有人形，选出符合条件的(星级，枪种)
        if( i==0 )arr_edit_i = 0;
        if( doll_origin[i].star == star && doll_origin[i].type == type)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText( QString::fromUtf8( doll_origin[i].name ) );
            ui->name_listWidget->addItem( item );

            arr_edit[arr_edit_i]=i;
            arr_edit_i++;
        }
    }
}

void calculation::on_name_listWidget_itemClicked(QListWidgetItem *item)
{
    int currenRow = ui->name_listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    int id = arr_edit[currenRow];
    ui->name_lineEdit->setText(tr("%1").arg(QString::fromUtf8(doll_origin[id].name)));//将这个行号显示在lineText编辑框中
    doll[0]=doll_origin[id];
    prepare();
    likability();
    doll_info_show(id);
    special_select(id);
    equipment_select(id);

    QList<QLabel*> lab_as = ui->doll_info_show->findChildren<QLabel *>();
    foreach(QLabel* see, lab_as)
    {see->setVisible(true);}
}

void calculation::doll_info_show(int id)
{
    /* QList<QLabel*> lab_as = ui->doll_info_show->findChildren<QLabel *>();
    foreach(QLabel* see, lab_as)
    {see->setVisible(true);} */

    ui->attribute_attack->setText(QString::number(doll[0].attack));
    ui->attribute_fire_rate->setText(QString::number(doll[0].fire_rate));
    ui->attribute_hit->setText(QString::number(doll[0].hit));
    ui->attribute_crit_per->setText(QString::number(doll[0].critical_per));
    ui->attribute_crit_dam->setText(QString::number(doll[0].crit_damage_rate));
    ui->attribute_armor->setText(QString::number(doll[0].armor));
    ui->attribute_bullet_num->setText(QString::number(doll[0].bullet_number));
    ui->attribute_move->setText(QString::number(doll[0].move));
}

void calculation::condition_enemy_set()
{
    //初始定义
    condition.frame = 600;

    enemy.attack = 100;
    enemy.fire_rate = 30;
    enemy.hit = 100;
    enemy.dodge = 30;
    enemy.armor = 0;
    enemy.armor_piercing = 100;
    enemy.move = 100;
    enemy.target_number = 1;
    enemy.deep_damage = 1;

    ui->day_radioButton->setChecked(true);
    ui->dodge_spinBox->setValue(30);
    ui->dodge_spinBox->setMaximum(800);
    ui->armor_spinBox->setValue(0);
    ui->armor_spinBox->setMaximum(800);
    ui->time_spinBox->setValue(20);
    ui->target_spinBox->setValue(1);

    QButtonGroup *dngroup = new QButtonGroup( ui->condition_widget );
    dngroup->addButton( ui->day_radioButton , 0 );
    dngroup->addButton( ui->night_radioButton , 1 );

    connect( dngroup , QOverload<int>::of(&QButtonGroup::buttonClicked) ,
          [=]( int singal ) {
               condition.day_or_night = singal ;
            });

    connect( ui->dodge_spinBox , QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
                enemy.dodge = i ;
            });

    connect( ui->armor_spinBox , QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
                enemy.armor = i ;
            });

    connect( ui->time_spinBox , QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
                condition.frame = i * FA ;
            });

    connect( ui->target_spinBox , QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
                enemy.target_number = i ;
            });

    connect( ui->elite_checkBox , QOverload<int>::of(&QCheckBox::stateChanged),
          [=](int state){
                enemy.elite_unit = state ;
            });
}

void calculation::fairy_select()
{
    int gap=0;

    ui->fairy_comboBox->addItem(QString::fromUtf8("空妖精"));
    for(int k=1 ; k<=57 ; k++){
        if(fairy_origin[k].id == 0){ gap++ ; continue; }
        ui->fairy_comboBox->addItem(QString::fromUtf8(fairy_origin[k].name));}
    ui->fairy_comboBox->setCurrentIndex(0);

    connect( ui->fairy_comboBox , QOverload<int>::of(&QComboBox::currentIndexChanged),
         [=](int index){
            if(index <= 25)fairy_id = index ;
            else fairy_id = index + gap;

            ui->buff_crit_dam_spinBox->setValue(fairy_origin[fairy_id].crit_damage_rate *= 100);
            ui->buff_attack_spinBox->setValue(fairy_origin[fairy_id].attack *= 100);
            ui->buff_hit_spinBox->setValue(fairy_origin[fairy_id].hit *= 100);
            condition.dodge_buff = fairy_origin[fairy_id].dodge;
            condition.armor_buff = fairy_origin[fairy_id].armor;
        });

    ui->fairy_gift_comboBox->addItem(QString::fromUtf8("空天赋"));
    ui->fairy_gift_comboBox->addItem(QString::fromUtf8("杀伤2"));
    ui->fairy_gift_comboBox->addItem(QString::fromUtf8("激昂"));
    ui->fairy_gift_comboBox->setCurrentIndex(0);

    connect( ui->fairy_gift_comboBox , QOverload<int>::of(&QComboBox::currentIndexChanged),
         [=](int index){
            fairy_gift_id = index ;
        });

    ui->fairy_skill_checkBox->setText(QString::fromUtf8("妖精技能"));
    connect( ui->fairy_skill_checkBox , QOverload<bool>::of(&QAbstractButton::toggled),
         [=](bool checked){
            if(checked == true)
                condition.fairy_skill = 1;
            else
                condition.fairy_skill = 0;
        });

}

void calculation::buff_set()
{
    ui->buff_attack_spinBox->setMaximum(1000);
    ui->buff_fire_rate_spinBox->setMaximum(1000);
    ui->buff_hit_spinBox->setMaximum(1000);
    ui->buff_crit_dam_spinBox->setMaximum(1000);
    ui->buff_crit_per_spinBox->setMaximum(1000);

    ui->buff_attack_spinBox->setSingleStep(5);
    ui->buff_fire_rate_spinBox->setSingleStep(5);
    ui->buff_hit_spinBox->setSingleStep(5);
    ui->buff_crit_dam_spinBox->setSingleStep(5);
    ui->buff_crit_per_spinBox->setSingleStep(5);

    ui->buff_attack_spinBox->setAccelerated(true);
    ui->buff_fire_rate_spinBox->setAccelerated(true);
    ui->buff_hit_spinBox->setAccelerated(true);
    ui->buff_crit_dam_spinBox->setAccelerated(true);
    ui->buff_crit_per_spinBox->setAccelerated(true);

    ui->buff_attack_spinBox->setSuffix("%");
    ui->buff_fire_rate_spinBox->setSuffix("%");
    ui->buff_hit_spinBox->setSuffix("%");
    ui->buff_crit_dam_spinBox->setSuffix("%");
    ui->buff_crit_per_spinBox->setSuffix("%");

    connect(ui->buff_attack_spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
            condition.attack_buff = (double)i / 100;
        });

    connect(ui->buff_fire_rate_spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
            condition.fire_rate_buff = (double)i / 100;
        });

    connect(ui->buff_hit_spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
            condition.hit_buff = (double)i / 100;
        });

    connect(ui->buff_crit_dam_spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
            condition.crit_damage_rate_buff = (double)i / 100;
        });

    connect(ui->buff_crit_per_spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
          [=](int i){
            condition.critical_per_buff = (double)i / 100;
        });
}

void calculation::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawImage(370,320,image);
}

void calculation::draw()
{
    int image_width=820,image_hight=400;    //定义画布的初始化大小
    image = QImage(image_width,image_hight,QImage::Format_RGB32);  //使用32位颜色
    QColor backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
    image.fill(backColor);

    QList<QLabel*> td_labels = ui->terminal_damage->findChildren<QLabel*>();
    foreach(QLabel* label, td_labels)
    {delete label;} //清空最终伤害中的标签

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点（？
    int image_below=20,image_left=50;//设定留给坐标刻度和空余的部分
    int pointx=image_left,pointy=image_hight-image_below;//确定坐标轴起点坐标
    int width=image_width-pointx-5,height=pointy-5;//确定坐标轴宽度跟高度
    //绘制坐标轴 坐标轴原点(35，280)
    //painter.drawRect(5,5,image_width-10,image_hight-10);//外围的矩形，周围留了5的间隙。
    painter.drawLine(pointx,pointy,width+pointx,pointy);//坐标轴x宽度为width
    painter.drawLine(pointx,pointy-height,pointx,pointy);//坐标轴y高度为height

    double kx=(double)width/(condition.frame-1);//x轴的系数

    double max_y=0; //选取y轴最大值
    for(int pos=1 ; pos<10 ; pos++){
        if(damage_together[pos][condition.frame-1] > max_y ){
            max_y = damage_together[pos][condition.frame-1];
        }
    }
    double ky=height/max_y;//y方向的比例系数

    QPen pen;
    pen.setWidth(1);
    int i = 0; //lable记录最终伤害第几行累加

    for( int pos=1 ; pos<10 ; pos++){
        if(damage_together[pos][condition.frame-1] <= 0)continue;
        i++;

        //新建qlable记录最终伤害 label_name
        QLabel* label_pos = new QLabel(ui->terminal_damage);
        QLabel* label_name = new QLabel(ui->terminal_damage);
        QLabel* label_damage = new QLabel(ui->terminal_damage);

        label_pos->setText(QString::number(pos));
        label_name->setText( QString::fromUtf8( doll[pos].name ) );
        label_pos->setGeometry(5 , 25*i+10 , 8 , 15);
        label_name->setGeometry( 15 , 25*i+10 , 160 , 15);
        label_damage->setGeometry(100 , 25*i+10 , 160 , 15);

        label_pos->show();
        label_name->show();
        label_damage->show();


        switch (pos) { //选择画笔颜色以及文本颜色
            case 1:
                {pen.setColor(QColor(0x66,0x66,0x66));
                label_name->setStyleSheet("color:#666666"); }break;
            case 2:
                {pen.setColor(QColor(0xCC,0x00,0x00));
                label_name->setStyleSheet("color:#CC0000"); }break;
            case 3:
                {pen.setColor(QColor(0xEE,0x77,0x00));
                label_name->setStyleSheet("color:#EE7700"); }break;
            case 4:
                {pen.setColor(QColor(0xEE,0xEE,0x00));
                label_name->setStyleSheet("color:#EEEE00"); }break;
            case 5:
                {pen.setColor(QColor(0x00,0xDD,0x00));
                label_name->setStyleSheet("color:#00DD00"); }break;
            case 6:
                {pen.setColor(QColor(0x00,0xDD,0xDD));
                label_name->setStyleSheet("color:#00DDDD"); }break;
            case 7:
                {pen.setColor(QColor(0x00,0x00,0xCC));
                label_name->setStyleSheet("color:#0000CC"); }break;
            case 8:
                {pen.setColor(QColor(0x77,0x00,0xBB));
                label_name->setStyleSheet("color:#7700BB"); }break;
            case 9:
                {pen.setColor(QColor(0xCC,0x00,0xCC));
                label_name->setStyleSheet("color:#CC00CC"); }break;
        default:
            break;
        }

        for(int j=0 ; j<condition.frame ; j++){//绘制折线图
            //由于y轴是倒着的，所以y轴坐标要pointy-damage[1][j]*ky 其中ky为比例系数

            painter.setPen(pen);
            painter.drawLine(pointx+kx*j,pointy-damage_together[pos][j]*ky,pointx+kx*(j+1),pointy- damage_together[pos][j+1]*ky);

            label_damage->setText(QString::number( floor(damage_together[pos][condition.frame-1]) ) );
        }

        QLabel* label_per = new QLabel(ui->terminal_damage);
        label_per->setGeometry(160 , 25*i+10 , 45 , 15);
        label_per->show();

        QString per_str = QString::number(floor((damage_together[pos][condition.frame-1]/damage_together[0][condition.frame-1]) *100)) + "%";
        label_per->setText(per_str);
    }

    QLabel* label_total = new QLabel(ui->terminal_damage); //最终伤害显示
    label_total->setGeometry(100 , 10 , 160 , 15);
    label_total->setText(  QString::number(ceil(damage_together[0][condition.frame-1])) );
    label_total->show();

    QPen penDegree; //坐标刻度笔刷
    penDegree.setColor(Qt::black);
    penDegree.setWidth(1);
    painter.setPen(penDegree);

    //画上x轴刻度线,像素显示分级，暂且20帧一格（60帧）
    int pix_per=(condition.frame/60);
    for(int i=0;i<pix_per ;i++)
    {
        painter.drawLine(pointx+(i+1)*width/pix_per,pointy,pointx+(i+1)*width/pix_per,pointy+4);
        painter.drawText(pointx+(i+0.65)*width/pix_per,
                            pointy+pix_per,QString::number((int)(((i+1)*60)))); //单位（60）*格数（i+1）
    }

    //y轴刻度线
    double _maStep=max_y / 10;//y轴刻度间隔需根据最大值来表示
    for(int i=0;i<10;i++)
    {
        //主要就是确定一个位置，然后画一条短短的直线表示刻度。
        painter.drawLine(pointx,pointy-(i+1)*height/10,
                            pointx-4,pointy-(i+1)*height/10);
        painter.drawText(pointx-45,pointy-(i+0.7)*height/10,
                            QString::number((int)(_maStep*(i+1))));
    }
    //以多少帧为准
    painter.drawText(pointx+15,pointy-(9+0.8)*height/10,
                        QString::number(FA));
    painter.drawText(pointx+30,pointy-(9+0.8)*height/10,
                        QString("frame"));

}

bool calculation::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->position_1) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_1->setText("null");
            else ui->position_1->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[1]=doll[0];
            doll[1]=doll[0];
            doll[0]=doll[10];

            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_2) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_2->setText("null");
            else ui->position_2->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[2]=doll[0];
            doll[2]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_3) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_3->setText("null");
            else ui->position_3->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[3]=doll[0];
            doll[3]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_4) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_4->setText("null");
            else ui->position_4->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[4]=doll[0];
            doll[4]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_5) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_5->setText("null");
            else ui->position_5->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[5]=doll[0];
            doll[5]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_6) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_6->setText("null");
            else ui->position_6->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[6]=doll[0];
            doll[6]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_7) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_7->setText("null");
            else ui->position_7->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[7]=doll[0];
            doll[7]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_8) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_8->setText("null");
            else ui->position_8->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[8]=doll[0];
            doll[8]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else if (obj == ui->position_9) {
        if (event->type() == QEvent::MouseButtonPress) {
            if(doll[0].id == 0) ui->position_9->setText("null");
            else ui->position_9->setText( QString::fromUtf8( doll[0].name ) );

            doll_reserve[9]=doll[0];
            doll[9]=doll[0];
            doll[0]=doll[10];
            clear_all();
            return true;
        }
        else {return false;}
    }
    else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

void calculation::clear_all()
{
    //清空装备栏信息
    QList<QRadioButton*> btns_1 = ui->equip_first->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_1)
    {delete btn;}

    QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_2)
    {delete btn;}

    QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_3)
    {delete btn;}

    ui->equip_first_label->setText(QString::fromUtf8(" "));
    ui->equip_second_label->setText(QString::fromUtf8(" "));
    ui->equip_third_label->setText(QString::fromUtf8(" "));

    //清空特殊人形选择框
    QList<QSpinBox*> wi_1 = ui->specialdoll_widget->findChildren<QSpinBox *>();
    foreach(QSpinBox* spin, wi_1)
    {delete spin;}

    QList<QLabel*> wi_2 = ui->specialdoll_widget->findChildren<QLabel *>();
    foreach(QLabel* lab, wi_2)
    {delete lab;}

    QList<QCheckBox*> wi_3 = ui->specialdoll_widget->findChildren<QCheckBox *>();
    foreach(QCheckBox* che, wi_3)
    {delete che;}

    QList<QRadioButton*> wi_4 = ui->specialdoll_widget->findChildren<QRadioButton *>();
    foreach(QRadioButton* rad, wi_4)
    {delete rad;}

    //隐藏人形属性显示控件
    QList<QLabel*> lab_as = ui->doll_info_show->findChildren<QLabel *>();
    foreach(QLabel* see, lab_as)
    {see->setVisible(false);}

}






