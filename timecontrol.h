#ifndef TIMECONTROL_H
#define TIMECONTROL_H


class TimeControl
{
public:
    TimeControl();

    startTimer();// (开始计时)
    pauseTimer();// (暂停计时)
    resetTimer();// (重置计时)
    checkTimeLeft();// (检查剩余时间)

    int totalTime;//(总时间限制，单位为秒)
    int byoYomiTime;// (读秒时间，单位为秒)
    int byoYomiFrequency;// (读秒次数，单位为秒)

    int blackTimeLeft;// (黑方剩余时间)
    int whiteTimeLeft;// (白方剩余时间)

    int blackbyoYomiTime;// (黑读秒时间，单位为秒)
    int blackbyoYomiFrequency;// (读秒次数，单位为秒)
    int whitebyoYomiTime;// (白读秒时间，单位为秒)
    int whitebyoYomiFrequency;// (读秒次数，单位为秒)

    int sumTime; //总用时
    int chaoshi;//-1未超时 0黑超时 1白超时

};

#endif // TIMECONTROL_H
