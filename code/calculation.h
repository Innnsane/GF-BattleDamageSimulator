#ifndef CALCULATION_H
#define CALCULATION_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QPaintEvent>
#include <QtGui>

#define FA 30

struct doll_info {
    int id;         //ID
    char name[20];	//名称
    int star;		//星级
    int type;		//枪种  1HG 2SMG 3RF 4AR 5MG 6SG
    int mod_sign;   //mod_sign 心智改造标志位
    double attack;      //attack 伤害
    double fire_rate;   //firing rate 射速
    double hit;         //hit 命中
    double dodge;       //dodge 闪避
    double skill1_before;      //技能1前置
    double skill1_last;        //技能1期间
    double skill1_cd;          //技能1冷却

    double bullet_number;	//bullet number 弹量         //部分人形可忽略
    double armor;	//护甲

    double critical_per;	//critical percent 暴击      //宏观调控
    double crit_damage_rate;//critical damage rate 爆伤
    double armor_piercing;	//armor piercing 穿甲
    double move;            //move 移动速度

    int    sign_z[25];         //各种标记 int
    double sign[10];        //各种标记 double
    short shield_quantity[30];//护盾量
    short shield_last[30];    //护盾持续时间
    int skill1_flag;        //技能1旗帜（前置、期间、冷却等） 初始置0
    int skill1_timing;      //技能1计时
    int recharge;           //recharge 射击间隔
    int fire_timing;		//firing timing 射击计时
    int fire_number;		//firing number 射击次数
    int bullet_counting;    //bullet counting 弹量计数
    double fixed_fire_rate; //fixed firing rate 固定射速
    double night_view_per;	//night view percent 夜视能力
    double max_field;       //最大立场
    double current_field;   //当前立场
    double injury_reduction;    //伤害减免
    double injury_advanced;     //伤害加减
    int fixed_injury;       //fixed injury 固定伤害
    int definitely_hit;     //definitely hit 必中  //0无效 1必中 2必不中
    int definitely_crit;	//definitely critical 必暴  //0无效 1必暴 2必不暴
    short influence[10] ;   //转换后影响格
    double attack_inf;      //伤害影响格
    double fire_rate_inf;   //射速影响格
    double hit_inf;         //命中影响格
    double dodge_inf;       //回避影响格
    double critical_per_inf;//暴击影响格
    double armor_inf;       //护甲影响格
    double cd_inf;          //冷却影响格
};

struct condition_info {
    int day_or_night;	//day 0 or night 1
    int frame;          //frame 计算时间(以30帧为准)
    int fairy_skill;    //妖精技能 0关闭 1开启
    double attack_buff;     //自定义buff 妖精光环也计算其中
    double fire_rate_buff;
    double hit_buff;
    double critical_per_buff;
    double crit_damage_rate_buff;
    double dodge_buff;
    double armor_buff;
};

struct enemy_info {
    double attack;      //attack 伤害
    double fire_rate;   //fire_rate 射速
    double hit;         //hit 命中
    double dodge;       //dodge 回避
    double armor;       //armor 护甲
    double critical_per;	//critical percent 暴击
    double crit_damage_rate;//critical damage rate 爆伤
    double armor_piercing;	//armor piercing 穿甲
    double move;            //move 移动速度
    double max_field;       //最大立场
    double current_field;   //当前立场
    double shield;      //shield 护盾
    int target_number;  //target_number范围伤害目标数量（包括编制）
    int elite_unit;     //Elite_Unit精英单位与否 true 2 false 0
    double deep_damage;	//伤害加减效果
    //效果 眩晕 引燃 麻痹 吸引 禁锢
    int Dizzy;
    int Ignite;
    int Paralysis;
    int Drawed;
    int Durance;
};

struct fairy_info {
    int id;         //游戏id
    char name[20];  //名称
    int type;       //类型 0战斗 1策略
    double crit_damage_rate;
    double attack;
    double hit;
    double dodge;
    double armor;

};

extern doll_info doll_origin[600];
extern doll_info doll[11];
extern doll_info doll_reserve[10];
extern doll_info doll_reserve_2[10];
extern enemy_info enemy;
extern enemy_info enemy_reserve;
extern condition_info condition;
extern fairy_info fairy_origin[60];
extern int fairy_id;
extern int fairy_gift_id;
extern double **damage;
extern double **damage_together;
extern double damage_all[10];
extern int rand_seed;
extern int Fw;
extern int of;
extern int out;

double max(double a, double b);
double min(double a, double b);
void mysrand (int seed);
double myrand ();
void prepare();
void likability();
void skill_select(int frame);
void influence_trans();
void influence_select();
void influence_calculate();
void buff_done();
void fairy_gift( int frame , int id );
void fairy_skill( int id );

namespace Ui {
class calculation;
}

class calculation : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculation(QWidget *parent = nullptr);
    ~calculation();

protected:
    void doll_select();
    void doll_present(int star , int id);
    void doll_info_show(int id);
    void clear_all();
    void equipment_select(int id);
    void equip_special(int id , int order);
    void special_select(int id);
    void condition_enemy_set();
    void buff_set();
    void fairy_select();
    void calculate();
    void draw();
    QColor color_select(int pos);
    void paintEvent(QPaintEvent *e);

private:
    Ui::calculation *ui;
    bool eventFilter(QObject *obj, QEvent *ev);
    QImage image;

private slots:
    void on_name_listWidget_itemClicked(QListWidgetItem *item);

};

#endif // CALCULATION_H

