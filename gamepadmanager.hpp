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
    void GamepadConnect();
    void GamepadDisconnect();
    void ChangeAxis_0(int);
    void ChangeAxis_1(int);
    void ChangeAxis_2(int);
    void ChangeAxis_3(int);
    void ChangeAxis_4(int);
    void ChangeAxis_5(int);
    void ChangeAxis_6(int);
    void ChangeAxis_7(int);
    void ChangeAxis_8(int);
    void ChangeAxis_9(int);
    void ChangeButton_0(int);
    void ChangeButton_1(int);
    void ChangeButton_2(int);
    void ChangeButton_3(int);
    void ChangeButton_4(int);
    void ChangeButton_5(int);
    void ChangeButton_6(int);
    void ChangeButton_7(int);
    void ChangeButton_8(int);
    void ChangeButton_9(int);
    void ChangeButton_10(int);
    void ChangeButton_11(int);
    void ChangeButton_12(int);
    void ChangeButton_13(int);
    void ChangeButton_14(int);
    void ChangeButton_15(int);
    void ChangeButton_16(int);
    void ChangeButton_17(int);
    void ChangeButton_18(int);
    void ChangeButton_19(int);
    void ChangeHat_0(int);
    void ChangeHat_1(int);

private:
    const static int AXISCOUNT = 10;
    const static int BUTTONSCOUNT = 20;
    const static int HATSCOUNT = 2;

    QTimer* m_timer;
    bool m_isGamepadConnect;
    int m_axis[AXISCOUNT];
    int m_buttons[BUTTONSCOUNT];
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
