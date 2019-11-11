#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>

#include <libdtk-2.0.16/DWidget/DApplication>

DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.loadTranslator();

    MainWindow m;
    QString config = "config.json";

    // 通过 CMake 构建时自动处理配置文件
    QString config_path = QCoreApplication::applicationDirPath() + "/" +config;
    QFile file(config_path);
    QFileInfo fileInfo(file);

    if(fileInfo.exists() && !file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
    } else {
        qDebug() << "File open!";
    }

    qDebug() << "当前的操作系统类型为：" << QSysInfo::productType();

    // 从文件构建Json对象
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    if(!jsonDocument.isNull() && jsonParseError.error == QJsonParseError::NoError){
        qDebug() << "文件解析成功！";
        if(jsonDocument.isObject()){
            QJsonObject jsonObject = jsonDocument.object();

            // 窗口标题名称
            if(jsonObject.contains("ApplicationName")){
                a.setApplicationName(jsonObject.value("ApplicationName").toString());
            }
            // 机构名称
            if(jsonObject.contains("OrganizationName")){
//                a.setOrganizationName(jsonObject.value("OrganizationName").toString());
            }
            // 软件版本
            if(jsonObject.contains("ApplicationVersion")){
                a.setApplicationVersion(DApplication::buildVersion(jsonObject.value("ApplicationVersion").toString()));
            }
            // 作者主页
            if(jsonObject.contains("ApplicationAcknowledgementPage")){
                a.setApplicationAcknowledgementPage(jsonObject.value("ApplicationAcknowledgementPage").toString());
            }
            // 软件图标
            if(jsonObject.contains("ProductIcon")){
//                a.setProductIcon(QIcon(jsonObject.value("ProductIcon").toString()));
            }
            // 产品名称
            if(jsonObject.contains("ProductName")){
//                a.setProductName(jsonObject.value("ProductName").toString());
            }
            // 软件简介
            if(jsonObject.contains("AppliationDescription")){
                a.setApplicationDescription(jsonObject.value("AppliationDescription").toString());
            }

            // 主窗口属性
            if(jsonObject.contains("MainWindowProperties")){
                qDebug() << "MainWindowProperties解析成功！";
                QJsonObject properties = jsonObject.value("MainWindowProperties").toObject();
                if(properties.contains("defaultWidth")){
                    qDebug() << properties.value("defaultWidth").toInt();
                    m.setFixedWidth(properties.value("defaultWidth").toInt());
                }
                if(properties.contains("defaultHeight")){
                    qDebug() << properties.value("defaultHeight").toInt();
                    m.setFixedHeight(properties.value("defaultHeight").toInt());
                }
            } else {
                qDebug() << "MainWindowProperties解析失败！";
            }
        }
    } else {
        qDebug() << "文件解析失败！";
    }

    file.close();

    m.show();

    return a.exec();
}
