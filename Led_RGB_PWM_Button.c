#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define R 11
#define G 13
#define B 15
#define BT1 33
#define BT2 35
#define BT3 37


int lv, mau, mode=1, dl;
int mamau[10][3] ={
                    {100,   0,     0},
                    {0,     100,   0},
                    {0,     0,     100},
                    {50,    50,    10},
                    {30,    50,    80},
                    {70,    50,    100},
                    {40,    30,    50},
                    {0,     50,    100},
                    {30,    100,   40},
                    {100,   100,   100}
                                    };

void KTBT1()
{
    if(digitalRead(BT1)==0)
    {
        delay(20);
        if(digitalRead(BT1)==0)
        {
            while (digitalRead(BT1)==0)
            {
                if(mode==2) mode =1;
                else mode++;
                printf("mode: %d \n", mode);
                while (digitalRead(BT1)==0);
            }
        }
    }
}

void KTBT2()
{
    if(digitalRead(BT2)==0)
    {
        delay(20);
        if(digitalRead(BT2)==0)
        {
            while (digitalRead(BT2)==0)
            {
                if(lv>=10) lv=0;
                else lv++;
                printf("lv: %d \n", lv);
                while (digitalRead(BT2)==0);
            }
        }
    }
}

void KTBT3()
{
    if(digitalRead(BT3)==0)
    {
        delay(20);
        if(digitalRead(BT3)==0)
        {
            while (digitalRead(BT3)==0)
            {
                if(dl>=3000) dl=300;
                else dl=dl+300;
                printf("Toc do doi mau: %d \n", dl);
                while (digitalRead(BT3)==0);
            }
        }
    }
}

int main()
{
    wiringPiSetupPhys();
    softPwmCreate(R, 0,100);
    softPwmCreate(G, 0,100);
    softPwmCreate(B, 0,100);
    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
    pinMode(BT3, INPUT);

    wiringPiISR(BT1, INT_EDGE_FALLING, &KTBT1);
    wiringPiISR(BT2, INT_EDGE_FALLING, &KTBT2);
    wiringPiISR(BT3, INT_EDGE_FALLING, &KTBT3);

    while(1)
    {
        if(mode==1) //CHop Tat
        {
            softPwmWrite(R,0);
            softPwmWrite(G,0);
            softPwmWrite(B,0);
            delay(250);
            softPwmWrite(R,mamau[mau][0]);
            softPwmWrite(G,mamau[mau][1]);
            softPwmWrite(B,mamau[mau][2]);
            delay(250);
        }
        else if(mode==2) //doi mau
        {
            if (mau>=9) mau=0;
            else mau++;
               // printf("mau: %d \n", mau);
                softPwmWrite(R,(mamau[mau][0])*lv/10);
                softPwmWrite(G,(mamau[mau][1])*lv/10);
                softPwmWrite(B,(mamau[mau][2])*lv/10);
                delay(dl);
        }

    }
}