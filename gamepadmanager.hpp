#ifndef MYGAMEPADMANAGER_HPP
#define MYGAMEPADMANAGER_HPP

#include <QObject>
#include <QTimer>
#include <SDL.h>

class MyGamepadManager : public QObject
{
    Q_OBJECT
public:
    explicit MyGamepadManager(QObject *parent = nullptr);

signals:
    GamepadConnect();
    GamepadDisconnect();
    ChangeAxis_0(double);
    ChangeAxis_1(double);
    ChangeAxis_2(double);
    ChangeAxis_3(double);
    ChangeAxis_4(double);
    ChangeAxis_5(double);
    ChangeAxis_6(double);
    ChangeAxis_7(double);
    ChangeAxis_8(double);
    ChangeAxis_9(double);
    ChangeButton_0(double);
    ChangeButton_1(double);
    ChangeButton_2(double);
    ChangeButton_3(double);
    ChangeButton_4(double);
    ChangeButton_5(double);
    ChangeButton_6(double);
    ChangeButton_7(double);
    ChangeButton_8(double);
    ChangeButton_9(double);
    ChangeButton_10(double);
    ChangeButton_11(double);
    ChangeButton_12(double);
    ChangeButton_13(double);
    ChangeButton_14(double);
    ChangeButton_15(double);
    ChangeButton_16(double);
    ChangeButton_17(double);
    ChangeButton_18(double);
    ChangeButton_19(double);
    ChangeHat_0(int);
    ChangeHat_1(int);

private:
    const static int AXISCOUNT = 10;
    const static int BUTTONSCOUNT = 20;
    const static int HATSCOUNT = 2;

    QTimer* m_timer;
    bool m_isGamepadConnect;
    double m_axis[AXISCOUNT];
    double m_buttons[BUTTONSCOUNT];
    int m_hats[HATSCOUNT];
    void setConnectionStatus(bool isConnect);
    void refreshGamepadInfo();
    void refreshAxisInfo(SDL_Joystick *joystik);
    void refreshButtonInfo(SDL_Joystick* joystik);
    void refreshHatInfo(SDL_Joystick *joystik);
    void initializeConnetions();
    void initializeTimer();
};

#endif // MYGAMEPADMANAGER_HPP
