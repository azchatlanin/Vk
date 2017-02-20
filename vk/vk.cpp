#include "vk.h"

Vk::Vk(const QString &app)
{
    QString strUrl = QString("https://oauth.vk.com/authorize"
                   "?client_id=%1"
                   "&scope=offline,email,friends,messages"
                   "&display=wap"
                   "&redirect_uri=https://oauth.vk.com/blank.html"
                   "&response_type=token").arg(app);
    m_url = QUrl::fromUserInput(strUrl);
}

QString Vk::mail() const
{
    return m_mail;
}

QString Vk::token() const
{
    return m_token;
}

QString Vk::name() const
{
    return m_name;
}

QString Vk::id() const
{
    return m_id;
}

QString Vk::photo() const
{
    return m_photo;
}

QStringList Vk::frendsPhoto() const
{
    return m_frendsPhoto;
}

QStringList Vk::frendsId() const
{
    return m_frendsId;
}

QStringList Vk::frendsName() const
{
    return m_frendsName;
}

QUrl Vk::url() const
{
    return m_url;
}

QUrl Vk::listening() const
{
    return m_listenUrl;
}

void Vk::setListening(const QUrl &listenUrl)
{
    QUrl url(listenUrl);
    url = url.toString().replace("#", "?");
    QUrlQuery query(url);
    m_token = query.queryItemValue("access_token");
    m_mail =  query.queryItemValue("email");

    userData();
}

void Vk::userData()
{
    QUrl url = QUrl::fromUserInput("https://api.vk.com/method/users.get");
    QByteArray reqdata;
    reqdata.append(QString("v=%1").arg(VK_VERSION));
    reqdata.append("&fields=photo_100");
    reqdata.append("&order=count");
    reqdata.append(QString("&access_token=%1").arg(m_token));

    networkRequest(url, reqdata);
}

void Vk::getFriends(const int count, const int start)
{
    QUrl url("https://api.vk.com/method/friends.get?v=5.60");
    QByteArray reqdata;
    reqdata.append(QString("v=%1").arg(VK_VERSION));
    reqdata.append("&fields=first_name,last_name,photo_100");
    reqdata.append("&order=count");
    reqdata.append(QString("&count=%1").arg(count));
    reqdata.append(QString("&offset=%1").arg(start));
    reqdata.append(QString("&access_token=%1").arg(m_token));

    networkRequest(url, reqdata);
}

void Vk::sendMessage(const QString &frendId, const QString &message)
{
    QUrl url = QUrl::fromUserInput("https://api.vk.com/method/messages.send");
    QByteArray reqdata;
    reqdata.append(QString("v=%1").arg(VK_VERSION));
    reqdata.append(QString("&user_id=%1").arg(frendId));
    reqdata.append(QString("&message=%1").arg(message));
    reqdata.append(QString("&access_token=%1").arg(m_token));

    networkRequest(url, reqdata);
}

void Vk::networkRequest(QUrl &url, QByteArray &reqdata)
{
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Accept-Encoding","identity");
    request.setUrl(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, reqdata);

    connect(manager, &QNetworkAccessManager::finished,
            this, &Vk::networkRequestResult);
    connect(manager, &QNetworkAccessManager::finished,
            manager, &QNetworkAccessManager::deleteLater);
}

void Vk::networkRequestResult(QNetworkReply *reply)
{
    QString result = (QString)reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(result.toUtf8());
    QJsonObject root = document.object();

    if(result.contains("count")) {
        QJsonValue items = root.value("response").toObject().value("items");
        if(items.isArray()){
            QJsonArray ja = items.toArray();
            for(int i = 0; i < ja.count(); i++){
                QJsonObject subtree = ja.at(i).toObject();
                m_frendsName.append(subtree.value("first_name").toString() + " "
                                    + subtree.value("last_name").toString());
                m_frendsId.append(QString::number(subtree.value("id").toInt()));
                m_frendsPhoto.append(subtree.value("photo_100").toString());
            }
        }
        emit fendsDataChange();
    } else {
        QJsonValue items = root.value("response");
        QJsonArray ja = items.toArray();
        for(int i = 0; i < ja.count(); i++){
            QJsonObject subtree = ja.at(i).toObject();
            m_name = subtree.value("first_name").toString() + " "
                     + subtree.value("last_name").toString();
            m_id = QString::number(subtree.value("id").toInt());
            m_photo =  subtree.value("photo_100").toString();
        }
        emit userDataChange();
    }
    reply->deleteLater();
}
