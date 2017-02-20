#ifndef VK_H
#define VK_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>

#define VK_VERSION      "5.62"

class Vk: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QUrl listening READ listening WRITE setListening)

    Q_PROPERTY(QString mail READ mail NOTIFY userDataChange)
    Q_PROPERTY(QString token READ token NOTIFY userDataChange)
    Q_PROPERTY(QString name READ name NOTIFY userDataChange)
    Q_PROPERTY(QString id READ id NOTIFY userDataChange)
    Q_PROPERTY(QString photo READ photo NOTIFY userDataChange)

    Q_PROPERTY(QStringList frendsPhoto READ frendsPhoto NOTIFY fendsDataChange)
    Q_PROPERTY(QStringList frendsId READ frendsId NOTIFY fendsDataChange)
    Q_PROPERTY(QStringList frendsName READ frendsName NOTIFY fendsDataChange)

public:
    explicit Vk(const QString &app);

public:
    QUrl url() const;
    QUrl listening() const;
    void setListening(const QUrl &listenUrl);

    QString mail() const;
    QString token() const;
    QString name() const;
    QString id() const;
    QString photo() const;

    QStringList frendsPhoto() const;
    QStringList frendsId() const;
    QStringList frendsName() const;

    Q_INVOKABLE void getFriends(const int count, const int start);
    Q_INVOKABLE void sendMessage(const QString &frendId, const QString &message);

private:    
    QUrl m_url;
    QUrl m_listenUrl;

    QString m_token;
    QString m_mail;
    QString m_name;
    QString m_id;
    QString m_photo;
    QStringList m_frendsName;
    QStringList m_frendsId;
    QStringList m_frendsPhoto;

private:
    void userData();
    void networkRequest(QUrl &url, QByteArray &reqdata);

signals:
    void userDataChange();
    void fendsDataChange();

private slots:
    void networkRequestResult(QNetworkReply *reply);
};

#endif // VK_H
