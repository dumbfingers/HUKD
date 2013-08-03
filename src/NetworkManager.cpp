/*
 * NetworkManager.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Yaxi Ye
 */

#include "NetworkManager.hpp"
#include <QMutex>

NetworkManager *NetworkManager::getInstance() {
	static NetworkManager *singleton = NULL;
    static QMutex mutex;
	if(singleton == NULL) {
		mutex.lock();
		if(!singleton) singleton = new NetworkManager();
		mutex.unlock();
	}
   	return singleton;
}

NetworkManager::NetworkManager() {
	_networkConfigManager = new QNetworkConfigurationManager(this);
	_networkSession = new QNetworkSession(_networkConfigManager->configurationFromIdentifier("bps:ti0"), this);
	_networkAccessManager = new QNetworkAccessManager(this);

	connect(_networkSession, SIGNAL(stateChanged(QNetworkSession::State)), this, SLOT(onNetworkStateChanged(QNetworkSession::State)));
	connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkRequestFinished(QNetworkReply*)));

}

NetworkManager::~NetworkManager() {}

void NetworkManager::get(QString urlString, QVariantMap urlParams) {
	QUrl url(urlString);
	QVariantMap::iterator i;
	for(i = urlParams.begin(); i != urlParams.end(); ++i) {
		url.addQueryItem(i.key(), i.value().toString());
	}
	_networkAccessManager->get(QNetworkRequest(url));
}

void NetworkManager::onNetworkStateChanged(QNetworkSession::State state) {
	qDebug() << "STATE CHANGED: " << state;
	bool connected = false;
	if(state == QNetworkSession::Connected) connected = true;
	emit networkStatusChanged(connected);
}
void NetworkManager::onNetworkRequestFinished(QNetworkReply* reply) {
	QUrl url = reply->url();
	QNetworkReply::NetworkError error = reply->error();
	if(error != QNetworkReply::NoError) {
		qDebug() << "Networking Request Error ( " << url << ") due to " << error;
		emit networkResponseFailed(url, error);
	} else {
		QString response = QString(reply->readAll());
		emit networkResponse(url, response);
	}
	reply->deleteLater();
}


