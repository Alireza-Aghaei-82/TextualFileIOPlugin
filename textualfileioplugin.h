#include <QQmlEngineExtensionPlugin>

class TextualFileIOPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)
};


//#include "TextualFileIO_MyModules_IO_TextualFileIOPlugin.moc"

void qml_register_types_MyModules_IO_TextualFileIO();

