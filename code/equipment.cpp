#include "calculation.h"
#include "ui_calculation.h"

#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QWidget>
#include <QtGui>

#include <math.h>


void  likability() //好感度计算，在函数内取整
{
    if(doll[0].mod_sign == 0)
    {
        doll[0].hit = ceil( doll[0].hit * 1.10 );
        doll[0].attack = ceil( doll[0].attack * 1.10 );
        doll[0].dodge = ceil( doll[0].dodge * 1.10 );
    } else {
        doll[0].hit = ceil( doll[0].hit * 1.15 );
        doll[0].attack = ceil( doll[0].attack * 1.15 );
        doll[0].dodge = ceil( doll[0].dodge * 1.15 );
    }
}


void calculation::equipment_select(int id)
{
    //删除equip_first中的QRadioButton
    QList<QRadioButton*> btns_1 = ui->equip_first->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_1)
    {delete btn;}

    //删除equip_second中的QRadioButton
    QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_2)
    {delete btn;}

    //删除equip_third中的QRadioButton
    QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
    foreach(QRadioButton* btn, btns_3)
    {delete btn;}

    if(doll[0].type == 1) //HG
    {
        //HG装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("夜视"));
        button_1_1->setGeometry(0,0,60,22);

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("消音"));
        button_1_2->setGeometry(60,0,60,22);
        button_1_2->setChecked(true);
        doll[0].critical_per += 0.2 ; doll[0].dodge += 10;
        ui->equip_first_label->setText(QString::fromUtf8("暴击+20% 回避+10"));

        QRadioButton* button_1_3 = new QRadioButton( ui->equip_first );
        button_1_3->setText(QString::fromUtf8("专属"));
        button_1_3->setGeometry(120,0,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        first_equip_group->addButton(button_1_3,3);
        button_1_1->show();
        button_1_2->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 1: //1 柯尔特左轮¤
        case 3: //3 M9
        case 5: //5 纳甘左轮¤
        case 7: //7 斯捷奇金
        case 10: //10 PPK
        case 91: //91 MP-446¤
        case 409: //409 clear
        case 410: //410 fail

        {
            button_1_3->show();
            button_1_2->setChecked(false);
            button_1_3->setChecked(true);

            doll[0].critical_per -= 0.2 ;doll[0].dodge -= 10;
        }break;
        default:  break;
        }

        switch (id) { //有专属装备人形的初始设定,不要忘记之前已经设定的装备属性
        case 1: //1 柯尔特左轮¤
            {{doll[0].attack += 3 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 10;}
            ui->equip_first_label->setText(QString::fromUtf8("伤害+3 暴击+20% 回避+10"));}break;
        case 3: //3 M9
            {{doll[0].hit += 3 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 20;}
            ui->equip_first_label->setText(QString::fromUtf8("命中+3 暴击+20% 回避+20"));}break;
        case 5: //5 纳甘左轮¤
            {{doll[0].hit += 4 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 14;}
            ui->equip_first_label->setText(QString::fromUtf8("命中+4 暴击+20% 回避+14"));}break;
        case 7: //7 斯捷奇金
            {{doll[0].sign_z[0] = 1;doll[0].hit += 4 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 10;}
            ui->equip_first_label->setText(QString::fromUtf8("技能+ 命中+4 暴击+20% 回避+10"));}break;
        case 10: //10 PPK
            {{doll[0].critical_per += 0.3;doll[0].dodge += 18;}
            ui->equip_first_label->setText(QString::fromUtf8("暴击+30% 回避+18"));}break;
        case 91: //91 MP-446¤
            {{doll[0].critical_per += 0.2;doll[0].dodge += 10;doll[0].hit += 8;}
            ui->equip_first_label->setText(QString::fromUtf8("命中+8 暴击+20% 回避+10"));}break;
        case 409:
            {{doll[0].sign_z[0] = 1;doll[0].night_view_per += 1 ;}
            ui->equip_first_label->setText(QString::fromUtf8("技能+ 夜视能力+100%"));}break;
        case 410:
            {{doll[0].sign_z[0] = 1;doll[0].night_view_per += 1 ;}
            ui->equip_first_label->setText(QString::fromUtf8("技能+ 夜视能力+100%"));}break;
        default:
            break;
        }

        if(id == 417) equip_special(doll[0].id , 1);//特殊人形装备格

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //夜视
                        if(checked == true)
                            {doll[0].night_view_per += 1 ;
                            ui->equip_first_label->setText(QString::fromUtf8("夜视能力+100%"));}
                        else doll[0].night_view_per -= 1 ;break;

                    case 2: //消音
                        if(checked == true)
                            {doll[0].critical_per += 0.2 ;doll[0].dodge += 10;
                            ui->equip_first_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                        else {doll[0].critical_per -= 0.2 ;doll[0].dodge -= 10;}break;

                    case 3: //专属
                        switch(id){
                        case 1: //1 柯尔特左轮¤
                            if(checked == true)
                                {{doll[0].attack += 3 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 10;}
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+3 暴击+20% 回避+10"));}
                            else {doll[0].attack -= 3 ;doll[0].critical_per -= 0.2 ;doll[0].dodge -= 10;}break;

                        case 3: //3 M9
                            if(checked == true)
                                {{doll[0].hit += 3 ;doll[0].critical_per += 0.2 ;doll[0].dodge += 20;}
                                ui->equip_first_label->setText(QString::fromUtf8("命中+3 暴击+20% 回避+20"));}
                            else {doll[0].hit -= 3 ;doll[0].critical_per -= 0.2 ;doll[0].dodge -= 20;}break;

                        case 5: //5 纳甘左轮¤
                            if(checked == true)
                                {doll[0].hit += 4 ; doll[0].critical_per += 0.2 ;doll[0].dodge += 14;
                                ui->equip_first_label->setText(QString::fromUtf8("命中+4 暴击+20% 回避+14"));}
                            else {doll[0].hit -= 4 ; doll[0].critical_per -= 0.2 ;doll[0].dodge -= 14;}break;

                        case 7: //7 斯捷奇金
                            if(checked == true)
                                {doll[0].sign_z[0] = 1;doll[0].hit += 4 ; doll[0].critical_per += 0.2 ;doll[0].dodge += 10;
                                ui->equip_first_label->setText(QString::fromUtf8("技能+ 命中+4 暴击+20% 回避+10"));}
                            else {doll[0].sign_z[0] = 0;doll[0].hit -= 4 ; doll[0].critical_per -= 0.2 ;doll[0].dodge -= 10;}break;

                        case 10: //10 PPK
                            if(checked == true)
                                {{doll[0].critical_per += 0.3;doll[0].dodge += 18; }
                                ui->equip_first_label->setText(QString::fromUtf8("暴击+30% 回避+18"));}
                            else {doll[0].critical_per -= 0.3;doll[0].dodge -= 18; }break;

                        case 91: //91 MP-446¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.2;doll[0].dodge += 10;doll[0].hit += 8;}
                                ui->equip_first_label->setText(QString::fromUtf8("命中+8 暴击+20% 回避+10"));}
                            else {doll[0].critical_per -= 0.2;doll[0].dodge -= 10;doll[0].hit -= 8;}break;

                        case 409: //409 clear
                            if(checked == true)
                                {{doll[0].sign_z[0] = 1;doll[0].night_view_per += 1 ;}
                                ui->equip_first_label->setText(QString::fromUtf8("技能+ 夜视能力+100%"));}
                            else {doll[0].sign_z[0] = 0;doll[0].night_view_per -= 1 ;}break;

                        case 410: //410 fail
                            if(checked == true)
                                {{doll[0].sign_z[0] = 1;doll[0].night_view_per += 1 ;}
                                ui->equip_first_label->setText(QString::fromUtf8("技能+ 夜视能力+100%"));}
                            else {doll[0].sign_z[0] = 0;doll[0].night_view_per -= 1 ;}break;

                        }break;


                    default:
                        break;
                    }
                });

        //HG装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("空尖"));
        button_2_1->setGeometry(0,0,60,22);
        button_2_1->setChecked(true);
        {doll[0].attack += 15 ; doll[0].armor_piercing -= 7 ;}
        ui->equip_second_label->setText(QString::fromUtf8("伤害+15 穿甲-7"));

        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("专属"));
        button_2_2->setGeometry(60,0,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        button_2_1->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 2: //2 M1911¤
        case 183: //竞争者
        {
            button_2_2->show();
            button_2_1->setChecked(false);
            button_2_2->setChecked(true);

            doll[0].attack -= 15 ; doll[0].armor_piercing += 7 ;
        }break;
        default:  break;
        }

        switch (id) { //有专属装备人形的初始设定,不要忘记之前已经设定的装备属性
        case 2:
            {{doll[0].attack += 17 ; doll[0].armor_piercing -= 7 ;}
            ui->equip_second_label->setText(QString::fromUtf8("伤害+17 穿甲-7"));}break;
        case 183: //竞争者
            {{doll[0].armor_piercing += 180;button_2_2->setText(QString::fromUtf8("穿甲"));}
            ui->equip_second_label->setText(QString::fromUtf8("穿甲+180"));}break;
        default:
            break;
        }

        if(id == 417) equip_special(doll[0].id , 2);//特殊人形装备格

        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //空尖
                        if(checked == true)
                            {{doll[0].attack += 15 ; doll[0].armor_piercing -= 7 ;}
                            ui->equip_second_label->setText(QString::fromUtf8("伤害+15 穿甲-7"));}
                        else {doll[0].attack -= 15 ; doll[0].armor_piercing += 7 ;}break;

                    case 2: //专属
                        switch(id){
                        case 2: //2 M1911¤
                            if(checked == true)
                                {{doll[0].attack += 17 ; doll[0].armor_piercing -= 7 ;}
                                ui->equip_second_label->setText(QString::fromUtf8("伤害+17 穿甲-7"));}
                            else {doll[0].attack -= 17 ; doll[0].armor_piercing += 7 ;}break;

                        case 183: //竞争者
                            if(checked == true)
                                {{doll[0].armor_piercing += 180;}
                                ui->equip_second_label->setText(QString::fromUtf8("穿甲+180"));}
                            else {doll[0].armor_piercing -= 180;}break;

                        }break;

                    default:
                        break;
                    }
                });

        //HG装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("X骨"));
        button_3_1->setGeometry(0,0,60,22);
        button_3_1->setChecked(true);
        {doll[0].dodge += 20;}
        ui->equip_third_label->setText(QString::fromUtf8("回避+20"));

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("T骨"));
        button_3_2->setGeometry(60,0,60,22);

        QRadioButton* button_3_3 = new QRadioButton( ui->equip_third );
        button_3_3->setText(QString::fromUtf8("专属"));
        button_3_3->setGeometry(120,0,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        third_equip_group->addButton(button_3_3,3);
        button_3_1->show();
        button_3_2->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 7: //7 斯捷奇金
        case 418: //418 SEI

        {
            button_3_3->show();
            button_3_1->setChecked(false);
            button_3_3->setChecked(true);

            {doll[0].dodge -= 20;}
        }break;
        default:  break;
        }

        switch (id) { //有专属装备人形的初始设定,不要忘记之前已经设定的装备属性
        case 7: //7 斯捷奇金
            {{doll[0].dodge += 20; doll[0].critical_per += 0.2;}
            ui->equip_third_label->setText(QString::fromUtf8("回避+20 暴击+20%"));}break;
        case 418: //418 SEI
            {{doll[0].dodge += 34;}
            ui->equip_third_label->setText(QString::fromUtf8("回避+34"));}break;
        default:
            break;
        }

        if(id == 417) equip_special(doll[0].id , 3);//特殊人形装备格

        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //X骨
                        if(checked == true)
                            {ui->equip_third_label->setText(QString::fromUtf8("回避+20"));}
                        break;
                    case 2: //T骨
                        if(checked == true)
                            {{doll[0].attack -= 6; doll[0].dodge += 35;}
                            ui->equip_third_label->setText(QString::fromUtf8("回避+35 伤害-6"));}
                        else {doll[0].attack += 6; doll[0].dodge -= 35;}break;

                    case 3: //专属
                        switch(id){
                        case 7: //7 斯捷奇金
                            if(checked == true)
                                {{doll[0].dodge += 20; doll[0].critical_per += 0.2;}
                                ui->equip_third_label->setText(QString::fromUtf8("回避+20 暴击+20%"));}
                            else {doll[0].dodge -= 20; doll[0].critical_per -= 0.2;}break;


                        case 418: //418 SEI
                            if(checked == true)
                                {{doll[0].dodge += 34;}
                                ui->equip_third_label->setText(QString::fromUtf8("回避+34"));}
                            else {doll[0].dodge -= 34;}break;

                        }break;

                    default:
                        break;
                    }
                });
    }

    else if(doll[0].type == 2) //SMG
    {
        //SMG装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("X骨"));
        button_1_1->setGeometry(0,0,60,22);

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("T骨"));
        button_1_2->setGeometry(60,0,60,22);
        button_1_2->setChecked(true);
        doll[0].dodge += 35;
        doll[0].attack -= 6;
        ui->equip_first_label->setText(QString::fromUtf8("回避+35 伤害-6"));

        QRadioButton* button_1_3 = new QRadioButton( ui->equip_first );
        button_1_3->setText(QString::fromUtf8("专属"));
        button_1_3->setGeometry(120,0,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        first_equip_group->addButton(button_1_3,3);
        button_1_1->show();
        button_1_2->show();

        switch (id) { //预先打开专属button 才可传递数据
        case 26: //MP5¤
        case 93: //93 IDW¤
        case 101: //101 UMP9¤
        case 102: //102 UMP40
        case 103: //103 UMP45¤

        {
            doll[0].dodge -= 35;
            doll[0].attack += 6;
            button_1_3->show();
            button_1_2->setChecked(false);
            button_1_3->setChecked(true);
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 26: //26 MP5¤
            {doll[0].dodge += 58; doll[0].attack -= 6;}
            { ui->equip_first_label->setText(QString::fromUtf8("回避+58 伤害-6"));}break;
        case 93: //93 IDW¤
            {doll[0].dodge += 37; doll[0].attack -= 6; doll[0].fire_rate += 3;}
            { ui->equip_first_label->setText(QString::fromUtf8("回避+37 伤害-6 射速+3"));}break;
        case 101: //101 UMP9¤
        case 102: //102 UMP40
        case 103: //103 UMP45¤
            {doll[0].dodge += 35;}
            { ui->equip_first_label->setText(QString::fromUtf8("回避+35"));}break;

        default:
            break;
        }

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //X骨
                        if(checked == true)
                            {doll[0].dodge += 20;
                            ui->equip_first_label->setText(QString::fromUtf8("回避+20"));}
                        else {doll[0].dodge -= 20;} break;

                    case 2: //T骨
                        if(checked == true)
                            {doll[0].attack -= 6 ;doll[0].dodge += 35;
                            ui->equip_first_label->setText(QString::fromUtf8("回避+35 伤害-6"));}
                        else {doll[0].attack += 6 ;doll[0].dodge -= 35;}break;

                    case 3:
                        switch (id) {
                        case 26: //26 MP5¤
                            if(checked == true)
                                {doll[0].dodge += 58; doll[0].attack -= 6;
                                ui->equip_first_label->setText(QString::fromUtf8("回避+58 伤害-6"));}
                            else {doll[0].dodge -= 58; doll[0].attack += 6;}break;

                        case 93: //93 IDW¤
                            if(checked == true)
                                {{doll[0].dodge += 37; doll[0].attack -= 6; doll[0].fire_rate += 3;}
                                ui->equip_first_label->setText(QString::fromUtf8("回避+37 伤害-6 射速+3"));}
                            else {doll[0].dodge -= 37; doll[0].attack += 6; doll[0].fire_rate -= 3;}break;


                        case 101: //101 UMP9¤
                        case 102: //102 UMP40
                        case 103: //103 UMP45¤
                            if(checked == true)
                                {doll[0].dodge += 35;
                                ui->equip_first_label->setText(QString::fromUtf8("回避+35"));}
                            else  {doll[0].dodge -= 35;}break;


                        }break;
                    default:
                        break;
                    }
                });

        //SMG装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("空尖"));
        button_2_1->setGeometry(0,0,60,22);
        button_2_1->setChecked(true);
        {doll[0].attack += 15 ; doll[0].armor_piercing -= 7 ;}
        ui->equip_second_label->setText(QString::fromUtf8("伤害+15 穿甲-7"));

        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("专属"));
        button_2_2->setGeometry(60,0,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        button_2_1->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 419: //419 DOROTHY

        {
            button_2_2->show();
            button_2_1->setChecked(false);
            button_2_2->setChecked(true);

            doll[0].attack -= 15 ; doll[0].armor_piercing += 7 ;
        }break;
        default:  break;
        }

        switch (id) { //有专属装备人形的初始设定,不要忘记之前已经设定的装备属性
        case 419: //419 DOROTHY
            {{doll[0].attack += 22 ; doll[0].armor_piercing -= 7 ;}
            ui->equip_second_label->setText(QString::fromUtf8("伤害+22 穿甲-7"));}break;
        default:
            break;
        }

        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //空尖
                        if(checked == true)
                            {{doll[0].attack += 15 ; doll[0].armor_piercing -= 7 ;}
                            ui->equip_second_label->setText(QString::fromUtf8("伤害+15 穿甲-7"));}
                        else {doll[0].attack -= 15 ; doll[0].armor_piercing += 7 ;}break;

                    case 2: //专属
                        switch(id){
                        case 419: //419 DOROTHY
                            if(checked == true)
                                {{doll[0].attack += 22 ; doll[0].armor_piercing -= 7 ;}
                                ui->equip_second_label->setText(QString::fromUtf8("伤害+22 穿甲-7"));}
                            else {doll[0].attack -= 22 ; doll[0].armor_piercing += 7 ;}break;

                        }break;
                    default:
                        break;
                    }
                });

        //SMG装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("光瞄"));
        button_3_1->setGeometry(0,0,60,22);

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("全息"));
        button_3_2->setGeometry(60,0,60,22);

        QRadioButton* button_3_3 = new QRadioButton( ui->equip_third );
        button_3_3->setText(QString::fromUtf8("红点"));
        button_3_3->setGeometry(120,0,60,22);

        QRadioButton* button_3_4 = new QRadioButton( ui->equip_third );
        button_3_4->setText(QString::fromUtf8("夜视"));
        button_3_4->setGeometry(0,22,60,22);

        QRadioButton* button_3_5 = new QRadioButton( ui->equip_third );
        button_3_5->setText(QString::fromUtf8("消音"));
        button_3_5->setGeometry(60,22,60,22);
        button_3_5->setChecked(true);
        doll[0].critical_per += 0.2 ; doll[0].dodge += 10;
        ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+10"));

        QRadioButton* button_3_6 = new QRadioButton( ui->equip_third );
        button_3_6->setText(QString::fromUtf8("专属"));
        button_3_6->setGeometry(120,22,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        third_equip_group->addButton(button_3_3,3);
        third_equip_group->addButton(button_3_4,4);
        third_equip_group->addButton(button_3_5,5);
        third_equip_group->addButton(button_3_6,6);
        button_3_1->show();
        button_3_2->show();
        button_3_3->show();
        button_3_4->show();
        button_3_5->show();

        switch (id) { //预先打开专属button 才可传递数据
        case 17: //17 M3
        case 18: //18 MAC-10
        case 26: //26 MP5¤
        case 29: //29 司登MkⅡ¤
        case 32: //32 微型乌兹¤
        case 94: //94 64式¤
        case 101: //101 UMP9¤
        case 103: //103 UMP45¤

        {
            button_3_6->show();
            button_3_5->setChecked(false);
            button_3_6->setChecked(true);

            doll[0].critical_per -= 0.2 ; doll[0].dodge -= 10;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 17: //17 M3
            {{doll[0].attack += 4; doll[0].dodge += 21; doll[0].critical_per += 0.28; }
            ui->equip_third_label->setText(QString::fromUtf8("伤害+4 回避+21 暴击+28%"));}break;
        case 18: //18 MAC-10
            {{doll[0].fire_rate -= 4; doll[0].dodge += 20; doll[0].critical_per += 0.35; }
            ui->equip_third_label->setText(QString::fromUtf8("射速-4 回避+20 暴击+35%"));}break;
        case 26: //26 MP5¤
            {{doll[0].attack += 10; doll[0].hit += 15; doll[0].fire_rate -= 4; }
            ui->equip_third_label->setText(QString::fromUtf8("伤害+10 命中+15 射速-4"));}break;
        case 29: //29 司登MkⅡ¤
            {{doll[0].critical_per += 0.2; doll[0].dodge += 15; }
            ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+15"));}break;
        case 32: //32 微型乌兹¤
            {{doll[0].hit += 36; doll[0].fire_rate -= 1; }
            ui->equip_third_label->setText(QString::fromUtf8("命中+36 射速-1"));}break;
        case 94: //94 64式¤
            {{doll[0].critical_per += 0.2 ; doll[0].dodge += 15; }
            ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+15"));}break;
        case 101: //101 UMP9¤
            {{doll[0].attack += 10; doll[0].hit += 14; doll[0].fire_rate -= 3; }
            ui->equip_third_label->setText(QString::fromUtf8("伤害+10 命中+14 射速-3"));}break;
        case 103: //103 UMP45¤
            {{doll[0].critical_per += 0.25 ; doll[0].dodge += 15; }
            ui->equip_third_label->setText(QString::fromUtf8("暴击+25% 回避+15"));}break;

        default:
            break;
        }

        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //光瞄
                        if(checked == true)
                            {doll[0].critical_per += 0.48 ;
                            ui->equip_third_label->setText(QString::fromUtf8("暴击+48%"));}
                        else doll[0].critical_per -= 0.48 ;break;

                    case 2: //全息
                        if(checked == true)
                            {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                            ui->equip_third_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                        else {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;

                    case 3: //红点
                        if(checked == true)
                            {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                            ui->equip_third_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                        else {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;

                    case 4: //夜视
                        if(checked == true)
                            {doll[0].night_view_per += 1 ;
                            ui->equip_third_label->setText(QString::fromUtf8("夜视能力+100%"));}
                        else doll[0].night_view_per -= 1 ;break;

                    case 5: //消音
                        if(checked == true)
                            {doll[0].critical_per += 0.2 ;doll[0].dodge += 10;
                            ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                        else {doll[0].critical_per -= 0.2 ;doll[0].dodge -= 10;}break;

                    case 6: //专属
                        switch (id) {

                        case 17: //17 M3
                            if(checked == true)
                                {{doll[0].attack += 4; doll[0].critical_per += 0.28; doll[0].dodge += 21;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+4 回避+21 暴击+28%"));}
                            else {doll[0].attack -= 4; doll[0].critical_per -= 0.28; doll[0].dodge -= 21;}break;

                        case 18: //18 MAC-10
                            if(checked == true)
                                {{doll[0].fire_rate -= 4; doll[0].dodge += 20; doll[0].critical_per += 0.35; }
                                ui->equip_third_label->setText(QString::fromUtf8("射速-4 回避+20 暴击+35%"));}
                            else {doll[0].fire_rate += 4; doll[0].dodge -= 20; doll[0].critical_per -= 0.35; }break;

                        case 26: //26 MP5¤
                            if(checked == true)
                                {{doll[0].attack += 10; doll[0].hit += 15; doll[0].fire_rate -= 4; }
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+10 命中+15 射速-4"));}
                            else {doll[0].attack -= 10; doll[0].hit -= 15; doll[0].fire_rate += 4; }break;

                        case 29: //29 司登MkⅡ¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.2 ;doll[0].dodge += 15;}
                                ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+15"));}
                            else {doll[0].critical_per -= 0.2 ;doll[0].dodge -= 15;}break;

                        case 32: //32 微型乌兹¤
                            if(checked == true)
                                {{doll[0].hit += 36; doll[0].fire_rate -= 1; }
                                ui->equip_third_label->setText(QString::fromUtf8("命中+36 射速-1"));}
                            else {doll[0].hit += 36; doll[0].fire_rate -= 1; }break;

                        case 94: //94 64式¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.2 ;doll[0].dodge += 15;}
                                ui->equip_third_label->setText(QString::fromUtf8("暴击+20% 回避+15"));}
                            else {doll[0].critical_per -= 0.2 ;doll[0].dodge -= 15;}break;

                        case 101: //101 UMP9¤
                            if(checked == true)
                                {{doll[0].attack += 10; doll[0].hit += 14; doll[0].fire_rate -= 3; }
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+10 命中+14 射速-3"));}
                            else {doll[0].attack -= 10; doll[0].hit -= 14; doll[0].fire_rate += 3; }break;

                        case 103: //103 UMP45¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.25 ;doll[0].dodge += 15;}
                                ui->equip_third_label->setText(QString::fromUtf8("暴击+25% 回避+15"));}
                            else {doll[0].critical_per -= 0.25 ;doll[0].dodge -= 15;}break;

                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });

    }

    else if(doll[0].type == 3) //RF
    {
        //RF装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("穿甲"));
        button_1_1->setGeometry(0,0,60,22);
        button_1_1->setChecked(true);
        doll[0].armor_piercing += 180 ;
        ui->equip_first_label->setText(QString::fromUtf8("穿甲+180"));

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("专属"));
        button_1_2->setGeometry(60,0,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        button_1_1->show();

        switch (id) { //预先打开专属button 才可传递数据
        case 36: //36 春田
        case 53: //53 NTW-20

        {
            button_1_2->show();
            button_1_1->setChecked(false);
            button_1_2->setChecked(true);

            doll[0].armor_piercing -= 180 ;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 36: //36 春田
            {{doll[0].fire_rate += 10; doll[0].armor_piercing += 195;}
            ui->equip_first_label->setText(QString::fromUtf8("射速+10 穿甲+195"));}break;
        case 53: //53 NTW-20
            {{doll[0].attack += 10; doll[0].armor_piercing += 180;}
            ui->equip_first_label->setText(QString::fromUtf8("伤害+10 穿甲+180"));}break;
        default:
            break;
        }

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //穿甲
                        if(checked == true)
                            {doll[0].armor_piercing += 180 ;
                            ui->equip_first_label->setText(QString::fromUtf8("穿甲+180"));}
                        else {doll[0].armor_piercing -= 180 ;}break;

                    case 2: //专属
                        switch (id){
                        case 36: //36 春田
                            if(checked == true)
                                {{doll[0].fire_rate += 10; doll[0].armor_piercing += 195;}
                                ui->equip_first_label->setText(QString::fromUtf8("射速+10 穿甲+195"));}
                            else {doll[0].fire_rate -= 10; doll[0].armor_piercing -= 195;}break;

                        case 53: //53 NTW-20
                            if(checked == true)
                                {{doll[0].attack += 10; doll[0].armor_piercing += 180;}
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+10 穿甲+180"));}
                            else {doll[0].attack -= 10; doll[0].armor_piercing -= 180;}break;

                        }break;

                    default:
                        break;
                    }
                });

        //RF装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("光瞄"));
        button_2_1->setGeometry(0,0,60,22);
        button_2_1->setChecked(true);
        doll[0].critical_per += 0.48 ;
        ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));

        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("全息"));
        button_2_2->setGeometry(60,0,60,22);

        QRadioButton* button_2_3 = new QRadioButton( ui->equip_second );
        button_2_3->setText(QString::fromUtf8("红点"));
        button_2_3->setGeometry(120,0,60,22);

        QRadioButton* button_2_4 = new QRadioButton( ui->equip_second );
        button_2_4->setText(QString::fromUtf8("消音"));
        button_2_4->setGeometry(0,22,60,22);

        QRadioButton* button_2_5 = new QRadioButton( ui->equip_second );
        button_2_5->setText(QString::fromUtf8("专属"));
        button_2_5->setGeometry(60,22,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        second_equip_group->addButton(button_2_3,3);
        second_equip_group->addButton(button_2_4,4);
        second_equip_group->addButton(button_2_5,5);
        button_2_1->show();
        button_2_2->show();
        button_2_3->show();
        button_2_4->show();

        switch (id) { //预先打开专属button 才可传递数据
        case 37: //37 M14¤
        case 39: //39 莫辛-纳甘¤
        case 46: //46 Kar98k
        case 50: //50 李-恩菲尔德
        case 51: //51 FN-49¤
        case 52: //52 BM59
        case 95: //95 汉阳造88式¤

        {
            button_2_5->show();
            button_2_1->setChecked(false);
            button_2_5->setChecked(true);

            doll[0].critical_per -= 0.48;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 37: //37 M14¤
            {{doll[0].hit += 10; doll[0].critical_per += 0.48; }
            ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 命中+10"));}break;
        case 39: //39 莫辛-纳甘¤
            {{doll[0].critical_per += 0.5; doll[0].hit += 6; }
            ui->equip_second_label->setText(QString::fromUtf8("暴击+50% 命中+6"));}break;
        case 46: //46 Kar98k
            {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.2; }
            ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 暴伤+20%"));}break;
        case 50: //50 李-恩菲尔德
            {{doll[0].critical_per += 0.48; doll[0].fire_rate += 4; }
            ui->equip_second_label->setText(QString::fromUtf8("射速+4 暴击+48%"));}break;
        case 51: //51 FN-49¤
            {{doll[0].critical_per += 0.48; doll[0].fire_rate += 5; }
            ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 射速+5"));}break;
        case 52: //52 BM59
            {{doll[0].critical_per += 0.5; doll[0].fire_rate += 6; doll[0].hit += 8; }
            ui->equip_second_label->setText(QString::fromUtf8("射速+6 命中+8 暴击+50%"));}break;
        case 95: //95 汉阳造88式¤
            {{doll[0].critical_per += 0.5; doll[0].attack += 5; }
            ui->equip_second_label->setText(QString::fromUtf8("暴击+50% 命中+5"));}break;
        default:
            break;
        }

        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //光瞄
                        if(checked == true)
                            {doll[0].critical_per += 0.48 ;
                            ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));}
                        else {doll[0].critical_per -= 0.48 ;}break;

                    case 2: //全息
                        if(checked == true)
                            {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                            ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                        else {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;

                    case 3: //红点
                        if(checked == true)
                            {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                            ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                        else {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;

                    case 4: //消音
                        if(checked == true)
                            {{doll[0].critical_per += 0.2 ;}
                            ui->equip_second_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                        else {doll[0].critical_per -= 0.2 ;}break;

                    case 5: //专属
                        switch (id) {

                        case 37: //M14¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].hit += 10; }
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 命中+10"));}
                            else {doll[0].critical_per -= 0.48; doll[0].hit -= 10;} break;

                        case 39: //莫辛-纳甘¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.5; doll[0].hit += 6; }
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+50% 命中+6"));}
                            else {doll[0].critical_per -= 0.5; doll[0].hit -= 6;} break;

                        case 46: //46 Kar98k
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.2; }
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 暴伤+20%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].crit_damage_rate -= 0.2;} break;

                        case 50: //50 李-恩菲尔德
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].fire_rate += 4; }
                                ui->equip_second_label->setText(QString::fromUtf8("射速+4 暴击+48%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].fire_rate -= 4; } break;

                        case 51: //51 FN-49¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].fire_rate += 5; }
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+48% 射速+5"));}
                            else {doll[0].critical_per -= 0.48; doll[0].fire_rate -= 5; } break;

                        case 52: //52 BM59
                            if(checked == true)
                                {{doll[0].critical_per += 0.5; doll[0].fire_rate += 6; doll[0].hit += 8; }
                                ui->equip_second_label->setText(QString::fromUtf8("射速+6 命中+8 暴击+50%"));}
                            else {doll[0].critical_per -= 0.5; doll[0].fire_rate -= 6; doll[0].hit -= 8; } break;

                        case 95: //95 汉阳造88式¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.5; doll[0].attack += 5; }
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+50% 命中+5"));}
                            else {doll[0].critical_per -= 0.5; doll[0].attack -= 5; } break;

                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });

        //RF装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("披风"));
        button_3_1->setGeometry(0,0,60,22);
        button_3_1->setChecked(true);
        doll[0].crit_damage_rate += 0.25 ;
        ui->equip_third_label->setText(QString::fromUtf8("暴伤+25% 移速-3"));

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("专属"));
        button_3_2->setGeometry(60,0,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        button_3_1->show();

        switch (id) { //预先打开专属button 才可传递数据
        case 39: //39 莫辛-纳甘¤
        case 42: //42 PTRD
        case 44: //44 SV-98¤
        case 420: //420 STELLA

        {
            button_3_2->show();
            button_3_1->setChecked(false);
            button_3_2->setChecked(true);
            doll[0].crit_damage_rate -= 0.25;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 39: //39 莫辛-纳甘¤
            {{doll[0].attack += 30; doll[0].crit_damage_rate += 0.3; doll[0].dodge += 5;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+30 暴伤+30% 回避+5"));}break;
        case 42: //42 PTRD
            {{doll[0].fire_rate += 4; doll[0].crit_damage_rate += 0.25;}
            ui->equip_third_label->setText(QString::fromUtf8("射速+4 暴伤+25% 移速-3"));}break;
        case 44: //44 SV-98¤
            {{doll[0].attack += 6; doll[0].crit_damage_rate += 0.25;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+6 暴伤+25% 移速-3"));}break;
        case 420: //420 STELLA
            {{doll[0].fire_rate += 3; doll[0].crit_damage_rate += 0.30;}
            ui->equip_third_label->setText(QString::fromUtf8("射速+3 暴伤+30% 移速-3"));}break;
        default:
            break;
        }

        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //披风
                        if(checked == true)
                            {doll[0].crit_damage_rate += 0.25 ;
                            ui->equip_third_label->setText(QString::fromUtf8("暴伤+25% 移速-3"));}
                        else {doll[0].crit_damage_rate -= 0.25 ;}break;

                    case 2: //专属
                        switch (id)
                        case 39: {//莫辛-纳甘¤
                            if(checked == true)
                                {{doll[0].attack += 30; doll[0].crit_damage_rate += 0.3; doll[0].dodge += 5; }
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+30 暴伤+30% 回避+5"));}
                            else {doll[0].attack -= 30; doll[0].crit_damage_rate -= 0.3; doll[0].dodge -= 5;}}break;

                        case 42: {//PTRD
                            if(checked == true)
                                {{doll[0].fire_rate += 4; doll[0].crit_damage_rate += 0.25; }
                                ui->equip_third_label->setText(QString::fromUtf8("射速+4 暴伤+25% 移速-3"));}
                            else {doll[0].fire_rate -= 4; doll[0].crit_damage_rate -= 0.25; }}break;

                        case 44: {//SV-98¤
                            if(checked == true)
                                {{doll[0].attack += 6; doll[0].crit_damage_rate += 0.25; }
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+6 暴伤+25% 移速-3"));}
                            else {doll[0].attack -= 6; doll[0].crit_damage_rate -= 0.25; }}break;

                        case 420: {//STELLA
                            if(checked == true)
                                {{doll[0].fire_rate += 3; doll[0].crit_damage_rate += 0.3; }
                                ui->equip_third_label->setText(QString::fromUtf8("射速+3 暴伤+3% 移速-3"));}
                            else {doll[0].fire_rate -= 3; doll[0].crit_damage_rate -= 0.3; }}break;

                    default:
                        break;
                    }
                });
    }

    else if(doll[0].type == 4) //AR
    {
        //AR装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("光瞄"));
        button_1_1->setGeometry(0,0,60,22);
        button_1_1->setChecked(true);
        doll[0].critical_per += 0.48 ;
        ui->equip_first_label->setText(QString::fromUtf8("暴击+48%"));

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("全息"));
        button_1_2->setGeometry(60,0,60,22);

        QRadioButton* button_1_3 = new QRadioButton( ui->equip_first );
        button_1_3->setText(QString::fromUtf8("红点"));
        button_1_3->setGeometry(120,0,60,22);

        QRadioButton* button_1_4 = new QRadioButton( ui->equip_first );
        button_1_4->setText(QString::fromUtf8("夜视"));
        button_1_4->setGeometry(0,22,60,22);

        QRadioButton* button_1_5 = new QRadioButton( ui->equip_first );
        button_1_5->setText(QString::fromUtf8("消音"));
        button_1_5->setGeometry(60,22,60,22);

        QRadioButton* button_1_6 = new QRadioButton( ui->equip_first );
        button_1_6->setText(QString::fromUtf8("专属"));
        button_1_6->setGeometry(120,22,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        first_equip_group->addButton(button_1_3,3);
        first_equip_group->addButton(button_1_4,4);
        first_equip_group->addButton(button_1_5,5);
        first_equip_group->addButton(button_1_6,6);
        button_1_1->show();
        button_1_2->show();
        button_1_3->show();
        button_1_4->show();
        button_1_5->show();

        switch (id) { //预先打开专属button才可传递数据
        case 58: //58 AK-47
        case 63: //63 G3¤
        case 64: //64 G36¤
        case 65: //65 HK416¤
        case 66: //66 56-1式
        case 69: //69 FAMAS
        case 74: //74 SIG-510
        case 118: //118 9A-91
        case 129: //129 95式
        case 130: //130 97式
        case 172: //172 RFB

        {
            button_1_6->show();
            button_1_1->setChecked(false);
            button_1_6->setChecked(true);

            doll[0].critical_per -= 0.48; //去除初始设定装备属性
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 58: //58 AK-47
        case 66: //66 56-1式
            {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.44;}
            ui->equip_first_label->setText(QString::fromUtf8("暴击+48% 暴伤+44%"));}break;
        case 63: //63 G3¤
            {{doll[0].critical_per += 0.48; doll[0].attack += 4; }
            ui->equip_first_label->setText(QString::fromUtf8("伤害+4 暴击+48%"));}break;
        case 64: //64 G36¤
            {{doll[0].critical_per += 0.48; doll[0].hit += 8; }
            ui->equip_first_label->setText(QString::fromUtf8("命中+8 暴击+48%"));}break;
        case 65: //65 HK416¤
            {{doll[0].critical_per += 0.25; doll[0].attack += 9; doll[0].hit += 14; }
            ui->equip_first_label->setText(QString::fromUtf8("伤害+8 命中+14 暴击+25%"));}break;
        case 69: //69 FAMAS
            {{doll[0].attack += 4; doll[0].hit += 4; doll[0].critical_per += 0.48;}
            ui->equip_first_label->setText(QString::fromUtf8("伤害+4 命中+4 暴击+48%"));}break;
        case 74: //74 SIG-510
            {{doll[0].attack += 9; doll[0].hit += 4; doll[0].critical_per += 0.5;}
            ui->equip_first_label->setText(QString::fromUtf8("伤害+9 命中+4 暴击+50%"));}break;
        case 118: //118 9A-91
            {{doll[0].attack += 8; doll[0].night_view_per += 1 ;}
            ui->equip_first_label->setText(QString::fromUtf8("伤害+8 夜视能力+100%"));}break;
        case 129: //129 95式
        case 130: //130 97式
            {{doll[0].critical_per += 0.48; doll[0].attack += 5; }
            ui->equip_first_label->setText(QString::fromUtf8("伤害+5 暴击+48%"));}break;
        case 172: //172 RFB
            {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.18;}
            ui->equip_first_label->setText(QString::fromUtf8("暴击+48% 暴伤+18%"));}break;
        default:
            break;
        }

        if(id == 54) equip_special(doll[0].id , 1);//特殊人形装备格

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //光瞄
                        if(checked == true)
                            {doll[0].critical_per += 0.48 ;
                            ui->equip_first_label->setText(QString::fromUtf8("暴击+48%"));}
                        else doll[0].critical_per -= 0.48 ;break;

                    case 2: //全息
                        if(checked == true)
                            {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                            ui->equip_first_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                        else {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;

                    case 3: //红点
                        if(checked == true)
                            {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                            ui->equip_first_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                        else {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;

                    case 4: //夜视
                        if(checked == true)
                            {doll[0].night_view_per += 1 ;
                            ui->equip_first_label->setText(QString::fromUtf8("夜视能力+100%"));}
                        else doll[0].night_view_per -= 1 ;break;

                    case 5: //消音
                        if(checked == true)
                            {doll[0].critical_per += 0.2 ;
                            ui->equip_first_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                        else doll[0].critical_per -= 0.2 ;break;

                    case 6: //专属
                        switch (id) {

                        case 58: //58 AK-47
                        case 66: //66 56-1式
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.44;}
                                ui->equip_first_label->setText(QString::fromUtf8("暴击+48% 暴伤+44%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].crit_damage_rate -= 0.44;}break;

                        case 63: //63 G3¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].attack += 4; }
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+4 暴击+48%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].attack -= 4; }break;

                        case 64: //64 G36¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].hit += 8; }
                                ui->equip_first_label->setText(QString::fromUtf8("命中+8 暴击+48%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].hit -= 8; }break;

                        case 65: //65 HK416¤
                            if(checked == true)
                                {{doll[0].critical_per += 0.25; doll[0].attack += 9; doll[0].hit += 14; }
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+8 命中+14 暴击+25%"));}
                            else {doll[0].critical_per -= 0.25; doll[0].attack -= 9; doll[0].hit -= 14; }break;

                        case 69: //69 FAMAS
                            if(checked == true)
                                {{doll[0].attack += 4; doll[0].hit += 4; doll[0].critical_per += 0.48;}
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+4 命中+4 暴击+48%"));}
                            else {doll[0].attack -= 4; doll[0].hit -= 4; doll[0].critical_per -= 0.48;}break;

                        case 74: //74 SIG-510
                            if(checked == true)
                                {{doll[0].attack += 9; doll[0].hit += 4; doll[0].critical_per += 0.5;}
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+9 命中+4 暴击+50%"));}
                            else {doll[0].attack -= 9; doll[0].hit -= 4; doll[0].critical_per -= 0.5;}break;

                        case 118: //118 9A-91
                            if(checked == true)
                                {{doll[0].attack += 8; doll[0].night_view_per += 1 ;}
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+8 夜视能力+100%"));}
                            else {doll[0].attack -= 8; doll[0].night_view_per -= 1 ;}break;

                        case 129: //129 95式
                        case 130: //130 97式
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].attack += 5; }
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+5 暴击+48%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].attack -= 5; }break;

                        case 172: //172 RFB
                            if(checked == true)
                                {{doll[0].critical_per += 0.48; doll[0].crit_damage_rate += 0.18;}
                                ui->equip_first_label->setText(QString::fromUtf8("暴击+48% 暴伤+18%"));}
                            else {doll[0].critical_per -= 0.48; doll[0].crit_damage_rate -= 0.18;}break;


                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });

        //AR装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("高速"));
        button_2_1->setGeometry(0,0,60,22);
        button_2_1->setChecked(true);
        doll[0].attack += 20;
        ui->equip_second_label->setText(QString::fromUtf8("伤害+20"));

        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("专属"));
        button_2_2->setGeometry(60,0,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        button_2_1->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 60: //60 AS Val¤
        case 61: //61 StG44¤

        {
            button_2_2->show();
            button_2_1->setChecked(false);
            button_2_2->setChecked(true);

            doll[0].attack -= 20;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 60:
            {{doll[0].attack += 24;}
            ui->equip_second_label->setText(QString::fromUtf8("伤害+24"));}break;
        case 61:
            {{doll[0].attack += 24;}
            ui->equip_second_label->setText(QString::fromUtf8("伤害+24"));}break;
        default:
            break;
        }

        if(id == 54 || id == 56 || id == 57) equip_special(doll[0].id , 2);//特殊人形装备格

        else{
        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //高速
                        if(checked == true)
                            {doll[0].attack += 20;
                            ui->equip_second_label->setText(QString::fromUtf8("伤害+20"));}
                        else
                            doll[0].attack -= 20;break;
                    case 2: //专属
                        switch (id) { //专属人形
                        case 60: //60 AS Val¤
                            if(checked == true)
                                {doll[0].attack += 24;
                                ui->equip_second_label->setText(QString::fromUtf8("伤害+24"));}
                            else
                                {doll[0].attack -= 24;}break;

                        case 61: //61 StG44¤
                            if(checked == true)
                                {doll[0].attack += 24;
                                ui->equip_second_label->setText(QString::fromUtf8("伤害+24"));}
                            else
                                {doll[0].attack -= 24;}break;

                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });
        }

        //AR装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("X骨"));
        button_3_1->setGeometry(0,0,60,22);
        button_3_1->setChecked(true);
        doll[0].dodge += 20;
        ui->equip_third_label->setText(QString::fromUtf8("回避+20"));

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("T骨"));
        button_3_2->setGeometry(60,0,60,22);

        QRadioButton* button_3_3 = new QRadioButton( ui->equip_third );
        button_3_3->setText(QString::fromUtf8("专属"));
        button_3_3->setGeometry(120,0,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        third_equip_group->addButton(button_3_3,3);
        button_3_1->show();
        button_3_2->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 55: //55 M4A1¤
        case 62: //62 G41
        case 65: //65 HK416¤

        {
            doll[0].dodge -= 20;
            button_3_3->show();
            button_3_1->setChecked(false);
            button_3_3->setChecked(true);
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 55: //M4A1¤
            {{doll[0].attack += 5; }
            ui->equip_third_label->setText(QString::fromUtf8("伤害+5 护甲+15"));}break;
        case 62: //G41
            {{doll[0].attack += 5 ; doll[0].hit += 5; }
            ui->equip_third_label->setText(QString::fromUtf8("伤害+5 命中+5"));}break;
        case 65: //HK416¤
            {{doll[0].crit_damage_rate += 0.1; }
            ui->equip_third_label->setText(QString::fromUtf8("暴伤+10% 回避+10"));}break;
        default:
            break;
        }

        if(id == 54 || id == 56 || id == 57) equip_special(doll[0].id , 3);

        else {
        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //X骨
                        if(checked == true)
                            ui->equip_third_label->setText(QString::fromUtf8("回避+20"));
                        break;
                    case 2: //T骨
                        if(checked == true)
                            {doll[0].attack -= 6 ;
                            ui->equip_third_label->setText(QString::fromUtf8("回避+35 伤害-6"));}
                        else
                            doll[0].attack += 6 ;
                        break;
                    case 3: //专属
                        switch (id) { //专属人形
                        case 55: //M4A1¤
                            if(checked == true)
                                {doll[0].attack += 5;
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+5 护甲+15"));}
                            else
                                {doll[0].attack -= 5;}
                            break;
                        case 62: //G41
                            if(checked == true)
                                {doll[0].attack += 5 ; doll[0].hit += 5;
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+5 命中+5"));}
                            else
                                {doll[0].attack -= 5 ; doll[0].hit -= 5;}
                            break;
                        case 65: //HK416¤
                            if(checked == true)
                                {doll[0].crit_damage_rate += 0.1;
                                ui->equip_third_label->setText(QString::fromUtf8("暴伤+10% 回避+10"));}
                            else
                                {doll[0].crit_damage_rate -= 0.1; }
                            break;
                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });
        }
    }

    else if(doll[0].type == 5) //MG
    {
        //MG装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("穿甲"));
        button_1_1->setGeometry(0,0,60,22);
        button_1_1->setChecked(true);
        doll[0].armor_piercing += 180 ;
        ui->equip_first_label->setText(QString::fromUtf8("穿甲+180"));

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("专属"));
        button_1_2->setGeometry(60,0,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        button_1_1->show();

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //穿甲
                        if(checked == true)
                            {doll[0].armor_piercing += 180 ;
                            ui->equip_first_label->setText(QString::fromUtf8("穿甲+180"));}
                        else
                            doll[0].armor_piercing -= 180 ;break;
                    case 2: //专属
                            break;
                    default:
                        break;
                    }
                });

        //MG装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("光瞄"));
        button_2_1->setGeometry(0,0,60,22);
        button_2_1->setChecked(true);
        doll[0].critical_per += 0.48 ;
        ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));


        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("全息"));
        button_2_2->setGeometry(60,0,60,22);

        QRadioButton* button_2_3 = new QRadioButton( ui->equip_second );
        button_2_3->setText(QString::fromUtf8("红点"));
        button_2_3->setGeometry(120,0,60,22);

        QRadioButton* button_2_4 = new QRadioButton( ui->equip_second );
        button_2_4->setText(QString::fromUtf8("专属"));
        button_2_4->setGeometry(0,22,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        second_equip_group->addButton(button_2_3,3);
        second_equip_group->addButton(button_2_4,4);
        button_2_1->show();
        button_2_2->show();
        button_2_3->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 75: //75 M1918¤
        case 81: //81 LWMMG¤
        case 89: //89 布伦¤
        case 110: //110 FG-42
        case 125: //125 MG4

        {
            doll[0].critical_per -= 0.48 ;
            button_2_4->show();
            button_2_1->setChecked(false);
            button_2_4->setChecked(true);
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 75: //M1918¤
            {{doll[0].hit += 30; doll[0].fire_rate -= 1; doll[0].critical_per += 0.1;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1 暴击+10%"));}break;
        case 81: //LWMMG¤
            {{doll[0].hit += 34; doll[0].attack += 2; doll[0].fire_rate -= 1;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+34 伤害+2 射速-1"));}break;
        case 89: //布伦¤
            {{doll[0].hit += 30; doll[0].attack += 5; doll[0].fire_rate -= 1;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+30 伤害+5 射速-1"));}break;
        case 110: //FG-42
            {{doll[0].hit += 32; doll[0].fire_rate -= 1; doll[0].critical_per += 0.24;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+32 射速-1 暴击+24%"));}break;
        case 125: //MG4
            {{doll[0].hit += 36; doll[0].fire_rate -= 1; doll[0].critical_per += 0.25;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+36 射速-1 暴击+25%"));}break;

        default:
            break;
        }

        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //光瞄
                        if(checked == true)
                            {doll[0].critical_per += 0.48 ;
                            ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));}
                        else
                            doll[0].critical_per -= 0.48 ;break;
                    case 2: //全息
                        if(checked == true)
                            {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                            ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                        else
                            {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;
                    case 3: //红点
                        if(checked == true)
                            {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                            ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                        else
                            {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;
                    case 4: //专属
                        switch (doll[0].id) {
                        case 75: //M1918¤
                            if(checked == true)
                                {{doll[0].hit += 30; doll[0].fire_rate -= 1; doll[0].critical_per += 0.1 ;}
                                ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1 暴击+10%"));}
                            else {doll[0].hit -= 30; doll[0].fire_rate += 1; doll[0].critical_per -= 0.1 ;}break;

                        case 81: //LWMMG¤
                            if(checked == true)
                                {{doll[0].hit += 34; doll[0].attack += 2; doll[0].fire_rate -= 1;}
                                ui->equip_second_label->setText(QString::fromUtf8("命中+34 伤害+2 射速-1"));}
                            else {doll[0].hit -= 34; doll[0].attack -= 2; doll[0].fire_rate += 1;}break;

                        case 89: //布伦¤
                            if(checked == true)
                                {{doll[0].hit += 30; doll[0].attack += 5; doll[0].fire_rate -= 1;}
                                ui->equip_second_label->setText(QString::fromUtf8("命中+30 伤害+5 射速-1"));}
                            else {doll[0].hit -= 30; doll[0].attack -= 5; doll[0].fire_rate += 1;}break;

                        case 110: //FG-42
                            if(checked == true)
                                {{doll[0].hit += 32; doll[0].fire_rate -= 1; doll[0].critical_per += 0.24;}
                                ui->equip_second_label->setText(QString::fromUtf8("命中+32 射速-1 暴击+24%"));}
                            else {doll[0].hit -= 32; doll[0].fire_rate += 1; doll[0].critical_per -= 0.24;}break;

                        case 125: //MG4
                            if(checked == true)
                                {{doll[0].hit += 36; doll[0].fire_rate -= 1; doll[0].critical_per += 0.25;}
                                ui->equip_second_label->setText(QString::fromUtf8("命中+36 射速-1 暴击+25%"));}
                            else {doll[0].hit -= 36; doll[0].fire_rate += 1; doll[0].critical_per -= 0.25 ;}break;


                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });

        //MG装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("弹链"));
        button_3_1->setGeometry(0,0,60,22);
        button_3_1->setChecked(true);
        doll[0].bullet_number += 5 ;
        doll[0].dodge -= 2;
        ui->equip_third_label->setText(QString::fromUtf8("弹链+5 回避-2"));

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("专属"));
        button_3_2->setGeometry(60,0,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        button_3_1->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 75: //75 M1918¤
        case 84: //84 RPD
        case 88: //88 MG3
        case 185: //185 阿梅利
        case 421: //421 ALMA

        {
            doll[0].bullet_number -= 5 ;
            doll[0].dodge += 2;
            button_3_2->show();
            button_3_1->setChecked(false);
            button_3_2->setChecked(true);
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 75: //M1918¤
            {{doll[0].attack -= 2; doll[0].fire_rate -= 1; doll[0].bullet_number += 6 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害-2 射速-1 弹链+6"));}break;
        case 84: //84 RPD
            {{doll[0].attack += 6; doll[0].dodge -= 2; doll[0].bullet_number += 5 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+6 回避-2 弹链+5"));}break;
        case 88: //MG3
            {{doll[0].attack -= 25; doll[0].hit -= 10; doll[0].dodge -= 2; doll[0].bullet_number += 30 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害-25 命中-10 弹链+30 回避-2"));}break;
        case 185: //阿梅利
            {{doll[0].attack += 8; doll[0].hit -= 3; doll[0].bullet_number += 6 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+8 命中-3 弹链+6"));}break;
        case 421: //ALMA
            {{doll[0].attack += 6; doll[0].dodge -= 2; doll[0].bullet_number += 6 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+6 回避-2 弹链+6"));}break;
        default:
            break;
        }

        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //弹链
                        if(checked == true)
                            {doll[0].bullet_number += 5;
                            ui->equip_third_label->setText(QString::fromUtf8("弹链+5 回避-2"));}
                        else doll[0].bullet_number -= 5; break;

                    case 2: //专属
                        switch (id) { //专属人形
                        case 75: //M1918¤
                            if(checked == true)
                                {{doll[0].attack -= 2; doll[0].fire_rate -= 1; doll[0].bullet_number += 6 ;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害-2 射速-1 弹链+6"));}
                            else {doll[0].attack += 2; doll[0].fire_rate += 1; doll[0].bullet_number -= 6 ;}break;

                        case 84: //84 RPD
                            if(checked == true)
                                {{doll[0].attack += 6; doll[0].dodge -= 2; doll[0].bullet_number += 5 ;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+6 回避-2 弹链+5"));}
                            else {doll[0].attack -= 6; doll[0].dodge += 2; doll[0].bullet_number -= 5 ;}break;

                        case 88: //MG3
                            if(checked == true)
                                {{doll[0].attack -= 25; doll[0].hit -= 10; doll[0].dodge -= 2; doll[0].bullet_number += 30 ;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害-25 命中-10 弹链+30 回避-2"));}
                            else {doll[0].attack += 25; doll[0].hit += 10; doll[0].dodge += 2; doll[0].bullet_number -= 30 ;}break;

                        case 185: //185 阿梅利
                            if(checked == true)
                                {{doll[0].attack += 8; doll[0].hit -= 3; doll[0].bullet_number += 6 ;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+8 命中-3 弹链+6"));}
                            else {doll[0].attack -= 8; doll[0].hit += 3; doll[0].bullet_number -= 6 ;}break;

                        case 421: //421 ALMA
                            if(checked == true)
                                {{doll[0].attack += 6; doll[0].dodge -= 2; doll[0].bullet_number += 6 ;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+6 回避-2 弹链+6"));}
                            else {doll[0].attack -= 6; doll[0].dodge += 2; doll[0].bullet_number -= 6 ;}break;

                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });
    }

    else if(doll[0].type == 6) //SG
    {
        //SG装备格1
        QButtonGroup* first_equip_group;
        first_equip_group = new QButtonGroup( ui->equip_first );

        QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
        button_1_1->setText(QString::fromUtf8("板甲"));
        button_1_1->setGeometry(0,0,60,22);
        button_1_1->setChecked(true);
        doll[0].armor += 10; doll[0].dodge -= 2;
        ui->equip_first_label->setText(QString::fromUtf8("护甲+10 回避-2"));

        QRadioButton* button_1_2 = new QRadioButton( ui->equip_first );
        button_1_2->setText(QString::fromUtf8("专属"));
        button_1_2->setGeometry(60,0,60,22);

        first_equip_group->addButton(button_1_1,1);
        first_equip_group->addButton(button_1_2,2);
        button_1_1->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 422 : //422 DANA

        {
            button_1_2->show();
            button_1_1->setChecked(false);
            button_1_2->setChecked(true);
            doll[0].armor -= 10; doll[0].dodge += 2;
        }break;
        default:
            break;
        }

        switch (id) { //有专属装备人形的初始设定
        case 422: //DANA
            {{doll[0].armor += 11; doll[0].dodge -= 2; doll[0].attack += 6;}
            ui->equip_first_label->setText(QString::fromUtf8("护甲+11 回避-2 伤害+6"));}break;

        default:
            break;
        }

        connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //穿甲
                        if(checked == true)
                            {{doll[0].armor += 10; doll[0].dodge -= 2;}
                            ui->equip_first_label->setText(QString::fromUtf8("护甲+10 回避-2"));}
                        else
                            {doll[0].armor -= 10; doll[0].dodge += 2;
                            ui->equip_first_label->setText(QString::fromUtf8("护甲+10 回避-2"));}break;
                    case 2: //专属
                        switch (id) { //专属人形
                        case 422: //DANA
                            if(checked == true)
                                {{doll[0].armor += 11; doll[0].dodge -= 2; doll[0].attack += 6;}
                                ui->equip_first_label->setText(QString::fromUtf8("护甲+11 回避-2 伤害+6"));}
                            else {doll[0].armor -= 11; doll[0].dodge += 2; doll[0].attack -= 6;}break;


                        default:
                            break;
                        }break;
                    default:
                        break;
                    }
                });

        //SG装备格2
        QButtonGroup* second_equip_group;
        second_equip_group = new QButtonGroup( ui->equip_second );

        QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
        button_2_1->setText(QString::fromUtf8("独头"));
        button_2_1->setGeometry(0,0,60,22);

        QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
        button_2_2->setText(QString::fromUtf8("猎鹿"));
        button_2_2->setGeometry(60,0,60,22);
        button_2_2->setChecked(true);
        doll[0].fire_number = doll[0].sign_z[0]*5; doll[0].attack += 15; doll[0].crit_damage_rate += 0.22;
        doll[0].sign_z[1] = 0;
        ui->equip_second_label->setText(QString::fromUtf8("伤害+15 暴伤+22%"));

        QRadioButton* button_2_3 = new QRadioButton( ui->equip_second );
        button_2_3->setText(QString::fromUtf8("专属"));
        button_2_3->setGeometry(0,22,60,22);

        second_equip_group->addButton(button_2_1,1);
        second_equip_group->addButton(button_2_2,2);
        second_equip_group->addButton(button_2_3,3);
        button_2_1->show();
        button_2_2->show();

        switch (id) { //预先打开专属button_3_3才可传递数据
        case 158: //158 KS-23

        {
            button_2_3->show();
            button_2_1->setChecked(false);
            button_2_3->setChecked(true);

            doll[0].attack -= 15; doll[0].crit_damage_rate -= 0.22;
        }break;
        default:  break;
        }

        switch (id) { //有专属装备人形的初始设定,不要忘记之前已经设定的装备属性
        case 158: //158 KS-23
            {{doll[0].attack += 18; doll[0].dodge += 4; doll[0].crit_damage_rate += 0.27;}
            ui->equip_second_label->setText(QString::fromUtf8("伤害+18 命中+4 爆伤+27%"));}break;
        default:
            break;
        }

        connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //独头
                        if(checked == true)
                            {doll[0].attack *= 3; doll[0].hit += 20; doll[0].fire_number = 5; doll[0].sign_z[1] = 1;
                            ui->equip_second_label->setText(QString::fromUtf8("目标-2 伤害*3 命中+20"));}
                        else {doll[0].attack /= 3; doll[0].hit -= 20; doll[0].fire_number = doll[0].sign_z[0]*5; doll[0].sign_z[1] = 0;}break;

                    case 2: //猎鹿
                        if(checked == true)
                            {doll[0].attack += 15 ;doll[0].crit_damage_rate += 0.22;
                            ui->equip_second_label->setText(QString::fromUtf8("伤害+15 暴伤+22%"));}
                        else {doll[0].attack -= 15 ;doll[0].crit_damage_rate -= 0.22;}break;

                    case 3: //专属
                        switch (doll[0].id) {
                        case 158: //158 KS-23
                            if(checked == true)
                                {{doll[0].attack += 18; doll[0].dodge += 4; doll[0].crit_damage_rate += 0.27;}
                                ui->equip_second_label->setText(QString::fromUtf8("伤害+18 命中+4 爆伤+27%"));}
                            else {doll[0].attack -= 18; doll[0].dodge -= 4; doll[0].crit_damage_rate -= 0.27;}break;


                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });

        //SG装备格3
        QButtonGroup* third_equip_group;
        third_equip_group = new QButtonGroup( ui->equip_third );

        QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
        button_3_1->setText(QString::fromUtf8("光瞄"));
        button_3_1->setGeometry(0,0,60,22);

        QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
        button_3_2->setText(QString::fromUtf8("全息"));
        button_3_2->setGeometry(60,0,60,22);

        QRadioButton* button_3_3 = new QRadioButton( ui->equip_third );
        button_3_3->setText(QString::fromUtf8("红点"));
        button_3_3->setGeometry(120,0,60,22);
        button_3_3->setChecked(true);
        doll[0].hit += 30 ; doll[0].fire_rate -= 1;
        ui->equip_third_label->setText(QString::fromUtf8("命中+30 射速-1"));

        QRadioButton* button_3_4 = new QRadioButton( ui->equip_third );
        button_3_4->setText(QString::fromUtf8("夜视"));
        button_3_4->setGeometry(0,22,60,22);

        QRadioButton* button_3_5 = new QRadioButton( ui->equip_third );
        button_3_5->setText(QString::fromUtf8("专属"));
        button_3_5->setGeometry(60,22,60,22);

        third_equip_group->addButton(button_3_1,1);
        third_equip_group->addButton(button_3_2,2);
        third_equip_group->addButton(button_3_3,3);
        third_equip_group->addButton(button_3_4,4);
        third_equip_group->addButton(button_3_5,5);
        button_3_1->show();
        button_3_2->show();
        button_3_3->show();
        button_3_4->show();

        connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
              [=](int i, bool checked)
                {
                    switch (i) {
                    case 1: //光瞄
                        if(checked == true)
                            {doll[0].critical_per += 0.48 ;
                            ui->equip_third_label->setText(QString::fromUtf8("暴击+48%"));}
                        else
                            doll[0].critical_per -= 0.48 ;break;
                    case 2: //全息
                        if(checked == true)
                            {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                            ui->equip_third_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                        else
                            {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;
                    case 3: //红点
                        if(checked == true)
                            {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                            ui->equip_third_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                        else
                            {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;
                    case 4: //夜视
                        if(checked == true)
                            {doll[0].night_view_per += 1 ;
                            ui->equip_third_label->setText(QString::fromUtf8("夜视能力+100%"));}
                        else
                            doll[0].night_view_per -= 1 ;break;
                    case 5: //专属
                        switch (doll[0].id) {

                        default:
                            break;
                        }break;

                    default:
                        break;
                    }
                });
    }
}

void calculation::equip_special(int id , int order) //特殊人形装备格，ar15，sop2，16哥
{
    switch (id) {
    case 54:
        switch (order) {
        case 1:{
            QList<QRadioButton*> btns_1 = ui->equip_first->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_1)
            {delete btn;}
            doll[0].critical_per -= 0.48; //减去原本初始设定的属性

            QButtonGroup* first_equip_group;
            first_equip_group = new QButtonGroup( ui->equip_first );

            QRadioButton* button_1_1 = new QRadioButton( ui->equip_first );
            button_1_1->setText(QString::fromUtf8("高速"));
            button_1_1->setGeometry(0,0,60,22);
            button_1_1->setChecked(true);
            doll[0].attack += 20;
            ui->equip_first_label->setText(QString::fromUtf8("伤害+20"));

            first_equip_group->addButton(button_1_1,1);
            button_1_1->show();

            connect(first_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //高速
                            if(checked == true)
                                {doll[0].attack += 20;
                                ui->equip_first_label->setText(QString::fromUtf8("伤害+20"));}
                            else
                                doll[0].attack -= 20;break;

                        default:
                            break;
                        }
                    });

        }break;

        case 2:{
            QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_2)
            {delete btn;}
            doll[0].attack -= 20; //减去原本初始设定的属性

            QButtonGroup* second_equip_group;
            second_equip_group = new QButtonGroup( ui->equip_second );

            QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
            button_2_1->setText(QString::fromUtf8("X骨"));
            button_2_1->setGeometry(0,0,60,22);

            QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
            button_2_2->setText(QString::fromUtf8("T骨"));
            button_2_2->setGeometry(60,0,60,22);
            button_2_2->setChecked(true);
            doll[0].attack -= 6;
            ui->equip_second_label->setText(QString::fromUtf8("回避+35 伤害-6"));

            second_equip_group->addButton(button_2_1,1);
            second_equip_group->addButton(button_2_2,2);
            button_2_1->show();
            button_2_2->show();

            connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //X骨
                            if(checked == true)
                                {ui->equip_second_label->setText(QString::fromUtf8("回避+20"));}
                            break;
                        case 2: //T骨
                            if(checked == true)
                                {doll[0].attack -= 6 ;
                                ui->equip_second_label->setText(QString::fromUtf8("回避+35 伤害-6"));}
                            else
                                {doll[0].attack += 6 ;}break;
                        default:
                            break;
                        }
                    });

        }break;

        case 3:{
            //删除equip_third中的QRadioButton
            QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_3)
            {delete btn;}
            doll[0].dodge -= 20 ; //减去原本初始设定的属性

            QButtonGroup* third_equip_group;
            third_equip_group = new QButtonGroup( ui->equip_third );

            QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
            button_3_1->setText(QString::fromUtf8("板甲"));
            button_3_1->setGeometry(0,0,60,22);

            QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
            button_3_2->setText(QString::fromUtf8("专属"));
            button_3_2->setGeometry(60,0,60,22);
            button_3_2->setChecked(true);
            {doll[0].fire_rate -= 10 ; doll[0].hit -= 20;}
            ui->equip_third_label->setText(QString::fromUtf8("护甲+20 回避+10 射速-10 命中-20"));

            third_equip_group->addButton(button_3_1,1);
            third_equip_group->addButton(button_3_2,2);
            button_3_1->show();
            button_3_2->show();

            connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //板甲
                            if(checked == true)
                                {ui->equip_third_label->setText(QString::fromUtf8("护甲+11 回避-2"));}
                            break;
                        case 2: //专属
                            if(checked == true)
                                {{doll[0].fire_rate -= 10 ; doll[0].hit -= 20;}
                                ui->equip_third_label->setText(QString::fromUtf8("护甲+20 回避+10 射速-10 命中-20"));}
                            else
                                {doll[0].fire_rate += 10 ; doll[0].hit += 20;}
                            break;
                        default:
                            break;
                        }
                    });
        }break;


        default:
            break;

        }break;

    case 56:
        switch (order) {
        case 2:{
            QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_2)
            {delete btn;}
            doll[0].attack -= 20 ; //减去原本初始设定的属性

            QButtonGroup* second_equip_group;
            second_equip_group = new QButtonGroup( ui->equip_second );

            QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
            button_2_1->setText(QString::fromUtf8("光瞄"));
            button_2_1->setGeometry(0,0,60,22);

            QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
            button_2_2->setText(QString::fromUtf8("全息"));
            button_2_2->setGeometry(60,0,60,22);

            QRadioButton* button_2_3 = new QRadioButton( ui->equip_second );
            button_2_3->setText(QString::fromUtf8("红点"));
            button_2_3->setGeometry(120,0,60,22);

            QRadioButton* button_2_4 = new QRadioButton( ui->equip_second );
            button_2_4->setText(QString::fromUtf8("夜视"));
            button_2_4->setGeometry(0,22,60,22);

            QRadioButton* button_2_5 = new QRadioButton( ui->equip_second );
            button_2_5->setText(QString::fromUtf8("消音"));
            button_2_5->setGeometry(60,22,60,22);

            QRadioButton* button_2_6 = new QRadioButton( ui->equip_second );
            button_2_6->setText(QString::fromUtf8("专属"));
            button_2_6->setGeometry(120,22,60,22);
            button_2_6->setChecked(true);
            {doll[0].hit += 14; doll[0].attack += 12; doll[0].fire_rate -= 2; }
            ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+12 射速-2"));


            second_equip_group->addButton(button_2_1,1);
            second_equip_group->addButton(button_2_2,2);
            second_equip_group->addButton(button_2_3,3);
            second_equip_group->addButton(button_2_4,4);
            second_equip_group->addButton(button_2_5,5);
            second_equip_group->addButton(button_2_6,6);
            button_2_1->show();
            button_2_2->show();
            button_2_3->show();
            button_2_4->show();
            button_2_5->show();
            button_2_6->show();

            connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //光瞄
                            if(checked == true)
                                {doll[0].critical_per += 0.48 ;
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));}
                            else
                                doll[0].critical_per -= 0.48 ;break;
                        case 2: //全息
                            if(checked == true)
                                {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                                ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                            else
                                {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;
                        case 3: //红点
                            if(checked == true)
                                {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                                ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                            else
                                {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;
                        case 4: //夜视
                            if(checked == true)
                                {doll[0].night_view_per += 1 ;
                                ui->equip_second_label->setText(QString::fromUtf8("夜视能力+100%"));}
                            else
                                doll[0].night_view_per -= 1 ;break;
                        case 5: //消音
                            if(checked == true)
                                {doll[0].critical_per += 0.2 ;
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                            else
                                doll[0].critical_per -= 0.2 ;break;
                        case 6: //专属
                            if(checked == true)
                                {{doll[0].hit += 14; doll[0].attack += 12; doll[0].fire_rate -= 2; }
                                ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+12 射速-2"));}
                            else
                                {doll[0].hit -= 14; doll[0].attack -= 12; doll[0].fire_rate += 2; }break;
                        default:
                            break;
                        }
                    });

        }break;

        case 3:{
            //删除equip_third中的QRadioButton
            QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_3)
            {delete btn;}
            doll[0].dodge -= 20 ; //减去原本初始设定的属性

            QButtonGroup* third_equip_group;
            third_equip_group = new QButtonGroup( ui->equip_third );

            QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
            button_3_1->setText(QString::fromUtf8("高速"));
            button_3_1->setGeometry(0,0,60,22);
            button_3_1->setChecked(true);
            {doll[0].attack += 20 ;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+20"));

            third_equip_group->addButton(button_3_1,1);
            button_3_1->show();

            connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //高速
                            if(checked == true)
                                {doll[0].attack += 20;
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+20"));}
                            else
                                doll[0].attack -= 20;
                            break;
                        default:
                            break;
                        }
                    });
        }break;


        default:
            break;

        }break;

    case 57:
        switch (order) {
        case 2:{
            QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_2)
            {delete btn;}
            doll[0].attack -= 20 ; //减去原本初始设定的属性

            QButtonGroup* second_equip_group;
            second_equip_group = new QButtonGroup( ui->equip_second );

            QRadioButton* button_2_1 = new QRadioButton( ui->equip_second );
            button_2_1->setText(QString::fromUtf8("光瞄"));
            button_2_1->setGeometry(0,0,60,22);

            QRadioButton* button_2_2 = new QRadioButton( ui->equip_second );
            button_2_2->setText(QString::fromUtf8("全息"));
            button_2_2->setGeometry(60,0,60,22);

            QRadioButton* button_2_3 = new QRadioButton( ui->equip_second );
            button_2_3->setText(QString::fromUtf8("红点"));
            button_2_3->setGeometry(120,0,60,22);

            QRadioButton* button_2_4 = new QRadioButton( ui->equip_second );
            button_2_4->setText(QString::fromUtf8("夜视"));
            button_2_4->setGeometry(0,22,60,22);

            QRadioButton* button_2_5 = new QRadioButton( ui->equip_second );
            button_2_5->setText(QString::fromUtf8("消音"));
            button_2_5->setGeometry(60,22,60,22);

            QRadioButton* button_2_6 = new QRadioButton( ui->equip_second );
            button_2_6->setText(QString::fromUtf8("专属"));
            button_2_6->setGeometry(120,22,60,22);
            button_2_6->setChecked(true);
            {doll[0].hit += 10 ; doll[0].crit_damage_rate += 0.2;}
            ui->equip_second_label->setText(QString::fromUtf8("命中+10 暴伤+20%"));


            second_equip_group->addButton(button_2_1,1);
            second_equip_group->addButton(button_2_2,2);
            second_equip_group->addButton(button_2_3,3);
            second_equip_group->addButton(button_2_4,4);
            second_equip_group->addButton(button_2_5,5);
            second_equip_group->addButton(button_2_6,6);
            button_2_1->show();
            button_2_2->show();
            button_2_3->show();
            button_2_4->show();
            button_2_5->show();
            button_2_6->show();

            connect(second_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //光瞄
                            if(checked == true)
                                {doll[0].critical_per += 0.48 ;
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+48%"));}
                            else
                                doll[0].critical_per -= 0.48 ;break;
                        case 2: //全息
                            if(checked == true)
                                {doll[0].hit += 14 ; doll[0].attack += 8 ; doll[0].fire_rate -= 4 ;
                                ui->equip_second_label->setText(QString::fromUtf8("命中+14 伤害+8 射速-4"));}
                            else
                                {doll[0].hit -= 14 ; doll[0].attack -= 8 ; doll[0].fire_rate += 4 ;}break;
                        case 3: //红点
                            if(checked == true)
                                {doll[0].hit += 30 ; doll[0].fire_rate -= 1;
                                ui->equip_second_label->setText(QString::fromUtf8("命中+30 射速-1"));}
                            else
                                {doll[0].hit -= 30 ; doll[0].fire_rate += 1;}break;
                        case 4: //夜视
                            if(checked == true)
                                {doll[0].night_view_per += 1 ;
                                ui->equip_second_label->setText(QString::fromUtf8("夜视能力+100%"));}
                            else
                                doll[0].night_view_per -= 1 ;break;
                        case 5: //消音
                            if(checked == true)
                                {doll[0].critical_per += 0.2 ;
                                ui->equip_second_label->setText(QString::fromUtf8("暴击+20% 回避+10"));}
                            else
                                doll[0].critical_per -= 0.2 ;break;
                        case 6: //专属
                            if(checked == true)
                                {doll[0].hit += 10 ; doll[0].crit_damage_rate += 0.2;
                                ui->equip_second_label->setText(QString::fromUtf8("命中+10 暴伤+20%"));}
                            else
                                {doll[0].hit -= 10 ; doll[0].crit_damage_rate -= 0.2;}break;
                        default:
                            break;
                        }
                    });

        }break;

        case 3:{
            //删除equip_third中的QRadioButton
            QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_3)
            {delete btn;}
            doll[0].dodge -= 20; //减去原本初始设定的属性

            QButtonGroup* third_equip_group;
            third_equip_group = new QButtonGroup( ui->equip_third );

            QRadioButton* button_3_1 = new QRadioButton( ui->equip_third );
            button_3_1->setText(QString::fromUtf8("高速"));
            button_3_1->setGeometry(0,0,60,22);

            QRadioButton* button_3_2 = new QRadioButton( ui->equip_third );
            button_3_2->setText(QString::fromUtf8("专属"));
            button_3_2->setGeometry(60,0,60,22);
            button_3_2->setChecked(true);
            {doll[0].attack += 25 ; doll[0].hit -= 1;}
            ui->equip_third_label->setText(QString::fromUtf8("伤害+25 命中-1"));

            third_equip_group->addButton(button_3_1,1);
            third_equip_group->addButton(button_3_2,2);
            button_3_1->show();
            button_3_2->show();

            connect(third_equip_group, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                  [=](int i, bool checked)
                    {
                        switch (i) {
                        case 1: //高速
                            if(checked == true)
                                {doll[0].attack += 20;
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+20"));}
                            else
                                doll[0].attack -= 20;
                            break;
                        case 2: //专属
                            if(checked == true)
                                {{doll[0].attack += 25 ; doll[0].hit -= 1;}
                                ui->equip_third_label->setText(QString::fromUtf8("伤害+25 命中-1"));}
                            else
                                {doll[0].attack -= 25 ; doll[0].hit += 1;}
                            break;
                        default:
                            break;
                        }
                    });
        }break;


        default:
            break;

        }break;

    case 417:
        switch (order) {
        case 1:{
            QList<QRadioButton*> btns_1 = ui->equip_first->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_1)
            {delete btn;}
            doll[0].critical_per -= 0.2 ;

            ui->equip_first_label->setText(" ");
        }break;

        case 2:{
            QList<QRadioButton*> btns_2 = ui->equip_second->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_2)
            {delete btn;}
            {doll[0].attack -= 15 ; doll[0].armor_piercing += 7 ;}

            ui->equip_second_label->setText(" ");
        }break;

        case 3:{
            //删除equip_third中的QRadioButton
            QList<QRadioButton*> btns_3 = ui->equip_third->findChildren<QRadioButton*>();
            foreach(QRadioButton* btn, btns_3)
            {delete btn;}
            {doll[0].dodge -= 20;}

            ui->equip_third_label->setText(" ");
        }break;

        default: break;
        }break;

    default:
        break;
    }
}
