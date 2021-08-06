#include "calculation.h"
#include "ui_calculation.h"

#include <QButtonGroup>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QtGui>

void calculation::special_select(int id)
{
    clear_all();

    switch (id) {
    case 7:{ //7 斯捷奇金
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("被攻击敌人血量小于30%"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[1] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 32:{ //32 微型乌兹¤
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("极小范围内伤害覆加效果"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(1);
        thespinbox->setMinimum(1);
        thespinbox->setSingleStep(1);
        thespinbox->setGeometry(169,0,42,22);
        thespinbox->show();
        doll[0].sign[0] = 1;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign[0] = d;
                });
    }break;



    case 46: //46 Kar98k
    case 180: //180 PzB39
    case 192: //192 JS05
    {
        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget) ;
        thecheck->setText(QString::fromUtf8("技能开启"));
        thecheck->setChecked(false);
        thecheck->show();
        doll[0].sign_z[5] = 0;

        connect( thecheck , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[5] = state ;
                });
    }break;

    case 34: //34 M1加兰德
    case 36: //36 春田
    case 38: //38 M21
    case 40: //40 SVT-38
    case 117: //117 PSG-1
    case 124: //124 Super SASS

    case 42: //42 PTRD 7层
    case 128: //128 M99 7层
    case 145: //145 OTs-44 7层
    case 179: //179 DSR-50 7层
    case 241: //241 RT-20 7层
    {
        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget) ;
        thecheck->setText(QString::fromUtf8("技能开启"));
        thecheck->setChecked(false);
        thecheck->show();
        doll[0].sign_z[5] = 0;

        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("蓄力层数"));
        thelabel->setGeometry(0,25,62,22);
        thelabel->setVisible(false);

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(1);
        thespinbox->setGeometry(67,25,42,22);
        thespinbox->setVisible(false);
        doll[0].sign_z[0] = 3;

        if(id == 42||id == 53||id == 128||id == 145||id == 179){ thespinbox->setMaximum(7); }
        else { thespinbox->setMaximum(5); }

        connect( thecheck , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[5] = state ;
                    if(state == 2){
                        thespinbox->setVisible(true);
                        thelabel->setVisible(true);}
                    else {
                        thespinbox->setVisible(false);
                        thelabel->setVisible(false);}
                });

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[0] = d;
                });
    }break;

    case 39: //39 莫辛-纳甘¤
    {
        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget) ;
        thecheck->setText(QString::fromUtf8("技能开启"));
        thecheck->setChecked(false);
        thecheck->show();
        thecheck->setGeometry(0 , 25 , 160 , 24);
        doll[0].sign_z[5] = 0;

        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("蓄力层数"));
        thelabel->setGeometry(0,50,62,22);
        thelabel->setVisible(false);

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(1);
        thespinbox->setMaximum(5);
        thespinbox->setGeometry(67,50,42,22);
        thespinbox->setVisible(false);
        doll[0].sign_z[0] = 3;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[0] = d;
                });

        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("普通攻击击杀敌人"));
        thecheckbox->setChecked(true);
        thecheckbox->setGeometry(0 , 0 , 160 , 24);
        thecheckbox->setVisible(true);
        doll[0].sign_z[1] = 2;

        QCheckBox* thecheckbox_2 = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox_2->setText(QString::fromUtf8("沉稳射击击杀敌人"));
        thecheckbox_2->setChecked(true);
        thecheckbox_2->setGeometry(0 , 75 , 160 , 24);
        thecheckbox_2->setVisible(false);
        doll[0].sign_z[2] = 2;

        connect( thecheck , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[5] = state ;
                    if(state == 2){
                        thecheckbox_2->setVisible(true);
                        thespinbox->setVisible(true);
                        thelabel->setVisible(true);}
                    else {
                        thecheckbox_2->setVisible(false);
                        thespinbox->setVisible(false);
                        thelabel->setVisible(false);}
                });

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
        connect( thecheckbox_2 , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[2] = state ;
                });

    }break;

    case 44: //44 SV-98¤
    {
        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget) ;
        thecheck->setText(QString::fromUtf8("技能开启"));
        thecheck->setChecked(false);
        thecheck->show();
        thecheck->setGeometry(0 , 25 , 160 , 24);
        doll[0].sign_z[5] = 0;

        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("蓄力层数"));
        thelabel->setGeometry(0,50,62,22);
        thelabel->setVisible(false);

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(1);
        thespinbox->setMaximum(5);
        thespinbox->setSingleStep(1);
        thespinbox->setGeometry(67,50,42,22);
        thespinbox->setVisible(false);
        doll[0].sign_z[0] = 3;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[0] = d;
                });

        connect( thecheck , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[5] = state ;
                    if(state == 2){
                        thespinbox->setVisible(true);
                        thelabel->setVisible(true);}
                    else {
                        thespinbox->setVisible(false);
                        thelabel->setVisible(false);}
                });

        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("静止不动进入伪装状态"));
        thecheckbox->setChecked(true);
        thecheckbox->setGeometry(0 , 0 , 240 , 24);
        doll[0].sign_z[1] = 2;

        thecheckbox->show();

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 53: //53 NTW-20
    {
        QCheckBox* thecheckk = new QCheckBox(ui->specialdoll_widget) ;
        thecheckk->setText(QString::fromUtf8("敌人血量50%以上"));
        thecheckk->setGeometry(0,0,200,22);
        thecheckk->setChecked(true);
        thecheckk->show();
        doll[0].sign_z[6] = 2;

        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget) ;
        thecheck->setText(QString::fromUtf8("技能开启"));
        thecheck->setGeometry(0,25,200,22);
        thecheck->setChecked(false);
        thecheck->show();
        doll[0].sign_z[5] = 0;

        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("蓄力层数"));
        thelabel->setGeometry(0,50,62,22);
        thelabel->setVisible(false);

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(1);
        thespinbox->setGeometry(67,50,42,22);
        thespinbox->setVisible(false);
        thespinbox->setMaximum(7);
        doll[0].sign_z[0] = 3;

        connect( thecheckk , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[6] = state;
                });

        connect( thecheck , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[5] = state ;
                    if(state == 2){
                        thespinbox->setVisible(true);
                        thelabel->setVisible(true);}
                    else {
                        thespinbox->setVisible(false);
                        thelabel->setVisible(false);}
                });

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[0] = d;
                });
    }break;

    case 55: //55 M4A1¤
    {
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("我方场上单位数量为3及以下"));
        thecheckbox->setChecked(true);
        doll[0].sign_z[1] = 2;

        thecheckbox->show();

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 56:
    case 57:{ //56 M4 SOPMODⅡ¤  57 ST AR-15¤
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("目标是否受申冤者印记标记"));
        thecheckbox->setChecked(true);
        doll[0].sign_z[4] = 2;

        thecheckbox->show();


        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[4] = state ;
                });
    }break;

    case 63:{ //63 G3¤
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("敌人生命小于50%(伤害)"));
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("敌人生命大于50%(眩晕)"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->setChecked(true);
        theradio_2->show();

        doll[0].sign_z[0] = 2;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int i)
                     {
                        if(i == 1)doll[0].sign_z[0] = 1;
                        else doll[0].sign_z[0] = 2;
                      });
    }break;

    case 64:{ //64 G36¤
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("影响格上友方人形数量"));
        thelabel->setGeometry(0,0,152,22);
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(2);
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(2);
        thespinbox->setSingleStep(1);
        thespinbox->setGeometry(155,0,42,22);
        thespinbox->show();
        thespinbox->setVisible(false);
        doll[0].sign_z[1] = 2;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[1] = d;
                });

        QCheckBox* thecheck = new QCheckBox(ui->specialdoll_widget);
        thecheck->setText(QString::fromUtf8("依据阵型"));
        thecheck->show();
        thecheck->setGeometry(0,25,200,22);
        thecheck->setChecked(true);
        doll[0].sign_z[0] = 1;

        connect(thecheck, QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    if(state == 0){
                        doll[0].sign_z[0] = 0;
                        thespinbox->setVisible(true);
                    }
                    else{
                        doll[0].sign_z[0] = 1;
                        thespinbox->setVisible(false);
                    }
                });
    }break;

    case 65:{ //65 HK416¤
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("杀伤榴弹击杀主目标"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 95:{ //95 汉阳造88式¤
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("血量最高的敌方为装甲单位"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("血量最高敌方为非装甲单位"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("全部手雷命中同一目标"));
        thecheckbox->setChecked(false);
        thecheckbox->setGeometry(0,46,220,23);
        doll[0].sign_z[1] = 0;

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int i)
                     {
                        if(i == 1){
                            doll[0].sign_z[0] = 1;
                            thecheckbox->setVisible(false);}
                        else {
                            doll[0].sign_z[0] = 2;
                            thecheckbox->setVisible(true);}
                      });

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 102:{ //102 UMP40
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("启用主动效果"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("启用被动效果"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int i)
                     {
                        if(i == 1)doll[0].sign_z[0] = 1;
                        else doll[0].sign_z[0] = 2;
                      });
    }break;

    /*case 103: //103 UMP45¤
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("目标射速"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(30);
        thespinbox->setMinimum(1);
        thespinbox->setMaximum(120);
        thespinbox->setSingleStep(1);
        thespinbox->setGeometry(75,0,42,22);
        thespinbox->show();
        enemy.fire_rate = 30;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    enemy.fire_rate = d;
                });
    }break;*/

    case 151: //151 M1887
    case 152: //152 M1897
    case 153: //153 M37
    case 154: //154 M500
    case 155: //
    case 156: //
    case 157: //
    case 158: //
    case 159: //
    case 160: //
    case 161: //
    case 162: //
    case 163: //
    case 164: //
    case 165: //
    case 188: //188 S.A.T.8
    case 189: //189 USAS-12
    case 190: //190 NS2000
    case 278: //278 Six12
    case 281: //281 CAWS
    case 282: //282 DP-12
    case 283: //283 解放者
    case 402: //402 艾尔菲尔特
    case 408: //408 希儿
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("攻击目标个数"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(1);
        thespinbox->setMaximum(3);
        thespinbox->setSingleStep(1);
        thespinbox->setGeometry(100,0,42,22);
        thespinbox->show();
        doll[0].sign_z[0] = 3;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int d){
                    doll[0].sign_z[0] = d;
                    doll[0].armor -= 10; doll[0].dodge += 2;
                    doll[0].attack -= 15; doll[0].crit_damage_rate -= 0.22;
                    doll[0].hit -= 30 ; doll[0].fire_rate += 1;
                    equipment_select(id);
                });
    }break;

    case 194:{ //194 K2
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("自动技能"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("手动技能(默认短点射模式)"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        QRadioButton* theradio_3 = new QRadioButton(ui->specialdoll_widget);
        theradio_3->setText(QString::fromUtf8("手动技能(默认单发模式)"));
        theradio_3->setGeometry(0,46,220,23);
        theradio_3->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);
        thegroup->addButton(theradio_3,3);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int i)
                     {
                        doll[0].sign_z[0] = i;
                      });

        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("单发模式攻击同一目标"));
        thecheckbox->setChecked(true);
        thecheckbox->setGeometry(0,69,220,23);
        thecheckbox->show();
        doll[0].sign_z[2] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[2] = state ;
                });
    }break;

    case 205: //205 AN-94
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("变更攻击目标的百分比"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(50);
        thespinbox->setSuffix("%");
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(100);
        thespinbox->setSingleStep(10);
        thespinbox->setGeometry(158,0,54,22);
        thespinbox->show();
        doll[0].sign_z[0] = 50;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[0] = value;
                });
    }break;

    case 213:{ //213 C-MS
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("亚音速弹常驻状态"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("勺尖弹常驻状态"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        QRadioButton* theradio_3 = new QRadioButton(ui->specialdoll_widget);
        theradio_3->setText(QString::fromUtf8("标准弹常驻状态"));
        theradio_3->setGeometry(0,46,220,23);
        theradio_3->show();

        doll[0].sign_z[0] = 1;
        doll[0].dodge *= 0.65;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);
        thegroup->addButton(theradio_3,3);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                      });
    }break;

    case 228:{ //228 樱花
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("技能持续时间内护盾破裂"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 231: //231 M82A1
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("战役中获得战斗胜利次数"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(3);
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(3);
        thespinbox->setGeometry(170,0,33,22);
        thespinbox->show();
        doll[0].sign_z[0] = 3;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[0] = value;
                });
    }break;

    case 235:{ //235 SPR A3G
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("受标记目标限制时间内死亡"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 236: //236 K11
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("榴弹重复轰炸百分比"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(50);
        thespinbox->setSuffix("%");
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(100);
        thespinbox->setSingleStep(10);
        thespinbox->setGeometry(142,0,54,22);
        thespinbox->show();
        doll[0].sign_z[0] = 50;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[0] = value;
                });
    }break;

    case 238:{ //238 88式
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("轻机枪模式"));
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("重机枪模式"));
        theradio_2->setChecked(true);
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 2;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                      });
    }break;

    case 243:{ //243 64式自
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("技能发动时敌人数量大于5组"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });

        QCheckBox* thecheckbox_2 = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox_2->setText(QString::fromUtf8("发动3s后敌人数量大于2组"));
        thecheckbox_2->setChecked(false);
        thecheckbox_2->setGeometry(0 , 23 , 200 , 23);
        thecheckbox_2->show();
        doll[0].sign_z[1] = 0;

        connect( thecheckbox_2 , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 245:{ //245 P90
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("被动始终触发"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 250:{ //250 HS2000
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("我方单位护盾存在三秒以上"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 251: //251 X95
    {
        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("目标损失生命百分比"));
        thelabel->show();

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(50);
        thespinbox->setSuffix("%");
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(100);
        thespinbox->setSingleStep(10);
        thespinbox->setGeometry(142,0,54,22);
        thespinbox->show();
        doll[0].sign_z[0] = 50;

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[0] = value;
                });
    }break;

    case 256:{ //256 隼
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("手动技能不开启主动"));
        thecheckbox->setChecked(false);
        thecheckbox->show();
        doll[0].sign_z[0] = 0;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 261:{ //261 QBU-88
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("始终攻击同一目标"));
        thecheckbox->setChecked(true);
        thecheckbox->show();
        doll[0].sign_z[0] = 2;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                });
    }break;

    case 266: //266 R93
    {
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("保持层数"));
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("每4次普攻切换"));
        theradio_2->setChecked(true);
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 2;

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(2);
        thespinbox->setMinimum(1);
        thespinbox->setMaximum(3);
        thespinbox->setGeometry(90,0,54,22);
        thespinbox->setVisible(false);
        doll[0].sign_z[1] = 2;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                        if(index == 2){thespinbox->setVisible(false); }
                        else {thespinbox->setVisible(true); }
                      });

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[0] = value;
                });
    }break;

    case 269:{ //269 P30
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("报复进行时"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("追讨的决心"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                      });
    }break;

    case 272:{ //272 沙漠之鹰
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("护盾计算在伤害内"));
        thecheckbox->setChecked(false);
        thecheckbox->show();
        doll[0].sign_z[1] = 0;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[1] = state ;
                });
    }break;

    case 274: //274 ACR
    {
        QCheckBox* thecheckbox = new QCheckBox(ui->specialdoll_widget) ;
        thecheckbox->setText(QString::fromUtf8("自定敌方减益数量"));
        thecheckbox->setChecked(false);
        thecheckbox->show();
        doll[0].sign_z[0] = 0;

        QSpinBox* thespinbox = new QSpinBox(ui->specialdoll_widget);
        thespinbox->setValue(0);
        thespinbox->setMinimum(0);
        thespinbox->setMaximum(8);
        thespinbox->setGeometry(150,0,30,22);
        doll[0].sign_z[1] = 0;

        connect( thecheckbox , QOverload<int>::of(&QCheckBox::stateChanged),
              [=](int state){
                    doll[0].sign_z[0] = state ;
                    if(state == 2)thespinbox->setVisible(true);
                    else thespinbox->setVisible(false);
                });

        connect(thespinbox, QOverload<int>::of(&QSpinBox::valueChanged),
              [=](int value){
                    doll[0].sign_z[1] = value;
                });
    }break;

    case 276:{ //276 Kord
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("贯穿效果"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("强击效果"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                      });
    }break;

    case 417:{ //417 Jill
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("苦辣酒"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("甜甜酸"));
        theradio_2->setGeometry(0,23,90,23);
        theradio_2->show();

        QRadioButton* theradio_3 = new QRadioButton(ui->specialdoll_widget);
        theradio_3->setText(QString::fromUtf8("甜苦酒"));
        theradio_3->setGeometry(0,46,90,23);
        theradio_3->show();

        QRadioButton* theradio_4 = new QRadioButton(ui->specialdoll_widget);
        theradio_4->setText(QString::fromUtf8("甜甜酒"));
        theradio_4->setGeometry(75,0,90,23);
        theradio_4->show();

        QRadioButton* theradio_5 = new QRadioButton(ui->specialdoll_widget);
        theradio_5->setText(QString::fromUtf8("苦酸辣"));
        theradio_5->setGeometry(75,23,90,23);
        theradio_5->show();

        QRadioButton* theradio_6 = new QRadioButton(ui->specialdoll_widget);
        theradio_6->setText(QString::fromUtf8("酒酒酒"));
        theradio_6->setGeometry(75,46,90,23);
        theradio_6->show();

        QRadioButton* theradio_7 = new QRadioButton(ui->specialdoll_widget);
        theradio_7->setText(QString::fromUtf8("其他"));
        theradio_7->setGeometry(150,0,90,23);
        theradio_7->show();
        theradio_7->setChecked(true);

        doll[0].sign_z[0] = 7;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);
        thegroup->addButton(theradio_3,3);
        thegroup->addButton(theradio_4,4);
        thegroup->addButton(theradio_5,5);
        thegroup->addButton(theradio_6,6);
        thegroup->addButton(theradio_7,7);

        QLabel* thelabel = new QLabel(ui->specialdoll_widget);
        thelabel->setText(QString::fromUtf8("提升我方全体伤害18%"));
        thelabel->setGeometry(0,69,300,46);
        thelabel->show();

        QFont ft;
        ft.setPointSize(8);
        thelabel->setFont(ft);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int i)
                     {
                        if(i == 1){
                            doll[0].sign_z[0] = 1;
                            thelabel->setText(QString::fromUtf8("提升霰弹20%护甲,30%伤害和命中"));}
                        else if(i == 2){
                            doll[0].sign_z[0] = 2;
                            thelabel->setText(QString::fromUtf8("提升机枪25%伤害和命中"));}
                        else if(i == 3){
                            doll[0].sign_z[0] = 3;
                            thelabel->setText(QString::fromUtf8("提升我方前排60%回避,其他单位提升\n20%伤害"));}
                        else if(i == 4){
                            doll[0].sign_z[0] = 4;
                            thelabel->setText(QString::fromUtf8("提升我方全体22%射速"));}
                        else if(i == 5){
                            doll[0].sign_z[0] = 5;
                            thelabel->setText(QString::fromUtf8("提升我方步枪和突击步枪25%暴击,\n使溢出暴击率的60%转化为暴伤提升"));}
                        else if(i == 6){
                            doll[0].sign_z[0] = 6;
                            thelabel->setText(QString::fromUtf8("提升我方全体35%伤害,5秒增益\n结束后降低15%伤害和命中"));}
                        else if(i == 7){
                            doll[0].sign_z[0] = 7;
                            thelabel->setText(QString::fromUtf8("提升我方全体伤害18%"));}
                      });

    }break;

    case 419:{ //419 Dorothy
        QRadioButton* theradio_1 = new QRadioButton(ui->specialdoll_widget);
        theradio_1->setText(QString::fromUtf8("MIRD113常驻状态"));
        theradio_1->setChecked(true);
        theradio_1->show();

        QRadioButton* theradio_2 = new QRadioButton(ui->specialdoll_widget);
        theradio_2->setText(QString::fromUtf8("纳米迷彩常驻状态"));
        theradio_2->setGeometry(0,23,220,23);
        theradio_2->show();

        doll[0].sign_z[0] = 1;

        QButtonGroup* thegroup = new QButtonGroup(ui->specialdoll_widget);
        thegroup->addButton(theradio_1,1);
        thegroup->addButton(theradio_2,2);

        connect( thegroup , QOverload<int>::of(&QButtonGroup::buttonPressed),
                      [=](int index)
                     {
                        doll[0].sign_z[0] = index;
                      });
    }break;






    default:
        break;

    }
}
