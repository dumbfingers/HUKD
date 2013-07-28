/*
 * DealRequest.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: allen
 */

#include "DealRequest.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

const QString appKey = "efb1a7b5e6b98d625211d31542656704";

DealRequest::DealRequest(QObject *parent) : QObject(parent)
{
	// TODO Auto-generated constructor stub

}

DealRequest::~DealRequest() {
	// TODO Auto-generated destructor stub
}

/*
 * TwitterRequest::requestTimeline(const QString &screenName)
 *
 * Makes a network call to retrieve the twitter feed for the specified screenname
 */
//! [0]
void DealRequest::requestDeal()
{
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);

    const QString queryUri = "http://api.hotukdeals.com/rest_api/v2/?key=" + appKey +"&output=json";
    QNetworkRequest request(queryUri);

    QNetworkReply* reply = networkAccessManager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(onDealReply()));
}

/*
 * TwitterRequest::onTimelineReply()
 *
 * Callback handler for QNetworkReply finished() signal
 */
//! [1]
void DealRequest::onDealReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer = reply->readAll();
                response = QString::fromUtf8(buffer);
                success = true;
            }
        } else {
            response =  tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Twitter request failed. Check internet connection");
    }

    emit complete(response, success);
}
