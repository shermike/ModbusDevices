#include "DeviceWidget.h"
#include "ModbusDevices.h"
#include "Settings.hpp"

QSettings *Settings::m_Settings = NULL;

ModbusDevices::ModbusDevices(QWidget *parent)
: QMainWindow(parent)
{
  ui.setupUi(this);
  LOG_INFO("START");

  ui.tabWidget->clear();

  addDevice("Example.ui");
  
  SETTINGS->beginGroup("MainWindow");
  restoreGeometry(SETTINGS->value("geometry").toByteArray());
  restoreState(SETTINGS->value("state").toByteArray());
  ui.splitter->restoreState(SETTINGS->value("splitter").toByteArray());
  SETTINGS->endGroup();
}

ModbusDevices::~ModbusDevices()
{
  SETTINGS->beginGroup("MainWindow");
  SETTINGS->setValue("geometry", saveGeometry());
  SETTINGS->setValue("state", saveState());
  SETTINGS->setValue("splitter", ui.splitter->saveState());
  SETTINGS->sync();
  SETTINGS->endGroup();
}

void ModbusDevices::addDevice(const QString& ui_file)
{
  LOG_INFO("Add widget from file: %s", ui_file.toUtf8().constData());
  DeviceWidget* widget(new DeviceWidget(this));
  try
  {
    widget->load(ui_file);
    ui.tabWidget->addTab(widget, widget->windowTitle());
  }
  catch (std::runtime_error& ex)
  {
    delete widget;
    LOG_ERROR("EXCEPTION: %s", ex.what());
  }
  
}
