#ifndef JOYSTICKMANAGER_HPP
#define JOYSTICKMANAGER_HPP

#include <QObject>
#include <QTimer>
#include <SDL.h>

class JoystickManager : public QObject
{
    Q_OBJECT
public:
    explicit JoystickManager(QObject *parent = nullptr);

signals:
    void JoystickConnect();
    void JoystickDisconnect();
    void ChangeAxis_0(int, int);
    void ChangeAxis_1(int, int);
    void ChangeAxis_2(int, int);
    void ChangeAxis_3(int, int);
    void ChangeAxis_4(int, int);
    void ChangeAxis_5(int, int);
    void ChangeAxis_6(int, int);
    void ChangeAxis_7(int, int);
    void ChangeAxis_8(int, int);
    void ChangeAxis_9(int, int);
    void ChangeButton_0(int, int);
    void ChangeButton_1(int, int);
    void ChangeButton_2(int, int);
    void ChangeButton_3(int, int);
    void ChangeButton_4(int, int);
    void ChangeButton_5(int, int);
    void ChangeButton_6(int, int);
    void ChangeButton_7(int, int);
    void ChangeButton_8(int, int);
    void ChangeButton_9(int, int);
    void ChangeButton_10(int, int);
    void ChangeButton_11(int, int);
    void ChangeButton_12(int, int);
    void ChangeButton_13(int, int);
    void ChangeButton_14(int, int);
    void ChangeButton_15(int, int);
    void ChangeButton_16(int, int);
    void ChangeButton_17(int, int);
    void ChangeButton_18(int, int);
    void ChangeButton_19(int, int);
    void ChangeHat_0(int, int);
    void ChangeHat_1(int, int);

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
    SDL_Joystick* joystik;
    void refreshAxisInfo(SDL_Joystick *joystik);
    void refreshButtonInfo(SDL_Joystick* joystik);
    void refreshHatInfo(SDL_Joystick *joystik);
    void initializeConnetions();
    void initializeTimer();
};

#endif // JOYSTICKMANAGER_HPP
