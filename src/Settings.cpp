#include <QDir>
#include "Settings.h"
#include <QSettings>
#include <QDebug>

static GSettings *GetApplicationSettings()
{
  GSettings *settings;
  QDir home = QDir();
    //First check to see if the Library folder exists where the executable is (for USB sticks)
  if(!home.exists("Library/GoldenCheetah"))
    settings = new GSettings(GC_SETTINGS_CO, GC_SETTINGS_APP);
  else
    settings = new GSettings(home.absolutePath()+"/gc", QSettings::IniFormat);
  return settings;
}

QVariant
GSettings::value(const QObject *me, const QString key, const QVariant def) const
{

    // debug output ?
    //for (const QObject *p=me; p; p = p->parent()) {
    //if (p->property("instanceName").toString() != "")
    //qDebug()<<p->property("instanceName").toString();
    //}

        return QSettings::value(key, def);
}


// initialise with no cyclist
// as soon as a cyclist is opened it will be intialised via mainwindow
GSettings *appsettings = GetApplicationSettings();
