#include <stdio.h>
#include <math.h>
#include "calculation.h"
#include "ui_calculation.h"

#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QtGui>

struct fairy_info fairy_origin[60]={
    {},
    //id  name   type crit_d attack  hit   dodge  armor
    { 1 , "勇士" , 0 , 0.00 , 0.25 , 0.80 , 0.40 , 0.10 },
    { 2 , "暴怒" , 0 , 0.40 , 0.15 , 0.00 , 0.40 , 0.10 },
    { 3 , "盾甲" , 0 , 0.22 , 0.22 , 0.00 , 0.00 , 0.25 },
    { 4 , "护盾" , 0 , 0.00 , 0.20 , 0.60 , 0.80 , 0.00 },
    { 5 , "防御" , 1 , 0.00 , 0.22 , 0.00 , 0.80 , 0.20 },
    { 6 , "嘲讽" , 0 , 0.25 , 0.18 , 0.58 , 0.28 , 0.08 },
    { 7 , "狙击" , 0 , 0.36 , 0.00 , 0.88 , 0.28 , 0.15 },
    { 8 , "炮击" , 0 , 0.00 , 0.55 , 0.00 , 0.56 , 0.06 },
    { 9 , "空袭" , 0 , 0.00 , 0.30 , 0.50 , 0.40 , 0.10 },
    { 10 , "增援" , 1 , 0.15 , 0.12 , 0.00 , 0.88 , 0.12 },
    { 11 , "空降" , 1 , 0.40 , 0.36 , 0.00 , 0.32 , 0.08 },
    { 12 , "布雷" , 1 , 0.00 , 0.25 , 0.44 , 0.85 , 0.00 },
    { 13 , "火箭" , 1 , 0.35 , 0.00 , 0.44 , 0.00 , 0.22 },
    { 14 , "工事" , 1 , 0.20 , 0.15 , 0.50 , 0.40 , 0.10 },
    { 15 , "指挥" , 0 , 0.36 , 0.36 , 0.00 , 0.32 , 0.08 },
    { 16 , "搜救" , 0 , 0.00 , 0.32 , 0.80 , 0.64 , 0.00 },
    { 17 , "照明" , 1 , 0.38 , 0.00 , 0.90 , 0.32 , 0.08 },
    { 18 , "黄金" , 0 , 0.25 , 0.20 , 0.62 , 0.50 , 0.12 },
    { 19 , "炊事" , 0 , 0.10 , 0.10 , 0.20 , 0.80 , 0.20 },
    { 20 , "花火" , 0 , 0.00 , 0.32 , 0.75 , 0.32 , 0.08 },
    { 21 , "年兽" , 0 , 0.25 , 0.25 , 0.00 , 0.20 , 0.20 },
    { 22 , "海滩" , 0 , 0.32 , 0.32 , 0.00 , 0.40 , 0.00 },
    { 23 , "连击" , 1 , 0.30 , 0.15 , 0.85 , 0.00 , 0.00 },
    { 24 , "立盾" , 0 , 0.00 , 0.00 , 0.72 , 0.32 , 0.22 },
    { 25 , "双生" , 0 , 0.18 , 0.00 , 0.60 , 0.48 , 0.12 },
    {},{},{},{},{},    //
    {},{},{},{},{},{},{},{},{},{}, //31-40
    {},{},{},{},{},{},{},{},{},{}, //41-50
    { 51 , "八重樱"  , 0 , 0.32 , 0.26 , 0.00 , 0.24 , 0.06 },
    { 52 , "辉夜姬"  , 1 , 0.32 , 0.00 , 0.70 , 0.24 , 0.15 },
    { 53 , "柯萝伊"  , 0 , 0.00 , 0.18 , 0.55 , 0.64 , 0.06 },
    { 54 , "希伊"   , 1 , 0.30 , 0.00 , 0.00 , 0.70 , 0.18 },
    { 55 , "世拉&"  , 0 , 0.20 , 0.15 , 0.40 , 0.50 , 0.00 },
    { 56 , "普蕾娅&" , 0 , 0.22 , 0.22 , 0.50 , 0.10 , 0.10 },
    { 57 , "安娜"    , 0 , 0.00 , 0.25 , 0.30 , 0.65 , 0.08 },

};

void fairy_gift( int frame , int id )
{
    for(int pos=1 ; pos<10 ; pos++)
    {
        if(frame == 0){
            switch (id) {

            case 0:
                break;

            case 1:
                doll[pos].attack *= 1.15; break;

            case 2:
                doll[pos].attack *= 1.10; break;

            default:
                break;
            }
        }
        if(frame == 8*FA || frame == 16*FA ){
            switch (id) {
            case 2:
                doll[pos].attack *= 1.10; break;

            default:
                break;
            }
        }
    }
}

void fairy_skill( int id )
{
    if(condition.fairy_skill == 1){
        switch ( id ) {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }
    }
}

void buff_done()
{
    for( int pos=1 ; pos<10 ; pos++){
        if(doll[pos].id == 0)continue;
        doll[pos].attack = ceil( doll[pos].attack * (1 + condition.attack_buff) ) ;
        doll[pos].fire_rate = ceil( doll[pos].fire_rate * (1 + condition.fire_rate_buff) ) ;
        doll[pos].hit = ceil( doll[pos].hit * (1 + condition.hit_buff) ) ;
        doll[pos].critical_per = ceil( doll[pos].critical_per * (1 + condition.critical_per_buff) * 100 ) /100 ;
        doll[pos].crit_damage_rate = ceil( doll[pos].crit_damage_rate * (1 + condition.crit_damage_rate_buff) * 100 ) /100 ;
        doll[pos].dodge = ceil( doll[pos].dodge * (1 + condition.dodge_buff) ) ;
        doll[pos].armor = ceil( doll[pos].armor * (1 + condition.armor_buff) ) ;
    }
}




