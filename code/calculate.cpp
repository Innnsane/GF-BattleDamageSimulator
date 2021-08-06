#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include"calculation.h"

#include <QWidget>
#include <QTime>
#include <QDebug>

double max(double a, double b);
double min(double a, double b);
int rand_seed;
void mysrand (int);
double myrand ();
void prepare();
int Fw=416;
int of;
int out;

//利用动态内存分配，用二维指针定义二维数组，建立一个damage[pos][帧数]用来存放计算数据，记得free内存
double **damage;
double **damage_together;
struct doll_info doll_reserve_2[10];
struct enemy_info enemy_reserve;

void calculation::calculate() {
    damage = (double **)malloc(sizeof(double*) * 10);  //damage数组负责记录逐帧伤害
    for (int i = 0; i < 10; i++) {
        damage[i] = (double *)malloc(sizeof(double) * (condition.frame + 1) );
        for(int j=0; j <= condition.frame ; j++) { damage[i][j]=0; }
    }

    damage_together = (double **)malloc(sizeof(double*) * 10);  //damage_together数组负责记录逐加伤害
    for (int i = 0; i < 10; i++) {
        damage_together[i] = (double *)malloc(sizeof(double) * (condition.frame + 1) );
        for(int j=0; j <= condition.frame ; j++) { damage_together[i][j]=0; }
    }

    mysrand (time (nullptr));

    for(int pos=1 ; pos<10 ; pos++){ doll_reserve[pos] = doll[pos]; }//保存第一行设定的原始数据
    enemy_reserve = enemy; //保存第二行设定的原始数据

    buff_done();//自设定光环计算 并妖精光环
    influence_calculate(); //影响格计算

    for(int pos=1 ; pos<10 ; pos++){ doll_reserve_2[pos] = doll[pos];} //重置

    for(int j=0 ; j<Fw ; j++){  //计算次数 计算完成后取平均数

        for(int pos=1 ; pos<10 ; pos++){ doll[pos] = doll_reserve_2[pos]; } //重置
        enemy = enemy_reserve;

    for (int frame = 0; frame <= condition.frame ; frame++) {		//如果该帧射出子弹，先判定技能生效或失效，再判定伤害
        if((frame == 0) || (frame == 8*FA ) || (frame == 16*FA ))fairy_gift( frame , fairy_gift_id );

        fairy_skill( fairy_id );//妖精技能计算
        skill_select(frame);//先从1号位开始进行技能生效判定，相同帧的技能释放顺序暂不考虑
        int pos;
        for ( pos = 1; pos < 10; pos++) { //遍历每个pos的人形
            if ( doll[pos].id == 0){continue;} //如果是空人形则跳过
            if ( doll[pos].fire_timing == 0 ) {
            for(int i=0 ; i < doll[pos].fire_number ; i++){	//单个人形五扩编伤害计算五次

                double hit_tem,hit = floor(doll[pos].hit), nhit = floor(doll[pos].hit*(1 - 0.9*(1 - doll[pos].night_view_per)));//命中选择
                double after_ceil, after_random, after_armor, after_crit, after_fixed, after_field, after_advanced;

                if(doll[pos].definitely_hit == 1) hit_tem=1;
                else if( condition.day_or_night == 0) hit_tem=(hit / (hit + enemy.dodge));
                else hit_tem=(nhit / (nhit + enemy.dodge)) ;
                if(hit_tem <= (myrand()/10000)) {continue;} //未命中

                after_ceil = ceil(doll[pos].attack);
                after_random = (1.15 - ((myrand()/10000) * 3) / 10) * after_ceil;
                after_armor = max(1, after_random + min(2, (floor(doll[pos].armor_piercing) - enemy.armor)));

                out++;
                if (doll[pos].definitely_crit == 1) after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);
                else if (doll[pos].definitely_crit == 2) after_crit = after_armor;
                else if (doll[pos].critical_per <= (myrand()/10000)) {after_crit = after_armor;}
                else after_crit = after_armor * (floor(doll[pos].crit_damage_rate * 100) / 100);

                after_fixed = max(0, ceil(after_crit + doll[pos].fixed_injury));
                if(enemy.max_field <= 0)after_field = after_fixed;
                else after_field = max(0, ceil(after_fixed*(1 - enemy.current_field/enemy.max_field)));
                after_advanced = max(1, floor(after_field * enemy.deep_damage * doll[pos].injury_advanced));
                //after_shield = max(0, after_advanced - enemy.shield);
                //enemy.shield = max(0, (int)enemy.shield - after_advanced);
                //damage[pos][frame]=after_shield;
                damage[pos][frame] += after_advanced; //计算得出的伤害放入数组，并累加
            }
        }
        }
    }
    }

    for(int pos=1 ; pos<10 ; pos++){   //取用之前保存的原始设定数据
        doll[pos] = doll_reserve[pos] ;
        enemy = enemy_reserve;}

    for(int a=1 ; a<10 ; a++){ //按次数取平均值且求和 a=人形位置 b=计算次数
        if(doll[a].id == 0)continue;
        for (int b=0 ; b <= condition.frame ; b++ ) {
            damage[a][b] /= Fw ;

            if(b==0)damage_together[a][0] = damage[a][0];   //每个人形的伤害累加
            else damage_together[a][b] = damage_together[a][b-1] + damage[a][b];
            damage_together[0][b] += damage_together[a][b]; //全部人形的伤害累加
        }
    }

    draw();
    repaint();
}

double max(double a, double b) {
    if (a > b) return a;
    else return b;
}

double min(double a, double b) {
    if (a < b) return a;
    else return b;
}

void mysrand (int seed){
    rand_seed = seed;
}

double myrand (){
    do{
        rand_seed = (rand_seed * 16807L) % ((1 << 31) - 1);
    }while(rand_seed > 0);
    return -(rand_seed%10000);
}


