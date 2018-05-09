#include "sctcversionchecker.h"
#include "../clientversion.h"

#include <boost/foreach.hpp>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

#define paternVersion "sctc-([0-9]+\\.)?([0-9]+\\.)?([0-9]+)-"

SctcVersionChecker::SctcVersionChecker(QObject *parent) : QObject(parent)
{
    currentVersion = Version(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION);
}

SctcVersionChecker::~SctcVersionChecker()
{

}

bool SctcVersionChecker::newVersionAvailable()
{
    Version maxReleaseVersion = getMaxReleaseVersion();

    if(maxReleaseVersion > currentVersion)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QList<Version> SctcVersionChecker::getVersions()
{
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(SCTC_RELEASES)));
    QEventLoop event;
    connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QString html = response->readAll();

    QRegularExpression regEx(paternVersion);
    QRegularExpressionMatchIterator regExIt = regEx.globalMatch(html);

    QList<Version> versions;

    while (regExIt.hasNext()) {
        QRegularExpressionMatch match = regExIt.next();
        QString versionString = match.captured().mid(5, match.captured().length() - 6); // get version string in format XX.XX.XX
        Version version(versionString);
        if(!versions.contains(version))
        {
            versions.append(version);
        }
    }
    return versions;
}

Version SctcVersionChecker::getMaxReleaseVersion()
{
    QList<Version> versions = getVersions();
    Version maxVersion;

    if(!versions.isEmpty())
    {
        maxVersion = *std::max_element(versions.begin(), versions.end());
    }
    return maxVersion;
}
