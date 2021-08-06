#include<stdio.h>
#include<math.h>
#include"calculation.h"

#include <QDebug>
#include <QTime>

double limit(int pos , double fire_rate_1);
void bomb( int pos , int frame , double power );
void snipe( int pos , int frame , int max_piles , double min_power , double max_power);
void direct_damage( int pos , int frame );
void shield_down(int pos , int frame);

static int timer=0;
static int rand_seed_skill;
void mysrand_skill (int);
double myrand_skill();

void skill_select(int frame) {
    if(frame==0 && timer==0 )mysrand_skill(time (nullptr));
    timer++;

    for(int pos=1 ; pos<10 ; pos++){

    if ( doll[pos].id != 0 ) {
        int	*pfire_timing = &doll[pos].fire_timing,
            *pskill1_timing = &doll[pos].skill1_timing,
            *pskill1_flag = &doll[pos].skill1_flag,
            *precharge = &doll[pos].recharge;
        double	*pfire_rate = &doll[pos].fire_rate;

        shield_down(pos , frame);

        switch (doll[pos].id) {

        case 1: {   //1 柯尔特左轮¤ 火力号令
            *pfire_timing += 1; *pskill1_timing += 1; doll[pos].sign_z[0]++;
            if(doll[pos].sign_z[0] % (4*FA) == 0) { //被动
                if(doll[pos].sign_z[1] < 3){ //小于三层
                    for (int i=1 ; i<10 ; i++ ) {
                        doll[i].hit *= 1.05;
                        doll[i].fire_rate *= 1.05; }
                    doll[pos].sign_z[1] ++; }
                if(doll[pos].sign_z[1] >= 3){ //大于三层 为了触发蟒蛇被动 先减免再增加
                    for (int i=1 ; i<10 ; i++ ) {
                        doll[i].hit /= 1.05;
                        doll[i].fire_rate /= 1.05; }
                    doll[pos].sign_z[1] ++; }
            }
            if(doll[pos].sign_z[0] % (4*FA) == 1){
                if(doll[pos].sign_z[1] >= 3){ //大于三层 为了触发蟒蛇被动 先减免再增加
                    for (int i=1 ; i<10 ; i++){
                        doll[i].hit *= 1.05;
                        doll[i].fire_rate *= 1.05; }}
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){doll[i].attack /= 1.25;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){doll[i].attack *= 1.25;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){doll[i].attack *= 1.25;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 2: {   //2 M1911¤ 烟雾弹
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.move /= 0.5;
                enemy.fire_rate /= 0.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.move *= 0.5;
                        enemy.fire_rate *= 0.6;
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.move *= 0.5;
                        enemy.fire_rate *= 0.6;
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

            if(doll[pos].sign_z[1] == 1){ doll[pos].attack *= 2; }
            if(doll[pos].sign_z[1] == 8){ doll[pos].attack /= 2; doll[pos].sign_z[1] = 0; }
            if(doll[pos].sign_z[1] >= 1){ doll[pos].sign_z[1]++; }

            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 3: {   //3 M9 闪光弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 4: {   //4 蟒蛇 无畏者之拥
            *pfire_timing += 1; *pskill1_timing += 1;
            //sign_z[1] 记录主动层数 sign_z[2]-sign_z[7]主动时间 24射击逻辑切换双倍
            //伤害1 射速2  回避3 命中4  暴击5 sign[1]-sign[5]记录上一帧的属性
            //8-10 11-13 14-16 17-19 20-22

            for(int i = 8 ; i < 23 ; i++){ //时间累加 超出时间则消除效果
                if(doll[pos].sign_z[i] > 0){ doll[pos].sign_z[i] ++;}
                if(doll[pos].sign_z[i] > 3*FA){
                    if( i >= 8 && i<= 10){ for(int k = 1; k < 10; k++){if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].attack /= 1.06;}}
                    else if( i >= 11 && i<= 13){ for(int k = 1; k < 10; k++){if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].fire_rate /= 1.06;}}
                    else if( i >= 14 && i<= 16){ for(int k = 1; k < 10; k++){if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].dodge /= 1.30;}}
                    else if( i >= 17 && i<= 19){ for(int k = 1; k < 10; k++){if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].hit /= 1.30;}}
                    else if( i >= 20 && i<= 22){ for(int k = 1; k < 10; k++){if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].critical_per /= 1.12;}}
                    doll[pos].sign_z[i] = 0;
                }
            }

            if(frame == 0){ //战斗开始前的属性值
                doll[pos].sign[1] = doll_reserve_2[pos].attack;
                doll[pos].sign[2] = doll_reserve_2[pos].fire_rate;
                doll[pos].sign[3] = doll_reserve_2[pos].dodge;
                doll[pos].sign[4] = doll_reserve_2[pos].hit;
                doll[pos].sign[5] = doll_reserve_2[pos].critical_per;}

            if(doll[pos].attack/doll[pos].sign[1] > 1.001){
                int j , tem_j = 8 , tem_max = doll[pos].sign_z[8];
                for( j = 8; j <= 10 ; j++){if(doll[pos].sign_z[j] == 0){tem_j = j; break; }
                    if(doll[pos].sign_z[j] > tem_max){tem_max = doll[pos].sign_z[j]; tem_j = j;}}
                if(doll[pos].sign_z[tem_j] == 0){
                    for(int k = 1; k < 10; k++) {if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].attack *= 1.06; }}
                doll[pos].sign_z[tem_j] = 1;}
            //qDebug() << frame << ":" << doll[pos].sign[1] << doll[pos].attack << doll[pos].sign_z[8] << doll[pos].sign_z[9] << doll[pos].sign_z[10];
            //qDebug() << frame << ":" << doll[1].attack << doll[2].attack;

            if(doll[pos].fire_rate/doll[pos].sign[2] > 1.001){
                int j , tem_j = 11 , tem_max = doll[pos].sign_z[11];
                for( j = 11; j <= 13 ; j++){if(doll[pos].sign_z[j] == 0){tem_j = j; break; }
                    if(doll[pos].sign_z[j] > tem_max){tem_max = doll[pos].sign_z[j]; tem_j = j;}}
                if(doll[pos].sign_z[tem_j] == 0){
                    for(int k = 1; k < 10; k++) {if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].fire_rate *= 1.06; }}
                doll[pos].sign_z[tem_j] = 1;}

            if(doll[pos].dodge/doll[pos].sign[3] > 1.001){
                int j , tem_j = 14 , tem_max = doll[pos].sign_z[14];
                for( j = 14; j <= 16 ; j++){if(doll[pos].sign_z[j] == 0){tem_j = j; break; }
                    if(doll[pos].sign_z[j] > tem_max){tem_max = doll[pos].sign_z[j]; tem_j = j;}}
                if(doll[pos].sign_z[tem_j] == 0){
                    for(int k = 1; k < 10; k++) {if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].dodge *= 1.30; }}
                doll[pos].sign_z[tem_j] = 1;}

            if(doll[pos].hit/doll[pos].sign[4] > 1.001){
                int j , tem_j = 17 , tem_max = doll[pos].sign_z[17];
                for( j = 17; j <= 19 ; j++){if(doll[pos].sign_z[j] == 0){tem_j = j; break; }
                    if(doll[pos].sign_z[j] > tem_max){tem_max = doll[pos].sign_z[j]; tem_j = j;}}
                if(doll[pos].sign_z[tem_j] == 0){
                    for(int k = 1; k < 10; k++) {if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].hit *= 1.30; }}
                doll[pos].sign_z[tem_j] = 1;}


            if(doll[pos].critical_per/doll[pos].sign[5] > 1.001){
                int j , tem_j = 20 , tem_max = doll[pos].sign_z[20];
                for( j = 20; j <= 22 ; j++){if(doll[pos].sign_z[j] == 0){tem_j = j; break; }
                    if(doll[pos].sign_z[j] > tem_max){tem_max = doll[pos].sign_z[j]; tem_j = j;}}
                if(doll[pos].sign_z[tem_j] == 0){
                    for(int k = 1; k < 10; k++) {if(doll[pos].influence[k] == 1 && doll[k].id != 0) doll[k].critical_per *= 1.12; }}
                doll[pos].sign_z[tem_j] = 1;}

            //qDebug() << frame << ":" << doll[1].critical_per << doll[pos].sign[5] << doll[pos].sign_z[20];
            //qDebug() << frame << ":" << doll[pos].hit << "-" << doll[pos].sign[4] << doll[pos].sign_z[17];
            { //数据对比完成 记录本帧属性
                doll[pos].sign[1] = doll[pos].attack;
                doll[pos].sign[2] = doll[pos].fire_rate;
                doll[pos].sign[3] = doll[pos].dodge;
                doll[pos].sign[4] = doll[pos].hit;
                doll[pos].sign[5] = doll[pos].critical_per;
            }

            //主动 第一发和最后一发双倍射击
            if(doll[pos].sign_z[24] == 2 && *pfire_timing == 1){doll[pos].fire_number /= 2; doll[pos].sign_z[24] = 1;}

            //qDebug() << frame << "2-" << doll[pos].sign_z[2] << "7-" << doll[pos].sign_z[7] <<doll[pos].fire_number;

            for (int i = 2 ; i <= 7 ; i++ ) {
                if(doll[pos].sign_z[i] > 0){ doll[pos].sign_z[i] ++; }
                if(doll[pos].sign_z[i] >= 5*FA ){
                    doll[pos].sign_z[i] = 0; doll[pos].attack /= 1.3 ;}}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[1] = 1; doll[pos].sign_z[2] = 1; doll[pos].attack *= 1.3; doll[pos].fire_number *= 2; doll[pos].sign_z[24] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    doll[pos].sign_z[1]++;
                    if(doll[pos].sign_z[1] == 2)doll[pos].fire_number /= 2;
                    if( doll[pos].sign_z[1] < 7 ){
                        doll[pos].attack *= 1.3;
                        doll[pos].sign_z[doll[pos].sign_z[1] + 1] = 1; }
                    else {*pskill1_flag = 2; doll[pos].sign_z[1] = 0; }
                    }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[1] = 1; doll[pos].sign_z[2] = 1; doll[pos].attack *= 1.3 ; doll[pos].fire_number *= 2; doll[pos].sign_z[24] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(((doll[pos].sign_z[7] == 0 && doll[pos].sign_z[2] == 0 && *pskill1_flag == 2) || (doll[pos].sign_z[7] > 0)) && doll[pos].sign_z[24] == 0){
                    doll[pos].sign_z[24] = 2; doll[pos].fire_number *= 2; } //前者为第六发未打出 后者为第六发打出 最后一击双重射击

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
            //qDebug() << frame << ":" << doll[pos].sign_z[1] << doll[pos].sign_z[2] << doll[pos].sign_z[3] << doll[pos].sign_z[4] << doll[pos].sign_z[5] << doll[pos].sign_z[6] << doll[pos].sign_z[7];
            //qDebug() << frame << ":" << *pskill1_flag << *pskill1_timing;
        }break;

        case 5: {   //5 纳甘左轮¤ 火力压制N
            *pfire_timing += 1; *pskill1_timing += 1;

            for ( int j = 1 ; j<2 ; j++ ) { //二技能被动
                if(doll[pos].sign_z[j] == 0)continue;

                doll[pos].sign_z[j]++;
                if(doll[pos].sign_z[j] >= 4*FA){
                    doll[pos].sign_z[j] = 0 ;
                    for (int i = 1; i < 10; i++){
                        doll[i].attack /= 1.1;
                        doll[i].hit /= 1.1;
            }}}
            //qDebug() << frame << ":" << doll[pos].attack << doll[pos].sign_z[0];

            if(*pskill1_flag == 1 && *pskill1_timing >= 5*FA && condition.day_or_night == 0){ //day
                enemy.attack /= 0.75;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 1 && *pskill1_timing >= 8*FA && condition.day_or_night == 1){ //night
                enemy.attack /= 0.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                if( doll[pos].sign_z[0] % 7 == 0 ){
                    if( doll[pos].sign_z[1] == 0 )doll[pos].sign_z[1] = 1;
                    else doll[pos].sign_z[2] = 1;

                    for (int i = 1; i < 10; i++){
                        doll[i].attack *= 1.1;
                        doll[i].hit *= 1.1;}
                }
                doll[pos].sign_z[0] ++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) enemy.attack *= 0.75;
                        if(condition.day_or_night == 1) enemy.attack *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) enemy.attack *= 0.75;
                        if(condition.day_or_night == 1) enemy.attack *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 6: {   //6 托卡列夫 掩护号令
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].dodge /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 7: {   //7 斯捷奇金 突击号令
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)doll[pos].critical_per -= 0.01; // 丝巾的暴击计算有误，补正

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ doll[i].fire_rate /= 1.25;
                    if(doll[pos].sign_z[0] == 1){doll[i].attack /= 1.04;}}
                doll[pos].critical_per /= 2;
                doll[pos].attack /= 1.25;
                if(doll[pos].sign_z[1] == 2){enemy.dodge /= 0.5;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ doll[i].fire_rate *= 1.25;
                            if(doll[pos].sign_z[0] == 1){doll[i].attack *= 1.04;}}
                        doll[pos].critical_per *= 2;
                        doll[pos].attack *= 1.25;
                        if(doll[pos].sign_z[1] == 2){enemy.dodge *= 0.5;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ doll[i].fire_rate *= 1.25;
                            if(doll[pos].sign_z[0] == 1){doll[i].attack *= 1.04;}}
                        doll[pos].critical_per *= 2;
                        doll[pos].attack *= 1.25;
                        if(doll[pos].sign_z[1] == 2){enemy.dodge *= 0.5;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 8: {   //马卡洛夫
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.hit /= 0.64;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.hit *= 0.64;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.hit *= 0.64;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 9: {   //P38
            *pfire_timing += 1; *pskill1_timing += 1;

            if ( *pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last ) {
                for (int i = 1; i < 10; i++)doll[i].hit /= 1.9;
                *pskill1_flag = 2;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                if(condition.day_or_night == 1){
                    switch (*pskill1_flag) {
                    case 0: {
                        if (*pskill1_timing >= doll[pos].skill1_before ) {
                            for (int i = 1; i < 10; i++)doll[i].hit *= 1.9;
                            *pskill1_timing = 0; *pskill1_flag = 1;
                        }}break;
                    case 1: break;
                    case 2: {
                        if (*pskill1_timing >= doll[pos].skill1_cd ) {
                            for (int i = 1; i < 10; i++)doll[i].hit *= 1.9;
                            *pskill1_timing = 0; *pskill1_flag = 1;
                        }}break;
                    }
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 10: {   //PPK
            *pfire_timing += 1; *pskill1_timing += 1;

            if ( *pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last ) {
                for (int i = 1; i < 10; i++) { doll[i].attack /= 1.1; doll[i].critical_per /= 1.35; }
                *pskill1_flag = 2;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++) { doll[i].attack *= 1.1; doll[i].critical_per *= 1.35; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++) { doll[i].attack *= 1.1; doll[i].critical_per *= 1.35; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 11: {   //P08
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && condition.day_or_night == 0 && *pskill1_timing >= 5*FA){
                for(int i=1 ; i<10 ; i++) doll[i].dodge /= 1.35;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 1 && condition.day_or_night == 1 && *pskill1_timing >= 8*FA){
                for(int i=1 ; i<10 ; i++) doll[i].dodge /= 1.85;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) for(int i=1 ; i<10 ; i++) doll[i].dodge *= 1.35;
                        if(condition.day_or_night == 1) for(int i=1 ; i<10 ; i++) doll[i].dodge *= 1.85;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) for(int i=1 ; i<10 ; i++) doll[i].dodge *= 1.35;
                        if(condition.day_or_night == 1) for(int i=1 ; i<10 ; i++) doll[i].dodge *= 1.85;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 12: {   //C96
            *pfire_timing += 1; *pskill1_timing += 1;

            if ( *pskill1_flag == 1 && *pskill1_timing >= 8*FA ) {
                if(condition.day_or_night == 1){
                    for (int i = 1; i < 10; i++){
                        if(doll[i].id == 0)continue;
                        doll[i].bullet_number -= 2;
                        doll[i].crit_damage_rate /= 1.2;}}
                *pskill1_flag = 2;
            }

            if ( *pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_last ) {
                if(condition.day_or_night == 1){
                    for (int i = 1; i < 10; i++)doll[i].hit /= 2.2;}
                *pskill1_flag = 3;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                if(condition.day_or_night == 1){
                    switch (*pskill1_flag) {
                    case 0: {
                        if (*pskill1_timing >= doll[pos].skill1_before ) {
                            if(condition.day_or_night == 1){
                                for (int i = 1; i < 10; i++){
                                    if(doll[i].id == 0)continue;
                                    doll[i].hit *= 2.2;
                                    doll[i].bullet_number += 2;
                                    doll[i].crit_damage_rate *= 1.2;}}
                            *pskill1_timing = 0; *pskill1_flag = 1;
                        }}break;
                    case 1: break;
                    case 2: break;
                    case 3: {
                        if (*pskill1_timing >= doll[pos].skill1_cd ) {
                            if(condition.day_or_night == 1){
                                for (int i = 1; i < 10; i++){
                                    if(doll[i].id == 0)continue;
                                    doll[i].hit *= 2.2;
                                    doll[i].bullet_number += 2;
                                    doll[i].crit_damage_rate *= 1.2;}}
                            *pskill1_timing = 0; *pskill1_flag = 1;
                        }}break;
                    }
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }

            //qDebug() << frame << ":" << doll[5].crit_damage_rate;
        }break;

        case 13: {   //92式
            *pfire_timing += 1; *pskill1_timing += 1;

            if ( *pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last ) {
                for (int i = 1; i < 10; i++) { doll[i].attack /= 1.1; doll[i].fire_rate *= 1.1; }
                *pskill1_flag = 2;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++) { doll[i].attack *= 1.1; doll[i].fire_rate *= 1.1; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++) { doll[i].attack *= 1.1; doll[i].fire_rate *= 1.1; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 14: {   //阿斯特拉左轮
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].fire_rate /= 1.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].fire_rate *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].fire_rate *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 15: {   //格洛克17
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.attack /= 0.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 16: {   //16 汤姆森
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].max_field = 0;
                doll[pos].current_field = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 17: {   //M3
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 18: {   //MAC-10
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.64;
                enemy.move /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 19: {   //FMG-9
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 20: {   //Vector
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Ignite -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 7 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 7 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 21: {   //PPsh-41
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 22: {   //PPS-43
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 23: {   //PP-90
            *pfire_timing += 1; *pskill1_timing += 1;
            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 1.45;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 1.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 1.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 24: {   //PP-2000
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 25: {   //MP-40
            *pfire_timing += 1; *pskill1_timing += 1;

            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Ignite -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 26: {   //MP5¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].max_field = 0;
                doll[pos].current_field = 0;
                for( int j=1 ; j <= min(enemy.target_number , 3) ; j++ ) doll[pos].dodge *= 1.2;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_last + 8*FA){
                for( int j=1 ; j <= min(enemy.target_number , 3) ; j++ ) doll[pos].dodge /= 1.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 27: {   //蝎式
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1;doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1;doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 28: {   //MP7
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate *= 1.2;
                doll[pos].hit *= 1.2;
                doll[pos].move /= 1.5;
                doll[pos].dodge /= 2.8;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate /= 1.2;
                        doll[pos].hit /= 1.2;
                        doll[pos].move *= 1.5;
                        doll[pos].dodge *= 2.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate /= 1.2;
                        doll[pos].hit /= 1.2;
                        doll[pos].move *= 1.5;
                        doll[pos].dodge *= 2.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 29: {   //司登MkⅡ¤
            *pfire_timing += 1; *pskill1_timing += 1; doll[pos].sign_z[1]++;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if( doll[pos].sign_z[0] == 0 && doll[pos].sign_z[1] >= 6*FA ){
                doll[pos].injury_reduction *= 0.65;
                doll[pos].sign_z[0] = 1; doll[pos].sign_z[1] = 0;
            }

            if( doll[pos].sign_z[0] == 1 && doll[pos].sign_z[1] >= 5*FA ){
                doll[pos].injury_reduction /= 0.65;
                doll[pos].sign_z[0] = 2;
            }

            if( doll[pos].sign_z[0] == 2 && doll[pos].sign_z[1] >= 16*FA ){
                doll[pos].injury_reduction *= 0.65;
                doll[pos].sign_z[0] = 1;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 31: {   //31 伯莱塔38型
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 32: {   //32 微型乌兹¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5 * FA)) { doll[pos].sign_z[0] = 0; }
            }

            if(doll[pos].sign_z[0] % 10 == 1){ //引燃伤害
                bomb( pos , frame , 1 * doll[pos].sign[0] );
            }

            if(doll[pos].sign_z[0] % 45 == 1){ //灼烧链接
                bomb( pos , frame , 0.8 * doll[pos].sign[0] );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].sign_z[0] = 1;doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].sign_z[0] = 1;doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 33: {   //33 M45
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.64;
                enemy.move /= 0.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 34: {   //34 M1加兰德 锁定射击 当前目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.6 , 5.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 35: {   //35 M1A1
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 36: {   //36 春田 沉稳射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.8 , 6);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 37: {   //37 M14¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= 6 * FA){
                doll[pos].crit_damage_rate /= 1.1;
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        doll[pos].crit_damage_rate *= 1.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3:
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        doll[pos].crit_damage_rate *= 1.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 38: {   //38 M21 瞄准射击 特定目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.6 , 5.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 39: {   //39 莫辛-纳甘¤ 沉稳射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            if( frame == 1 ){
                if( doll[pos].sign_z[1] == 2 )doll[pos].attack *= 1.2;
            }

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 3 , 6.5);
                    if( doll[pos].sign_z[2] == 2 ){doll[pos].fire_rate *= 1.3;}  //被动技能是否触发
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;
                    *precharge = floor(1500 / limit( pos , *pfire_rate ));}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if( doll[pos].sign_z[2] == 2 && *pskill1_timing >= 5*FA ){doll[pos].fire_rate /= 1.3;}
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }

        }break;

        case 40: {   //40 SVT-38 瞄准射击 特定目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.4 , 5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 41: {   //41 西蒙诺夫
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 42: {   //42 PTRD 阻断射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3.1 , 7);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 43: {   //43 SVD
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 44: {   //44 SV-98¤ 阻断射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            if( doll[pos].sign_z[1] == 2 && (frame == 3*FA || (*pskill1_flag == 2 && *pskill1_timing == 3*FA)) ){
                doll[pos].fire_rate *= 1.08;
                doll[pos].hit *= 1.08;
            }

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    double min_power=2.8, max_power=6;
                    if(doll[pos].sign_z[1] == 2){
                        min_power *= 1.18; max_power *= 1.18;
                        doll[pos].fire_rate /= 1.08;
                        doll[pos].hit /= 1.08;
                    }
                    snipe( pos , frame , 5 , min_power , max_power);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 46: {   //46 Kar98k 锁链射击 当前目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //第一次瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 3.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            case 2:{ //第二次瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 3.5);
                    *pskill1_flag = 3;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 3: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 47: {   //47 G43
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){ doll[pos].fire_rate /= 1.28; }
                else { doll[pos].fire_rate /= 1.85; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].fire_rate *= 1.28; }
                        else { doll[pos].fire_rate *= 1.85; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].fire_rate *= 1.28; }
                        else { doll[pos].fire_rate *= 1.85; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 48: {   //48 WA2000
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 49: {   //49 56式半
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 50: {   //50 李-恩菲尔德
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 51: {   //51 FN-49¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65; doll[pos].fire_rate /= 1.15;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65; doll[pos].fire_rate *= 1.15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65; doll[pos].fire_rate *= 1.15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 52: {   //52 BM59
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate *= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 53: {   //53 NTW-20 阻断射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){
                if(doll[pos].sign_z[6] == 2)doll[pos].injury_advanced *= 1.1;
            }

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3.4 , 8);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 54: {   //54 M16A1
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 55: {   //55 M4A1¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                if(doll[pos].sign_z[1] == 2){ //二技能结束
                    doll[pos].attack /= 6 ;
                    doll[pos].fire_rate /= 0.3;
                    doll[pos].definitely_hit = 0;
                }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        if(doll[pos].sign_z[1] == 2){ //二技能开炮
                            doll[pos].attack *= 6 ;
                            doll[pos].fire_rate *= 0.3;
                            doll[pos].definitely_hit = 1;
                        }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        if(doll[pos].sign_z[1] == 2){ //二技能开炮
                            doll[pos].attack *= 6 ;
                            doll[pos].fire_rate *= 0.3;
                            doll[pos].definitely_hit = 1;
                        }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }

            if(doll[pos].sign_z[2] == 1) //
            {
                doll[pos].attack *= 6 ;
                doll[pos].definitely_hit = 1;
                doll[pos].fire_number = 5;
                doll[pos].sign_z[2] = 0;
                *pfire_timing = 2;
            }
            if(doll[pos].sign_z[1] == 2 && *pskill1_flag == 1 && *pfire_timing == 1)
            {
                doll[pos].attack /= 6 ;
                doll[pos].definitely_hit = 0;
                doll[pos].fire_number = enemy.target_number - 1;
                doll[pos].sign_z[2] = 1;
                *pfire_timing = 0;
            }
        }break;

        case 56: {   //56 M4 SOPMODⅡ¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 15 );
                        if(doll[pos].sign_z[4] == 2){ bomb( pos , frame , 2.15 * 3 ); }
                        else { bomb( pos , frame , 1.9 * 3 ); }
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 15 );
                        if(doll[pos].sign_z[4] == 2){ bomb( pos , frame , 2.15 * 3 ); }
                        else { bomb( pos , frame , 1.9 * 3 ); }
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 57: {   //57 ST AR-15¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }

            if(*pfire_timing == 1 && doll[pos].sign_z[5] == 1){
                if(doll[pos].sign_z[4] == 2) doll[pos].attack /= 0.2;
                else doll[pos].attack /= 0.1;
                *pfire_timing = 2;
                doll[pos].sign_z[5] = 0;
            }
            if(*pfire_timing == 1 && *pskill1_flag == 1){
                if(doll[pos].sign_z[4] == 2) doll[pos].attack *= 0.2;
                else doll[pos].attack *= 0.1;
                *pfire_timing = 0;
                doll[pos].sign_z[5] = 1;
            }
        }break;

        case 58: {   //58 AK-47
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                {doll[pos].attack /= 1.35; doll[pos].hit /= 2;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        {doll[pos].attack *= 1.35; doll[pos].hit *= 2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        {doll[pos].attack *= 1.35; doll[pos].hit *= 2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 59: {   //59 AK-74U
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 2){ enemy.attack /= 0.5; enemy.hit /= 0.5; }
                else { enemy.attack /= 0.25; enemy.hit /= 0.25; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(enemy.elite_unit == 2){ enemy.attack /= 0.5; enemy.hit /= 0.5; }
                        else { enemy.attack *= 0.25; enemy.hit /= 0.25; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(enemy.elite_unit == 2){ enemy.attack /= 0.5; enemy.hit /= 0.5; }
                        else { enemy.attack *= 0.25; enemy.hit /= 0.25; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 60: {   //60 AS Val¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if( doll[pos].sign[2] >= 0 ){ doll[pos].sign[2] ++; }
            if( doll[pos].sign[2] >= 3 * FA ){ doll[pos].definitely_hit = 0; doll[pos].sign[2] = 0; }
            if( (frame == 0 && (doll[pos].attack > doll_reserve_2[pos].attack) )||( frame != 0 && (doll[pos].attack > doll[pos].sign[1]) ) ){
                doll[pos].definitely_hit = 1;
                doll[pos].sign[2] = 1;
            }
            doll[pos].sign[1] = doll[pos].attack ;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if( condition.day_or_night == 1 ){doll[pos].attack /= 3;}
                else { doll[pos].attack /= 1.7; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if( condition.day_or_night == 1 ){doll[pos].attack *= 3;}
                        else { doll[pos].attack *= 1.7; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if( condition.day_or_night == 1 ){doll[pos].attack *= 3;}
                        else { doll[pos].attack *= 1.7; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 61: {   //61 StG44¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5 * 1.2 * 3 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5 * 1.2 * 3 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 62: {   //62 G41
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)qDebug() << doll[pos].critical_per;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 63: {   //63 G3¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(doll[pos].sign_z[0]==1) bomb( pos , frame , 12 * 5 );
                        else  bomb( pos , frame , 12 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(doll[pos].sign_z[0]==1) bomb( pos , frame , 12 * 5 );
                        else  bomb( pos , frame , 12 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 64: {   //64 G36¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){
                if(doll[pos].sign_z[0] == 1){
                    doll[pos].sign_z[1] = 0;
                    for (int i = 1; i < 10; i++) {
                        if (doll[pos].influence[i] == 1 && doll[i].id != 0) doll[pos].sign_z[1]++;
                    }
                }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= 5*FA){
                if(doll[pos].sign_z[1] > 0){ for(int i_G36 = doll[pos].sign_z[1]; i_G36 >= 1 ; i_G36--) {
                        doll[pos].fire_rate /= 1.1;
                    }}
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        if(doll[pos].sign_z[1] > 0){ for(int i_G36 = doll[pos].sign_z[1]; i_G36 >= 1 ; i_G36--) {
                                doll[pos].fire_rate *= 1.1;
                            }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        if(doll[pos].sign_z[1] > 0){ for(int i_G36 = doll[pos].sign_z[1]; i_G36 >= 1 ; i_G36--) {
                                doll[pos].fire_rate *= 1.1;
                            }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 65: {   //65 HK416¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(doll[pos].sign_z[1] % 10 == 1){
                doll[pos].attack *= 0.6;
                direct_damage( pos , frame );
                doll[pos].attack /= 0.6;
            }

            if(doll[pos].sign_z[1] >= 1){
                doll[pos].sign_z[1]++;
                if(doll[pos].sign_z[1] >= 3*FA){
                    doll[pos].sign_z[1] = 0;
                    enemy.deep_damage /= 1.2;
                }
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 16 );
                        if(doll[pos].sign_z[0] == 2) bomb( pos , frame , 3.5 );
                        else  {enemy.deep_damage *= 1.2; doll[pos].sign_z[1] = 1;}
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 16 );
                        if(doll[pos].sign_z[0] == 2) bomb( pos , frame , 3.5 );
                        else  {enemy.deep_damage *= 1.2; doll[pos].sign_z[1] = 1;}
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 66: {   //66 56-1式 爆破榴弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 68: {   //68 L85A1
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.35;
                doll[pos].fire_rate /= 1.15;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.35;
                        doll[pos].fire_rate *= 1.15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.35;
                        doll[pos].fire_rate *= 1.15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 69: {   //69 FAMAS 爆破榴弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 70: {   //70 FNC
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 71: {   //71 加利尔
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 72: {   //72 TAR-21
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                doll[pos].fire_rate /= 1.25;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        doll[pos].fire_rate *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        doll[pos].fire_rate *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 73: {   //73 AUG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;

                if( *pskill1_flag == 1 ) *precharge = 10;
                else *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 74: {   //74 SIG-510
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 75: {   //75 M1918¤ 火力专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting == 1){ doll[pos].attack *= 1.4; }
                if(doll[pos].bullet_counting == 4){ doll[pos].attack /= 1.4; }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    //*precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);
                    *precharge = 5*FA ;}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 77: {   //77 M2HB 连珠终结
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting ++; doll[pos].sign_z[1] ++;

                if(doll[pos].sign_z[1] % 4 == 0){
                    doll[pos].attack *= 2.4;
                    doll[pos].definitely_crit = 2;}

                if(doll[pos].sign_z[1] % 4 == 1 && doll[pos].sign_z[1] != 1){
                    doll[pos].attack /= 2.4;
                    doll[pos].definitely_crit = 0;}

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 11; }

                *pfire_timing = 0;
            }
        }break;

        case 78: {   //78 M60 火力专注N-MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 1) doll[pos].attack /= 2.05; //夜间
                else doll[pos].attack /= 1.35; //昼间
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 1) doll[pos].attack *= 2.05; //夜间
                        else doll[pos].attack *= 1.35; //昼间
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 1) doll[pos].attack *= 2.05; //夜间
                        else doll[pos].attack *= 1.35; //昼间
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 79: {   //79 M249 SAW 蓄势待发N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 1) doll[pos].attack /= 1.45; //夜间
                else doll[pos].attack /= 1.1; //昼间
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        if(condition.day_or_night == 1) doll[pos].attack *= 1.45; //夜间
                        else doll[pos].attack *= 1.1; //昼间
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        if(condition.day_or_night == 1) doll[pos].attack *= 1.45; //夜间
                        else doll[pos].attack *= 1.1; //昼间
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 4; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 80: {   //80 M1919A4 猎杀冲动
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 1.65;
                doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 1.65;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 1.65;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 81: {   //81 LWMMG¤ 猎杀冲动
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 1.7;
                doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {


                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if((myrand_skill()/10000) <= 0.2){
                    if(doll[pos+2].id != 0 && pos == 1 && pos == 4 && pos == 7){
                        doll[pos+2].dodge *= 1.8;
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos+2].shield_last[j] == 0){
                                doll[pos+2].shield_quantity[j] = 5;
                                doll[pos+2].shield_last[j] = 6*FA;
                                break;}}}}
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 1.7;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1:
                    if(doll[pos+2].id != 0 && pos == 1 && pos == 4 && pos == 7){
                        doll[pos+2].dodge *= 1.8;
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos+2].shield_last[j] == 0){
                                doll[pos+2].shield_quantity[j] = 5;
                                doll[pos+2].shield_last[j] = 6*FA;
                                break;}}}
                    break;
                case 2: {
                    if((myrand_skill()/10000) <= 0.2){
                    if(doll[pos+2].id != 0 && pos == 1 && pos == 4 && pos == 7){
                        doll[pos+2].dodge *= 1.8;
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos+2].shield_last[j] == 0){
                                doll[pos+2].shield_quantity[j] = 5;
                                doll[pos+2].shield_last[j] = 6*FA;
                                break;}}}}
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 1.7;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 82: {   //82 DP28 蓄势待发
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.28;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.28;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.28;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 3; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 84: {   //84 RPD 火力专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 85: {   //85 PK 连珠终结
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting ++; doll[pos].sign_z[1] ++;

                if(doll[pos].sign_z[1] % 4 == 0){
                    doll[pos].attack *= 2.6;
                    doll[pos].definitely_crit = 2;}

                if(doll[pos].sign_z[1] % 4 == 1 && doll[pos].sign_z[1] != 1){
                    doll[pos].attack /= 2.6;
                    doll[pos].definitely_crit = 0;}

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 11; }

                *pfire_timing = 0;
            }
        }break;

        case 86: {   //86 MG42 火力专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 87: {   //87 MG34 火力专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 88: {   //88 MG3 蓄势待发
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 4; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 89: {   //89 布伦¤ 蓄势待发
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                if(frame == 0) { doll[pos].hit *= 1.15; doll[pos].bullet_number += 1; } //初始一层
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].sign_z[2] ++; //被动计数
                    if(doll[pos].sign_z[2] < 3){ //三层
                        doll[pos].hit *= 1.15; doll[pos].bullet_number += 1; }

                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 4; doll[pos].sign_z[1] = 0; }

                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 90: {   //90 FNP-9 掩护压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.dodge /= 0.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.dodge *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.dodge *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 91: {   //91 MP-446¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= 4*FA){
                for (int i = 1; i < 10; i++){
                    if(doll[pos].influence[i] == 1)doll[i].fire_rate /= 1.2;}
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.72;
                for (int i = 1; i < 10; i++)
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.72;
                        for (int i = 1; i < 10; i++){
                            if(doll[pos].influence[i] == 1)doll[i].fire_rate *= 1.2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.72;
                        for (int i = 1; i < 10; i++){
                            if(doll[pos].influence[i] == 1)doll[i].fire_rate *= 1.2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 92: {   //92 Spectre M4
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 93: {   //93 IDW¤
            *pfire_timing += 1; *pskill1_timing += 1; doll[pos].sign_z[2]++;

            if(frame == 0){ doll[pos].sign_z[1] = 3; doll[pos].attack *= 1.728; doll[pos].fire_rate *= 1.331;}

            if(doll[pos].sign_z[2] % (2*FA) == 0 && doll[pos].sign_z[1] > 0 ){
                doll[pos].sign_z[1]--; doll[pos].attack /= 1.2; doll[pos].fire_rate /= 1.1; }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.3;
                        doll[pos].sign_z[1] = 3; doll[pos].attack *= 1.728; doll[pos].fire_rate *= 1.331;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.3;
                        doll[pos].sign_z[1] = 3; doll[pos].attack *= 1.728; doll[pos].fire_rate *= 1.331;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 94: {   //94 64式¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                else enemy.hit /= 0.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        else enemy.hit *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        else enemy.hit *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 95: {   //95 汉阳造88式¤
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 1)doll[pos].attack /= 2;
                else doll[pos].attack /= 1.35;
                doll[pos].move /= 6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 1)doll[pos].attack *= 2;
                        else doll[pos].attack *= 1.35;
                        doll[pos].move *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 1)doll[pos].attack *= 2;
                        else doll[pos].attack *= 1.35;
                        doll[pos].move *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(*pskill1_timing == 0){ //二技能
                    if(doll[pos].sign_z[0] == 1){ //装甲单位
                        double after_ceil, after_random, after_armor, after_advanced;
                        after_ceil = ceil(doll[pos].attack * 0.5);
                        after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
                        after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));
                        after_advanced = max(1, floor(after_armor * enemy.deep_damage));
                        damage[pos][frame] += ((after_advanced * enemy.target_number) + max(1, floor(after_random * 2 * enemy.deep_damage))*1.5);
                    }
                    else { //非装甲单位
                        for(int k=0 ; k<7 ; k++){
                            double hit_tem,hit = floor(doll[pos].hit), nhit = floor(doll[pos].hit*0.1);//命中选择
                            double after_ceil, after_random, after_armor, after_fixed, after_advanced;

                            if(doll[pos].definitely_hit == 1) hit_tem=1;
                            else if( condition.day_or_night == 0) hit_tem=(hit / (hit + enemy.dodge));
                            else hit_tem=(nhit / (nhit + enemy.dodge)) ;
                            if(hit_tem <= (myrand_skill()/10000)) {continue;}

                            if(k>0){ //全部手雷是否命中同一目标
                                if(doll[pos].sign_z[1] == 0){ after_ceil = ceil(doll[pos].attack) * 0.5; }
                                else after_ceil = ceil(doll[pos].attack) * 0.25;}
                            else after_ceil = ceil(doll[pos].attack) * 0.5;
                            after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
                            after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));
                            after_fixed = max(0, ceil(after_armor + doll[pos].fixed_injury));
                            after_advanced = max(1, floor(after_fixed*enemy.deep_damage));
                            damage[pos][frame] += after_advanced;
                        }
                    }
                }

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 96: {   //96 灰熊Mk Ⅴ
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].attack /= 1.25;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 97: {   //97 M950A
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].fire_rate /= 1.25;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].fire_rate *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].fire_rate *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 98: {   //98 SPP-1
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.dodge /= 0.45;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.dodge *= 0.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.dodge *= 0.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 99: {   //99 Mk23
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && condition.day_or_night == 0 && *pskill1_timing >= 5*FA){
                for(int i=1 ; i<10 ; i++) doll[i].attack /= 1.2;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 1 && condition.day_or_night == 1 && *pskill1_timing >= 8*FA){
                for(int i=1 ; i<10 ; i++) doll[i].attack /= 1.35;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) for(int i=1 ; i<10 ; i++) doll[i].attack *= 1.2;
                        if(condition.day_or_night == 1) for(int i=1 ; i<10 ; i++) doll[i].attack *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) for(int i=1 ; i<10 ; i++) doll[i].attack *= 1.2;
                        if(condition.day_or_night == 1) for(int i=1 ; i<10 ; i++) doll[i].attack *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 100: {   //100 P7
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].dodge /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 101: {   //101 UMP9¤
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= 5*FA){
                if(enemy.elite_unit == 0){ //被眩晕
                    enemy.Dizzy += 1;
                    if(pos>0 && pos<4){ doll[pos+3].attack *= 1.5; doll[pos+6].attack *= 1.5; }
                    else if(pos>3 && pos<7){ doll[pos+3].attack *= 1.5; doll[pos-3].attack *= 1.5; }
                    else{ doll[pos-6].attack *= 1.5; doll[pos-3].attack *= 1.5; }}
                else {//未被眩晕或者目标死亡
                    if(pos>0 && pos<4){ doll[pos+3].dodge *= 1.25; doll[pos+6].dodge *= 1.25; }
                    else if(pos>3 && pos<7){ doll[pos+3].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }
                    else{ doll[pos-6].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }}
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0){ //被眩晕
                            enemy.Dizzy += 1;
                            if(pos>0 && pos<4){ doll[pos+3].attack *= 1.5; doll[pos+6].attack *= 1.5; }
                            else if(pos>3 && pos<7){ doll[pos+3].attack *= 1.5; doll[pos-3].attack *= 1.5; }
                            else{ doll[pos-6].attack *= 1.5; doll[pos-3].attack *= 1.5; }
                        }
                        else {//未被眩晕或者目标死亡
                            if(pos>0 && pos<4){ doll[pos+3].dodge *= 1.25; doll[pos+6].dodge *= 1.25; }
                            else if(pos>3 && pos<7){ doll[pos+3].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }
                            else{ doll[pos-6].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }
                        }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0){ //被眩晕
                            enemy.Dizzy += 1;
                            if(pos>0 && pos<4){ doll[pos+3].attack *= 1.5; doll[pos+6].attack *= 1.5; }
                            else if(pos>3 && pos<7){ doll[pos+3].attack *= 1.5; doll[pos-3].attack *= 1.5; }
                            else{ doll[pos-6].attack *= 1.5; doll[pos-3].attack *= 1.5; }
                        }
                        else {//未被眩晕或者目标死亡
                            if(pos>0 && pos<4){ doll[pos+3].dodge *= 1.25; doll[pos+6].dodge *= 1.25; }
                            else if(pos>3 && pos<7){ doll[pos+3].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }
                            else{ doll[pos-6].dodge *= 1.25; doll[pos-3].dodge *= 1.25; }
                        }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 102: {   //102 UMP40
            *pfire_timing += 1; *pskill1_timing += 1;

            if (frame % 60 == 0 && frame <= 240){
                if (doll[pos].sign_z[0] == 2){
                    doll[pos].dodge *= 1.1;
                    doll[pos].attack *= 0.95;}
                if (doll[pos].sign_z[0] == 1){
                    doll[pos].attack *= 1.3;
                    doll[pos].dodge *= 0.75;}
            }

            if (*pfire_timing == *precharge || frame == 0) {
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 103: {   //103 UMP45¤
            *pfire_timing += 1; *pskill1_timing += 1;

            int enemy_recharge = 1500/30;
            if(doll[pos].sign_z[1] == 1){ //烟雾弹开启
                doll[pos].sign_z[3]++;
                if(doll[pos].sign_z[3] >= enemy_recharge)
                {damage[pos][frame] += (50 * enemy.target_number); doll[pos].sign_z[3] = 0;
                enemy_recharge = floor(1500/floor(enemy.fire_rate));}
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.move /= 0.45;
                enemy.fire_rate /= 0.6;
                doll[pos].sign_z[1] = 0;
                doll[pos].sign_z[3] = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.move *= 0.45;
                        enemy.fire_rate *= 0.6;
                        doll[pos].sign_z[1] = 1;
                        enemy_recharge = floor(1500/floor(enemy.fire_rate));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.move *= 0.45;
                        enemy.fire_rate *= 0.6;
                        doll[pos].sign_z[1] = 1;
                        enemy_recharge = floor(1500/floor(enemy.fire_rate));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 104: {   //104 G36C
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].max_field = 0;
                doll[pos].current_field = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].max_field = 9999;
                        doll[pos].current_field = 9999;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 105: {   //105 OTs-12
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 106: {   //106 FAL
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 2 && *pskill1_timing == 10){ bomb( pos , frame , 5 ); }
            if(*pskill1_flag == 2 && *pskill1_timing == 20){ bomb( pos , frame , 5 ); }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 107: {   //107 F2000
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 108: {   //108 CZ-805
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 4.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 4.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 109: {   //109 MG5
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting ++; doll[pos].sign_z[1] ++;

                if(doll[pos].sign_z[1] % 4 == 0){
                    doll[pos].attack *= 3;
                    doll[pos].definitely_crit = 2;}

                if(doll[pos].sign_z[1] % 4 == 1 && doll[pos].sign_z[1] != 1){
                    doll[pos].attack /= 3;
                    doll[pos].definitely_crit = 0;}

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 11; }

                *pfire_timing = 0;
            }
        }break;

        case 110: {   //110 FG-42 猎杀冲动
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 1.60;
                doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 1.60;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 1.60;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 111: {   //111 AAT-52
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].attack /= 1.3;
                else doll[pos].attack /= 1.85;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.3;
                        else doll[pos].attack *= 1.85;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.3;
                        else doll[pos].attack *= 1.85;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 112: {   //112 内格夫
            *pfire_timing += 1; *pskill1_timing += 1;

            for(int k=1; k<5 ; k++){
                if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] ++;  }
                if(doll[pos].sign_z[k] > 25*FA){ doll[pos].sign_z[k] = 0; doll[pos].attack /= 1.5; }
            }

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                if(doll[pos].bullet_counting == 1 && frame >= 50) {
                    for(int k=1; k<5 ; k++){
                        if(doll[pos].sign_z[k] == 0){ doll[pos].sign_z[k] = 1;break;  }}}
                //qDebug() << frame << doll[pos].sign_z[1] << doll[pos].sign_z[2] << doll[pos].sign_z[3] << doll[pos].sign_z[4];
                //qDebug() << frame << doll[pos].attack ;

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    doll[pos].attack *= 1.5;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 113: {   //113 谢尔久科夫
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].attack /= 1.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 114: {   //114 维尔德MkⅡ
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.hit /= 0.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.hit *= 0.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.hit *= 0.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 115: {   //115 索米
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 116: {   //116 Z-62
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Ignite -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 117: {   //117 PSG-1 沉稳射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.8 , 6);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 118: {   //118 9A-91
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].attack /= 1.6;
                else doll[pos].attack /= 2.8;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.6;
                        else doll[pos].attack *= 2.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.6;
                        else doll[pos].attack *= 2.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 119: {   //119 OTs-14
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].attack /= 1.7;
                else doll[pos].attack /= 3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.7;
                        else doll[pos].attack *= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.7;
                        else doll[pos].attack *= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 120: {   //120 ARX-160
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 11 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 11 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 121: {   //121 Mk48 猎杀冲动
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 1.7;
                doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 1.7;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 1.7;
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 122: {   //122 G11
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_number = 5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 15;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 123: {   //123 P99
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].dodge /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 124: {   //124 Super SASS 沉稳射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 5 , 2.6 , 5.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 125: {   //125 MG4
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.35;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 4; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 126: {   //126 NZ75
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 127: {   //127 79式
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 128: {   //128 M99
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3.4 , 8);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 129: {   //129 95式
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 130: {   //130 97式
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 131: {   //131 EVO 3
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 132: {   //132 59式
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && condition.day_or_night == 0 && *pskill1_timing >= 5*FA){
                enemy.dodge /= 0.6;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 1 && condition.day_or_night == 1 && *pskill1_timing >= 8*FA){
                enemy.dodge /= 0.25;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) enemy.dodge *= 0.6;
                        else enemy.dodge *= 0.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) enemy.dodge *= 0.6;
                        else enemy.dodge *= 0.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 133: {   //133 63式
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].hit /= 6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].hit *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].hit *= 6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 134: {   //134 AR70
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 11 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 11 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 135: {   //135 SR-3MP
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 3.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 3.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 3.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 136: {   //136 PP-19
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 137: {   //137 PP-19-01
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.6;
                enemy.move /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.6;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.6;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 138: {   //138 6P62
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.35;
                doll[pos].hit /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.35;
                        doll[pos].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.35;
                        doll[pos].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 139: {   //139 Bren Ten
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++)doll[i].attack /= 1.18;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.18;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++)doll[i].attack *= 1.18;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 140: {   //140 PSM
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ doll[i].hit /= 1.55; doll[i].dodge /= 1.28; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ doll[i].hit *= 1.55; doll[i].dodge *= 1.28; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ doll[i].hit *= 1.55; doll[i].dodge *= 1.28; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 141: {   //141 USP Compact
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++) doll[i].hit /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++) doll[i].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++) doll[i].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 142: {   //142 Five-seveN
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ doll[i].fire_rate /= 1.2; doll[i].critical_per /= 1.2; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ doll[i].fire_rate *= 1.2; doll[i].critical_per *= 1.2; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ doll[i].fire_rate *= 1.2; doll[i].critical_per *= 1.2; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 143: {   //143 RO635
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.attack /= 0.75;
                doll[pos].dodge /= 1.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.attack *= 0.75;
                        doll[pos].dodge *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.attack *= 0.75;
                        doll[pos].dodge *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 144: {   //144 MT-9
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 145: {   //145 OTs-44
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3 , 6.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 146: {   //146 G28
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 147: {   //147 SSG 69
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 148: {   //148 IWS 2000
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.8;
                doll[pos].fire_rate /= 0.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.8;
                        doll[pos].fire_rate *= 0.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.8;
                        doll[pos].fire_rate *= 0.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 149: {   //149 AEK-999 猎杀冲动N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0) { doll[pos].hit /= 1.2; }
                else { doll[pos].hit /= 1.7; doll[pos].attack /= 1.4; }
                doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) { doll[pos].hit *= 1.2; }
                        else { doll[pos].hit *= 1.7; doll[pos].attack *= 1.4; }
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) { doll[pos].hit *= 1.2; }
                        else { doll[pos].hit *= 1.7; doll[pos].attack *= 1.4; }
                        doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 150: {   //150 希普卡
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 151: {   //151 M1887 终结打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if( *pskill1_flag == 1 && *pfire_timing == 0){ *pfire_timing = 1; *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                *pfire_timing = 0;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        damage[pos][frame] += max(1, floor(1000 * enemy.deep_damage));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                        *pfire_timing -= 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        damage[pos][frame] += max(1, floor(1000 * enemy.deep_damage));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                        *pfire_timing -= 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

            }
        }break;

        case 152: {   //152 M1897 震荡打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 2; *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 2; *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2;}
        }break;

        case 153: {   //153 M37 震荡打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 2.5; *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 2.5; *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2;}
        }break;

        case 154: {   //154 M500 防护专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].armor /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].armor *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].armor *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 155: {   //155 M590 防护专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].armor /= 1.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].armor *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].armor *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 156: {   //156 Super-Shorty 生存本能
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].armor /= 1.5; doll[pos].dodge /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].armor *= 1.5; doll[pos].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].armor *= 1.5; doll[pos].dodge *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 157: {   //157 KSG 生存本能
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].armor /= 1.6; doll[pos].dodge /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].armor *= 1.6; doll[pos].dodge *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].armor *= 1.6; doll[pos].dodge *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 158: {   //158 KS-23 火力专注SG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.2; doll[pos].fire_number = doll[pos].sign_z[0]*5;
                if(doll[pos].sign_z[1] == 1){ doll[pos].attack *= 3; doll[pos].fire_number = 5;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = min(5,enemy.target_number) *5;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = 25;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 159: {   //159 RMB-93 震荡打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 2; *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 2; *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2; }
        }break;

        case 160: {   //160 Saiga-12 巨羚号角
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].sign_z[3] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    if(doll[pos].sign_z[3] == 1){
                        doll[pos].sign_z[3] = 2; doll[pos].attack /= 1.5; doll[pos].attack *= 2.5;break;}
                    if(doll[pos].sign_z[3] == 2){
                        doll[pos].sign_z[3] = 3; doll[pos].attack /= 2.5; doll[pos].attack *= 3.5;break;}
                    if(doll[pos].sign_z[3] == 3){
                        doll[pos].sign_z[3] = 0; doll[pos].attack /= 3.5; *pskill1_flag = 2;break;}
                    }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5; doll[pos].sign_z[3] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 161: {   //161 97式霰 火力专注SG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.2; doll[pos].fire_number = doll[pos].sign_z[0]*5;
                if(doll[pos].sign_z[1] == 1){ doll[pos].attack *= 3; doll[pos].fire_number = 5;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = min(5,enemy.target_number) *5;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = 25;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 162: {   //162 SPAS-12 火力专注SG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.2; doll[pos].fire_number = doll[pos].sign_z[0]*5;
                if(doll[pos].sign_z[1] == 1){ doll[pos].attack *= 3; doll[pos].fire_number = 5;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = min(5,enemy.target_number) *5;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.2; doll[pos].fire_number = 25;
                        if(doll[pos].sign_z[1] == 1)doll[pos].attack /= 3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 163: {   //163 AA-12 酮血症
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].bullet_number -= 10; doll[pos].fire_rate /= 1.8;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 10; doll[pos].fire_rate *= 1.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 10; doll[pos].fire_rate *= 1.8;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 164: {   //164 FP-6 失乐园
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for(int j=0 ; j<5 ; j++){
                    if((pos - 6 + j*3)>0 && (pos - 6 + j*3)<10 && doll[pos - 6 + j*3].id != 0)doll[pos - 6 + j*3].injury_reduction /= 0.7; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb(pos , frame , 0.8);
                        for(int j=0 ; j<5 ; j++){
                            if((pos - 6 + j*3)>0 && (pos - 6 + j*3)<10 && doll[pos - 6 + j*3].id != 0)doll[pos - 6 + j*3].injury_reduction *= 0.7; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb(pos , frame , 0.8);
                        for(int j=0 ; j<5 ; j++){
                            if((pos - 6 + j*3)>0 && (pos - 6 + j*3)<10 && doll[pos - 6 + j*3].id != 0)doll[pos - 6 + j*3].injury_reduction *= 0.7; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 165: {   //165 M1014 应激性暗示
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].armor /= 1.3; doll[pos].attack /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].armor *= 1.3; doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].armor *= 1.3; doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 166: {   //166 CZ75 观测者直击
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 ){ doll[pos].attack /= 10; *pskill1_flag = 2; }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 10;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 10;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 167: {   //167 HK45 强袭号令
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ doll[i].attack /= 1.15; doll[i].hit /= 1.1; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ doll[i].attack *= 1.15; doll[i].hit *= 1.1; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ doll[i].attack *= 1.15; doll[i].hit *= 1.1; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 168: {   //168 Spitfire 突击压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.72;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.72;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.72;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 169: {   //169 SCW 机动专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.5; doll[pos].dodge /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.5; doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.5; doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 170: {   //170 Ash-12.7 歼灭专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5; doll[pos].critical_per /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 171: {   //171 利贝罗勒 猩红回响
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if((pos - 3)>0 && (pos - 3)<10 && doll[pos - 3].id != 0){
                    doll[pos -3].attack /= 1.25; doll[pos -3].fire_rate /= 1.25; doll[pos -3].hit /= 1.25; }
                if((pos + 3)>0 && (pos + 3)<10 && doll[pos + 3].id != 0){
                    doll[pos +3].attack /= 1.25; doll[pos +3].fire_rate /= 1.25; doll[pos +3].hit /= 1.25; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if((pos - 3)>0 && (pos - 3)<10 && doll[pos - 3].id != 0){
                            doll[pos -3].attack *= 1.25; doll[pos -3].fire_rate *= 1.25; doll[pos -3].hit *= 1.25; }
                        if((pos + 3)>0 && (pos + 3)<10 && doll[pos + 3].id != 0){
                            doll[pos +3].attack *= 1.25; doll[pos +3].fire_rate *= 1.25; doll[pos +3].hit *= 1.25; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if((pos - 3)>0 && (pos - 3)<10 && doll[pos - 3].id != 0){
                            doll[pos -3].attack *= 1.25; doll[pos -3].fire_rate *= 1.25; doll[pos -3].hit *= 1.25; }
                        if((pos + 3)>0 && (pos + 3)<10 && doll[pos + 3].id != 0){
                            doll[pos +3].attack *= 1.25; doll[pos +3].fire_rate *= 1.25; doll[pos +3].hit *= 1.25; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 172: {   //172 RFB
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.8; doll[pos].hit /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.8; doll[pos].hit *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.8; doll[pos].hit *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 173: {   //173 PKP
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting ++; doll[pos].sign_z[1] ++;

                if((myrand_skill()/10000) < 0.2){
                    doll[pos].sign_z[2] = 1; }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 11; }
                *pfire_timing = 0;
            }
            if(doll[pos].sign_z[2] == 1 && *pfire_timing == 1){ *pfire_timing = 0; doll[pos].sign_z[2] = 2; doll[pos].definitely_crit = 1; }
            if(doll[pos].sign_z[2] == 2 && *pfire_timing == 1){ *pfire_timing = 2; doll[pos].sign_z[2] = 0; doll[pos].definitely_crit = 0; }
        }break;

        case 174: {   //174 八一式马 突击专注N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].fire_rate /= 1.3;
                else doll[pos].fire_rate /= 1.9;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0)doll[pos].fire_rate *= 1.3;
                        else doll[pos].fire_rate *= 1.9;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0)doll[pos].fire_rate *= 1.3;
                        else doll[pos].fire_rate *= 1.9;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 175: {   //175 ART556 冲锋专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.85; doll[pos].hit /= 1.25;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.85; doll[pos].fire_rate *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.85; doll[pos].hit *= 1.25;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 176: {   //176 TMP 掩护专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 177: {   //177 KLIN 燃烧弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Ignite -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6.5 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 178: {   //178 F1 烟雾弹
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.64;
                enemy.move /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 179: {   //179 DSR-50 崩甲射击 血量最高目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    if(enemy.armor > 0) snipe( pos , frame , 7 , 4 , 10);
                    else snipe( pos , frame , 7 , 2.8 , 6);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 180: {   //180 PzB39 贯通射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 2*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 2.8);
                    for(int j=1 ; j<enemy.target_number ; j++){ snipe( pos , frame , 0 , 0 , 1.8); }
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 181: {   //181 T91 歼灭专注N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){ doll[pos].attack /= 1.5; doll[pos].critical_per /= 1.25; }
                else { doll[pos].attack /= 2.2; doll[pos].critical_per /= 1.5; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.25; }
                        else { doll[pos].attack *= 2.2; doll[pos].critical_per *= 1.5; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.25; }
                        else { doll[pos].attack *= 2.2; doll[pos].critical_per *= 1.5; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 182: {   //182 wz.29 突击专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 183: {   //183 竞争者 断罪者魔弹 前/中/后 最远/血量最高/最近
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 3);
                    enemy.deep_damage *= 1.4;
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if(*pskill1_flag == 2 && *pskill1_timing >= 5*FA){enemy.deep_damage /= 1.4; *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (*pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;
                case 1: break;
                case 2: {
                    *pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}break;
                case 3: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
            //qDebug() << frame << *pskill1_flag << *pskill1_timing << enemy.deep_damage;
        }break;

        case 184: {   //184 T-5000 锁定专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.5; doll[pos].hit /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.5; doll[pos].hit *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.5; doll[pos].hit *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 185: {   //185 阿梅利 蓄势待发N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].attack /= 1.11;
                else doll[pos].attack /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.11;
                        else doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 4; doll[pos].sign_z[1] = 1;
                        if(condition.day_or_night == 0)doll[pos].attack *= 1.11;
                        else doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 4; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 186: {   //186 P226 突击压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 187: {   //187 Ak 5 火力专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 188: {   //188 S.A.T.8 坚壁理论
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i = 3 ; i <= 9 ; i += 3){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 35;
                                        doll[i].shield_last[j] = 5*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i = 3 ; i <= 9 ; i += 3){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 35;
                                        doll[i].shield_last[j] = 5*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 189: {   //189 USAS-12 狂热突袭
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.6; doll[pos].bullet_number += 4; doll[pos].sign_z[2] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.6; doll[pos].bullet_number += 4; doll[pos].sign_z[2] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    if(doll[pos].sign_z[2] == 1){ *precharge = floor( 65 + 15 * doll[pos].bullet_number ) + 1*FA; doll[pos].bullet_number -= 4; doll[pos].sign_z[2] = 0; }
                    else *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 190: {   //190 NS2000 震荡打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 2; *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 2; *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2;}
        }break;

        case 191: {   //191 M12 燃烧弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Ignite -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 1 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 6 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Ignite += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 192: {   //192 JS05 贯通射击 最远目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 2*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 3);
                    for(int j=1 ; j<enemy.target_number ; j++){ snipe( pos , frame , 0 , 0 , 2); } //目标额外受到2倍伤害
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;} //对穿透的敌人造成两倍伤害
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 193: {   //193 T65 歼灭专注N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){ doll[pos].attack /= 1.45; doll[pos].critical_per /= 1.22; }
                else { doll[pos].attack /= 2; doll[pos].critical_per /= 1.4; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.45; doll[pos].critical_per *= 1.22; }
                        else { doll[pos].attack *= 2; doll[pos].critical_per *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.45; doll[pos].critical_per *= 1.22; }
                        else { doll[pos].attack *= 2; doll[pos].critical_per *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 194: {   //194 K2 热力过载
            *pfire_timing += 1; *pskill1_timing += 1;
            if(frame == 0){ *pskill1_flag = 1; doll[pos].sign_z[1] = 0; doll[pos].fire_number *= 3; doll[pos].attack *= 0.52; }

            if (*pfire_timing == *precharge || frame == 0) {
                if(*pskill1_flag == 1 || *pskill1_flag == 3)doll[pos].sign_z[1] ++; //温度提升
                else if(*pskill1_flag == 2 && doll[pos].sign_z[1]>0 )doll[pos].sign_z[1] --; //温度下降
                if(doll[pos].sign_z[1] == 15){ for(int j=0 ; j<15 ; j++){ doll[pos].attack *= 0.98; doll[pos].hit *= 0.98; }} //热力过载
                if(doll[pos].sign_z[1] > 15 && doll[pos].sign_z[1] <= 20){ doll[pos].attack *= 0.98; doll[pos].hit *= 0.98; }

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 1: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(doll[pos].sign_z[0] == 1 || doll[pos].sign_z[0] == 3) //技能操作选择
                        { doll[pos].attack /= 0.52; doll[pos].fire_number /= 3; *pskill1_timing = 0; *pskill1_flag = 2;
                            doll[pos].attack *= 1.05; doll[pos].sign_z[3] = 1; doll[pos].move *= 0.6; doll[pos].dodge *= 0.6; }
                    }}break;
                case 2: {
                    if(doll[pos].sign_z[3] <= 10 && doll[pos].sign_z[2] == 2 && doll[pos].sign_z[0] == 3){
                        doll[pos].attack *= 1.05; doll[pos].sign_z[3]++; }
                    else if(*pskill1_timing < doll[pos].skill1_cd && doll[pos].sign_z[3] <= 10 && doll[pos].sign_z[2] == 2) {
                        doll[pos].attack *= 1.05; doll[pos].sign_z[3]++; }
                    else if (*pskill1_timing >= doll[pos].skill1_cd && doll[pos].sign_z[0] == 1) {
                        for(int k=0 ; k<doll[pos].sign_z[3] ; k++){doll[pos].attack /= 1.05; }
                        doll[pos].fire_number *= 3; doll[pos].attack *= 0.52;  doll[pos].sign_z[3] = 0;
                        doll[pos].move /= 0.6; doll[pos].dodge /= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 3;
                    }}break;
                case 3: {
                    if (*pskill1_timing >= 3*FA ) {
                        if(doll[pos].sign_z[0] == 1 || doll[pos].sign_z[0] == 3)
                        { doll[pos].attack /= 0.52; doll[pos].fire_number /= 3; *pskill1_timing = 0; *pskill1_flag = 2;
                            doll[pos].attack *= 1.05; doll[pos].sign_z[3] = 1; doll[pos].move *= 0.6; doll[pos].dodge *= 0.6; }
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));

                //qDebug() << frame << ":" << "tem-" << doll[pos].sign_z[1] << "att-" << doll[pos].attack << "num-" << doll[pos].fire_number;
            }
        }break;

        case 195: {   //195 HK23 蓄势待发
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 3; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 196: {   //196 Zas M21 夜枭轰鸣
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 2 && enemy.target_number >= 3 && *pskill1_timing >= 3*FA){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && enemy.target_number < 3 && *pskill1_timing >= 8*FA){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 3 );
                        if(enemy.target_number >= 3) enemy.deep_damage *= 1.15;
                        else  {doll[pos].attack *= 1.6;}
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 3 );
                        if(enemy.target_number >= 3) enemy.deep_damage *= 1.15;
                        else  {doll[pos].attack *= 1.6;}
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 197: {   //197 卡尔卡诺M1891 玛尔斯号角
            *pfire_timing += 1; *pskill1_timing += 1;

            for(int j=1 ; j<4 ; j++){
                if(doll[pos].sign_z[j] > 0){ doll[pos].sign_z[j]++; } //时间累计
                if(doll[pos].sign_z[j] > 30){
                    doll[pos].sign_z[j] = 0; //持续时间结束该层数置零
                    for( ; j<=4 ; j++){ //消除效果
                        if((pos - 6 + j*3) > 0 && (pos - 6 + j*3) < 10){ //同列人形
                            doll[pos - 6 + j*3].critical_per /= 1.04; doll[pos - 6 + j*3].fire_rate /= 1.04; } }}
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for(int j=1 ; j<10 ; j++){ if(doll[j].type == 3) {doll[pos].fire_rate /= 1.08; doll[pos].critical_per /= 1.08; }}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {

                if((myrand_skill()/10000) <= 0.4){
                    int j=0 , k_tem=doll[pos].sign_z[1] , k_min=1 ;
                    for( ; j<=4 ; j++){
                        if((pos - 6 + j*3) > 0 && (pos - 6 + j*3) < 10){
                            doll[pos - 6 + j*3].critical_per *= 1.04; doll[pos - 6 + j*3].fire_rate *= 1.04; } }
                    for(int k=2 ; k<4 ; k++){
                        if(doll[pos].sign_z[k] < k_tem){ k_tem = doll[pos].sign_z[k]; k_min = k; } }
                    doll[pos].sign_z[k_min] = 1;
                }

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int j=1 ; j<10 ; j++){ if(doll[j].type == 3) {doll[pos].fire_rate *= 1.08; doll[pos].critical_per *= 1.08; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int j=1 ; j<10 ; j++){ if(doll[j].type == 3) {doll[pos].fire_rate *= 1.08; doll[pos].critical_per *= 1.08; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }

            //qDebug() << frame << doll[pos].fire_rate << doll[pos].sign_z[1] << doll[pos].sign_z[2] << doll[pos].sign_z[3] ;
        }break;

        case 198: {   //198 卡尔卡诺M91/38 墨尔斯假面
            *pfire_timing += 1; *pskill1_timing += 1;

            if(doll[pos].sign_z[2] == 1){
                if(enemy.elite_unit == 0)doll[pos].attack /= 45;
                else doll[pos].attack /= 3;
                doll[pos].sign_z[2] = 0;}

            if (*pfire_timing == *precharge || frame == 0) {
                if((myrand_skill()/10000) <= 0.7) doll[pos].sign_z[1] += 2;
                if(*pskill1_flag == 0 && *pskill1_timing >= doll[pos].skill1_before){ doll[pos].sign_z[1] += 18; *pskill1_timing = 0; *pskill1_flag = 2;}
                if(*pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_cd){ doll[pos].sign_z[1] += 18; *pskill1_timing = 0;}
                if(doll[pos].sign_z[1] >= 20){
                    if(enemy.elite_unit == 0)doll[pos].attack *= 45;
                    else doll[pos].attack *= 3;
                    doll[pos].sign_z[1] = 0;
                    doll[pos].sign_z[2] = 1;}
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 199: {   //199 80式 火力专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 200: {   //200 XM3 突击专注N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0)doll[pos].fire_rate /= 1.32;
                else doll[pos].fire_rate /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0)doll[pos].fire_rate *= 1.32;
                        else doll[pos].fire_rate *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0)doll[pos].fire_rate *= 1.32;
                        else doll[pos].fire_rate *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 201: {   //201 猎豹M1 阻断射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3 , 6.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 202: {   //202 雷电 临界点射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    double hit_tem,hit = floor(doll[pos].hit), nhit = floor(doll[pos].hit*(1 - 0.9*(1 - doll[pos].night_view_per)));//命中选择

                    if(doll[pos].definitely_hit == 1) hit_tem=1;
                    else if( condition.day_or_night == 0) hit_tem=(hit / (hit + enemy.dodge));
                    else hit_tem=(nhit / (nhit + enemy.dodge)) ;
                    if((myrand()/10000) < hit_tem) {snipe( pos , frame , 0 , 0 , 12);}

                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;
                    *precharge = 2*FA; }
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (*pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0; *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0; *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 203: {   //203 蜜獾 机动专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 2.5; doll[pos].dodge /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2.5; doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2.5; doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 204: {   //204 芭莉斯塔 机动专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if( frame % 45 == 0 ){ doll[pos].sign[1]++; } //标记增加

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    if(doll[pos].sign[1] > 1 || *pskill1_timing <= doll[pos].skill1_last )
                        { doll[pos].sign[1]--; }
                    else {
                        if( doll[pos].sign[1]<0 )doll[pos].sign[1] = 0;
                        doll[pos].fire_number /= 2;
                        *pskill1_timing = 0; *pskill1_flag = 2;}
                    }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
            qDebug() << frame << doll[pos].sign[1];
        }break;

        case 205: {   //205 AN-94 人偶扳机
            *pfire_timing += 1; *pskill1_timing += 1;

            if(doll[pos].sign_z[2] == 1){
                doll[pos].fire_number /= 2; doll[pos].sign_z[2] = 0; }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_number /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;}
                    else if((myrand()/100) < doll[pos].sign_z[0]){ doll[pos].fire_number *= 2; doll[pos].sign_z[2] = 1; }
                    }break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;}
                    else if((myrand()/100) < doll[pos].sign_z[0]){ doll[pos].fire_number *= 2; doll[pos].sign_z[2] = 1; }
                    }break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 206: {   //206 AK-12 雪狼之眼
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.35; doll[pos].fire_rate /= 1.35; doll[pos].hit /= 1.35; doll[pos].critical_per /= 1.35;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.35; doll[pos].fire_rate *= 1.35; doll[pos].hit *= 1.35; doll[pos].critical_per *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.35; doll[pos].fire_rate *= 1.35; doll[pos].hit *= 1.35; doll[pos].critical_per *= 1.35;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 207: {   //207 CZ2000 黎明气焰
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){ doll[pos].attack /= 1.65; doll[pos].critical_per /= 1.25; }
                else { doll[pos].hit /= 1.4; doll[pos].fire_rate /= 1.5; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.65; doll[pos].critical_per *= 1.25; }
                        else { doll[pos].hit *= 1.4; doll[pos].fire_rate *= 1.5; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].attack *= 1.65; doll[pos].critical_per *= 1.25; }
                        else { doll[pos].hit *= 1.4; doll[pos].fire_rate *= 1.5; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 208: {   //208 HK21 无差别崩坏
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.4; doll[pos].hit /= 1.3; doll[pos].move /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 2; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.4; doll[pos].hit *= 1.3; doll[pos].move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 2; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.4; doll[pos].hit *= 1.3; doll[pos].move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 2; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 209: {   //209 OTs-39 闪光弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0)enemy.Dizzy -= 1;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        if(enemy.elite_unit == 0)enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 210: {   //210 CZ52 火力号令
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){doll[i].attack /= 1.2;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){doll[i].attack *= 1.2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){doll[i].attack *= 1.2;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 211: {   //211 SRS 狩猎示范
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6; doll[pos].hit /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6; doll[pos].hit *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6; doll[pos].hit *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 212: {   //212 K5 战地哲学馆
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){
                    if(doll[pos].influence[i] == 1){
                        switch(doll[i].type){
                        case 1:
                        case 2: { doll[i].dodge /= 1.4; }break;
                        case 3:
                        case 4: { doll[i].attack /= 1.22; }break;
                        case 5:
                        case 6: { doll[i].dodge /= 1.8; }break;
                    }}}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){
                            if(doll[pos].influence[i] == 1){
                                switch(doll[i].type){
                                case 1:
                                case 2: { doll[i].dodge *= 1.4; }break;
                                case 3:
                                case 4: { doll[i].attack *= 1.22; }break;
                                case 5:
                                case 6: { doll[i].dodge *= 1.8; }break;
                            }}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){
                            if(doll[pos].influence[i] == 1){
                                switch(doll[i].type){
                                case 1:
                                case 2: { doll[i].dodge *= 1.4; }break;
                                case 3:
                                case 4: { doll[i].attack *= 1.22; }break;
                                case 5:
                                case 6: { doll[i].dodge *= 1.8; }break;
                            }}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 213: {   //213 C-MS 心情链环
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {

                if (*pskill1_flag == 0 && *pskill1_timing >= doll[pos].skill1_before ) {
                    doll[pos].dodge /= 1.65;
                    switch(doll[pos].sign_z[0]){
                    case 1: break;
                    case 2: doll[pos].attack *= 1.85; break;
                    case 3: doll[pos].hit *= 3; break;
                    }
                    *pskill1_timing = 0;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 214: {   //214 ADS 风暴潮
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(doll[pos].sign_z[3] > 0)doll[pos].sign_z[3]++;
            if(doll[pos].sign_z[3] > 2.4*FA){ doll[pos].sign_z[3] = 0; enemy.Dizzy -= 1; }

            if (*pfire_timing == *precharge || frame == 0){
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] += 3; doll[pos].sign_z[1] += 5; doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 1; }
                    else if((myrand()/10000) < 0.4){ doll[pos].sign_z[1] += 1; }
                    }break;
                case 1: {
                    doll[pos].sign_z[1] += 1;
                    }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] += 3; doll[pos].sign_z[1] += 5; doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 1; }
                    else if((myrand()/10000) < 0.4){ doll[pos].sign_z[1] += 1; }
                    }break;
                }

                if(doll[pos].sign_z[1] >= 5){ bomb(pos,frame,6); enemy.Dizzy += 1; doll[pos].sign_z[3] = 1; doll[pos].sign_z[1] = 0;}
                if(doll[pos].sign_z[2] >= 5){ bomb(pos,frame,6); doll[pos].sign_z[1] = 0;}

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));

                //qDebug() << frame << "1:" << doll[pos].sign_z[1] << "2:" << doll[pos].sign_z[2] << "3:" << doll[pos].sign_z[3];
            }
        }break;

        case 215: {   //215 MDR 危机嗅探器
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(doll[pos+1].id != 0){doll[pos+1].dodge /= 1.8; }
                else { doll[pos].attack /= 1.45; doll[pos].fire_rate /= 1.22; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(doll[pos+1].id != 0 && pos != 3 && pos != 6 && pos!= 9){
                            doll[pos+1].dodge *= 1.8;
                            for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                if(doll[pos+1].shield_last[j] == 0){
                                    doll[pos+1].shield_quantity[j] = 40;
                                    doll[pos+1].shield_last[j] = 10*FA;
                                    break;}}}
                        else { doll[pos].attack *= 1.45; doll[pos].fire_rate *= 1.22; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(doll[pos+1].id != 0 && pos != 3 && pos != 6 && pos!= 9){
                            doll[pos+1].dodge *= 1.8;
                            for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                if(doll[pos+1].shield_last[j] == 0){
                                    doll[pos+1].shield_quantity[j] = 40;
                                    doll[pos+1].shield_last[j] = 10*FA;
                                    break;}}}
                        else { doll[pos].attack *= 1.45; doll[pos].fire_rate *= 1.22; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 216: {   //216 XM8 杀伤榴弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 12 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 12 );
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 217: {   //217 SM-1 突击专注T
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 218: {   //218 T77 掩护专注T
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 220: {   //220 MP-443 火力压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.attack /= 0.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 221: {   //221 GSh-18 锁链冲击
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_number /= 2; doll[pos].definitely_crit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number *= 2; doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number *= 2; doll[pos].definitely_crit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 222: {   //222 TAC-50 枫华萤火
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].sign_z[1] == 1){
                    double after_ceil,after_random,after_crit,after_advanced;

                    after_ceil = ceil(doll[pos].attack) * 4.5;
                    after_random = (1.15 - ((myrand()/10000) * 3) / 10) * after_ceil;
                    if (doll[pos].critical_per <= (myrand()/10000)) after_crit = after_random;
                    else after_crit = after_random * (floor(doll[pos].crit_damage_rate * 100) / 100);
                    after_advanced = max(1, floor(after_crit*enemy.deep_damage));
                    damage[pos][frame] += after_advanced * 5;

                    doll[pos].sign_z[1] = 0;
                }

            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 223: {   //223 Model L 锁定专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.4; doll[pos].hit /= 1.9;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.4; doll[pos].hit *= 1.9;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.4; doll[pos].hit *= 1.9;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 224: {   //224 PM-06 隐秘专注N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){ doll[pos].dodge /= 1.5; doll[pos].hit /= 1.4; }
                else {doll[pos].dodge /= 1.5; doll[pos].hit /= 1.4; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].dodge *= 1.5; doll[pos].hit *= 1.4; }
                        else {doll[pos].dodge *= 1.5; doll[pos].hit *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].dodge *= 1.5; doll[pos].hit *= 1.4; }
                        else {doll[pos].dodge *= 1.5; doll[pos].hit *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 225: {   //225 Cx4 风暴 隐秘专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 1.8; doll[pos].hit /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 1.8; doll[pos].hit *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 1.8; doll[pos].hit *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 226: {   //226 Mk12 愤怒灵感
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.3; doll[pos].crit_damage_rate /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.3; doll[pos].crit_damage_rate *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.3; doll[pos].crit_damage_rate *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 227: {   //227 A-91 杀伤榴弹N
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 1){doll[pos].attack /= 1.5; doll[pos].hit /= 1.5; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 10 );
                        if(condition.day_or_night == 1){doll[pos].attack *= 1.5; doll[pos].hit *= 1.5; }
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 10 );
                        if(condition.day_or_night == 1){doll[pos].attack *= 1.5; doll[pos].hit *= 1.5; }
                        doll[pos].fire_number = 4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 228: {   //228 樱花 樱反像
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= 10*FA){
                if(doll[pos].sign_z[0] == 2) doll[pos].dodge /= 1.65;
                else doll[pos].attack /= 1.85;
                doll[pos].sign_z[1] = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos].shield_last[j] == 0){
                                doll[pos].shield_quantity[j] = 42;
                                doll[pos].shield_last[j] = 5*FA;
                                break;}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    if(*pskill1_timing >= 5*FA && doll[pos].sign_z[1] == 0){
                        if(doll[pos].sign_z[0] == 2) doll[pos].dodge *= 1.65;
                        else doll[pos].attack *= 1.85;
                        doll[pos].sign_z[1] = 1; }
                    }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos].shield_last[j] == 0){
                                doll[pos].shield_quantity[j] = 42;
                                doll[pos].shield_last[j] = 5*FA;
                                break;}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 229: {   //229 M870 地狱公路
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing % FA == 0 ){
                doll[pos].current_field -= 100; }

            if(*pskill1_flag  == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].max_field = 0;
                doll[pos].current_field = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].max_field = 1000;
                        doll[pos].current_field = 1000;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].max_field = 1000;
                        doll[pos].current_field = 1000;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 230: {   //230 OBR 锁定专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.45; doll[pos].hit /= 1.45;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.45; doll[pos].hit *= 1.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.45; doll[pos].hit *= 1.45;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 231: {   //231 M82A1 伪神的启示
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){ doll[pos].sign_z[1] = 3; }

            if(doll[pos].sign_z[2] > 1){
                doll[pos].sign_z[2] ++;
                if(doll[pos].sign_z[2] > 5*FA){ doll[pos].sign_z[2] = 0; enemy.attack /= 0.8; } }

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1*FA ) { //造成伤害
                    double power_plus = 4.2;
                    for(int i=0 ; i<doll[pos].sign_z[0] ; i++)power_plus *= 1.1;

                    if(doll[pos].sign_z[1] > 1) snipe( pos , frame , 0 , 0 , power_plus);
                    else { snipe( pos , frame , 0 , 0 , power_plus * 2); doll[pos].sign_z[2] = 1; enemy.attack *= 0.8; }
                    doll[pos].sign_z[1] --;
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[1] > 0 && *pskill1_timing >= doll[pos].skill1_before){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (doll[pos].sign_z[1] > 0 && *pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 232: {   //232 MP-448 掩护压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.dodge /= 1.54;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.dodge *= 1.54;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.dodge *= 1.54;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 233: {   //233 Px4 风暴 狩猎筹码
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ doll[i].critical_per /= 0.8; doll[i].crit_damage_rate /= 1.50; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ doll[i].critical_per *= 0.8; doll[i].crit_damage_rate *= 1.50; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ doll[i].critical_per *= 0.8; doll[i].crit_damage_rate *= 1.50; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 234: {   //234 JS 9 临阵磨枪
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for(int i=0 ; i<3 ; i++){ doll[pos].attack /= 1.5; }
                for(int j=0 ; j<min(6 , enemy.target_number-1) ; j++){ doll[pos].attack *= 1.5; doll[pos].dodge /= 1.35;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i=0 ; i<3 ; i++){ doll[pos].attack *= 1.5; }
                        for(int j=0 ; j<min(6 , enemy.target_number-1) ; j++){ doll[pos].attack /= 1.5; doll[pos].dodge *= 1.35;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i=0 ; i<3 ; i++){ doll[pos].attack *= 1.5; }
                        for(int j=0 ; j<min(6 , enemy.target_number-1) ; j++){ doll[pos].attack /= 1.5; doll[pos].dodge *= 1.35;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 235: {   //235 SPR A3G 自我气焰
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 2 && *pskill1_timing >= 5*FA && doll[pos].sign_z[0] == 2 && doll[pos].sign_z[1] == 1){
                doll[pos].fire_rate /= 1.25; doll[pos].sign_z[1] = 0;}

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 5.5);
                    if(doll[pos].sign_z[0] == 2){ doll[pos].fire_rate *= 1.25; doll[pos].sign_z[1] = 1; }
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (*pskill1_timing >= doll[pos].skill1_before){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 236: {   //236 K11 恐惧榴弹
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 0)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 4 );
                        for(int j=0 ; j<4 ; j++){
                            if((myrand()/10000) < doll[pos].sign_z[0]){ bomb( pos , frame , 4 ); bomb( pos , frame , 2 ); }
                            else bomb( pos , frame , 4 );}
                        doll[pos].fire_number = 0;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb( pos , frame , 4 );
                        for(int j=0 ; j<4 ; j++){
                            if((myrand()/10000) < doll[pos].sign_z[0]){ bomb( pos , frame , 4 ); bomb( pos , frame , 2 ); }
                            else bomb( pos , frame , 4 );}
                        doll[pos].fire_number = 0;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 237: {   //237 SAR-21 大流星暴
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;

                if( *pskill1_flag == 1 ) *precharge = 10;
                else *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 238: {   //238 88式 懒惰的怒火
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){ doll[pos].move *= 1.5; doll[pos].hit *= 0.8; }
            if(frame == 6*FA){ if(doll[pos].sign_z[0] == 2){
                    doll[pos].move /= 1.5; doll[pos].hit /= 0.8; doll[pos].bullet_number += 2; doll[pos].hit *= 1.3; } }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 239: {   //239 03式 歼灭专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5; doll[pos].critical_per /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5; doll[pos].critical_per *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 240: {   //240 Mk46 强袭专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5; doll[pos].hit /= 1.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].hit *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5; doll[pos].hit *= 1.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 241: {   //241 RT-20 阻断射击 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 7 , 3 , 6.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (doll[pos].sign_z[5] == 2 && *pskill1_timing >= (doll[pos].skill1_before + (doll[pos].sign_z[0] - 1) * FA)){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 242: {   //242 P22 决战序列
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                {doll[1].attack /= 1.25; doll[4].attack /= 1.25; doll[7].attack /= 1.25;}
                {doll[2].dodge /= 1.6; doll[2].hit /= 1.6; doll[5].dodge /= 1.6; doll[5].hit /= 1.6; doll[8].dodge /= 1.6; doll[8].hit /= 1.6;}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        {doll[1].attack *= 1.25; doll[4].attack *= 1.25; doll[7].attack *= 1.25;}
                        {doll[2].dodge *= 1.6; doll[2].hit *= 1.6; doll[5].dodge *= 1.6; doll[5].hit *= 1.6; doll[8].dodge *= 1.6; doll[8].hit *= 1.6;}
                        for(int i = 3 ; i <= 9 ; i += 3){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 53;
                                        doll[i].shield_last[j] = 8*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        {doll[1].attack *= 1.25; doll[4].attack *= 1.25; doll[7].attack *= 1.25;}
                        {doll[2].dodge *= 1.6; doll[2].hit *= 1.6; doll[5].dodge *= 1.6; doll[5].hit *= 1.6; doll[8].dodge *= 1.6; doll[8].hit *= 1.6;}
                        for(int i = 3 ; i <= 9 ; i += 3){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 53;
                                        doll[i].shield_last[j] = 8*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 243: {   //243 64式自 未来预警
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(doll[pos].sign_z[0] == 2){ doll[pos].fire_rate /= 1.8; doll[pos].hit /= 1.8;}
                else {doll[pos].attack /= 1.9;}

                if(doll[pos].sign_z[1] == 1){
                    if(doll[pos+1].id != 0){ //该位置上存在人形
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos+1].shield_last[j] == 0){
                                doll[pos+1].shield_quantity[j] = 25;
                                doll[pos+1].shield_last[j] = 5*FA;
                                break;}}}
                    if( pos+4 <= 9 && doll[pos+4].id != 0){
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos+4].shield_last[j] == 0){
                                doll[pos+4].shield_quantity[j] = 25;
                                doll[pos+4].shield_last[j] = 5*FA;
                                break;}}
                    }
                }
                if(doll[pos].sign_z[1] == 0){ doll[pos].attack *= 1.55;
                    for(int j=1 ; j<10 ; j++){ if(doll[pos].influence[j] == 1)doll[j].attack *= 1.55;  }} //等于2时加护盾
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= 5*FA){
                if(doll[pos].sign_z[1] == 0){ doll[pos].attack /= 1.55;
                    for(int j=1 ; j<10 ; j++){ if(doll[pos].influence[j] == 1)doll[j].attack /= 1.55;  }} //等于2时加护盾
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(doll[pos].sign_z[0] == 2){ doll[pos].fire_rate *= 1.8; doll[pos].hit *= 1.8;}
                        else {doll[pos].attack *= 1.9;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(doll[pos].sign_z[0] == 2){ doll[pos].fire_rate *= 1.8; doll[pos].hit *= 1.8;}
                        else {doll[pos].attack *= 1.9;}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 244: {   //244 TEC-9 火力压制N
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= 5*FA && condition.day_or_night == 0){ //day
                enemy.attack /= 0.78;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 1 && *pskill1_timing >= 8*FA && condition.day_or_night == 1){ //night
                enemy.attack /= 0.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0) enemy.attack *= 0.78;
                        if(condition.day_or_night == 1) enemy.attack *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0) enemy.attack *= 0.78;
                        if(condition.day_or_night == 1) enemy.attack *= 0.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 245: {   //245 P90 灰鼠
            *pfire_timing += 1; *pskill1_timing += 1;

            //doll[pos].sign_z[1] 主动计时  doll[pos].sign_z[2] 被动计时 doll[pos].sign_z[3] 被动剩余次数

            if(doll[pos].sign_z[0] == 2 && frame % (6*FA) == 0){ doll[pos].sign_z[3] = 4;
                doll[pos].definitely_hit = 1; doll[pos].definitely_crit = 1;}

            if (*pfire_timing == *precharge || frame == 0) {
                if(doll[pos].sign_z[3] == 0){ doll[pos].definitely_hit = 0; doll[pos].definitely_crit = 0;}
                if(doll[pos].sign_z[3] > 0){ doll[pos].sign_z[3] --; }

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
            //qDebug() << frame << doll[pos].sign_z[3];
        }break;

        case 247: {   //247 K31 紧急流速
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.8; doll[pos].hit /= 0.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.8; doll[pos].hit *= 0.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.8; doll[pos].hit *= 0.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 248: {   //248 杰里科 深红月蚀
            *pfire_timing += 1; *pskill1_timing += 1;

            int i;
            for (i = 1; i < 10; i++){ if((doll[i].type == 5 || doll[i].type == 6) && doll[i].bullet_counting == 0 && doll[i].fire_timing == 1){
                    if(doll[pos].sign_z[i] < 3){ doll[i].attack *= 1.05; doll[i].hit *= 1.05; doll[pos].sign_z[i] ++; }
                    qDebug() << frame << i << doll[pos].sign_z[i];
                }}

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                for (int i = 1; i < 10; i++){ if(doll[pos].influence[i] == 1){ doll[pos].attack /= 1.15; }}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for (int i = 1; i < 10; i++){ if(doll[pos].influence[i] == 1){ doll[pos].attack *= 1.15; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for (int i = 1; i < 10; i++){ if(doll[pos].influence[i] == 1){ doll[pos].attack *= 1.15; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 249: {   //249 62式 强袭专注MG
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.45; doll[pos].hit /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.45; doll[pos].hit *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.45; doll[pos].hit *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 250: {   //250 HS2000 反击者壁垒
            *pfire_timing += 1; *pskill1_timing += 1;

            if(doll[pos].sign_z[0] == 2 && *pskill1_flag == 1 && *pskill1_timing >= 3*FA){
                for (int i = 1; i < 10; i++){ doll[i].attack *= 1.35; doll[i].hit *= 1.35; }
                *pskill1_flag = 2;}

            if(doll[pos].sign_z[0] == 2 && *pskill1_flag == 2 && *pskill1_timing >= 8*FA){
                for (int i = 1; i < 10; i++){ doll[i].attack /= 1.35; doll[i].hit /= 1.35; }
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i = 1 ; i <= 9 ; i ++ ){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 42;
                                        doll[i].shield_last[j] = 6*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i = 1 ; i <= 9 ; i ++ ){
                            if(doll[i].id != 0){ //该位置上存在人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 42;
                                        doll[i].shield_last[j] = 6*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                //qDebug() << frame << doll[pos].attack;
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 251: {   //251 X95 花之锁
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= (1 + 3 * doll[pos].sign_z[0]/100);
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= (1 + 3 * doll[pos].sign_z[0]/100);
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= (1 + 3 * doll[pos].sign_z[0]/100);
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 252: {   //252 KSVK 震荡冲击弹 最近目标
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 4);
                    bomb(pos , frame , 0.5);
                    enemy.hit *= 0.8; enemy.fire_rate *= 0.8;
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if(*pskill1_flag == 2 && *pskill1_timing >= 5){
                enemy.hit /= 0.8; enemy.fire_rate /= 0.8;
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置+蓄力
                    if (*pskill1_timing >= doll[pos].skill1_before){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 3: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
        }break;

        case 253: {   //253 刘易斯 力天使
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[2] 被动层数
            if(frame == 1){doll[pos].bullet_number ++; }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    double recharge_s;
                    if(doll[pos].sign_z[2] < 2){ doll[pos].bullet_number ++; doll[pos].sign_z[2] ++; }
                    recharge_s = (4 + 200 / limit( pos , *pfire_rate )) * 30 * (1 - 0.15*doll[pos].sign_z[2]);
                    //qDebug() << frame << recharge_s << floor(recharge_s);
                    *precharge = floor(recharge_s);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
                //qDebug() << frame << doll[pos].bullet_number << doll[pos].sign_z[2];
            }
        }break;

        case 254: {   //254 UKM-2000 白夜独奏曲
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(condition.day_or_night == 0){doll[pos].hit /= 1.4; }
                else {doll[pos].hit /= 1.8; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(condition.day_or_night == 0){ doll[pos].bullet_number += 2; doll[pos].hit *= 1.4; }
                        else { doll[pos].bullet_number += 4; doll[pos].hit *= 1.8; }
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(condition.day_or_night == 0){ doll[pos].bullet_number += 2; doll[pos].hit *= 1.4; }
                        else { doll[pos].bullet_number += 4; doll[pos].hit *= 1.8; }
                        doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    double recharge_s = (4 + 200 / limit( pos , *pfire_rate )) * 30;

                    if(doll[pos].sign_z[1] == 1){
                        if(condition.day_or_night == 0){ doll[pos].bullet_number -= 2; recharge_s *= 1; }
                        else { doll[pos].bullet_number -= 4; recharge_s *= 0.7; }
                        doll[pos].sign_z[1] = 0; }

                    doll[pos].bullet_counting = 0;
                    *precharge = floor(recharge_s);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 255: {   //255 侦察者 火力专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 256: {   //256 隼 夕阳隼
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[2]普通子弹 doll[pos].sign_z[3]特殊子弹 doll[pos].sign_z[0]手动技能不开启主动

            if(frame == 0){ doll[pos].sign_z[2] = 2;}
            if((frame >= 8*FA && (frame-6*FA)%(8*FA) == 1) || frame == 6*FA){
                if(doll[pos].sign_z[3] < 2){ doll[pos].sign_z[3] ++; doll[pos].attack *= 1.18; doll[pos].hit *= 1.18;} }

            if (*pfire_timing == *precharge || frame == 0) {

                switch (*pskill1_flag) {
                case 0: { //前置
                    if (doll[pos].sign_z[0] == 0 && doll[pos].sign_z[3] > 0 && *pskill1_timing >= doll[pos].skill1_before){
                        *pskill1_flag = 1;*pskill1_timing = 0;}
                    else{ doll[pos].sign_z[2] --;
                        if(doll[pos].sign_z[2] == 0){ doll[pos].sign_z[2] = 2; *precharge = 60;}
                        else{ *precharge = FA; }
                        *pfire_timing = 0; }
                }break;

                case 2: { //冷却
                    if (doll[pos].sign_z[0] == 0 && doll[pos].sign_z[3] > 0 && *pskill1_timing >= doll[pos].skill1_cd ) {
                        *pskill1_flag = 1;*pskill1_timing = 0;}
                    else{ doll[pos].sign_z[2] --;
                        if(doll[pos].sign_z[2] == 0){ doll[pos].sign_z[2] = 2; *precharge = 60;}
                        else{ *precharge = FA; }
                        *pfire_timing = 0; }
                }break;
                default: break; }
            }

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 2*FA ) { //造成伤害
                    double after_ceil,after_random,after_crit,after_advanced;

                    after_ceil = ceil(doll[pos].attack) * 2.5;
                    after_random = (1.15 - ((myrand()/10000) * 3) / 10) * after_ceil;
                    if (doll[pos].critical_per <= (myrand()/10000)) after_crit = after_random;
                    else after_crit = after_random * (floor(doll[pos].crit_damage_rate * 100) / 100);
                    after_advanced = max(1, floor(after_crit*enemy.deep_damage));
                    damage[pos][frame] += after_advanced * 5;

                    doll[pos].sign_z[3] --; doll[pos].attack /= 1.18; doll[pos].hit /= 1.18;
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default: break; }

            qDebug() << frame << doll[pos].sign_z[2] << doll[pos].sign_z[3];
        }break;

        case 257: {   //257 M200 无言杀意
            *pfire_timing += 1; *pskill1_timing += 1;
            if(frame == 0 && enemy.armor > 0){ doll[pos].attack *= 1.05;}

            for(int k=1; k<5 ; k++){
                if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] ++;  }
                if(doll[pos].sign_z[k] > 3*FA){ doll[pos].sign_z[k] = 0; enemy.attack /= 0.9; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.armor > 0){ doll[pos].attack *= 1.05;}
                doll[pos].attack /= 2; doll[pos].definitely_hit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(enemy.armor > 0){ doll[pos].attack /= 1.05;}
                        doll[pos].attack *= 2; doll[pos].definitely_hit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    *precharge = floor(1.5 * FA * max( 0 , 1 -  min( 0.3 , doll[pos].cd_inf )));
                    enemy.attack *= 0.9;
                    for(int k=1; k<5 ; k++){
                        if(doll[pos].sign_z[k] == 0){ doll[pos].sign_z[k] = 1;break; }}
                    }break;
                case 2: {
                    *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        if(enemy.armor > 0){ doll[pos].attack /= 1.05;}
                        doll[pos].attack *= 2; doll[pos].definitely_hit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
            }
        }break;

        case 258: {   //258 马盖尔 冲锋专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5; doll[pos].fire_rate /= 1.2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].fire_rate *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5; doll[pos].fire_rate *= 1.2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 259: {   //259 PM-9 冲锋专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].dodge /= 2; doll[pos].attack /= 0.7; doll[pos].hit /= 0.7; doll[pos].fire_number /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].dodge *= 2; doll[pos].attack *= 0.7; doll[pos].hit *= 0.7; doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].dodge *= 2; doll[pos].attack *= 0.7; doll[pos].hit *= 0.7; doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 260: {   //260 PA-15 劲爆乐园
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1){
                doll[pos].attack /= 2;

                double after_ceil,after_random,after_armor,after_crit,after_advanced;

                after_ceil = ceil(doll[pos].attack);
                after_random = (1.15 - ((myrand()/10000) * 3) / 10) * after_ceil;
                after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));

                if (doll[pos].definitely_crit == 1) after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);
                else if (doll[pos].definitely_crit == 2) after_crit = after_armor;
                else if (doll[pos].critical_per <= (myrand()/10000)) after_crit = after_armor;
                else after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);
                after_advanced = max(1, floor(after_crit*enemy.deep_damage));
                damage[pos][frame] += after_advanced * enemy.target_number;

                doll[pos].attack /= 2; doll[pos].definitely_hit = 0;
                *pskill1_flag = 2;}

            if(*pskill1_flag == 2 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.Dizzy -= 1;
                *pskill1_flag = 3;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 狙击后1 技能期2 冷却3
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 4; doll[pos].definitely_hit = 1; enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: break;
                case 3: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 4; doll[pos].definitely_hit = 1; enemy.Dizzy += 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 261: {   //261 QBU-88 乱石崩云 血量最高
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[2]同一目标攻击计数  doll[pos].sign_z[0]始终攻击同一目标

            switch (*pskill1_flag) {
            case 1:{ //瞄准
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 5);
                    bomb(pos , frame , 0.5);
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;}
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: { //前置+蓄力
                    if (*pskill1_timing >= doll[pos].skill1_before){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;
                case 2: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0;*precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default: break; }

                if(*pskill1_flag != 1 && doll[pos].sign_z[0] == 2){
                    doll[pos].sign_z[2] ++;
                    if(doll[pos].sign_z[2] == 3){ bomb(pos , frame , 1.5); doll[pos].sign_z[2] = 0;}
                }
            }
        }break;

        case 262: {   //262 EM-2 碎碎曲奇弹 随机敌方
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[2]快速射击次数

            if(*pskill1_flag == 1 && doll[pos].sign_z[2] == 3){
                doll[pos].definitely_hit = 0; doll[pos].attack /= 3.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].definitely_hit = 1; doll[pos].attack *= 3.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].definitely_hit = 1; doll[pos].attack *= 3.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                *pfire_timing = 0;

                if(*pskill1_flag == 1){ *precharge = 10; doll[pos].sign_z[2] ++; } //快速射击
                else *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 263: {   //263 MG36 光影帷幕
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[3]SMG缩短换弹时间 doll[pos].sign_z[4]AR提升命中 doll[pos].sign_z[5]SG提升弹量

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.55;
                for(int j=1 ; j<10 ; j++){
                    if(doll[pos].influence[j] == 1 && doll[j].type == 2){ doll[pos].hit /= 1.25; }}
                doll[pos].sign_z[3] = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                if(doll[pos].bullet_counting == 1){
                    for(int j=1 ; j<10 ; j++){
                        if(doll[pos].influence[j] == 1){ doll[j].injury_reduction /= 0.8;}
                    }}

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.55;
                        for(int j=1 ; j<10 ; j++){
                            if(doll[pos].influence[j] == 1){
                                switch (doll[j].type) {
                                case 2: if(doll[pos].sign_z[3] < 3){doll[pos].sign_z[3] += 1; doll[pos].hit *= 1.25; }break;
                                case 4: if(doll[pos].sign_z[4] < 3){doll[pos].sign_z[4] += 1;}break;
                                case 6: if(doll[pos].sign_z[5] < 3){doll[pos].sign_z[5] += 1; doll[pos].bullet_number += 1;}break;
                                default: break;}}}

                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.55;
                        for(int j=1 ; j<10 ; j++){
                            if(doll[pos].influence[j] == 1){
                                switch (doll[j].type) {
                                case 2: if(doll[pos].sign_z[3] < 3){doll[pos].sign_z[3] += 1; doll[pos].hit *= 1.25; }break;
                                case 4: if(doll[pos].sign_z[4] < 3){doll[pos].sign_z[4] += 1;}break;
                                case 6: if(doll[pos].sign_z[5] < 3){doll[pos].sign_z[5] += 1; doll[pos].bullet_number += 1;}break;
                                default: break;}}}

                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    double recharge_s = (4 + 200 / limit( pos , *pfire_rate )) * 30;
                    for(int j=1 ; j<10 ; j++){ //被动 友方单位减伤
                        if(doll[pos].influence[j] == 1){ doll[j].injury_reduction /= 0.8;}  }
                    for(int k=0 ; k<doll[pos].sign_z[4] ; k++){ recharge_s *= 0.75; }
                    doll[pos].sign_z[4] = 0;
                    doll[pos].bullet_number -= doll[pos].sign_z[5];
                    doll[pos].sign_z[5] = 0;

                    *precharge = floor(recharge_s);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
                //qDebug() << frame << doll[pos].hit << doll[pos].sign_z[3];
            }
        }break;

        case 264: {   //264 绍沙 百合纹章
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[3]百合纹章 doll[pos].sign_z[4]消耗的百合纹章 doll[pos].sign_z[5]

            if(frame % (4*FA) == 0 && doll[pos].sign_z[3] <= 4){ doll[pos].sign_z[3] ++; }

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[4] = min(2 , doll[pos].sign_z[3]);
                        doll[pos].sign_z[3] -= doll[pos].sign_z[4];
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    if (doll[pos].sign_z[4] < 2 && *pskill1_timing >= doll[pos].skill1_cd ) {
                        double change = min(2 , doll[pos].sign_z[3]);
                        doll[pos].sign_z[4] += change;
                        doll[pos].sign_z[3] -= change;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    double recharge_s = (4 + 200 / limit( pos , *pfire_rate )) * 30;
                    for(int k=0 ; k<doll[pos].sign_z[4] ; k++){ recharge_s *= 0.8;}
                    doll[pos].sign_z[4] = 0;
                    *precharge = floor(recharge_s);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
            //qDebug() << frame << doll[pos].bullet_counting << doll[pos].sign_z[3] << doll[pos].sign_z[4];
        }break;

        case 265: {   //265 HK33 突击专注T
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 266: {   //266 R93 强运扳机
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[0]层数模式 1.固定层数/2.每4次普攻切换  doll[pos].sign_z[1]固定层数
            // doll[pos].sign_z[2]攻击同一目标计数 doll[pos].sign_z[3-5]buff计时 doll[pos].sign_z[9]buff层数

            if(frame == 0 && doll[pos].sign_z[0] == 1){
                for(int j=0 ; j<doll[pos].sign_z[1] ; j++)doll[pos].fire_rate *= 1.1; }

            for(int k=3; k<6 ; k++){
                if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] ++;  }
                if(doll[pos].sign_z[k] > 3*FA){ doll[pos].sign_z[k] = 0; doll[pos].fire_rate /= 1.1; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.4;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].sign_z[2] ++;

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: { }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.4;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break; }

                if(doll[pos].sign_z[0] == 2){
                    if(doll[pos].sign_z[2] != 1){
                        doll[pos].fire_rate *= 1.1;
                        int min_k=3,min_k_value=doll[pos].sign_z[3];
                        for(int k=3; k<6 ; k++){
                            if(doll[pos].sign_z[k] < min_k_value){ min_k=k; min_k_value=doll[pos].sign_z[k];}}
                        if(doll[pos].sign_z[min_k] != 0)doll[pos].fire_rate /= 1.1;
                        doll[pos].sign_z[min_k] = 1;}

                    if(doll[pos].sign_z[2] >= 5 && *pskill1_flag != 1){ //重新索敌
                        for(int k=3; k<6 ; k++){ if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] = 0; doll[pos].fire_rate /= 1.1;}}
                        doll[pos].sign_z[2] = 0;}

                    if(doll[pos].sign_z[2] >= 5 && *pskill1_flag == 1){ doll[pos].sign_z[2] = 0; }
                    }

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }

            //qDebug() << frame << doll[pos].sign_z[2] << *pskill1_flag << doll[pos].fire_rate;
            //qDebug() << " " << doll[pos].sign_z[3] << doll[pos].sign_z[4] << doll[pos].sign_z[5];
        }break;

        case 267: {   //267 MP41 烟雾弹
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.fire_rate /= 0.64;
                enemy.move /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.fire_rate *= 0.64;
                        enemy.move *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 268: {   //268 T-CMS 火力专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 269: {   //269 P30 睚眦必报
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){
                if(doll[pos].sign_z[0] == 1)for(int i=0 ; i<10 ; i++) doll[i].fire_rate *= 1.1;
                else for(int i=0 ; i<10 ; i++) doll[i].move *= 1.6;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 270: {   //270 四式 突击专注T
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[2]子弹计数

            if(doll[pos].definitely_hit == 1){ doll[pos].definitely_hit = 0;}

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.55;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].sign_z[2] ++;
                if(doll[pos].sign_z[2] % 3 == 0){ doll[pos].definitely_hit = 1;
                    double after_ceil, after_random, after_armor, after_crit, after_advanced;
                    after_ceil = ceil(doll[pos].attack);
                    after_random = (1.15 - ((myrand()/10000) * 3) / 10) * after_ceil;
                    after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));

                    if (doll[pos].definitely_crit == 1) after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);
                    else if (doll[pos].definitely_crit == 2) after_crit = after_armor;
                    else if (doll[pos].critical_per <= (myrand()/10000)) after_crit = after_armor;
                    else after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);
                    after_advanced = max(1, floor(after_crit*enemy.deep_damage));

                    damage[pos][frame] += after_advanced * enemy.target_number;}

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.55;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 271: {   //271 K3 蓄势待发
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.3;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[1] = 1;
                        doll[pos].attack *= 1.3;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    if(doll[pos].sign_z[1] == 1){
                        doll[pos].bullet_number -= 3; doll[pos].sign_z[1] = 0; }
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 272: {   //272 沙漠之鹰 威慑印记
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[0]对有标记有护盾的单位的攻击次数

            if(frame == 0 && doll[pos].sign_z[1] == 2){ doll[pos].fire_number *= 2; }

            //qDebug() << frame << doll[pos].attack << doll[pos].critical_per;
            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.4; enemy.deep_damage /= 1.1;
                for(int k=0 ; k<doll[pos].sign_z[0] ; k++){ doll[pos].injury_advanced /= 1.6; }
                doll[pos].sign_z[0] = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.4; enemy.deep_damage *= 1.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.4; enemy.deep_damage *= 1.1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(*pskill1_flag == 1 && doll[pos].sign_z[0] < 3){ doll[pos].sign_z[0] ++; doll[pos].injury_advanced *= 1.6; }

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 273: {   //273 SSG3000 沉默猎手
            *pfire_timing += 1; *pskill1_timing += 1;

            for(int k=1; k<5 ; k++){
                if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] ++;  }
                if(doll[pos].sign_z[k] > 3*FA){ doll[pos].sign_z[k] = 0; enemy.attack /= 0.9; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.armor > 0){ doll[pos].attack *= 1.05;}
                doll[pos].attack /= 2; doll[pos].definitely_hit = 0;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.8; doll[pos].definitely_hit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    *precharge = floor(1.5 * FA * max( 0 , 1 -  min( 0.3 , doll[pos].cd_inf )));
                    enemy.attack *= 0.9;
                    for(int k=1; k<5 ; k++){
                        if(doll[pos].sign_z[k] == 0){ doll[pos].sign_z[k] = 1;break; }}
                    }break;
                case 2: {
                    *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.8; doll[pos].definitely_hit = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
            }
        }break;

        case 274: {   //274 ACR 火力专注
            *pfire_timing += 1; *pskill1_timing += 1;
            // doll[pos].sign_z[0]自定减益 doll[pos].sign_z[1]自定减益数量 doll[pos].sign_z[2]effect数量 doll[pos].sign_z[3-8]自身攻击目标计时
            if(frame == 0){ doll[pos].sign[1] = enemy.dodge; doll[pos].sign[2] = enemy.armor;}

            for(int k=3; k<9 ; k++){
                if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] ++;  }
                if(doll[pos].sign_z[k] > 3*FA){ doll[pos].sign_z[k] = 0; enemy.attack /= 0.8; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_rate /= 1.5;
                for(int k=3; k<9 ; k++){ if(doll[pos].sign_z[k] >= 1){ doll[pos].sign_z[k] = 0; enemy.attack /= 0.8;}}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                //消除上一轮的增益
                if(doll[pos].sign_z[2] == 0){}
                else if(doll[pos].sign_z[2] == 1){doll[pos].attack /= 1.1;}
                else{doll[pos].attack /= (1.1 + (0.05*(doll[pos].sign_z[2]-1)));}

                //本轮射击的增益
                if(doll[pos].sign_z[0] == 2){doll[pos].sign_z[2] = doll[pos].sign_z[1];}
                else{ int effect = 0;
                    if( enemy.attack - enemy_reserve.attack <= -0.001){ effect ++; }
                    if( enemy.fire_rate - enemy_reserve.fire_rate <= -0.001){ effect ++; }
                    if( enemy.hit - enemy_reserve.hit <= -0.001){ effect ++; }
                    if( enemy.dodge - enemy_reserve.dodge <= -0.001){ effect ++; }
                    if( enemy.armor - enemy_reserve.armor <= -0.001){ effect ++; }
                    if( enemy.move - enemy_reserve.move <= -0.001){ effect ++; }
                    if( enemy.Dizzy > 0){ effect ++; }
                    if( enemy.Ignite > 0){ effect ++; }
                    doll[pos].sign_z[2] = effect; }

                if(doll[pos].sign_z[2] == 0){}
                else if(doll[pos].sign_z[2] == 1){doll[pos].attack *= 1.1;}
                else{doll[pos].attack *= (1.1 + (0.05*(doll[pos].sign_z[2]-1)));}

                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_rate *= 1.5;
                        enemy.attack *= 0.8;
                        int min_k=3,min_k_value=doll[pos].sign_z[3];
                        for(int k=3; k<9 ; k++){
                            if(doll[pos].sign_z[k] < min_k_value){ min_k=k; min_k_value=doll[pos].sign_z[k];}}
                        if(doll[pos].sign_z[min_k] != 0)enemy.attack /= 0.8;
                        doll[pos].sign_z[min_k] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_rate *= 1.5;
                        enemy.attack *= 0.8;
                        int min_k=3,min_k_value=doll[pos].sign_z[3];
                        for(int k=3; k<9 ; k++){
                            if(doll[pos].sign_z[k] < min_k_value){ min_k=k; min_k_value=doll[pos].sign_z[k];}}
                        if(doll[pos].sign_z[min_k] != 0)enemy.attack /= 0.8;
                        doll[pos].sign_z[min_k] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
                //qDebug() << frame << doll[pos].sign_z[2] << enemy.move;
            }
        }break;

        case 275: {   //275 M1895 CB 有备无患
            *pfire_timing += 1; *pskill1_timing += 1; doll[pos].sign_z[1] ++;
            // doll[pos].sign_z[0]备用弹链 doll[pos].sign_z[1]备用弹链获得计时 doll[pos].sign_z[2]备用弹链可启用
            // doll[pos].sign_z[3-12]命中减益

            if(frame == 0){ doll[pos].sign_z[0] = 30;}
            if(doll[pos].sign_z[1] > (3*FA) && (doll[pos].bullet_counting != 0 || doll[pos].sign_z[2] != 0)){
                doll[pos].sign_z[0] ++; doll[pos].sign_z[1] = 0; }

            if (*pfire_timing == *precharge || frame == 0) {
                if(doll[pos].sign_z[2] == 0){ doll[pos].bullet_counting ++; }
                if(doll[pos].sign_z[2] == 1){ doll[pos].sign_z[0] --; }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number + doll[pos].sign_z[2]){
                    doll[pos].bullet_counting = 0; doll[pos].sign_z[2] = 1; doll[pos].attack *= 1.5; }
                if(doll[pos].sign_z[0] <= 0 && doll[pos].bullet_counting == 0){
                    doll[pos].sign_z[2] = 0; doll[pos].attack /= 1.5;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else *precharge = 10;

                *pfire_timing = 0;
                //qDebug() << frame << doll[pos].bullet_counting << doll[pos].sign_z[0];
            }
        }break;

        case 276: {   //276 Kord 高压冲击
            *pfire_timing += 1; *pskill1_timing += 1;

            if( doll[pos].sign_z[0] == 1 ){ doll[pos].attack *= 0.7; doll[pos].armor_piercing *= 0.5; }
            if( doll[pos].sign_z[0] == 1 ){ doll[pos].attack *= 1.2; doll[pos].hit *= 1.2; }

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                if( doll[pos].sign_z[0] == 1 )bomb(pos,frame,1);

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                *pfire_timing = 0;
            }
        }break;

        case 277: {   //277 VP70 火力压制
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                enemy.attack /= 0.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        enemy.attack *= 0.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 278: {   //278 Six12 震荡打击
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 2; *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 2; *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2; }
        }break;

        case 279: {   //279 INSAS 强袭专注
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.35; doll[pos].hit /= 2;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.35; doll[pos].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.35; doll[pos].hit *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 281: {   //281 CAWS 次元仇焰
            *pfire_timing += 1; *pskill1_timing += 1;
            // 2蓄力计时 3无护盾sign

            if(doll[pos].sign_z[2] > 0){
                doll[pos].sign_z[2]++;
                if(doll[pos].sign_z[2] > 4.5*FA){ //超出时限
                    bomb(pos , frame , 5.5);
                    bomb(pos , frame , 5.5);
                    bomb(pos , frame , 5.5);
                    doll[pos].sign_z[2] = 0;}
                for(int i = 1 ; i <= 30 ; i++){ //假使护盾不再存在
                    if(doll[pos].shield_quantity[i] != 0){ doll[pos].sign_z[3] = 1; break; }
                    else doll[pos].sign_z[3] = 0;}
                if(doll[pos].sign_z[3] == 0){ //护盾消失时所攒层数
                    if(doll[pos].sign_z[2] >= 1.5*FA)bomb(pos , frame , 5.5);
                    if(doll[pos].sign_z[2] >= 3*FA)bomb(pos , frame , 5.5);
                    doll[pos].sign_z[3] = 0;
                    doll[pos].sign_z[2] = 0;}}

            if(doll[pos].sign_z[2] == 0){
                for(int i = 1 ; i <= 30 ; i++){
                    if(doll[pos].shield_quantity[i] != 0){ doll[pos].sign_z[2] = 1; break; }}}

            //qDebug() << frame << ":" << doll[pos].sign_z[2] << doll[pos].shield_quantity[1] << doll[pos].shield_quantity[2];

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos].shield_last[j] == 0){
                                doll[pos].shield_quantity[j] = 40;
                                doll[pos].shield_last[j] = 5*FA;
                                break;}}
                        doll[pos].sign_z[3] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                            if(doll[pos].shield_last[j] == 0){
                                doll[pos].shield_quantity[j] = 40;
                                doll[pos].shield_last[j] = 5*FA;
                                break;}}
                        doll[pos].sign_z[3] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 282: {   //282 DP-12 诡秘民谣
            *pfire_timing += 1; *pskill1_timing += 1;
            //2特殊弹量 3减伤持续

            if(doll[pos].sign_z[3] > 0){
                doll[pos].sign_z[3]++;
                if(doll[pos].sign_z[3] > 5*FA){
                    doll[pos].sign_z[3] = 0;
                    doll[pos].injury_reduction /= 0.75;
                    if(pos != 1 && pos != 4 && pos != 7){ doll[pos - 1].injury_reduction /= 0.75; }
                }}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[2] = 3;
                        if(doll[0].sign_z[1] == 0)doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].bullet_number += 3; doll[pos].sign_z[2] = 3;
                        if(doll[0].sign_z[1] == 0)doll[pos].fire_number *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(*pskill1_flag == 1){
                    doll[pos].sign_z[2]--;
                    if( doll[pos].sign_z[2] == 0 ){
                        if(doll[0].sign_z[1] == 0)doll[pos].fire_number /= 2;
                    }}

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;

                    for(int j = 1 ; j <= 30 ; j++){ //被动 为自身增加护盾
                        if(doll[pos].shield_last[j] == 0){
                            doll[pos].shield_quantity[j] = 40;
                            doll[pos].shield_last[j] = 5*FA;
                            break;}}

                    doll[pos].injury_reduction *= 0.75;
                    doll[pos].sign_z[3] = 1;
                    if(pos != 1 && pos != 4 && pos != 7){ doll[pos - 1].injury_reduction *= 0.75; }

                    if(*pskill1_flag == 1){doll[pos].bullet_number -= 3; *pskill1_flag = 2; } //减去增加的额外弹量
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 283: {   //283 解放者 制裁冲击
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].fire_number /= 4; doll[pos].attack /= 0.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number *= 4; doll[pos].attack *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number *= 4; doll[pos].attack *= 0.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;

        case 286: {   //SIG556-3
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)qDebug() << doll[pos].critical_per;
            //sign_z[1] 层数

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1; *precharge = 12;
                    }else *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    }break;
                case 1: { //技能开启期
                    doll[pos].sign_z[1] ++ ;
                    *precharge = 12;
                    if(doll[pos].sign_z[1] >= 13){
                        *precharge = floor(1500 / limit( pos , *pfire_rate )) + 60;
                        doll[pos].sign_z[1] = 0;}
                    }break;
                }
                *pfire_timing = 0;
                //qDebug() << frame << *pskill1_flag << doll[pos].sign_z[1];
            }
        }break;

        case 287: {   //SIG556
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)qDebug() << doll[pos].critical_per;
            //sign_z[1] 层数

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: { //技能开启期
                    doll[pos].sign_z[1] ++ ;
                    if(doll[pos].sign_z[1] >= 13){
                        doll[pos].attack /= 1.5; *pskill1_flag = 2; *pskill1_timing = 0;
                        doll[pos].sign_z[1] = 11;}
                    }break;
                case 2: { //技能关闭期
                    if (*pskill1_timing >= doll[pos].skill1_cd && doll[pos].sign_z[1] <= 2) {
                        doll[pos].attack *= 1.5; *pskill1_flag = 1; *pskill1_timing = 0;
                        doll[pos].sign_z[1] ++ ;}
                    else{ doll[pos].sign_z[1] --; }
                    }break;
                }
                *pfire_timing = 0;

                if(*pskill1_flag == 1)*precharge = floor(1500/120);
                else *precharge = floor(1500 / limit( pos , *pfire_rate ));
                //qDebug() << frame << *pskill1_flag << doll[pos].sign_z[1];
            }
        }break;

        case 288: {   //SIG556-2
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)qDebug() << doll[pos].critical_per;
            //sign_z[1] 层数

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5; doll[pos].sign_z[1] = 1;
                        *pskill1_timing = 0; *pskill1_flag = 1;*precharge = floor(1500/120);
                    }
                    else{*precharge = floor(1500 / limit( pos , *pfire_rate ));}}break;
                case 1: { //技能开启期
                    doll[pos].sign_z[1] ++ ;
                    *precharge = floor(1500/120);
                    if(*pskill1_timing >= doll[pos].skill1_cd){
                        doll[pos].attack /= 1.5; *pskill1_flag = 2; *pskill1_timing = 0;
                        doll[pos].sign_z[1] --;
                        *precharge = floor(1500 / limit( pos , *pfire_rate ));
                    }
                    else if(doll[pos].sign_z[1] >= 13){
                        *pskill1_flag = 1; *pskill1_timing = -floor(1500 / limit( pos , *pfire_rate )) - 2*30;
                        doll[pos].sign_z[1] = 0;
                        *precharge = floor(1500 / limit( pos , *pfire_rate )) + 2*30;}
                    }break;
                case 2: { //技能关闭期
                    if (*pskill1_timing >= doll[pos].skill1_cd) {
                        doll[pos].attack *= 1.5; *pskill1_flag = 1; *pskill1_timing = 0;
                        doll[pos].sign_z[1] ++ ; *precharge = floor(1500/120);}
                    else{ if(doll[pos].sign_z[1] > 0)doll[pos].sign_z[1] --;
                        *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                    }break;
                }
                *pfire_timing = 0;
                //qDebug() << frame << *pskill1_flag << doll[pos].sign_z[1];
            }
        }break;

        case 289: {   //R5
            *pfire_timing += 1; *pskill1_timing += 1;
            //if(frame == 0)qDebug() << doll[pos].critical_per;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.75;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.75;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 401: {   //401 诺爱尔
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        double after_ceil, after_random, after_armor, after_advanced;
                        after_ceil = ceil(doll[pos].attack * 1.2);
                        after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
                        after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));
                        after_advanced = max(1, floor(after_armor * enemy.deep_damage));
                        damage[pos][frame] += (8 * after_advanced * enemy.target_number);
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        double after_ceil, after_random, after_armor, after_advanced;
                        after_ceil = ceil(doll[pos].attack * 1.2);
                        after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
                        after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));
                        after_advanced = max(1, floor(after_armor * enemy.deep_damage));
                        damage[pos][frame] += (8 * after_advanced * enemy.target_number);
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 402: {   //402 艾尔菲尔特
            *pfire_timing += 1; *pskill1_timing += 1;

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].sign_z[2] = 0;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }

            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 0)
                { doll[pos].attack *= 20; doll[pos].sign_z[8] = doll[pos].fire_number; doll[pos].fire_number = 1;
                *pfire_timing = 0; doll[pos].sign_z[2] = 1; }
            if(*pskill1_flag == 1 && *pfire_timing == 1 && doll[pos].sign_z[2] == 1)
                { doll[pos].attack /= 20; doll[pos].fire_number = doll[pos].sign_z[8]; doll[pos].sign_z[8] = 0;
                *pfire_timing = 2; doll[pos].sign_z[2] = 2; *pskill1_flag = 2; }
        }break;

        case 403: {   //403 琪亚娜
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(enemy.elite_unit == 0) {enemy.Paralysis -= 1; enemy.deep_damage /= 1.4; }
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].fire_number = 4;
                        double after_random, after_advanced;
                        after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * ceil(doll[pos].attack) * doll[pos].crit_damage_rate;
                        after_advanced = max(1, floor(after_random * enemy.deep_damage));
                        damage[pos][frame] += (after_advanced * enemy.target_number);

                        if(enemy.elite_unit == 0) {enemy.Paralysis += 1; enemy.deep_damage *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].fire_number = 4;
                        double after_random, after_advanced;
                        after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * ceil(doll[pos].attack) * doll[pos].crit_damage_rate;
                        after_advanced = max(1, floor(after_random * enemy.deep_damage));
                        damage[pos][frame] += (after_advanced * enemy.target_number);

                        if(enemy.elite_unit == 0) {enemy.Paralysis += 1; enemy.deep_damage *= 1.4; }
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
            //qDebug() << frame << ":" << enemy.deep_damage << *pskill1_flag << *pskill1_timing;
        }break;

        case 404: {   //404 雷电芽衣
            *pfire_timing += 1; *pskill1_timing += 1;

            switch (*pskill1_flag) {
            case 1:{ //瞄准期间
                if (*pskill1_timing >= 1.5*FA ) { //造成伤害
                    snipe( pos , frame , 0 , 0 , 5);
                    if(enemy.elite_unit == 0)enemy.Paralysis += 1;
                    *pskill1_flag = 2;*pskill1_timing = 0;*pfire_timing = 0;
                    *precharge = 2*FA; }
            }break;
            default:
                break;
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {

                case 0: { //前置
                    if (*pskill1_timing >= doll[pos].skill1_before ){*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0; *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;
                case 2: {
                    if (*pskill1_timing >= 3*FA ) {if(enemy.elite_unit == 0)enemy.Paralysis -= 1; *pskill1_flag = 3;*pfire_timing = 0;}
                    else {*pfire_timing = 0; *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                case 3: { //冷却
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {*pskill1_flag = 1;*pskill1_timing = 0;}
                    else {*pfire_timing = 0; *precharge = floor(1500 / limit( pos , *pfire_rate ));}
                }break;

                default:
                    break;
                }
            }
            qDebug() << frame << ":" << enemy.Paralysis;
        }break;

        case 405: {   //405 布洛妮娅
            *pfire_timing += 1; *pskill1_timing += 1;
            if(doll[pos].sign_z[0] > 0){
                doll[pos].sign_z[0] ++;
                if(doll[pos].sign_z[0] >= (5*FA)){
                    doll[pos].sign_z[0] = 0;
                    enemy.Drawed -= 1;
                }
            }

            if(doll[pos].sign_z[0] % 10 == 1){
                bomb( pos , frame , 0.2 );
            }

            if(doll[pos].fire_number == 4)doll[pos].fire_number = 5;

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb( pos , frame , 0.2 );
                        doll[pos].sign_z[0] = 1; doll[pos].fire_number = 4; enemy.Drawed += 1;
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 2: break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 406: {   //406 德丽莎
            *pfire_timing += 1; *pskill1_timing += 1;

            if( doll[pos].sign_z[1] > 0 ){
                doll[pos].sign_z[1] ++;
                if(doll[pos].sign_z[1] > 2*FA){enemy.Durance -= 1; doll[pos].sign_z[1] = 0; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: {
                    if((myrand_skill()/10000) <= 0.3){
                        if(doll[pos].sign_z[1] == 0)enemy.Durance += 1;
                        doll[pos].sign_z[1] = 1;
                    }
                }break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 2;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
            //qDebug() << frame << enemy.Durance;
        }break;

        case 407: {   //407 无量塔姬子
            *pfire_timing += 1; *pskill1_timing += 1;

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.6; enemy.move /= 0.7; enemy.attack /= 0.7;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.6; enemy.move *= 0.7; enemy.attack *= 0.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.6; enemy.move *= 0.7; enemy.attack *= 0.7;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 408: {   //408 希儿
            *pfire_timing += 1; *pskill1_timing += 1;

            doll[pos].sign_z[3] ++;
            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                if(doll[pos].bullet_counting == 1)doll[pos].attack /= 3;

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    doll[pos].attack *= 3;
                    if(doll[pos].sign_z[3] < 3*FA){*precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                    else{*precharge = 1; doll[pos].sign_z[3] = 0;}}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }
                *pfire_timing = 0;
            }
            //qDebug() << frame << ":" << doll[pos].bullet_counting << *precharge << *pfire_timing;
        }break;

        case 409: {   //409 clear
            *pfire_timing += 1; *pskill1_timing += 1;
            //攻击数量记录 sign_z[7] 攻击次数记录 sign_z[8] 1-5pos 11-15time 9sign(havebuff

            for(int i = 11 ; i <= 15 ; i++){
                if(doll[pos].sign_z[i] >= 1){
                    doll[pos].sign_z[i] ++;
                    if(doll[pos].sign_z[i] > 3*FA){
                        int doll_id_tem = doll[pos].sign_z[i - 10];
                        if(doll[pos].sign_z[0] == 0){doll[doll_id_tem].hit /= 1.3; doll[doll_id_tem].attack /= 1.3;}
                        if(doll[pos].sign_z[0] == 1){doll[doll_id_tem].hit /= 1.4; doll[doll_id_tem].attack /= 1.4;}
                        doll[pos].sign_z[i] = 0;
                        doll[pos].sign_z[i - 10] = 0;
                    }}}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i = 1; i <= 15 ; i++){doll[pos].sign_z[i] = 0;}
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i = 1; i <= 15 ; i++){doll[pos].sign_z[i] = 0;}
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }

                if(*pskill1_flag == 2){
                    if(doll[pos].sign_z[8] == 0){doll[pos].fire_number = 0;}
                    doll[pos].sign_z[8] ++;
                }

                if(doll[pos].sign_z[8] >= 1 && doll[pos].sign_z[8] <= 5){
                    int damage_rank[10]={0};
                    for(int i = 1; i <= 9 ; i++){for(int t = 0 ; t <= frame ; t++){damage_rank[i] += damage[i][t]; }}

                    int damage_max = damage_rank[0] , rank_doll = 0;
                    for(int i = 1; i <= 9 ; i++){
                        for(int j = 1; j <= 5 ; j++){if(doll[pos].sign_z[j] == i){doll[pos].sign_z[9] = 1; break;}} //发现已有buff
                        if(doll[pos].sign_z[9] == 1){doll[pos].sign_z[9] = 0; continue;} //该人形已有buff，退出
                        if(damage_rank[i] > damage_max){damage_max = damage_rank[i]; rank_doll = i;}} //没有buff比较大小
                    //qDebug() << frame << ":" << damage_rank[1] << damage_rank[2] << damage_rank[3] << rank_doll;

                    if(doll[pos].sign_z[0] == 0){doll[rank_doll].hit *= 1.3; doll[rank_doll].attack *= 1.3;}
                    if(doll[pos].sign_z[0] == 1){doll[rank_doll].hit *= 1.4; doll[rank_doll].attack *= 1.4;}
                    doll[pos].sign_z[doll[pos].sign_z[8]] = rank_doll;
                    doll[pos].sign_z[doll[pos].sign_z[8] + 10] = 1;}
                else if(*pskill1_flag == 2){doll[pos].fire_number = 5 ;}

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
                //qDebug() << frame << ":" << doll[pos].fire_number << doll[pos].sign_z[8] ;
                //qDebug() << frame << ":" << doll[1].attack << doll[2].attack << doll[3].attack ;
            }
        }break;

        case 410: {   //410 fail
            *pfire_timing += 1; *pskill1_timing += 1;
            //攻击次数记录 sign_z[8] 1-2记录  3signdebuff

            for(int i = 1 ; i <= 2 ; i++){
                if(doll[pos].sign_z[i] >= 1){
                    doll[pos].sign_z[i] ++;
                    if(doll[pos].sign_z[i] > 3*FA){
                        if(doll[pos].sign_z[0] == 0){enemy.fire_rate /= 0.88; enemy.hit /= 0.88;}
                        if(doll[pos].sign_z[0] == 1){enemy.fire_rate /= 0.85; enemy.hit /= 0.85;}
                        doll[pos].sign_z[i] = 0;
                    }}}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i = 1; i <= 2 ; i++){doll[pos].sign_z[i] = 0;}
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i = 1; i <= 2 ; i++){doll[pos].sign_z[i] = 0;}
                        *pskill1_timing = 0; *pskill1_flag = 2;
                    }}break;
                }

                if(*pskill1_flag == 2){
                    if(doll[pos].sign_z[8] == 0){doll[pos].fire_number = 0;}
                    doll[pos].sign_z[8] ++;
                }

                if(doll[pos].sign_z[8] >= 1 && doll[pos].sign_z[8] <= 5){
                    for(int i = 1; i <= 2 ; i++){
                        if(doll[pos].sign_z[i] == 0){
                            if(doll[pos].sign_z[0] == 0){enemy.fire_rate *= 0.88; enemy.hit *= 0.88;}
                            if(doll[pos].sign_z[0] == 1){enemy.fire_rate *= 0.85; enemy.hit *= 0.85;}
                            doll[pos].sign_z[i] = 1; doll[pos].sign_z[3] = 1; break;
                        }}
                    if(doll[pos].sign_z[3] == 0 && (doll[pos].sign_z[1] < doll[pos].sign_z[2])){doll[pos].sign_z[1] = 1; }
                    else if(doll[pos].sign_z[3] == 0){doll[pos].sign_z[2] = 1;  }
                }
                else if(*pskill1_flag == 2){doll[pos].fire_number = 5 ;}

                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
                //qDebug() << frame << ":" << doll[pos].fire_number << doll[pos].sign_z[8] ;
                qDebug() << frame << ":" << enemy.hit ;
            }
        }break;

        case 417: {   //417 Jill
            *pfire_timing += 1; *pskill1_timing += 1;
            doll[pos].fire_number = 0;

            if(*pskill1_flag == 1 && *pskill1_timing >= 5*FA){
                if(doll[pos].sign_z[0] == 6){ for(int i = 1 ; i <= 9 ; i++){ doll[i].attack /= 1.35; doll[i].attack *= 0.85; doll[i].hit *= 0.85;}}
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                if(doll[pos].sign_z[0] == 1){
                    for(int i = 1 ; i <= 9 ; i++){
                        if(doll[i].id != 0 && doll[i].type == 6){doll[i].armor /= 1.2; doll[i].attack /= 1.3; doll[i].hit /= 1.3;}}}
                else if(doll[pos].sign_z[0] == 2){
                    for(int i = 1 ; i <= 9 ; i++){
                        if(doll[i].id != 0 && doll[i].type == 5){doll[i].attack /= 1.25; doll[i].hit /= 1.25; }}}
                else if(doll[pos].sign_z[0] == 3){
                    for(int i = 3 ; i <= 9 ; i += 3){
                        if(doll[i].id != 0){doll[pos].sign_z[3] = 1;break;}
                        else doll[pos].sign_z[3] = 0;}
                    if(doll[pos].sign_z[3] == 1){for(int i=3;i<=9;i+=3){doll[i].dodge /= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack /= 1.2;}for(int i=2;i<=8;i+=3){doll[i].attack /= 1.2;}}
                    else if(doll[pos].sign_z[3] == 0){for(int i=2;i<=8;i+=3){doll[i].dodge /= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack /= 1.2;}}}
                else if(doll[pos].sign_z[0] == 4){
                    for(int i = 1 ; i <= 9 ; i++){
                        if(doll[i].id != 0){doll[i].fire_rate /= 1.22;}}}
                else if(doll[pos].sign_z[0] == 5){
                    for(int i = 1 ; i <= 9 ; i++){
                        if(doll[i].id != 0 && (doll[i].type == 3 || doll[i].type == 4)){
                            doll[i].critical_per /= 1.25;
                            if(doll[i].critical_per > 1){doll[i].crit_damage_rate /= doll[pos].sign_z[5]; doll[pos].sign_z[5] = 1; }}}}
                else if(doll[pos].sign_z[0] == 6){
                    for(int i = 1 ; i <= 9 ; i++){ doll[i].attack /= 0.85; doll[i].hit /= 0.85; }}
                else if(doll[pos].sign_z[0] == 7){
                    for(int i = 1 ; i <= 9 ; i++){ doll[i].attack /= 1.18; }}
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        if(doll[pos].sign_z[0] == 1){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && doll[i].type == 6){doll[i].armor *= 1.2; doll[i].attack *= 1.3; doll[i].hit *= 1.3;}}}
                        else if(doll[pos].sign_z[0] == 2){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && doll[i].type == 5){doll[i].attack *= 1.25; doll[i].hit *= 1.25; }}}
                        else if(doll[pos].sign_z[0] == 3){
                            for(int i = 3 ; i <= 9 ; i += 3){
                                if(doll[i].id != 0){doll[pos].sign_z[3] = 1;break;}
                                else doll[pos].sign_z[3] = 0;}
                            if(doll[pos].sign_z[3] == 1){for(int i=3;i<=9;i+=3){doll[i].dodge *= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack *= 1.2;}for(int i=2;i<=8;i+=3){doll[i].attack *= 1.2;}}
                            else if(doll[pos].sign_z[3] == 0){for(int i=2;i<=8;i+=3){doll[i].dodge *= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack *= 1.2;}}}
                        else if(doll[pos].sign_z[0] == 4){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0){doll[i].fire_rate *= 1.22;}}}
                        else if(doll[pos].sign_z[0] == 5){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && (doll[i].type == 3 || doll[i].type == 4)){
                                    doll[i].critical_per *= 1.25;
                                    if(doll[i].critical_per > 1){doll[pos].sign_z[5] = (1 + 0.6*(doll[i].critical_per - 1)); doll[i].crit_damage_rate *= doll[pos].sign_z[5]; }}}}
                        else if(doll[pos].sign_z[0] == 6){
                            for(int i = 1 ; i <= 9 ; i++){ doll[i].attack *= 1.35; }}
                        else if(doll[pos].sign_z[0] == 7){
                            for(int i = 1 ; i <= 9 ; i++){ doll[i].attack *= 1.18; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= ceil( doll[pos].skill1_cd *0.7)) {
                        if(doll[pos].sign_z[0] == 1){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && doll[i].type == 6){doll[i].armor *= 1.2; doll[i].attack *= 1.3; doll[i].hit *= 1.3;}}}
                        else if(doll[pos].sign_z[0] == 2){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && doll[i].type == 5){doll[i].attack *= 1.25; doll[i].hit *= 1.25; }}}
                        else if(doll[pos].sign_z[0] == 3){
                            for(int i = 3 ; i <= 9 ; i += 3){
                                if(doll[i].id != 0){doll[pos].sign_z[3] = 1;break;}
                                else doll[pos].sign_z[3] = 0;}
                            if(doll[pos].sign_z[3] == 1){for(int i=3;i<=9;i+=3){doll[i].dodge *= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack *= 1.2;}for(int i=2;i<=8;i+=3){doll[i].attack *= 1.2;}}
                            else if(doll[pos].sign_z[3] == 0){for(int i=2;i<=8;i+=3){doll[i].dodge *= 1.6;}for(int i=1;i<=7;i+=3){doll[i].attack *= 1.2;}}}
                        else if(doll[pos].sign_z[0] == 4){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0){doll[i].fire_rate *= 1.22;}}}
                        else if(doll[pos].sign_z[0] == 5){
                            for(int i = 1 ; i <= 9 ; i++){
                                if(doll[i].id != 0 && (doll[i].type == 3 || doll[i].type == 4)){
                                    doll[i].critical_per *= 1.25;
                                    if(doll[i].critical_per > 1){doll[i].crit_damage_rate *= (1 + 0.6*(doll[i].critical_per - 1)); }}}}
                        else if(doll[pos].sign_z[0] == 6){
                            for(int i = 1 ; i <= 9 ; i++){ doll[i].attack *= 1.35; }}
                        else if(doll[pos].sign_z[0] == 7){
                            for(int i = 1 ; i <= 9 ; i++){ doll[i].attack *= 1.18; }}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 418: {   //418 Sei
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0){
                for(int i = 1 ; i <= 9 ; i += 1){
                    if(doll[i].id == 20){
                        doll[pos].skill1_cd = ceil(doll[pos].skill1_cd * 0.9);
                    }
                }
            }

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        for(int i = 1 ; i <= 9 ; i += 1){
                            if(doll[i].id != 0 && (doll[i].type == 1 || doll[i].type == 2 || doll[i].type == 6)){ //该位置上存在手枪 霰弹枪 冲锋枪人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 32;
                                        doll[i].shield_last[j] = 5*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        for(int i = 1 ; i <= 9 ; i += 1){
                            if(doll[i].id != 0 && (doll[i].type == 1 || doll[i].type == 2 || doll[i].type == 6)){ //该位置上存在手枪 霰弹枪 冲锋枪人形
                                for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                                    if(doll[i].shield_last[j] == 0){
                                        doll[i].shield_quantity[j] = 32;
                                        doll[i].shield_last[j] = 5*FA;
                                        break;}}}}
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
            *pfire_timing = 0;
            *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 419: {   //419 Dorothy
            *pfire_timing += 1; *pskill1_timing += 1;

            if(frame == 0 && doll[pos].sign_z[0] == 1){
                doll[pos].attack *= 2;
                if( pos-6 >=1 ){doll[pos-6].hit *= 0.6; doll[pos-6].dodge *= 1.8;}
                if( pos-3 >=1 ){doll[pos-3].hit *= 0.6; doll[pos-3].dodge *= 1.8;}
                if( pos+3 <=9 ){doll[pos+3].hit *= 0.6; doll[pos+3].dodge *= 1.8;}
                if( pos+6 <=9 ){doll[pos+6].hit *= 0.6; doll[pos+6].dodge *= 1.8;}
            }

            if(frame == 0 && doll[pos].sign_z[0] == 2){
                doll[pos].dodge *= 2;
                if( pos-6 >=1 ){doll[pos-6].dodge *= 0.6; doll[pos-6].hit *= 1.8;}
                if( pos-3 >=1 ){doll[pos-3].dodge *= 0.6; doll[pos-3].hit *= 1.8;}
                if( pos+3 <=9 ){doll[pos+3].dodge *= 0.6; doll[pos+3].hit *= 1.8;}
                if( pos+6 <=9 ){doll[pos+6].dodge *= 0.6; doll[pos+6].hit *= 1.8;}
            }

            for(int i = 1; i <= 9 ; i++){
                if(doll[i].id == 417 && doll[i].skill1_flag == 1 && doll[i].sign_z[0] == 3 && doll[pos].sign_z[2] == 0){
                    if(doll[pos].sign_z[0] == 1){
                        doll[pos].attack *= 2;
                        if( pos-6 >=1 ){doll[pos-6].hit *= (0.8/0.6);}
                        if( pos-3 >=1 ){doll[pos-3].hit *= (0.8/0.6);}
                        if( pos+3 <=9 ){doll[pos+3].hit *= (0.8/0.6);}
                        if( pos+6 <=9 ){doll[pos+6].hit *= (0.8/0.6);}
                    }

                    if(doll[pos].sign_z[0] == 2){
                        doll[pos].dodge *= 2;
                        if( pos-6 >=1 ){doll[pos-6].dodge *= (0.8/0.6);}
                        if( pos-3 >=1 ){doll[pos-3].dodge *= (0.8/0.6);}
                        if( pos+3 <=9 ){doll[pos+3].dodge *= (0.8/0.6);}
                        if( pos+6 <=9 ){doll[pos+6].dodge *= (0.8/0.6);}
                    }

                    doll[pos].sign_z[2] = 1;
                }

                if(doll[i].id == 417 && doll[i].skill1_flag == 2 && doll[i].sign_z[0] == 3 && doll[pos].sign_z[2] == 1){
                    if(doll[pos].sign_z[0] == 1){
                        doll[pos].attack *= 2;
                        if( pos-6 >=1 ){doll[pos-6].hit *= (0.6/0.8);}
                        if( pos-3 >=1 ){doll[pos-3].hit *= (0.6/0.8);}
                        if( pos+3 <=9 ){doll[pos+3].hit *= (0.6/0.8);}
                        if( pos+6 <=9 ){doll[pos+6].hit *= (0.6/0.8);}
                    }

                    if(doll[pos].sign_z[0] == 2){
                        doll[pos].dodge *= 2;
                        if( pos-6 >=1 ){doll[pos-6].dodge *= (0.6/0.8);}
                        if( pos-3 >=1 ){doll[pos-3].dodge *= (0.6/0.8);}
                        if( pos+3 <=9 ){doll[pos+3].dodge *= (0.6/0.8);}
                        if( pos+6 <=9 ){doll[pos+6].dodge *= (0.6/0.8);}
                    }

                    doll[pos].sign_z[2] = 0;
                }
            }

            if (*pfire_timing == *precharge || frame == 0) {
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 420: {   //420 Stella
            *pfire_timing += 1; *pskill1_timing += 1;
            //sign_z[2]攻击计数 3暴击轮标志 4jill技能效果 5jill技能标志

            if(frame == 0){
                doll[pos].attack *= 0.5;
                doll[pos].fire_number *= 2;
            }

            for(int i = 1; i <= 9 ; i++){
                if(doll[i].id == 417 && doll[i].skill1_flag == 1 && doll[i].sign_z[0] == 5 && doll[pos].sign_z[5] == 0){
                    doll[pos].sign_z[4] = 10;
                    doll[pos].sign_z[5] = 1;
                }

                if(doll[i].id == 417 && doll[i].skill1_flag == 2 && doll[i].sign_z[0] == 5 && doll[pos].sign_z[5] == 1){
                    doll[pos].sign_z[4] = 16;
                    doll[pos].sign_z[5] = 0;
                }
            }

            if(doll[pos].sign_z[3] == 1){
                doll[pos].crit_damage_rate /= 1.5;
                doll[pos].sign_z[3] = 0;
            }

            if(doll[pos].sign_z[2] >= doll[pos].sign_z[4]){
                doll[pos].crit_damage_rate *= 1.5;
                doll[pos].sign_z[2] = 0;
                doll[pos].sign_z[3] = 1;
            }

            for(int i=1;i<=9;i++){
                if(doll[i].id == 418 && doll[i].fire_timing == 0){doll[pos].sign_z[2] ++; }
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.5;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                switch (*pskill1_flag) { //前置0 技能期1 冷却2
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.5;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }
                doll[pos].sign_z[2] += 2;
                *pfire_timing = 0;
                *precharge = floor(1500 / limit( pos , *pfire_rate ));
            }
        }break;

        case 421: {   //421 Alma
            *pfire_timing += 1; *pskill1_timing += 1;

            for(int i=1;i<=9;i++){
                if(frame == 0 && doll[i].id == 417 && doll[i].sign_z[0] == 2)doll[pos].skill1_last += 1;
            }

            if(*pskill1_flag == 1 && *pskill1_timing >= doll[pos].skill1_last){
                doll[pos].attack /= 1.65;
                *pskill1_flag = 2;}

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;
                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        doll[pos].attack *= 1.65;
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor((4 + 200 / limit( pos , *pfire_rate )) * 30);}
                else{ *precharge = 10; }

                if(*pfire_timing == 1 && doll[pos].sign_z[5] == 1){
                    doll[pos].attack /= 0.4;
                    doll[pos].fire_number /= 2;
                    *pfire_timing = 2;
                    doll[pos].sign_z[5] = 0;
                }
                if(*pfire_timing == 1 && *pskill1_flag == 1){
                    doll[pos].attack *= 0.4;
                    doll[pos].fire_number *= 2;
                    *pfire_timing = 0;
                    doll[pos].sign_z[5] = 1;
                }

                *pfire_timing = 0;
            }
        }break;

        case 422: {   //422 Dana
            *pfire_timing += 1; *pskill1_timing += 1;
            if(frame == 0 && doll[pos].sign_z[1] == 0){ doll[pos].attack /= 0.6; doll[pos].fire_number = 5;}
            if(frame == 0 && doll[pos].sign_z[1] == 1){ doll[pos].attack *= 1.8; doll[pos].fire_number = 5;}

            for(int i = 1; i <= 9 ; i++){
                if(doll[i].id == 417 && doll[i].skill1_flag == 1 && doll[i].sign_z[0] == 1 && doll[pos].sign_z[5] == 0){
                    for(int j = 1 ; j <= 30 ; j++){ //遍历找无护盾的格子
                        if(doll[pos].shield_last[j] == 0){
                            doll[pos].shield_quantity[j] = doll[pos].armor;
                            doll[pos].shield_last[j] = 8*FA;
                            break;}}
                    doll[pos].sign_z[5] = 1;
                }
            }

            if (*pfire_timing == *precharge || frame == 0) {
                doll[pos].bullet_counting++;

                switch (*pskill1_flag) {
                case 0: {
                    if (*pskill1_timing >= doll[pos].skill1_before ) {
                        bomb(pos , frame , 0.6+(0.01 * doll[pos].armor));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                case 1: break;
                case 2: {
                    if (*pskill1_timing >= doll[pos].skill1_cd ) {
                        bomb(pos , frame , 0.6+(0.01 * doll[pos].armor));
                        *pskill1_timing = 0; *pskill1_flag = 1;
                    }}break;
                }

                if(doll[pos].bullet_counting >= doll[pos].bullet_number){
                    doll[pos].bullet_counting = 0;
                    *precharge = floor( 65 + 15 * doll[pos].bullet_number );}
                else{ *precharge = floor(1500 / limit( pos , *pfire_rate )); }

                *pfire_timing = 0;
            }
        }break;


        default:
            printf("Unknown doll.");
        }
    }
    }
}

double limit(int pos , double fire_rate_1)
{
    double fire_rate_2 = floor(fire_rate_1);

    switch (doll[pos].type) {

    case 1:
        return (max(15, min(120, fire_rate_2)));
    case 2:
        return (max(15, min(120, fire_rate_2)));
    case 3:
        return (max(15, min(120, fire_rate_2)));
    case 4:
        return (max(15, min(120, fire_rate_2)));
    case 5:
        return (max(1, min(1000, fire_rate_2)));
    case 6:
        return (max(15, min(60, fire_rate_2)));
    default:
        return 0 ;
    }
}

void bomb( int pos , int frame , double power ){
    double after_ceil, after_random, after_advanced;

    mysrand_skill(time (nullptr));
    after_ceil = ceil(doll[pos].attack) * power;
    after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
    after_advanced = max(1, floor(after_random * enemy.deep_damage));

    damage[pos][frame] += (after_advanced * enemy.target_number);
}

void snipe( int pos , int frame , int max_piles , double min_power , double max_power)
{
    double power,after_ceil, after_random, after_advanced;

    if( min_power <= 0) { power = max_power; }
    else { power = 1 + (max_power - min_power) * (doll[pos].sign_z[0] - 1) / (max_piles - 1); }

    mysrand_skill(time (nullptr));
    after_ceil = ceil(doll[pos].attack) * power * 5;
    after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
    after_advanced = max(1, floor(after_random * enemy.deep_damage));

    damage[pos][frame] += after_advanced;
}

void direct_damage( int pos , int frame ) //直接伤害,不计算命中,不计算暴击
{
    double after_ceil, after_random, after_armor, after_fixed, after_advanced;

    mysrand_skill(time (nullptr));
    after_ceil = ceil(doll[pos].attack);
    after_random = (1.15 - ((myrand_skill()/10000) * 3) / 10) * after_ceil;
    after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));
    after_fixed = max(0, ceil(after_armor + doll[pos].fixed_injury));
    after_advanced = max(1, floor(after_fixed*enemy.deep_damage));
    damage[pos][frame] += after_advanced; //计算得出的伤害放入数组，并累加
}

void mysrand_skill (int seed){
    rand_seed_skill = seed;
}

double myrand_skill (){
    do{
        rand_seed_skill = (rand_seed_skill * 16807L) % ((1 << 31) - 1);
    }while(rand_seed_skill > 0);
    return -(rand_seed_skill%10000);
}

void shield_down(int pos , int frame)
{
    for(int i=1 ; i<=30 ; i++){
        if(doll[pos].shield_quantity[i] > 0){
            doll[pos].shield_last[i] -= 1;
            if(doll[pos].shield_last[i] <= 0){
                doll[pos].shield_quantity[i] = 0;
            }
        }
    }
    //qDebug() << frame << ":" << doll[3].shield_quantity[1] << doll[3].shield_last[1] << doll[3].shield_quantity[2] << doll[3].shield_last[2];
    //qDebug() << frame << ":" << doll[6].shield_quantity[1] << doll[6].shield_last[1];
}






