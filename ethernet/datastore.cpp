#include "datastore.hpp"
#include <QShortcut>
#include <QSound>

DataStore::DataStore(Settings* settings, QWidget *parent) :
    QObject(parent),
    _connector(new TcpConnector(settings, this)),
    _serverIpDialog(new ServerIpDialog(settings, parent)),
    _debugDialog(new DataDebugDialog(&_telimetry, &_control, parent)),
    _fileDialog(new QFileDialog(parent)),
    _packageDebugDialog(new PackageDebugDialog(&_debug, parent)),
    _pdDialog(new PdDialog(parent))
{
    _initTimer();
    _initConnections();
    _createShortcuts();
}

void DataStore::SetAxisX(int axis)
{
    axis = abs(axis) < AXISTOLERANCE ? 0 : axis;
    _control.axis_x = static_cast<std::int8_t>(axis - axis * 2 * _mainCameraIndex);
}

void DataStore::SetAxisY(int axis)
{
    axis = abs(axis) < AXISTOLERANCE ? 0 : axis;
    _control.axis_y = static_cast<std::int8_t>(axis - axis * 2 * _mainCameraIndex );
}

void DataStore::SetAxisZ(int axis)
{
    if (_enable_pd.depth_pd == 1) axis = abs(axis) < AXISTOLERANCE ? 0 : axis;
    if (_control.axis_z && !axis)
        QSound::play("sound.wav");
    _control.axis_z = static_cast<std::int8_t>(axis);
}

void DataStore::SetAxisW(int axis)
{
    axis = abs(axis) < AXISTOLERANCE ? 0 : axis;
    _control.axis_w = static_cast<std::int8_t>(axis);
}

void DataStore::SetManRotateRigth(int val)
{
    _control.manipulator_rotate = static_cast<char>(val);
}

void DataStore::SetManRotateLLeft(int val)
{
    _control.manipulator_rotate = static_cast<char>(-val);
}

void DataStore::SetManOpen(int val)
{
    _control.manipulator_open_close = static_cast<char>(val);
}

void DataStore::SetManClose(int val)
{
    _control.manipulator_open_close = static_cast<char>(-val);
}

void DataStore::SetMainCameraRotateRight(int val)
{
    _control.camera_rotate[_mainCameraIndex] = static_cast<char>(val);
}

void DataStore::SetMainCameraRotateLeft(int val)
{
    _control.camera_rotate[_mainCameraIndex] = static_cast<char>(-val);
}

void DataStore::SetSubCameraRotateRight(int val)
{
    _control.camera_rotate[(_mainCameraIndex + 1) % 2] = static_cast<char>(val);
}

void DataStore::SetSubCameraRotateLeft(int val)
{
    _control.camera_rotate[(_mainCameraIndex + 1) % 2] = static_cast<char>(-val);
}

void DataStore::SetMagnetOn(int val)
{
    _control.magnet = static_cast<char>(1);
}

void DataStore::SetMagnetOff(int val)
{
    _control.magnet = static_cast<char>(0);
}

void DataStore::SetAcousticOn(int val)
{
    _control.realese = static_cast<char>(val);
}

void DataStore::SetAcousticOff(int val)
{
    _control.realese = static_cast<char>(-val);
}

void DataStore::SetPower(int val)
{
    _power = val;
}

void DataStore::SetSalto(int val)
{
    val = abs(val) < AXISTOLERANCE ? 0 : val;
    _debug.thruster_power[4] = static_cast<int8_t>(val);
    _debug.thruster_power[5] = static_cast<int8_t>(val);
    _debug.thruster_power[6] = static_cast<int8_t>(-val);
    _debug.thruster_power[7] = static_cast<int8_t>(-val);
    _packageDebugDialog->Update();
}

void DataStore::SetBochka(int val)
{
    val = abs(val) < AXISTOLERANCE ? 0 : val;
    _debug.thruster_power[4] = static_cast<int8_t>(val);
    _debug.thruster_power[6] = static_cast<int8_t>(val);
    _debug.thruster_power[5] = static_cast<int8_t>(-val);
    _debug.thruster_power[7] = static_cast<int8_t>(-val);
    _packageDebugDialog->Update();
}

void DataStore::SetTwisting_motors(int index, int val)
{
    _control.twisting_motors[index] = static_cast<char>(val);
}

void DataStore::SetMainCameraIndex(int index)
{
    _mainCameraIndex = index;
}

void DataStore::SetEnablePd(int index)
{
    rov_types::rov_enable_pd pkg(_enable_pd);
    switch (index) {
        case 0:
            pkg.yaw_pd = _enable_pd.yaw_pd == 1 ? 0 : 1;
            break;
        case 1:
            pkg.depth_pd = _enable_pd.depth_pd == 1 ? 0 : 1;
            break;
        case 2:
            pkg.roll_pd = _enable_pd.roll_pd == 1 ? 0 : 1;
            break;
        case 3:
            pkg.pitch_pd = _enable_pd.pitch_pd == 1 ? 0 : 1;
            break;
    }
    qDebug() << index;
    _connector->Send(pkg.serialize());
}

void DataStore::SetSecondManOpen(int val)
{
    _control.secondary_manipulator = static_cast<char>(val);
}

void DataStore::SetSecondManClose(int val)
{
    _control.secondary_manipulator = static_cast<char>(-val);
}

void DataStore::SetFlashLightPowerUp()
{
    _control.flashlight = 1;
}

void DataStore::SetFlashLightPowerDown()
{
    _control.flashlight = -1;
}

void DataStore::SetFlashLightPowerSave()
{
    _control.flashlight = 0;
}

void DataStore::DisablePID()
{
    rov_types::rov_enable_pd pkg;
    pkg.depth_pd = 0;
    pkg.pitch_pd = 0;
    pkg.roll_pd = 0;
    pkg.yaw_pd = 0;
    _connector->Send(pkg.serialize());
}

void DataStore::ChangeEnable()
{
    if (!_timer->isActive())
        _timer->start(50);
    else
        _timer->stop();
}

void DataStore::_initTimer()
{
    _timer = new QTimer(this);
    ChangeEnable();
}

void DataStore::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &DataStore::_onTick);
    connect(_connector, &TcpConnector::dataUpdate, this, &DataStore::_parsePackage);
    connect(_connector, &TcpConnector::Connect, [this](){
        _updatePd();
        emit tcpConnect();
    });
    connect(_connector, &TcpConnector::Disconnect, [this](){emit tcpDisconnect();});
    connect(_fileDialog, &QFileDialog::fileSelected, this, &DataStore::_sendHardwareFirmware);
    connect(_packageDebugDialog, &PackageDebugDialog::visibleChange, [this](bool f){ _debugMode = f; });
    connect(this, &DataStore::pdUpdate, _pdDialog, &PdDialog::UpdatePd);
    connect(this, &DataStore::enablePdUpdate, _pdDialog, &PdDialog::UpdateEnablePd);
    connect(_pdDialog, &PdDialog::PdChange, this, &DataStore::_sendPd);
    connect(_pdDialog, &PdDialog::NeedUpdate, this, &DataStore::_updatePd);
}

void DataStore::_onTick()
{
    _debugDialog->Update();
    if (_debugMode){
        _connector->Send(_debug.serialize());
        return;
    }

    rov_types::rov_control pkg(_control);
//    pkg.axis_x *= (_power / 100.0);
//    pkg.axis_y *= (_power / 100.0);
    pkg.axis_z *= (_power / 100.0);
//    pkg.axis_w *= (_power / 100.0);
    _connector->Send(pkg.serialize());
}

void DataStore::_createShortcuts()
{
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), static_cast<QWidget*>(parent())), &QShortcut::activated, [this](){_debugDialog->show();});
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_2), static_cast<QWidget*>(parent())), &QShortcut::activated, [this](){_packageDebugDialog->show();});
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_9), static_cast<QWidget*>(parent())), &QShortcut::activated, [this](){_fileDialog->show();});
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_6), static_cast<QWidget*>(parent())), &QShortcut::activated, [this](){_pdDialog->show();});
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_5), static_cast<QWidget*>(parent())), &QShortcut::activated, [this](){_serverIpDialog->show();});
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), static_cast<QWidget*>(parent())), &QShortcut::activated, this, &DataStore::ChangeEnable);
}

void DataStore::_parsePackage(const std::vector<uint8_t> &package)
{
    for (size_t i = 0; i < package.size();)
        switch (package[i]) {
            case rov_types::rov_telimetry::meta().packet_id:
                _telimetry.deserialize(std::vector<uint8_t>(package.begin() + static_cast<int>(i),
                                                            package.begin() + static_cast<int>(i) + rov_types::rov_telimetry::meta().packet_size));
                i += rov_types::rov_telimetry::meta().packet_size;
                emit telimetryUpdate(_telimetry.yaw, _telimetry.pitch, _telimetry.roll, _telimetry.depth);
                break;
            case rov_types::rov_pd::meta().packet_id:
                _pd.deserialize(std::vector<uint8_t>(package.begin() + static_cast<int>(i),
                                                            package.begin() + static_cast<int>(i) + rov_types::rov_pd::meta().packet_size));
                i += rov_types::rov_pd::meta().packet_size;
//                qDebug() << "pf update";
                emit pdUpdate(_pd);
                break;
            case rov_types::rov_enable_pd::meta().packet_id:
                _enable_pd.deserialize(std::vector<uint8_t>(package.begin() + static_cast<int>(i),
                                                            package.begin() + static_cast<int>(i) + rov_types::rov_enable_pd::meta().packet_size));
                i += rov_types::rov_enable_pd::meta().packet_size;
//                qDebug() << "enable update" <;
                emit enablePdUpdate(_enable_pd);
                break;
            default:
                qDebug() << "Bad pkg";
                i = package.size();
        }
}

void DataStore::_sendHardwareFirmware(QString fileName)
{
    std::cout << fileName.toStdString() << std::endl;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "Bad File" << std::endl;
        return;
    }
    QTextStream in(&file);
    _hardware_firmware.firmware = in.readAll().toStdString();
    _hardware_firmware.size = _hardware_firmware.firmware.size();
    _connector->Send(_hardware_firmware.serialize());
    std::cout << "Poslan!" << std::endl;
}

void DataStore::_sendPd(rov_types::rov_pd pd)
{
    _connector->Send(pd.serialize());
}

void DataStore::_updatePd()
{
    qDebug() << "update";
    rov_types::rov_pd pkg;
    _connector->Send(pkg.serialize());

    rov_types::rov_enable_pd pkge;
    _connector->Send(pkge.serialize());
}
