#ifndef DATASTORE_HPP
#define DATASTORE_HPP

#include <QObject>
#include <QTimer>
#include <QFileDialog>

#include "rov_data_types/rov_data_types.hpp"
#include "tcpconnetor.hpp"
#include "datadebugdialog.hpp"
#include "packagedebugdialog.hpp"
#include "pddialog.hpp"
#include "serveripdialog.hpp"
#include "settings.hpp"

class DataStore : public QObject
{
    Q_OBJECT
public:
    explicit DataStore(Settings *settings, QWidget *parent = nullptr);
    void SetAxisX(int axis);
    void SetAxisY(int axis);
    void SetAxisZ(int axis);
    void SetAxisW(int axis);
    void SetManRotateRigth(int val);
    void SetManRotateLLeft(int val);
    void SetManOpen(int val);
    void SetManClose(int val);
    void SetMainCameraRotateRight(int val);
    void SetMainCameraRotateLeft(int val);
    void SetSubCameraRotateRight(int val);
    void SetSubCameraRotateLeft(int val);
    void SetMagnetOn(int val);
    void SetMagnetOff(int val);
    void SetAcousticOn(int val);
    void SetAcousticOff(int val);
    void SetPower(int val);
    void SetSalto(int val);
    void SetBochka(int val);
    void SetTwisting_motors(int index, int val);
    void SetMainCameraIndex(int index);
    void SetEnablePd(int index);
    void SetSecondManOpen(int val);
    void SetSecondManClose(int val);
    void DisablePID();
    void ChangeEnable();

signals:
    void telimetryUpdate(float yaw, float pitch, float roll, float depth);
    void pdUpdate(rov_types::rov_pd);
    void enablePdUpdate(rov_types::rov_enable_pd);
    void tcpConnect();
    void tcpDisconnect();

private:
    void _initTimer();
    void _initConnections();
    void _onTick();
    void _createShortcuts();
    void _parsePackage(const std::vector<std::uint8_t> &package);
    void _sendHardwareFirmware(QString fileName);
    void _sendPd(rov_types::rov_pd pd);
    void _updatePd();

    int AXISTOLERANCE = 10;
    TcpConnector* _connector;
    QTimer* _timer;
    ServerIpDialog* _serverIpDialog;
    DataDebugDialog* _debugDialog;
    QFileDialog* _fileDialog;
    PackageDebugDialog* _packageDebugDialog;
    PdDialog* _pdDialog;
    rov_types::rov_telimetry _telimetry;
    rov_types::rov_control _control;
    rov_types::rov_hardware_firmware _hardware_firmware;
    rov_types::rov_debug _debug;
    rov_types::rov_enable_pd _enable_pd;
    rov_types::rov_pd _pd;
    bool _debugMode = false;
    int _mainCameraIndex = 0;
    int _power = 100;
};

#endif // DATASTORE_HPP
